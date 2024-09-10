#include "libmessagekit/common.h"

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

void print_error_and_free(const char* message, char* to_free)
{
    fprintf(stderr, "%s\n", message);
    if (to_free != NULL)
    {
        free(to_free);
    }
}

char* combine_path_and_filename(const char* directory, const char* filename, int* error_code)
{
    if (directory == NULL || filename == NULL || error_code == NULL) {
        if (error_code != NULL) {
            *error_code = ERROR_INVALID_PARAMS;
        }
        return NULL;
    }

    size_t path_length = strlen(directory) + strlen(filename) + 2;
    char* full_path = malloc(path_length);

    if (full_path != NULL)
    {
        snprintf(full_path, path_length, "%s%c%s", directory, PATH_SEPARATOR, filename);
        *error_code = ERROR_NONE;
    }
    else
    {
        *error_code = ERROR_MEMORY_ALLOCATION;
    }

    return full_path;
}

int load_from_file(const char* path, char** content)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        fprintf(stderr, "Cannot open file: %s\n", path);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *content = malloc(size + 1);
    if (*content == NULL)
    {
        fclose(file);
        fprintf(stderr, "%d\n", ERROR_MEMORY_ALLOCATION);
        return -1;
    }

    const size_t read_size = fread(*content, 1, size, file);
    fclose(file);

    if (read_size != size)
    {
        print_error_and_free("Error reading file", *content);
        return -1;
    }

    (*content)[size] = '\0';
    return 0;
}