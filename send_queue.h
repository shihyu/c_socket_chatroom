#ifndef __SEND_QUEUE_H__
#define __SEND_QUEUE_H__

#include <stdint.h>

struct send_queue;

struct send_message {
    void * data;
    uint32_t sz;
};

/// 创建 send_queue 
struct send_queue * send_queue_create();

/// 销毁 send_queue
void send_queue_destroy(struct send_queue * q);

/// 销毁 send_message
void send_message_destroy(struct send_message * msg);

/// 将 send_message 压入 send_queue
void send_queue_push(struct send_queue * q, struct send_message * msg);

/// 从 send_queue 弹出 send_message
struct send_message * send_queue_pop(struct send_queue * q);

/// send_queue 中, send_message 的数量
uint32_t send_queue_count(struct send_queue * q);

#endif // __SEND_QUEUE_H__