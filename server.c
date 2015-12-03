#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "user.h"
#include "userlist.h"
#include "print_utils.h"

#define LOGIN       1   // 登录
#define LOGOUT      2   // 登出
#define MESSAGE     3   // 发送消息给各位
#define USERLUST    4   // 用户列表

static struct cmd_queue * g_cmd_queue = NULL;
static struct send_queue * g_send_queue = NULL;
static struct userlist * g_userlist = NULL;

int main(void)
{
    trace("launch chatroom server...");
    trace("close chatroom server...");
    return 0;
}


