#ifndef SETTINGS_H
#define SETTINGS_H

#include "common.h"
#include "config.h"

/**
 * @struct UserSettings
 * @brief Structure containing user-specific settings and profile information.
 *
 * @field status User's current status message.
 * @field display_name User's display name.
 * @field profile_picture Pointer to the user's profile picture data.
 * @field profile_picture_size Size of the profile picture data in bytes.
 * @field notifications_enabled Boolean indicating if notifications are enabled.
 */
typedef struct {
    char status[MAX_STATUS_LENGTH];
    char display_name[MAX_STATUS_LENGTH];
    uint8_t* profile_picture;
    size_t profile_picture_size;
    bool notifications_enabled;
} UserSettings;

/**
 * @function set_display_name
 * @brief Sets the user's display name.
 *
 * @param display_name The new display name to set. Must not exceed MAX_STATUS_LENGTH.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_display_name(const char* display_name);

/**
 * @function set_status
 * @brief Sets the user's status message.
 *
 * @param status The new status message to set. Must not exceed MAX_STATUS_LENGTH.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_status(const char* status);

/**
 * @function set_profile_picture
 * @brief Sets the user's profile picture.
 *
 * @param image_data Pointer to the image data.
 * @param image_size Size of the image data in bytes.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_profile_picture(const uint8_t* image_data, size_t image_size);

/**
 * @function get_settings
 * @brief Retrieves the current user settings.
 *
 * @param settings Pointer to a UserSettings structure where the current settings will be stored.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode get_settings(UserSettings* settings);

/**
 * @function reset_settings
 * @brief Resets all user settings to their default values.
 *
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode reset_settings();

/**
 * @function delete_account
 * @brief Deletes the user's account and all associated data.
 *
 * This operation is irreversible. All user data, including messages, contacts, and settings, will be permanently deleted.
 *
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode delete_account();

#endif //SETTINGS_H