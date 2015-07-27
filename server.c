#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include <socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "user.h"
#include "userlist.h"
#include "print_utils.h"
#include "cmd_queue.h"

#define LOGIN       1   // 登录
#define LOGOUT      2   // 登出
#define MESSAGE     3   // 发送消息给各位
#define USERLUST    4   // 用户列表

static struct cmd_queue * g_cmd_queue = NULL;
static struct send_queue * g_send_queue = NULL;
static struct userlist * g_userlist = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 接收线程
////////////////////////////////////////////////////////////////////////////////////////////////////

static void * recv_thread(void * arg)
{
    trace("接收线程启动");

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 发送线程
////////////////////////////////////////////////////////////////////////////////////////////////////

static void * send_thread(void * arg)
{
    trace("发送线程启动");

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 逻辑线程
////////////////////////////////////////////////////////////////////////////////////////////////////

static void * logic_thread(void * arg)
{
    trace("逻辑线程启动");

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 其他
////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    struct userlist * ul = userlist_create();

    int i;
    for (i = 0; i < 10; ++i)
    {
        struct user * u = user_create();

        char tmp[64] = { 0, };
        sprintf(tmp, "name %d", i);

        uint32_t id = userlist_new_id(ul);
        user_init(u, tmp, i, id);

        userlist_add(ul, u);

        memset(tmp, 0, 64);
        sprintf(tmp, "添加 user, user.id = %u", user_get_id(u));
        std_print(tmp);
    }

    std_print("-------------------------------");

    for (i = 0; i < 5; ++i)
    {
        struct user * u = userlist_find_with_id(ul, i);
        if (u)
        {
            userlist_remove(ul, u);
            std_print("移除 user.");
        }
    }

    trace("用户数量 %d", userlist_count(ul));

    userlist_destroy(ul);
    trace("销毁 userlist.");

    std_print("-------------------------------");

    struct cmd_queue * cq = cmd_queue_create();
    for (i = 0; i < 100; ++i)
    {
        struct cmd_message * msg = (struct cmd_message *)malloc(sizeof(struct cmd_message));
        msg->cmd = 0;
        msg->data = NULL;
        msg->sz = 0;
        msg->next = NULL;

        cmd_queue_push(cq, msg);
    }

    struct cmd_message * msg = cmd_queue_pop(cq);
    while (msg)
    {
        cmd_message_destroy(msg);
        msg = cmd_queue_pop(cq);
    }

    trace("cmd_queue count = %u", cmd_queue_count(cq));

    cmd_queue_destroy(cq);
    trace("销毁 cmd_queue.");

    std_print("-------------------------------");

    g_cmd_queue = cmd_queue_create();
    g_send_queue = send_queue_create();
    g_userlist = userlist_create();

    // 开启接收线程
    pthread_t recv_thread_id = 0;
    if (pthread_create(&recv_thread_id, NULL, &recv_thread, NULL))
    {
        trace("创建接收线程失败.");
        return 1;
    }

    // 开启发送线程
    pthread_t send_thread_id = 0;
    if (pthread_create(&send_thread_id, NULL, &send_thread, NULL))
    {
        trace("创建发送线程失败.");
        return 1;
    }

    // 开启逻辑线程
    pthread_t logic_thread_id = 0;
    if (pthread_create(&logic_thread_id, NULL, &logic_thread, NULL))
    {
        trace("创建逻辑线程失败.");
        return 1;
    }

    pthread_join(recv_thread_id, NULL);
    pthread_join(send_thread_id, NULL);
    pthread_join(logic_thread_id, NULL);

    printf("server close... bye.\n");
    return 0;
}


