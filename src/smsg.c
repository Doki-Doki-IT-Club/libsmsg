#include "../smsg.h"

int size_by_type(int type)
{
    switch (type)
    {
    case SMSG_TYPE_SERVICE:
        return sizeof(sm_service);
        break;

    case SMSG_TYPE_MESSAGE:
        return sizeof(sm_message);
        break;

    case SMSG_TYPE_CLIENT_INIT:
        return sizeof(sm_init);
        break;

    case SMSG_TYPE_USERS_ONLINE:
        return sizeof(sm_users_online);
        break;
    
    default:
        return -1;
        break;
    }
}