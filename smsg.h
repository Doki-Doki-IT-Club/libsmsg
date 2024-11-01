#ifndef __LIBSMSG_H__
#define __LIBSMSG_H__

// DEFINES

#define MSG_TXT_FIELD_SIZE 64
#define CLIENT_NAME_FILED_SIZE 16
#define USERS_ONLINE_LIST_SIZE 64

#define SMSG_TYPE_FLAGS 0
#define SMSG_TYPE_MESSAGE 1
#define SMSG_TYPE_CLIENT_INIT 2
#define SMSG_TYPE_USERS_ONLINE 3

// STRUCTS

/*
SMSG Core-type
*/
typedef struct sm
{
    /*Field that must be used for check message type*/
    int type;
} sm;

/*
SMSG Type: UsersOnline

#define: SMSG_TYPE_USERS_ONLINE
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

#define: SMSG_TYPE_FLAGS
*/
typedef struct sm_flags
{
    /*Message type*/
    sm super;

    /*Service flags union*/
    union service
    {
        /*Decimal cast of all flags*/
        unsigned int cast : 2;
        
        struct
        {
            /*Flag for close connection and client*/
            unsigned b_exit : 1;

            /*Flag for reboot client and connection */
            unsigned b_reboot : 1;
        };
    } service;
} sm_flags;

/*
SMSG Type: Message

#define: SMSG_TYPE_MESSAGE
*/
typedef struct sm_message
{
    /*Message type*/
    sm super;
    
    unsigned int client_id;
    char client_name[CLIENT_NAME_FILED_SIZE];

    unsigned int text_len;
    char text[MSG_TXT_FIELD_SIZE];

    /*Message flags union*/
    union flags
    {
        /*Decimal cast of all flags*/
        unsigned int cast : 2;

        struct
        {
            /*Flag for send message to all clients (global message)*/
            unsigned b_global : 1;

            /*Flag for say client that is its message*/
            unsigned b_self : 1;
        };
    } flags;
} sm_message;

/*
SMSG Type: Initial

Message type: SMSG_TYPE_CLIENT_INIT
*/
typedef struct sm_init
{
    /*Message type*/
    sm super;
    
    unsigned int self_id;
} sm_init;

#endif