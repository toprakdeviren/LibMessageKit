#ifndef CONVERSATIONS_H
#define CONVERSATIONS_H

#include "common.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CONVERSATION_TYPE_INDIVIDUAL,
    CONVERSATION_TYPE_GROUP
} ConversationType;

typedef enum {
    MESSAGE_TYPE_TEXT,
    MESSAGE_TYPE_IMAGE,
    MESSAGE_TYPE_VIDEO,
    MESSAGE_TYPE_AUDIO,
    MESSAGE_TYPE_FILE,
    // Add other message types as needed
} MessageType;

typedef struct {
    char conversation_id[MAX_CONVERSATION_ID_LENGTH];
    ConversationType type;
    char name[MAX_CONVERSATION_NAME_LENGTH];  // For group chats or contact name for individual
    char last_message_preview[MAX_LAST_MESSAGE_PREVIEW_LENGTH];
    MessageType last_message_type;
    int64_t last_message_timestamp;
    uint32_t unread_count;
    bool is_pinned;
    bool is_archived;
    // Add other relevant fields as needed
} ConversationSummary;

// Callback function types
typedef void (*ConversationListCallback)(const ConversationSummary conversations[], size_t count, ErrorCode error);
typedef void (*ConversationOperationCallback)(const ConversationSummary conversation[], ErrorCode error);
typedef void (*OperationCallback)(ErrorCode error);

/**
 * @brief Retrieves recent conversations.
 *
 * @param limit Maximum number of conversations to retrieve.
 * @param offset Number of conversations to skip (for pagination).
 * @param include_archived Whether to include archived conversations.
 * @param callback Function to receive the list of conversations and error code.
 */
void get_recent_conversations(size_t limit, size_t offset, bool include_archived, ConversationListCallback callback);

/**
 * @brief Searches recent conversations.
 *
 * @param query The search query string.
 * @param callback Function to receive the list of matching conversations and error code.
 */
void search_recent_conversations(const char* query, ConversationListCallback callback);

/**
 * @brief Pins a conversation.
 *
 * @param conversation_id The ID of the conversation to pin.
 * @param callback Function to receive the operation result and updated conversation summary.
 */
void pin_conversation(const char* conversation_id, ConversationOperationCallback callback);

/**
 * @brief Unpins a conversation.
 *
 * @param conversation_id The ID of the conversation to unpin.
 * @param callback Function to receive the operation result and updated conversation summary.
 */
void unpin_conversation(const char* conversation_id, ConversationOperationCallback callback);

/**
 * @brief Archives a conversation.
 *
 * @param conversation_id The ID of the conversation to archive.
 * @param callback Function to receive the operation result and updated conversation summary.
 */
void archive_conversation(const char* conversation_id, ConversationOperationCallback callback);

/**
 * @brief Unarchives a conversation.
 *
 * @param conversation_id The ID of the conversation to unarchive.
 * @param callback Function to receive the operation result and updated conversation summary.
 */
void unarchive_conversation(const char* conversation_id, ConversationOperationCallback callback);

/**
 * @brief Marks all messages in a conversation as read.
 *
 * @param conversation_id The ID of the conversation to mark as read.
 * @param callback Function to receive the operation result and updated conversation summary.
 */
void mark_conversation_as_read(const char* conversation_id, ConversationOperationCallback callback);

/**
 * @brief Retrieves pinned conversations.
 *
 * @param callback Function to receive the list of pinned conversations and error code.
 */
void get_pinned_conversations(ConversationListCallback callback);

/**
 * @brief Retrieves archived conversations.
 *
 * @param limit Maximum number of archived conversations to retrieve.
 * @param offset Number of archived conversations to skip (for pagination).
 * @param callback Function to receive the list of archived conversations and error code.
 */
void get_archived_conversations(size_t limit, size_t offset, ConversationListCallback callback);

 /**
  * @brief Blocks a user.
  *
  * @param user_id The ID of the user to block.
  * @param callback Function to receive the operation result.
  */
 void block_user(const char* user_id, OperationCallback callback);

 /**
  * @brief Unblocks a user.
  *
  * @param user_id The ID of the user to unblock.
  * @param callback Function to receive the operation result.
  */
 void unblock_user(const char* user_id, OperationCallback callback);

#ifdef __cplusplus
}
#endif

#endif //CONVERSATIONS_H
