#ifndef CALL_HISTORY_H
#define CALL_HISTORY_H

#include "common.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

// Call types
typedef enum {
    CALL_TYPE_INCOMING,
    CALL_TYPE_OUTGOING,
    CALL_TYPE_MISSED,
    CALL_TYPE_REJECTED
} CallType;

// Call history entry details
typedef struct {
    char call_id[CALL_ID_LENGTH];
    char contact_id[CONTACT_ID_LENGTH];
    int64_t timestamp;
    CallType type;
    uint32_t duration;  // In seconds
} CallHistoryEntry;

// Call history filter options
typedef struct {
    int64_t start_date;
    int64_t end_date;
    CallType type;
    bool include_read;
    bool include_unread;
    char contact_id[CONTACT_ID_LENGTH];
} CallHistoryFilter;

// Callback function types
typedef void (*FetchHistoryCallback)(const CallHistoryEntry* entries, size_t count, ErrorCode error);
typedef void (*OperationCallback)(ErrorCode error);
typedef void (*GetCallDetailsCallback)(const CallHistoryEntry* entry, ErrorCode error);

/**
 * @brief Fetches call history based on given filter criteria.
 *
 * @param filter Filter criteria. If NULL, all history is fetched.
 * @param limit Maximum number of entries to fetch. Zero means no limit.
 * @param offset Number of entries to skip (for pagination).
 * @param callback Function to receive the results and error code.
 */
void fetch_call_history(const CallHistoryFilter* filter, size_t limit, size_t offset, FetchHistoryCallback callback);

/**
 * @brief Deletes a specific call history entry.
 *
 * @param call_id ID of the call to be deleted.
 * @param callback Function to receive the operation result.
 */
void delete_call_history_entry(const char* call_id, OperationCallback callback);

/**
 * @brief Deletes all call history entries.
 *
 * @param callback Function to receive the operation result.
 */
void delete_all_call_history(OperationCallback callback);

/**
 * @brief Searches the call history.
 *
 * @param query Search query string.
 * @param callback Function to receive the search results and error code.
 */
void search_call_history(const char* query, FetchHistoryCallback callback);

/**
 * @brief Retrieves details of a specific call.
 *
 * @param call_id ID of the call to fetch details for.
 * @param callback Function to receive the call details and error code.
 */
void get_call_details(const char* call_id, GetCallDetailsCallback callback);

/**
 * @brief Exports call history to a file.
 *
 * @param format Export format (e.g., "CSV", "JSON").
 * @param file_path Path of the file to export to.
 * @param callback Function to receive the operation result.
 */
void export_call_history(const char* format, const char* file_path, OperationCallback callback);

#ifdef __cplusplus
}
#endif

#endif //CALL_HISTORY_H
