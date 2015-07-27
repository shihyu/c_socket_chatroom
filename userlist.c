#include "userlist.h"
#include "user.h"
#include "print_utils.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/// 链表节点
struct usernode {
    struct user * u;
    struct usernode * next;
};

/// user 链表, 单向链表
struct userlist {
    struct usernode * head;
    uint32_t inc_count;

    int lock;
};

#define LOCK(ul) while (__sync_lock_test_and_set(&ul->lock, 1)) {};
#define UNLOCK(ul) __sync_lock_release(&ul->lock);

struct userlist * userlist_create()
{
    struct userlist * ul = (struct userlist *)malloc(sizeof(struct userlist));
    if (!ul)
    {
        err_print("create userlist error.");
        return NULL;
    }

    memset(ul, 0, sizeof(struct userlist));

    return ul;
}

void userlist_destroy(struct userlist * ul)
{
    LOCK(ul)

    while (ul->head)
    {
        struct usernode * un = ul->head;
        ul->head = un->next;

        user_destroy(un->u);
        free(un);
    };

    UNLOCK(ul)

    free(ul);
}

bool userlist_add(struct userlist * ul, struct user * u)
{
    assert(ul && u);

    LOCK(ul)

    bool exist = false;
    struct usernode * un = ul->head;
    while (un)
    {
        struct user * tu = un->u;

        if (strcmp(user_get_name(tu), user_get_name(u)) == 0)
        {
            exist = true;
            break;
        }

        if (user_get_sockfd(tu) == user_get_sockfd(u))
        {
            exist = true;
            break;
        }

        if (user_get_id(tu) == user_get_id(u))
        {
            exist = true;
            break;
        }

        un = un->next;
    }

    if (!exist)
    {
        un = ul->head;

        if (un)
        {
            while (un)
            {
                // 遍历到最后一个元素, 并且将 user 添加到链表
                if (un->next == NULL)
                {
                    struct usernode * nun = (struct usernode *)malloc(sizeof(struct usernode));
                    nun->u = u;
                    nun->next = NULL;
                    un->next = nun;

                    ++ul->inc_count;

                    break;
                }

                un = un->next;
            };
        }
        else
        {
            struct usernode * nun = (struct usernode *)malloc(sizeof(struct usernode));
            nun->u = u;
            nun->next = NULL;
            ul->head = nun;

            ++ ul->inc_count;
        }
    }

    UNLOCK(ul)

    return !exist;
}

void userlist_remove(struct userlist * ul, struct user * u)
{
    assert(ul && u);

    LOCK(ul)

    struct usernode * un = ul->head;
    if (un)
    {
        if (un->u == u)
        {
            ul->head = un->next;

            user_destroy(un->u);
            free(un);
        }
        else
        {
            while (un)
            {
                if (un->next && un->next->u == u)
                {
                    struct usernode * node = un->next;
                    un->next = node->next;

                    user_destroy(node->u);
                    free(node);

                    break;
                }

                un = un->next;
            }
        }
    }

    UNLOCK(ul)
}

uint32_t userlist_new_id(struct userlist * ul)
{
    return ul->inc_count;
}

uint32_t userlist_count(struct userlist * ul)
{
    LOCK(ul)
    uint32_t count = 0;
    struct usernode * un = ul->head;
    while (un)
    {
        ++count;
        un = un->next;
    }

    UNLOCK(ul)

    return count;
}

struct user * userlist_find_with_sockfd(struct userlist * ul, int sockfd)
{
    LOCK(ul)

    struct usernode * un = ul->head;
    while (un)
    {
        if (user_get_sockfd(un->u) == sockfd)
        {
            UNLOCK(ul)
            return un->u;
        }

        un = un->next;
    }

    UNLOCK(ul)

    return NULL;
}

struct user * userlist_find_with_id(struct userlist * ul, uint32_t id)
{
    LOCK(ul)

    struct usernode * un = ul->head;
    while (un)
    {
        if (user_get_id(un->u) == id)
        {
            UNLOCK(ul);
            return un->u;
        }

        un = un->next;
    }

    UNLOCK(ul)

    return NULL;
}

struct user * userlist_find_with_name(struct userlist * ul, char * name)
{
    LOCK(ul);

    struct usernode * un = ul->head;
    while (un)
    {
        if (strcmp(user_get_name(un->u), name) == 0)
        {
            UNLOCK(ul);
            return un->u;
        }

        un = un->next;
    }

    UNLOCK(ul);

    return NULL;
}
