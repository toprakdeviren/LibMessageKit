#ifndef MESSAGING_H
#define MESSAGING_H

#include "common.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum MessageType
 * @brief Enumeration of supported message types.
 */
typedef enum {
    MESSAGE_TYPE_TEXT,   /**< Text message */
    MESSAGE_TYPE_IMAGE,  /**< Image message */
    MESSAGE_TYPE_VIDEO,  /**< Video message */
    MESSAGE_TYPE_AUDIO,  /**< Audio message */
    MESSAGE_TYPE_FILE    /**< File message */
} MessageType;

/**
 * @struct MessageResult
 * @brief Structure containing the result of a message operation.
 *
 * @field message_id Unique identifier of the message.
 * @field error Error code indicating the result of the operation.
 */
typedef struct {
    char message_id[MESSAGE_ID_LENGTH];
    ErrorCode error;
} MessageResult;

/**
 * @struct AttachmentData
 * @brief Structure containing data for message attachments.
 *
 * @field data Pointer to the attachment data.
 * @field size Size of the attachment data in bytes.
 */
typedef struct {
    const void* data;
    size_t size;
} AttachmentData;

/**
 * @struct FetchMessagesParams
 * @brief Parameters for fetching messages.
 *
 * @field conversation_id ID of the conversation to fetch messages from.
 * @field from_timestamp Timestamp to start fetching messages from.
 * @field limit Maximum number of messages to fetch.
 */
typedef struct {
    char conversation_id[MESSAGE_ID_LENGTH];
    int64_t from_timestamp;
    size_t limit;
} FetchMessagesParams;

/**
 * @struct BulkMessageOperation
 * @brief Structure for bulk message operations.
 *
 * @field message_ids Array of message IDs for bulk operations.
 * @field count Number of message IDs in the array.
 */
typedef struct {
    const char* message_ids[MAX_BULK_MESSAGES];
    size_t count;
} BulkMessageOperation;

/**
 * @struct Message
 * @brief Structure representing a message.
 *
 * @field id Unique identifier of the message.
 * @field conversation_id ID of the conversation the message belongs to.
 * @field sender_id ID of the message sender.
 * @field type Type of the message.
 * @field timestamp Timestamp of when the message was sent.
 * @field content Content of the message.
 */
typedef struct {
    char id[MESSAGE_ID_LENGTH];
    char conversation_id[MESSAGE_ID_LENGTH];
    char sender_id[MESSAGE_ID_LENGTH];
    MessageType type;
    int64_t timestamp;
    char content[MAX_CONTENT_LENGTH];
} Message;

/**
 * @typedef MessageCallback
 * @brief Callback function type for message operations.
 *
 * @param result Pointer to MessageResult containing the operation result.
 */
typedef void (*MessageCallback)(const MessageResult* result);

/**
 * @typedef FetchMessagesCallback
 * @brief Callback function type for fetching messages.
 *
 * @param result Pointer to MessageResult containing the operation result.
 * @param messages Array of fetched messages.
 * @param message_count Number of messages in the array.
 */
typedef void (*FetchMessagesCallback)(const MessageResult* result, const Message messages[], size_t message_count);

/**
 * @typedef SearchMessagesCallback
 * @brief Callback function type for searching messages.
 *
 * @param result Pointer to MessageResult containing the operation result.
 * @param messages Array of found messages.
 * @param message_count Number of messages in the array.
 */
typedef void (*SearchMessagesCallback)(const MessageResult* result, const Message messages[], size_t message_count);

/**
 * @typedef DeleteMessagesCallback
 * @brief Callback function type for deleting messages.
 *
 * @param result Pointer to MessageResult containing the operation result.
 */
typedef void (*DeleteMessagesCallback)(const MessageResult* result);

/**
 * @typedef ReplyMessageCallback
 * @brief Callback function type for replying to messages.
 *
 * @param result Pointer to MessageResult containing the operation result.
 */
typedef void (*ReplyMessageCallback)(const MessageResult* result);

/**
 * @typedef ReactionCallback
 * @brief Callback function type for message reactions.
 *
 * @param result Pointer to MessageResult containing the operation result.
 */
typedef void (*ReactionCallback)(const MessageResult* result);

/**
 * @typedef ForwardMessagesCallback
 * @brief Callback function type for forwarding messages.
 *
 * @param result Pointer to MessageResult containing the operation result.
 */
typedef void (*ForwardMessagesCallback)(const MessageResult* result);

/**
 * @function send_text_message
 * @brief Sends a text message to the specified conversation.
 *
 * @param conversation_id The ID of the conversation to send the message to.
 * @param text The content of the message to be sent.
 * @param callback Function to be called when the operation is complete.
 */
void send_text_message(const char* conversation_id, const char* text, MessageCallback callback);

/**
 * @function send_attachment_message
 * @brief Sends an attachment message to the specified conversation.
 *
 * @param conversation_id The ID of the conversation to send the message to.
 * @param type The type of the attachment (image, video, audio, file).
 * @param attachment Pointer to the AttachmentData structure containing the attachment.
 * @param callback Function to be called when the operation is complete.
 */
void send_attachment_message(const char* conversation_id, MessageType type, const AttachmentData* attachment, MessageCallback callback);

/**
 * @function fetch_messages
 * @brief Fetches messages from a conversation based on the provided parameters.
 *
 * @param params Pointer to FetchMessagesParams structure containing fetch parameters.
 * @param callback Function to be called with the fetched messages.
 */
void fetch_messages(const FetchMessagesParams* params, FetchMessagesCallback callback);

/**
 * @function delete_message
 * @brief Deletes a single message.
 *
 * @param message_id The ID of the message to delete.
 * @param callback Function to be called when the operation is complete.
 */
void delete_message(const char* message_id, DeleteMessagesCallback callback);

/**
 * @function delete_messages
 * @brief Deletes multiple messages in a bulk operation.
 *
 * @param operation Pointer to BulkMessageOperation structure containing the messages to delete.
 * @param callback Function to be called when the operation is complete.
 */
void delete_messages(const BulkMessageOperation* operation, DeleteMessagesCallback callback);

/**
 * @function reply_message
 * @brief Replies to a specific message.
 *
 * @param original_message_id The ID of the message being replied to.
 * @param reply_text The content of the reply message.
 * @param callback Function to be called when the operation is complete.
 */
void reply_message(const char* original_message_id, const char* reply_text, ReplyMessageCallback callback);

/**
 * @function search_messages
 * @brief Searches for messages in a conversation.
 *
 * @param conversation_id The ID of the conversation to search in.
 * @param query The search query string.
 * @param callback Function to be called with the search results.
 */
void search_messages(const char* conversation_id, const char* query, SearchMessagesCallback callback);

/**
 * @function reaction_to_message
 * @brief Adds a reaction to a message.
 *
 * @param message_id The ID of the message to react to.
 * @param reaction The reaction to add (e.g., emoji).
 * @param callback Function to be called when the operation is complete.
 */
void reaction_to_message(const char* message_id, const char* reaction, ReactionCallback callback);

/**
 * @function forward_message
 * @brief Forwards a single message to another conversation.
 *
 * @param message_id The ID of the message to forward.
 * @param target_conversation_id The ID of the conversation to forward the message to.
 * @param callback Function to be called when the operation is complete.
 */
void forward_message(const char* message_id, const char* target_conversation_id, ForwardMessagesCallback callback);

/**
 * @function forward_messages
 * @brief Forwards multiple messages to another conversation in a bulk operation.
 *
 * @param operation Pointer to BulkMessageOperation structure containing the messages to forward.
 * @param target_conversation_id The ID of the conversation to forward the messages to.
 * @param callback Function to be called when the operation is complete.
 */
void forward_messages(const BulkMessageOperation* operation, const char* target_conversation_id, ForwardMessagesCallback callback);

#ifdef __cplusplus
}
#endif

#endif // MESSAGING_H