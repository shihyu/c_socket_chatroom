#ifndef __USERLIST_H__
#define __USERLIST_H__

#include <stdint.h>
#include <stdbool.h>

struct user;
struct userlist;

/// 创建 userlist
struct userlist * userlist_create();

/// 销毁 userlist, 里面的 user 对象也会被全部释放掉
void userlist_destroy(struct userlist * ul);

/// 添加 user 到 userlist
bool userlist_add(struct userlist * ul, struct user * u);

/// 从 userlist 移除 user, 同时删除 user
void userlist_remove(struct userlist * ul, struct user * u);

/// 新的 id
uint32_t userlist_new_id(struct userlist * ul);

/// 当前 user 的总数量
uint32_t userlist_count(struct userlist * ul);

/// 使用 socket fd 找到对应的 user
struct user * userlist_find_with_sockfd(struct userlist * ul, int sockfd);

/// 使用 id 找到对应的 user
struct user * userlist_find_with_id(struct userlist * ul, uint32_t id);

/// 使用 name 找到对应的 user
struct user * userlist_find_with_name(struct userlist * ul, char * name);

#endif // __USERLIST_H__