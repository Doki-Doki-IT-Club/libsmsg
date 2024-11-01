#include "../smsg.h"
#include <netinet/in.h>
#include <stdlib.h>

void * sm_create(int type)
{
    void * ret = NULL;
    
    switch (type)
    {
        case SMSG_TYPE_SERVICE:
            ret = (sm_service *) malloc(sizeof(sm_service));
            break;

        case SMSG_TYPE_MESSAGE:
            ret = (sm_message *) malloc(sizeof(sm_message));
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ret = (sm_init *) malloc(sizeof(sm_init));
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ret = (sm_users_online *) malloc(sizeof(sm_users_online));
            break;
    }

    return ret;
}

void sm_destroy(void * msg)
{
    if (msg == NULL) { return; }

    free(msg);
}

long sm_size_by_type(void * msg)
{
    if (msg == NULL) { return; }

    long ret = 0;

    switch (((sm *) msg)->type)
    {
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