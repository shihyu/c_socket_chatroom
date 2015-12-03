#include <stdlib.h>
#include <string.h>

#include "buffer_link.h"

struct buffer_link * buffer_link_create()
{
    struct buffer_link * bl = (struct buffer_link *)malloc(sizeof(struct buffer_link));
    memset(bl, 0, sizeof(struct buffer_link));
    return bl;
}

void buffer_link_destroy(struct buffer_link * bl)
{
    while (bl->head)
    {
        struct buffer_node * next = bl->head->next;
        buffer_link_destroy_node(bl->head);
        bl->head = next;
    }

    bl->head = bl->tail = NULL;
    free(bl);
}

void buffer_link_append(struct buffer_link * bl, void * buf, uint32_t sz)
{
    struct buffer_node * bn = (struct buffer_node *)malloc(sizeof(struct buffer_node));
    memset(bn, 0, sizeof(struct buffer_node));

    bn->buffer = buf;
    bn->sz = sz;

    if (bl->head == bl->tail)
    {
        bl->head = bl->tail = bn;
    }
    else
    {
        bl->tail->next = bn;
        bl->tail = bn;
    }
}

void buffer_link_destroy_node(struct buffer_node * bn)
{
    free(bn->buffer); bn->buffer = NULL;
    bn->next = NULL;
    free(bn);
}

