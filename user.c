#include "user.h"
#include "print_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NAME_LEN    64

struct user {
    char name[NAME_LEN];    // 用户名
    int sockfd;         // socket fd
    uint32_t id;        // user id
};

struct user * user_create()
{
    struct user * nu = (struct user *)malloc(sizeof(struct user));
    if (!nu)
    {
        err_print("create user error.");
        return NULL;
    }

    memset(nu, 0, sizeof(struct user));

    return nu;
}

void user_destroy(struct user * u)
{
    free(u);
}

bool user_init(struct user * u, char * name, int sockfd, uint32_t id)
{
    assert(u);
    assert(name);

    size_t len = strlen(name);
    assert(NAME_LEN > len);

    memset(u->name, 0, NAME_LEN);
    memcpy(u->name, name, len);

    u->sockfd = sockfd;
    u->id = id;

    return true;
}

char * user_get_name(struct user * u)
{
    return u->name;
}

int user_get_sockfd(struct user * u)
{
    return u->sockfd;
}

uint32_t user_get_id(struct user * u)
{
    return u->id;
}

