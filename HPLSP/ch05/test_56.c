


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

    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number \n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Connection failed\n");
    }
    else 
    {
        const char *oob_data = "abc";
        const char *normal_data = "123";

        send(sockfd, normal_data, strlen(normal_data), 0);
        send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
        send(sockfd, normal_data, strlen(normal_data), 0);
    }

    // 关闭socket
    close(sockfd);
    return 0;
}