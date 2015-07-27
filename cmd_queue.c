#include "cmd_queue.h"
#include "print_utils.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct cmd_queue {
    struct cmd_message * head;
    int lock;
};

#define LOCK(q) while (__sync_lock_test_and_set(&q->lock, 1)) {};
#define UNLOCK(q) __sync_lock_release(&q->lock);

struct cmd_queue * cmd_queue_create()
{
    struct cmd_queue * cq = (struct cmd_queue *)malloc(sizeof(struct cmd_queue));
    if (cq == NULL)
    {
        err_print("create cmd_queue error.");
        return NULL;
    }

    memset(cq, 0, sizeof(struct cmd_queue));

    return cq;
}

void cmd_queue_destroy(struct cmd_queue * q)
{
    LOCK(q);

    while (q->head)
    {
        struct cmd_message * msg = q->head;
        q->head = q->head->next;
        cmd_message_destroy(msg);
    }

    UNLOCK(q);

    free(q);
}

void cmd_message_destroy(struct cmd_message * msg)
{
    assert(msg);

    if (msg->data != NULL)
    {
        free(msg->data);
    }

    free(msg);
}

void cmd_queue_push(struct cmd_queue * q, struct cmd_message * msg)
{
    LOCK(q);

    struct cmd_message * head = q->head;
    if (head == NULL)
    {
        q->head = msg;
    }
    else
    {
        while (head->next)
        {
            head = head->next;
        }

        head->next = msg;
    }

    UNLOCK(q);
}

struct cmd_message * cmd_queue_pop(struct cmd_queue * q)
{
    LOCK(q);

    assert(q);

    struct cmd_message * head = q->head;
    if (head != NULL)
    {
        q->head = head->next;
    }

    UNLOCK(q);

    return head;
}

uint32_t cmd_queue_count(struct cmd_queue * q)
{
    LOCK(q);

    assert(q);

    uint32_t count = 0;
    struct cmd_message * head = q->head;
    while (head)
    {
        ++count;
        head = head->next;
    }

    UNLOCK(q);

    return count;
}