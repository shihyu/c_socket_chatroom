#ifndef __CMD_QUEUE_H__
#define __CMD_QUEUE_H__

#include <stdint.h>

struct cmd_queue;

struct cmd_message {
    int cmd;
    void * data;
    uint32_t sz;
    struct cmd_message * next;
};

/// 创建 cmd_queue
struct cmd_queue * cmd_queue_create();

/// 销毁 cmd_queue, 会把队列内的 message 资源也全部释放
void cmd_queue_destroy(struct cmd_queue * q);

/// 销毁 message
void cmd_message_destroy(struct cmd_message * msg);

/// 向 queue 中压入 msg
void cmd_queue_push(struct cmd_queue * q, struct cmd_message * msg);

/// 从 queue 中弹出 msg
struct cmd_message * cmd_queue_pop(struct cmd_queue * q);

/// 队列的大小
uint32_t cmd_queue_count(struct cmd_queue * q);

#endif // __CMD_QUEUE_H__