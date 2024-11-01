#include "../smsg.h"
#include <netinet/in.h>

void msg_htonl(void * msg)
{
    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SERVICE:
            ((sm_service *) msg)->super.size = htonl(((sm_service *) msg)->super.size);
            ((sm_service *) msg)->super.type = htonl(((sm_service *) msg)->super.type);
            ((sm_service *) msg)->b_exit = htonl(((sm_service *) msg)->b_exit);
            ((sm_service *) msg)->b_reboot = htonl(((sm_service *) msg)->b_reboot);
            break;

        case SMSG_TYPE_MESSAGE:
            ((sm_message *) msg)->super.size = htonl(((sm_message *) msg)->super.size);
            ((sm_message *) msg)->super.type = htonl(((sm_message *) msg)->super.type);
            ((sm_message *) msg)->b_global = htonl(((sm_message *) msg)->b_global);
            ((sm_message *) msg)->b_self = htonl(((sm_message *) msg)->b_self);
            ((sm_message *) msg)->client_id = htonl(((sm_message *) msg)->client_id);
            ((sm_message *) msg)->text_len = htonl(((sm_message *) msg)->text_len);
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ((sm_init *) msg)->super.size = htonl(((sm_init *) msg)->super.size);
            ((sm_init *) msg)->super.type = htonl(((sm_init *) msg)->super.type);
            ((sm_init *) msg)->self_id = htonl(((sm_init *) msg)->self_id);
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ((sm_users_online *) msg)->super.size = htonl(((sm_users_online *) msg)->super.size);
            ((sm_users_online *) msg)->super.type = htonl(((sm_users_online *) msg)->super.type);
            ((sm_users_online *) msg)->users_count = htonl(((sm_users_online *) msg)->users_count);
            break;
    }
}

void msg_ntohl(void * msg)
{
    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SERVICE:
            ((sm_service *) msg)->super.size = ntohl(((sm_service *) msg)->super.size);
            ((sm_service *) msg)->super.type = ntohl(((sm_service *) msg)->super.type);
            ((sm_service *) msg)->b_exit = ntohl(((sm_service *) msg)->b_exit);
            ((sm_service *) msg)->b_reboot = ntohl(((sm_service *) msg)->b_reboot);
            break;

        case SMSG_TYPE_MESSAGE:
            ((sm_message *) msg)->super.size = ntohl(((sm_message *) msg)->super.size);
            ((sm_message *) msg)->super.type = ntohl(((sm_message *) msg)->super.type);
            ((sm_message *) msg)->b_global = ntohl(((sm_message *) msg)->b_global);
            ((sm_message *) msg)->b_self = ntohl(((sm_message *) msg)->b_self);
            ((sm_message *) msg)->client_id = ntohl(((sm_message *) msg)->client_id);
            ((sm_message *) msg)->text_len = ntohl(((sm_message *) msg)->text_len);
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ((sm_init *) msg)->super.size = ntohl(((sm_init *) msg)->super.size);
            ((sm_init *) msg)->super.type = ntohl(((sm_init *) msg)->super.type);
            ((sm_init *) msg)->self_id = ntohl(((sm_init *) msg)->self_id);
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ((sm_users_online *) msg)->super.size = ntohl(((sm_users_online *) msg)->super.size);
            ((sm_users_online *) msg)->super.type = ntohl(((sm_users_online *) msg)->super.type);
            ((sm_users_online *) msg)->users_count = ntohl(((sm_users_online *) msg)->users_count);
            break;
    }
}

void size_by_type(void * super)
{
    switch (((sm *) super)->type)
    {
        case SMSG_TYPE_SERVICE:
            ((sm *) super)->size = sizeof(sm_service);
            break;

        case SMSG_TYPE_MESSAGE:
            ((sm *) super)->size = sizeof(sm_message);
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ((sm *) super)->size = sizeof(sm_init);
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ((sm *) super)->size = sizeof(sm_users_online);
            break;
    }
}