#ifndef DB_H
#define DB_H

#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opens a connection to the SQLite database.
 *
 * @param file_path The directory path where the database file will be stored.
 * @param file_name The name of the database file.
 * @return Zero on success, or an error code on failure.
 */
int db_open(const char* file_path, const char* file_name);

/**
 * @brief Closes the current database connection.
 */
void db_close();

/**
 * @brief Initializes the database schema.
 *
 * @param schema_path The full path to the SQL schema file.
 * @return Zero on success, or an error code on failure.
 */
int db_init_schema(const char* schema_path);


/**
 * @brief Executes a SQL query on the connected database.
 *
 * @param query The SQL query string to be executed.
 * @return Zero on success, or an error code on failure.
 */
 int execute_query(const char* query);

#ifdef __cplusplus
}
#endif

#endif //DB_H