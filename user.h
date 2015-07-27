#ifndef __USER_H__
#define __USER_H__

#include <stdint.h>
#include <stdbool.h>

struct user;

/// 创建 user
struct user * user_create();

/// 释放 user
void user_destroy(struct user * u);

/**
 * 初始化 user
 * @param u user
 * @param name 名字, 会对其数据进行复制
 * @param sockfd socket fd
 * @param id user 的 id
 */
bool user_init(struct user * u, char * name, int sockfd, uint32_t id);

/// 获得 name
char * user_get_name(struct user * u);

/// 获得 sockfd
int user_get_sockfd(struct user * u);

/// 获得 id
uint32_t user_get_id(struct user * u);

#endif // __USER_H__