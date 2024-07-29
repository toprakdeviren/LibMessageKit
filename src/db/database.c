#include "database.h"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

#define MEMORY_ALLOCATION_ERROR "Memory allocation failed"

typedef struct
{
    sqlite3* handle;
} Database;

static Database* db = NULL;

void print_error_and_free(const char* message, char* to_free)
{
    fprintf(stderr, "%s\n", message);
    if (to_free != NULL)
    {
        free(to_free);
    }
}

char* construct_full_path(const char* directory, const char* file)
{
    size_t path_length = strlen(directory) + strlen(file) + 2;
    char* full_path = malloc(path_length);

    if (full_path != NULL)
    {
        snprintf(full_path, path_length, "%s%c%s", directory, PATH_SEPARATOR, file);
    }
    else
    {
        fprintf(stderr, "%s\n", MEMORY_ALLOCATION_ERROR);
    }

    return full_path;
}

int db_open(const char* directory, const char* file_name)
{
    if (directory == NULL || file_name == NULL)
    {
        fprintf(stderr, "Invalid directory or file name\n");
        return SQLITE_ERROR;
    }

    char* full_path = construct_full_path(directory, file_name);
    if (full_path == NULL)
    {
        return SQLITE_NOMEM;
    }

    db = malloc(sizeof(Database));
    if (db == NULL)
    {
        free(full_path);
        fprintf(stderr, "%s\n", MEMORY_ALLOCATION_ERROR);
        return SQLITE_NOMEM;
    }

    const int result_code = sqlite3_open(full_path, &db->handle);
    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db->handle));
        sqlite3_close(db->handle);
        free(db);
        db = NULL;
    }
    else
    {
        fprintf(stderr, "Database opened successfully: %s\n", full_path);
    }

    free(full_path);
    return result_code;
}

void db_close()
{
    if (db)
    {
        sqlite3_close(db->handle);
        free(db);
        db = NULL;
        fprintf(stderr, "Database closed\n");
    }
}

int load_schema_from_file(const char* path, char** schema_sql)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        fprintf(stderr, "Cannot open schema file: %s\n", path);
        return SQLITE_ERROR;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *schema_sql = malloc(size + 1);
    if (*schema_sql == NULL)
    {
        fclose(file);
        fprintf(stderr, MEMORY_ALLOCATION_ERROR);
        return SQLITE_NOMEM;
    }

    const size_t read_size = fread(*schema_sql, 1, size, file);
    fclose(file);

    if (read_size != size)
    {
        print_error_and_free("Error reading schema file", *schema_sql);
        return SQLITE_ERROR;
    }

    (*schema_sql)[size] = '\0';
    return SQLITE_OK;
}

int db_init_schema(const char* schema_path)
{
    if (schema_path == NULL || db == NULL)
    {
        fprintf(stderr, "Invalid schema file path or database not opened\n");
        return SQLITE_ERROR;
    }

    char* schema_sql = NULL;
    int result_code = load_schema_from_file(schema_path, &schema_sql);
    if (result_code != SQLITE_OK)
    {
        return result_code;
    }

    char* err_msg = NULL;
    result_code = sqlite3_exec(db->handle, schema_sql, 0, 0, &err_msg);

    if (result_code != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stderr, "Schema initialized successfully\n");
    }

    free(schema_sql);
    return result_code;
}
