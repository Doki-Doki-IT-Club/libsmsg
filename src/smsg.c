#include <stdlib.h>

#include "../smsg.h"

void * sm_create(int type)
{
    void * ret = NULL;
    
    switch (type)
    {
        case SMSG_TYPE_SM:
            ret = (sm *) malloc(sizeof(sm));
            ((sm *) ret)->type = SMSG_TYPE_SM;
            break;

        case SMSG_TYPE_SERVICE:
            ret = (sm_service *) malloc(sizeof(sm_service));
            ((sm_service *) ret)->super.type = SMSG_TYPE_SERVICE;
            break;

        case SMSG_TYPE_MESSAGE:
            ret = (sm_message *) malloc(sizeof(sm_message));
            ((sm_message *) ret)->super.type = SMSG_TYPE_MESSAGE;
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ret = (sm_init *) malloc(sizeof(sm_init));
            ((sm_init *) ret)->super.type = SMSG_TYPE_CLIENT_INIT;
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ret = (sm_users_online *) malloc(sizeof(sm_users_online));
            ((sm_users_online *) ret)->super.type = SMSG_TYPE_USERS_ONLINE;
            break;
    }

    return ret;
}

void sm_destroy(void * msg)
{
    if (msg == NULL) { return; }

    free(msg);
}

void * sm_get_value(void * msg, int field_num)
{
    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SERVICE:
            switch (field_num)
            {
            case 0: // b_exit
                return (bool *) (((sm_service *) msg)->b_exit);
                break;
            case 1: // b_reboot
                return (bool *) (((sm_service *) msg)->b_reboot);
                break;
            }
            break;
    }
}

void sm_set_value(void * msg)
{}

void sm_set_size(void * msg, int size)
{}

void sm_set_type(void * msg, int type)
{}

int sm_get_size(void * msg)
{
    if (msg == NULL) { return -1; }

    return ((sm *) msg)->size;
}

int sm_get_type(void * msg)
{
    if (msg == NULL) { return -1; }

    return ((sm *) msg)->type;
}

long sm_size_by_type(void * msg)
{
    if (msg == NULL) { return -1; }

    long ret = -1;

    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SM:
            ret = sizeof(sm);
            break;

        case SMSG_TYPE_SERVICE:
            ret = sizeof(sm_service);
            break;

        case SMSG_TYPE_MESSAGE:
            ret = sizeof(sm_message);
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ret = sizeof(sm_init);
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ret = sizeof(sm_users_online);
            break;
    }

    ((sm *) msg)->size = ret;

    return ret;
}