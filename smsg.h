#ifndef __LIBSMSG_H__
#define __LIBSMSG_H__

// +-------------------+
// |  I N C L U D E S  |
// +-------------------+

#include <string.h>
#include <stdlib.h>

#ifdef __LIBSMSG_USE_JNI__
#include <jni.h>
#endif

// +-----------------+
// |  D E F I N E S  |
// +-----------------+

#define bool int
#define true 1
#define false 0

#define MSG_TXT_FIELD_SIZE 256      //! Will be deprecated in Base-1
#define CLIENT_NAME_FILED_SIZE 32   //! Will be deprecated in Base-1
#define USERS_ONLINE_LIST_SIZE 64   //! Will be deprecated in Base-1

#define SMSG_TYPE_SM 0
#define SMSG_TYPE_SERVICE 1
#define SMSG_TYPE_MESSAGE 2
#define SMSG_TYPE_CLIENT_INIT 3
#define SMSG_TYPE_USERS_ONLINE 4

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
@brief Destroy the SMSG object.

@param msg pointer to SMSG object that will be destroyed.
*/
void sm_destroy(void * msg);

/*
@brief Return size of current SMSG object.
@param msg pointer to SMSG object.

@return
Size of current SMSG object in bytes.
*/
int sm_get_size(void * msg);

/*
@brief Return type of current SMSG object.
@param msg pointer to SMSG object.

@return
Type of input SMSG object.
*/
int sm_get_type(void * msg);

/*
@brief Return pointer to value in current SMSG object.
@param msg pointer to SMSG object.
@param field_num number of field in SMSG object.
@param index position in values array (optional).

@return
Pointer to value.
*/
void * sm_get_value(void * msg, int field_num, int index);

/*
@brief Set super.size with current SMSG type
@param msg pointer to SMSG object.

@return
Count of bytes.
*/
long sm_size_by_type(void * msg);

/*
@brief Set new value to current field in current SMSG object.
@param msg pointer to SMSG object.
@param field_num number of field in SMSG object.
@param value pointer to new value.
@param index position in values array (optional).
*/
void sm_set_value(void * msg, int field_num, void * value, int index);

/*
@brief Return number of field by string name in current SMSG object.
@param msg pointer to SMSG object.
@param field_name string name of field.

@return
Number of field.
*/
int sm_parse_field_num(void * msg,  const char * field_name);

/*
@brief Return number of type by string name in current SMSG object.
@param msg pointer to SMSG object.
@param field_name string name of field.

@return
Number of type.
*/
int sm_parse_type_num(const char * type_name);

/*
@brief Return pointer to int value.
@param value int value to get pointer.

@return
Pinter to int value.
*/
void * intTP(int value);

/*
@brief Return int value by pointer.
@param pointer pointer to value.

@return
Int value.
*/
int intPT(void * pointer);

// +-----------------+
// |  S T R U C T S  |
// +-----------------+

/*
SMSG Super-type

@note `SMSG_TYPE_SM`
*/
typedef struct sm
{
    /*Field that must be used for check message type*/
    int type;

    /*Field that must be used for check message size*/
    int size;

} sm;

/*
SMSG Type: Flags

@note `SMSG_TYPE_SERVICE`
*/
typedef struct sm_service
{
    /*Message type*/
    sm super;

    /*Flag for close connection and client*/
    bool b_exit;

    /*Flag for reboot client and connection */
    bool b_reboot;

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
    bool b_global;

    /*Flag for say client that is its message*/
    bool b_self;

} sm_message;

/*
SMSG Type: Initial

@note `SMSG_TYPE_CLIENT_INIT`
*/
typedef struct sm_client_init
{
    /*Message type*/
    sm super;
    
    unsigned int self_id;

} sm_client_init;

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

#endif