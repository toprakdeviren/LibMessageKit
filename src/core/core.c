#include "libmessagekit/core.h"
#include "libmessagekit/common.h"
#include "database.h"

static CoreConfig global_config;
static bool is_initialized = false;

ErrorCode init(const CoreConfig* config) {
    if (is_initialized) {
        return ERROR_ALREADY_INITIALIZED;
    }

    if (config == NULL)
    {
        return ERROR_INVALID_PARAMETERS;
    }

    if (config->storage_path == NULL)
    {
        return ERROR_INVALID_STORAGE_PATH;
    }

    if (config->database_filename == NULL)
    {
        return ERROR_INVALID_DATABASE_FILENAME;
    }

    memcpy(&global_config, config, sizeof(CoreConfig));

    int db_result = db_open(config->storage_path, config->database_filename);
    if (db_result != SQLITE_OK) {
        return ERROR_DATABASE_INITIALIZATION;
    }

    char* schema_path = malloc(strlen(config->storage_path) + strlen("/schema.sql") + 1);
    if (schema_path == NULL) {
        db_close();
        return ERROR_MEMORY_ALLOCATION;
    }
    sprintf(schema_path, "%s/schema.sql", config->storage_path);

    db_result = db_init_schema(schema_path);
    free(schema_path);

    if (db_result != SQLITE_OK) {
        db_close();
        return ERROR_SCHEMA_INITIALIZATION;
    }

    is_initialized = true;
    return ERROR_NONE;
}

ErrorCode set_notification_token(const char* token)
{
    if (token == NULL || strlen(token) == 0)
    {
        return ERROR_INVALID_PARAMS;
    }

    const char* sql = "UPDATE app_settings SET notification_token = ? WHERE id = 1;";

    if (execute_query(sql) != 0)
    {
        return ERROR_DATABASE;
    }

    return ERROR_NONE;
}