

#include <sys/socket.h>
#include <netinet/in.h> // INET_ADDRSTRLEN
#include <arpa/inet.h> // 地址转化函数
#include <signal.h>
#include <libgen.h> // basename()

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h> 
#include <stdbool.h>



static bool stop = false;
// SIGTERM 信号的处理函数。触发时结束主程序的循环
static void handle_term(int sig)
{
    stop = true;
}

int main(int argc, char *argv[])
{

    signal(SIGTERM, handle_term);
    if (argc <= 3)
    {
        printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // 创建一个IPv4地址结构体
    struct sockaddr_in address;
    //bzero(&address, sizeof(address));
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, backlog);
    assert(ret != -1);

    // 循环等待连接，知道SIGTERM信号将它中断
    while (!stop)
    {
        sleep(1);
    }
    // 关闭socket
    close(sock);
    return 0;
}