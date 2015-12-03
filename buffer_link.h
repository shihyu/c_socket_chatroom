#ifndef __BUFFER_LINK_H__
#define __BUFFER_LINK_H__

#include <stdint.h>

struct buffer_node {
    char * buffer;
    uint32_t sz;
    struct buffer_node * next;
};

struct buffer_link {
    struct buffer_node * head;
    struct buffer_node * tail;
    uint32_t offset;
};

/// 创建 buffer_link 对象
struct buffer_link * buffer_link_create();

/// 销毁 buffer_link 对象
void buffer_link_destroy(struct buffer_link * bl);

/** 
 * 添加写数据
 * @param bl buffer_link 对象
 * @param buf 数据指针
 * @param sz 数据大小
 * @author Zhenyu Yao
 */
void buffer_link_append(struct buffer_link * bl, void * buf, uint32_t sz);

/**
 * 销毁 buffer_node 对象
 * @param bn buffer_node 对象
 * @author Zhenyu Yao
 */
void buffer_link_destroy_node(struct buffer_node * bn);

#endif // __BUFFER_LINK_H__