#ifndef CALL_H
#define CALL_H

#include "common.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CALL_TYPE_AUDIO,
    CALL_TYPE_VIDEO
} CallType;

typedef enum {
    CALL_STATE_INITIATING,
    CALL_STATE_RINGING,
    CALL_STATE_CONNECTED,
    CALL_STATE_HOLDING,
    CALL_STATE_ENDED
} CallState;

typedef struct {
    char call_id[CALL_ID_LENGTH];
    char peer_id[USER_ID_LENGTH];
    CallType type;
    CallState state;
    bool is_outgoing;
    bool is_muted;
    // Add other relevant fields as needed
} CallInfo;

// Callback function types
typedef void (*CallOperationCallback)(const CallInfo* call_info, ErrorCode error);
typedef void (*CallStateChangeCallback)(const CallInfo* call_info);

/**
 * @brief Starts a call with the specified user.
 *
 * @param peer_id The ID of the user to call.
 * @param type The type of call (audio or video).
 * @param callback Function to receive the call information and error code.
 */
void start_call(const char* peer_id, CallType type, CallOperationCallback callback);

/**
 * @brief Answers an incoming call.
 *
 * @param call_id The ID of the call to answer.
 * @param callback Function to receive the call information and error code.
 */
void answer_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Rejects an incoming call.
 *
 * @param call_id The ID of the call to reject.
 * @param callback Function to receive the operation result.
 */
void reject_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Ends an ongoing call.
 *
 * @param call_id The ID of the call to end.
 * @param callback Function to receive the operation result.
 */
void end_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Puts an ongoing call on hold.
 *
 * @param call_id The ID of the call to put on hold.
 * @param callback Function to receive the call information and error code.
 */
void hold_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Resumes a call that was on hold.
 *
 * @param call_id The ID of the call to resume.
 * @param callback Function to receive the call information and error code.
 */
void resume_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Switches between audio and video call.
 *
 * @param call_id The ID of the call to switch.
 * @param new_type The new call type to switch to.
 * @param callback Function to receive the call information and error code.
 */
void switch_call_type(const char* call_id, CallType new_type, CallOperationCallback callback);

/**
 * @brief Mutes the local audio in a call.
 *
 * @param call_id The ID of the call to mute.
 * @param callback Function to receive the call information and error code.
 */
void mute_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Unmutes the local audio in a call.
 *
 * @param call_id The ID of the call to unmute.
 * @param callback Function to receive the call information and error code.
 */
void unmute_call(const char* call_id, CallOperationCallback callback);

/**
 * @brief Registers a callback for call state changes.
 *
 * @param callback Function to be called when the call state changes.
 */
void register_call_state_change_callback(CallStateChangeCallback callback);

#ifdef __cplusplus
}
#endif

#endif //CALL_H
