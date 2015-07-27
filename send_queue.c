#include "send_queue.h"
#include "print_utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct send_queue {
    struct send_message * head;

    int lock;
};

#define LOCK(q) while (__sync_lock_test_and_set(&q->lock, 1)) {};
#define UNLOCK(q) __sync_lock_release(&q->lock);

struct send_queue * send_queue_create()
{
    struct send_queue * sq = (struct send_queue *)malloc(sizeof(struct send_queue));
    if (sq == NULL)
    {
        err_print("create send_queue error.");
        return NULL;
    }

    memset(sq, 0, sizoef(struct send_queue));

    return sq;
}

void send_queue_destroy(struct send_queue * q)
{
    LOCK(q)

    struct send_message * sm = q->head;
    while (q->head)
    {
        struct send_message * msg = q->head;
        q->head = msg->next;
        send_message_destroy(msg);
    }

    UNLOCK(q)
}

void send_message_destroy(struct send_message * msg)
{
    free(msg->data);
    free(msg);
}

void send_queue_push(struct send_queue * q, struct send_message * msg)
{
    LOCK(q)

    if (q->head == NULL)
    {
        q->head = msg;
    }
    else
    {
        struct send_messsage * sm = q->head;
        while (sm->next)
        {
            sm = sm->next;
        }

        sm->next = msg;
    }

    UNLOCK(q)
}

struct send_messsage * send_queue_pop(struct send_queue * q)
{
    LOCK(q)

    

    UNLOCK(q)
}

uint32_t send_queue_count(struct send_queue * q)
{
    LOCK(q)

    

    UNLOCK(q)
}