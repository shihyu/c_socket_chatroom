#ifndef __SOCKET_OBJECT_H__
#define __SOCKET_OBJECT_H__

struct buffer_link;

struct message_node {
    char * buf;
    struct message_node * next;
};

struct message_queue {
    struct message_node * head;
    struct message_node * tail;
};

struct socket_object {
    int sockfd;             // socket fd
    struct buffer_link * wl; // 写数据缓存
    struct buffer_link * rl;  // 读数据缓存
    struct message_queue * msg_queue;   // 实际的数据内容
};

/**
 * 创建 socket_object 对象
 * @return socket_object 对象
 * @author Zhenyu Yao
 */
struct socket_object * socket_object_create();

/**
 * 释放 socket_object 对象
 * @param so socket_object
 * @author Zhenyu Yao
 */
void socket_object_destroy(struct socket_object * so);

/**
 * 将 so->rl 内的数据压入到 so->msg_queue 中, 数据以 '\n' 字符分段
 * @param so socket_object 对象
 * @return 如果有压入成功则返回 1, 否则返回 0
 * @author Zhenyu Yao
 */
int socket_object_push_msg(struct socket_object * so);

/**
 * 从 so->msg_queue 中弹出 1 个 message_node 对象
 * @param so socket_object 对象
 * @return 如果成功弹出返回 message_node 对象, 否则返回 NULL
 * @author Zhenyu Yao
 */
struct message_node * socket_object_pop_msg(struct socket_object * so);

/**
 * 删除 message_node 对象资源
 * @param mn message_node 对象
 * @author Zhenyu Yao
 */
void socket_object_destroy_message_node(struct message_node * mn);

#endif // __SOCKET_OBJECT_H__