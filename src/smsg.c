#include "../smsg.h"

void * sm_create(int type)
{
    void * ret = NULL;
    
    switch (type)
    {
        case SMSG_TYPE_SM:
            ret = (sm *) malloc(sizeof(sm));
            memset(ret, 0, sizeof(sm));
            ((sm *) ret)->type = SMSG_TYPE_SM;
            break;

        case SMSG_TYPE_SERVICE:
            ret = (sm_service *) malloc(sizeof(sm_service));
            memset(ret, 0, sizeof(sm_service));
            ((sm_service *) ret)->super.type = SMSG_TYPE_SERVICE;
            break;

        case SMSG_TYPE_MESSAGE:
            ret = (sm_message *) malloc(sizeof(sm_message));
            memset(ret, 0, sizeof(sm_message));
            ((sm_message *) ret)->super.type = SMSG_TYPE_MESSAGE;
            break;

        case SMSG_TYPE_CLIENT_INIT:
            ret = (sm_client_init *) malloc(sizeof(sm_client_init));
            memset(ret, 0, sizeof(sm_client_init));
            ((sm_client_init *) ret)->super.type = SMSG_TYPE_CLIENT_INIT;
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ret = (sm_users_online *) malloc(sizeof(sm_users_online));
            memset(ret, 0, sizeof(sm_users_online));
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

int sm_parse_type_num(const char * type_name)
{
    if (strcmp(type_name, "sm") == 0) { return 0; }
    if (strcmp(type_name, "sm_service") == 0) { return 1; }
    if (strcmp(type_name, "sm_message") == 0) { return 2; }
    if (strcmp(type_name, "sm_client_init") == 0) { return 3; }
    if (strcmp(type_name, "sm_users_online") == 0) { return 4; }

    return -1;
}

int sm_parse_field_num(void * msg, const char * field_name)
{
    if (msg == NULL) { return -1; }

    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SM:
            if (strcmp(field_name, "size") == 0) { return 0; }
            if (strcmp(field_name, "type") == 0) { return 1; }
            break;

        case SMSG_TYPE_SERVICE:
            if (strcmp(field_name, "b_exit") == 0) { return 0; }
            if (strcmp(field_name, "b_reboot") == 0) { return 1; }
            break;

        case SMSG_TYPE_MESSAGE:
            if (strcmp(field_name, "b_global") == 0) { return 0; }
            if (strcmp(field_name, "b_self") == 0) { return 1; }
            if (strcmp(field_name, "client_id") == 0) { return 2; }
            if (strcmp(field_name, "client_name") == 0) { return 3; }
            if (strcmp(field_name, "text") == 0) { return 4; }
            if (strcmp(field_name, "text_len") == 0) { return 5; }
            break;

        case SMSG_TYPE_CLIENT_INIT:
            if (strcmp(field_name, "self_id") == 0) { return 0; }
            break;

        case SMSG_TYPE_USERS_ONLINE:
            if (strcmp(field_name, "names") == 0) { return 0; }
            if (strcmp(field_name, "users_count") == 0) { return 1; }
            break;

        default:
            return -1;
            break;
    }

    return -1;
}

void * sm_get_value(void * msg, int field_num, int index)
{
    if (msg == NULL) { return NULL; }

    // switch (field_num)
    // {
    // case 0:
    //     return (void *) &(((sm *) msg)->size);
    //     break;
    // case 1:
    //     return (void *) &(((sm *) msg)->type);
    //     break;
    // }

    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SM:
            break;

        case SMSG_TYPE_SERVICE:
            switch (field_num)
            {
            case 0:
                return (void *) (((sm_service *) msg)->b_exit);
                break;
            case 1:
                return (void *) (((sm_service *) msg)->b_reboot);
                break;
            }
            break;

        case SMSG_TYPE_MESSAGE:
            switch (field_num)
            {
            case 0:
                return (void *) (((sm_message *) msg)->b_global);
                break;
            case 1:
                return (void *) (((sm_message *) msg)->b_self);
                break;
            case 2:
                return (void *) &(((sm_message *) msg)->client_id);
                break;
            case 3:
                return (char *) (((sm_message *) msg)->client_name);
                break;
            case 4:
                return (char *) (((sm_message *) msg)->text);
                break;
            case 5:
                return (void *) &(((sm_message *) msg)->text_len);
                break;
            }
            break;

        case SMSG_TYPE_CLIENT_INIT:
            switch (field_num)
            {
            case 0:
                return (void *) &(((sm_client_init *) msg)->self_id);
                break;
            }
            break;

        case SMSG_TYPE_USERS_ONLINE:
            switch (field_num)
            {
            case 0:
                return (void *) (((sm_users_online *) msg)->names)[index];
                break;
            case 1:
                return (void *) &(((sm_users_online *) msg)->users_count);
                break;
            }
            break;

        default:
            return NULL;
            break;
    }

    return NULL;
}

void sm_set_value(void * msg, int field_num, void * value, int index)
{
    if (msg == NULL) { return; }

    // switch (field_num)
    // {
    // case 0:
    //     (((sm *) msg)->size) = * (int *) value;
    //     break;
    // case 1:
    //     (((sm *) msg)->type) = * (int *) value;
    //     break;
    // }

    switch (((sm *) msg)->type)
    {
        case SMSG_TYPE_SM:
            break;

        case SMSG_TYPE_SERVICE:
            switch (field_num)
            {
            case 0:
                (((sm_service *) msg)->b_exit) = * (bool *) value;
                break;
            case 1:
                (((sm_service *) msg)->b_reboot) = * (bool *) value;
                break;
            }
            break;

        case SMSG_TYPE_MESSAGE:
            switch (field_num)
            {
            case 0:
                (((sm_message *) msg)->b_global) = * (bool *) value;
                break;
            case 1:
                (((sm_message *) msg)->b_self) = * (bool *) value;
                break;
            case 2:
                (((sm_message *) msg)->client_id) = * (int *) value;
                break;
            case 3:
                strncpy((((sm_message *) msg)->client_name), (char *) value, CLIENT_NAME_FILED_SIZE);
                break;
            case 4:
                strncpy((((sm_message *) msg)->text), (char *) value, MSG_TXT_FIELD_SIZE);
                break;
            case 5:
                (((sm_message *) msg)->text_len) = * (int *) value;
                break;
            }
            break;

        case SMSG_TYPE_CLIENT_INIT:
            switch (field_num)
            {
            case 0:
                (((sm_client_init *) msg)->self_id) = * (int *) value;
                break;
            }
            break;

        case SMSG_TYPE_USERS_ONLINE:
            switch (field_num)
            {
            case 0:
                strncpy((((sm_users_online *) msg)->names)[index], (char *) value, USERS_ONLINE_LIST_SIZE);
                break;
            case 1:
                (((sm_users_online *) msg)->users_count) = * (int *) value;
                break;
            }
            break;
    }

    free(value);
}

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
            ret = sizeof(sm_client_init);
            break;

        case SMSG_TYPE_USERS_ONLINE:
            ret = sizeof(sm_users_online);
            break;
    }

    ((sm *) msg)->size = ret;

    return ret;
}

void * intTP(int value)
{
    void * res = malloc(sizeof(int));
    * (int *) res = value;
    return res;
}

int intPT(void * value)
{ return * (int *) value; }