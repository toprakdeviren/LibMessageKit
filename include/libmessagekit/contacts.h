#ifndef CONTACTS_H
#define CONTACTS_H

#include "common.h"
#include "private/config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char contact_id[MAX_CONTACT_ID_LENGTH];
    char name[MAX_CONTACT_NAME_LENGTH];
    char user_id[MAX_CONTACT_ID_LENGTH];  // Unique identifier in the messaging system
} Contact;

// Callback function types
typedef void (*ContactOperationCallback)(const Contact* contact, ErrorCode error);
typedef void (*ContactListCallback)(const Contact* contacts, size_t count, ErrorCode error);

/**
 * @brief Adds a new contact to the user's personal address book.
 *
 * @param contact The contact information to add.
 * @param callback Function to receive the operation result and the added contact.
 */
void add_contact(const Contact* contact, ContactOperationCallback callback);

/**
 * @brief Updates an existing contact in the user's address book.
 *
 * @param contact The updated contact information.
 * @param callback Function to receive the operation result and the updated contact.
 */
void update_contact(const Contact* contact, ContactOperationCallback callback);

/**
 * @brief Deletes a contact from the user's address book.
 *
 * @param contact_id The ID of the contact to delete.
 * @param callback Function to receive the operation result.
 */
void delete_contact(const char* contact_id, ContactOperationCallback callback);

/**
 * @brief Retrieves a contact by their ID.
 *
 * @param contact_id The ID of the contact to retrieve.
 * @param callback Function to receive the retrieved contact and error code.
 */
void get_contact(const char* contact_id, ContactOperationCallback callback);

/**
 * @brief Retrieves all contacts in the user's address book.
 *
 * @param callback Function to receive the list of contacts and error code.
 */
void get_all_contacts(ContactListCallback callback);

/**
 * @brief Searches for contacts based on a query string.
 *
 * @param query The search query (e.g., name or user ID).
 * @param callback Function to receive the list of matching contacts and error code.
 */
void search_contacts(const char* query, ContactListCallback callback);

#ifdef __cplusplus
}
#endif

#endif //CONTACTS_H