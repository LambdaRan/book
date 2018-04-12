

#include <sys/socket.h>
#include <netinet/in.h> // INET_ADDRSTRLEN
#include <arpa/inet.h> // 地址转化函数
#include <libgen.h> // basename()

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h> 
#include <stdbool.h>
#include <errno.h>

int main(int argc, char *argv[])
{

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

    // 暂停20秒以等待客户连接和相关操作
    sleep(20);
    struct sockaddr_in client;
    socklen_t client_addrlen = sizeof(client);
    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlen);
    if (connfd < 0)
    {
        printf("errno is : %d\n", errno);
    }
    else 
    {
        //　接收连接成功打印客户端ＩＰ地址和端口号
        char remote[INET_ADDRSTRLEN];
        printf("connected: with ip: %s and port: %d \n",
            inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client.sin_port));
        close(connfd);
    }
    // 关闭socket
    close(sock);
    return 0;
}