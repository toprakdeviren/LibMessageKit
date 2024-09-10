#ifndef USER_H
#define USER_H

#include "common.h"
#include "private/config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct RegistrationInfo
 * @brief structure containing user registration information.
 *
 * @field phone_number User's phone number (optional).
 * @field user_name User's username (optional).
 */
typedef struct {
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    char user_name[MAX_USERNAME_LENGTH];
} RegistrationInfo;

/**
 * @struct UserProfile
 * @brief Structure containing user profile information.
 *
 * @field user_id Unique identifier for the user.
 * @field display_name User's display name.
 * @field phone_number User's phone number.
 * @field profile_picture_url URL of the user's profile picture.
 */
typedef struct {
    char user_id[USER_ID_LENGTH];
    char display_name[MAX_DISPLAY_NAME_LENGTH];
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    char profile_picture_url[MAX_URL_LENGTH];
} UserProfile;

/**
 * @enum VerificationType
 * @brief Enumeration of supported verification types.
 */
typedef enum {
    VERIFICATION_TYPE_SMS,
    VERIFICATION_TYPE_PIN,
    VERIFICATION_TYPE_HARDWARE_KEY,
    VERIFICATION_TYPE_BIOMETRIC
} VerificationType;

/**
 * @struct VerificationData
 * @brief structure containing verification data for different verification types.
 *
 * @field type The type of verification.
 * @field data Union of different verification data types.
 */
typedef struct {
    VerificationType type;
    union {
        char sms_code[MAX_SMS_CODE_LENGTH];
        char pin[MAX_PIN_LENGTH];
        void* hardware_key_data;
        void* biometric_data;
    } data;
} VerificationData;

/**
 * @typedef RegistrationCallback
 * @brief Callback function type for registration operations.
 *
 * @param error_code Error code indicating success or failure of the operation.
 * @param user_profile Pointer to UserProfile structure containing the registered user's information.
 */
typedef void (*RegistrationCallback)(ErrorCode error_code, const UserProfile* user_profile);

/**
 * @typedef VerificationCallback
 * @brief Callback function type for verification operations.
 *
 * @param error Error code indicating success or failure of the operation.
 */
typedef void (*VerificationCallback)(ErrorCode error);

/**
 * @typedef ProfileUpdateCallback
 * @brief Callback function type for profile update operations.
 *
 * @param error_code Error code indicating success or failure of the operation.
 * @param user_profile Pointer to UserProfile structure containing the updated user profile information.
 */
typedef void (*ProfileUpdateCallback)(ErrorCode error_code, const UserProfile* user_profile);

/**
 * @function register_user
 * @brief Registers a new user with the provided information.
 *
 * @param info Pointer to RegistrationInfo structure containing the user's registration information.
 * @param callback Function to be called when the registration operation is complete.
 */
void register_user(const RegistrationInfo* info, RegistrationCallback callback);

/**
 * @function request_verification
 * @brief Requests verification for the specified user and verification type.
 *
 * @param type The type of verification to request.
 * @param callback Function to be called when the verification request is complete.
 */
void request_verification(VerificationType type, VerificationCallback callback);

/**
 * @function verify_pin
 * @brief Verifies the user's PIN.
 *
 * This function checks if the provided PIN matches the stored PIN for the given user.
 * It can be used for authentication purposes or before allowing sensitive operations.
 *
 * @param pin The PIN to be verified.
 * @param callback Function to be called when the verification process is complete.
 *                 The callback will receive an ErrorCode indicating the result of the operation.
 */
void verify_pin(const char* pin, VerificationCallback callback);

/**
 * @function update_user_profile
 * @brief Updates the user's profile information.
 *
 * @param profile Pointer to UserProfile structure containing the updated profile information.
 * @param callback Function to be called when the update operation is complete.
 */
void update_user_profile(const UserProfile* profile, ProfileUpdateCallback callback);

/**
 * @function get_user_profile
 * @brief Retrieves the current user's profile information.
 *
 * @param callback Function to be called with the retrieved profile information.
 */
void get_user_profile(ProfileUpdateCallback callback);

/**
 * @function set_user_pin
 * @brief Sets a new PIN for the user.
 *
 * @param pin The new PIN to set.
 * @param callback Function to be called when the operation is complete.
 */
void set_user_pin(const char* pin, VerificationCallback callback);

/**
 * @function change_user_pin
 * @brief Changes the user's PIN.
 *
 * @param old_pin The current PIN.
 * @param new_pin The new PIN to set.
 * @param callback Function to be called when the operation is complete.
 */
void change_user_pin(const char* old_pin, const char* new_pin, VerificationCallback callback);

/**
 * @function delete_user_account
 * @brief Deletes the user's account and all associated data.
 *
 * This operation is irreversible. All user data, including messages, contacts, and settings, will be permanently deleted.
 *
 * @param callback Function to be called when the deletion operation is complete.
 */
void delete_user_account(RegistrationCallback callback);

#ifdef __cplusplus
}
#endif

#endif // USER_H