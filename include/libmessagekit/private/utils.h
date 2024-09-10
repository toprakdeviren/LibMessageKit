#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Combines a directory and a filename into a full path.
 *
 * This function takes two strings, a directory and a filename, and combines them into a full path.
 * The resulting path is returned as a dynamically allocated string. The caller is responsible for freeing the memory.
 * If any of the input parameters are NULL or if memory allocation fails, an error code is returned.
 *
 * @param directory The directory part of the path.
 * @param filename  The filename part of the path.
 * @param error_code A pointer to an integer where the error code will be stored.
 *
 * @return The full path as a dynamically allocated string, or NULL if an error occurred.
 *
 * @see utils.h
 * @see error_codes.h
 * @see combine_path_and_filename
 */
char* combine_path_and_filename(const char* directory, const char* filename, int* error_code);

/**
 * @brief Print an error message and free a pointer.
 *
 * This function prints the given error message and frees the memory pointed to by the
 * provided pointer. It is used to handle error conditions where a memory allocation
 * or other resource acquisition has failed.
 *
 * @param error_message The error message to be printed.
 * @param ptr_to_free   A pointer to the memory to be freed.
 *
 * @see utils.h
 */
void print_error_and_free(const char* error_message, void* ptr_to_free);

/**
 * @brief Loads the contents of a file into a dynamically allocated char buffer.
 *
 * This function opens a file specified by the path parameter and reads its contents into a dynamically allocated memory buffer.
 *
 * @param path The path of the file to load.
 * @param content A pointer to a char pointer that will be updated to point to the content of the file.
 *
 * @return Zero if the file is successfully loaded and the content is updated, -1 otherwise.
 *
 * @sa print_error_and_free
 */
int load_from_file(const char* path, char** content);

#endif //UTILS_H