#ifndef SETTINGS_H
#define SETTINGS_H

#include "common.h"
#include "private/config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct UserSettings
 * @brief structure containing user-specific settings and preferences.
 *
 * @field status: User's current status message.
 * @field display_name: User's display name.
 * @field notifications_enabled: Boolean indicating if notifications are enabled.
 * @field theme: User's preferred theme.
 * @field language: User's preferred language.
 */
typedef struct {
    char status[MAX_STATUS_LENGTH];
    char display_name[MAX_DISPLAY_NAME_LENGTH];
    bool notifications_enabled;
    int theme;
    char language[MAX_LANGUAGE_CODE_LENGTH];
} UserSettings;

/**
 * @function set_user_status
 * @brief Sets the user's status message.
 *
 * @param status The new status message to set.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_user_status(const char* status);

/**
 * @function set_display_name
 * @brief Sets the user's display name.
 *
 * @param display_name The new display name to set.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_display_name(const char* display_name);

/**
 * @function set_notification_preferences
 * @brief Sets the user's notification preferences.
 *
 * @param enabled Boolean indicating if notifications should be enabled.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_notification_preferences(bool enabled);

/**
 * @function set_theme
 * @brief Sets the user's preferred theme.
 *
 * @param theme The theme identifier to set.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_theme(int theme);

/**
 * @function set_language
 * @brief Sets the user's preferred language.
 *
 * @param language_code The language code to set.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_language(const char* language_code);

/**
 * @function get_user_settings
 * @brief Retrieves the current user settings.
 *
 * @param settings Pointer to a UserSettings structure where the current settings will be stored.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode get_user_settings(UserSettings* settings);

/**
 * @function reset_user_settings
 * @brief Resets all user settings to their default values.
 *
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode reset_user_settings();

#ifdef __cplusplus
}
#endif

#endif //SETTINGS_H