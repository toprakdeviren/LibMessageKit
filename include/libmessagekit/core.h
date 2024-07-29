#ifndef CORE_H
#define CORE_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

// Note: Platform specific infos host only on a client, not will send to server. Brief in white paper.

/**
 * @enum Platform
 * @brief Enumeration of supported platforms.
 */
typedef enum {
 PLATFORM_IOS_PHONE,
 PLATFORM_IOS_TABLET,
 PLATFORM_ANDROID_PHONE,
 PLATFORM_ANDROID_TABLET,
 PLATFORM_WEB,
 PLATFORM_MACOS,
 PLATFORM_WINDOWS,
 PLATFORM_LINUX,
 PLATFORM_BSD,
 PLATFORM_UNKNOWN
} Platform;

/**
 * @enum DeviceType
 * @brief Enumeration of device types.
 */
typedef enum {
 DEVICE_TYPE_PHONE,
 DEVICE_TYPE_TABLET,
 DEVICE_TYPE_DESKTOP,
 DEVICE_TYPE_WEB,
 DEVICE_TYPE_UNKNOWN
} DeviceType;

 /**
  * @struct CoreConfig
  * @brief Configuration structure for initializing the core library.
  *
  * @field Storage_path The path where the library will store its data.
  * @field Database_filename The name of the database file to be used.
  * @field Platform The specific platform on which the library is running.
  * @field Platform_version The version of the platform.
  * @field Device_type The type of device (phone, tablet, desktop, etc.).
  * @field Device_model Optional field for the specific device model.
  */
 typedef struct {
  const char* storage_path;
  const char* database_filename;
  Platform platform;
  const char* platform_version;
  DeviceType device_type;
  const char* device_model;  // Optional, can be NULL
 } CoreConfig;

/**
 * @function init
 * @brief Initializes the core library with the provided configuration.
 *
 * This function must be called before any other library function. It sets up
 * the necessary resources and prepares the library for use, taking into account
 * the specific platform and device type it's running on.
 *
 * @param config Pointer to a CoreConfig structure containing initialization parameters.
 * @return ErrorCode indicating success or failure of the initialization.
 */
ErrorCode init(const CoreConfig* config);

/**
 * @function migrate_data
 * @brief Migrates all library data to a new storage location.
 *
 * This function moves all existing data from the current storage location
 * to the specified new path. It should be used in conjunction with set_storage_path.
 *
 * @param new_path The path to migrate the data to.
 * @return ErrorCode indicating success or failure of the migration.
 */
ErrorCode migrate_data(const char* new_path);

/**
 * @function set_notification_token
 * @brief Sets the notification token for push notifications.
 *
 * This function should be called to set or update the token used for
 * receiving push notifications.
 *
 * @param token The new notification token.
 * @return ErrorCode indicating success or failure of the operation.
 */
ErrorCode set_notification_token(const char* token);

/**
 * @function update_notification_token
 * @brief Updates the existing notification token.
 *
 * This function is similar to set_notification_token, but it's specifically
 * for updating an existing token. It may perform additional operations
 * related to token updates.
 *
 * @param token The updated notification token.
 * @return ErrorCode indicating success or failure of the update.
 */
ErrorCode update_notification_token(const char* token);

/**
 * @function get_platform
 * @brief Retrieves the current platform the library is running on.
 *
 * @return Platform enum indicating the current platform.
 */
Platform get_platform();

/**
 * @function get_platform_version
 * @brief Retrieves the version of the current platform.
 *
 * @return A string representing the platform version.
 */
const char* get_platform_version();

/**
 * @function get_device_type
 * @brief Retrieves the type of device the library is running on.
 *
 * @return DeviceType enum indicating the current device type.
 */
DeviceType get_device_type();

/**
 * @function get_device_model
 * @brief Retrieves the model of the device, if available.
 *
 * @return A string representing the device model, or NULL if not available.
 */
const char* get_device_model();

#ifdef __cplusplus
}
#endif

#endif //CORE_H