#ifndef __LIBSMSG_H__
#define __LIBSMSG_H__

// +-------------------+
// |  I N C L U D E S  |
// +-------------------+

#include <stdbool.h>

// +-----------------+
// |  D E F I N E S  |
// +-----------------+

#define MSG_TXT_FIELD_SIZE 64
#define CLIENT_NAME_FILED_SIZE 16
#define USERS_ONLINE_LIST_SIZE 64

#define SMSG_TYPE_SERVICE 0
#define SMSG_TYPE_MESSAGE 1
#define SMSG_TYPE_CLIENT_INIT 2
#define SMSG_TYPE_USERS_ONLINE 3

// +-----------------------+
// |  P R O T O T Y P E S  |
// +-----------------------+

/*
@brief Create new SMSG object with needed type.

@param type type of massage that will be created.

@note Must be destroyed using sm_destroy() when no longer need it.
*/
void * sm_create(int type);

/*
@brief Create new SMSG object with needed type.

@param msg pointer to SMSG object that will be destroyed.
*/
void sm_destroy(void * msg);

/*
@brief Set super.size with current SMSG type
@param super pointer to SMSG instance.

@return
Count of bytes for current SMSG type message.
*/
long sm_size_by_type(void * super);

// +-----------------+
// |  S T R U C T S  |
// +-----------------+

/*
SMSG Core-type
*/
typedef struct sm
{
    /*Field that must be used for check message type*/
    int type;

    /*Field that must be used for check message size*/
    int size;

} sm;

/*
SMSG Type: UsersOnline

@note `SMSG_TYPE_USERS_ONLINE`
*/
typedef struct sm_users_online
{
    /*Message type*/
    sm super;

    int users_count;
    char names[USERS_ONLINE_LIST_SIZE][CLIENT_NAME_FILED_SIZE];

} sm_users_online;

/*
SMSG Type: Flags

@note `SMSG_TYPE_SERVICE`
*/
typedef struct sm_service
{
    /*Message type*/
    sm super;

    /*Flag for close connection and client*/
    bool b_exit : 1;

    /*Flag for reboot client and connection */
    bool b_reboot : 1;

} sm_service;

/*
SMSG Type: Message

@note `SMSG_TYPE_MESSAGE`
*/
typedef struct sm_message
{
    /*Message type*/
    sm super;
    
    unsigned int client_id;
    char client_name[CLIENT_NAME_FILED_SIZE];

    unsigned int text_len;
    char text[MSG_TXT_FIELD_SIZE];

    /*Flag for send message to all clients (global message)*/
    bool b_global : 1;

    /*Flag for say client that is its message*/
    bool b_self : 1;

} sm_message;

/*
SMSG Type: Initial

@note `SMSG_TYPE_CLIENT_INIT`
*/
typedef struct sm_init
{
    /*Message type*/
    sm super;
    
    unsigned int self_id;

} sm_init;

#endif