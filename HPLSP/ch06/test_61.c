

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>


#include <libgen.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("Usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);


    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr *)&client, &client_addrlength);
    if (connfd < 0)
    {
        printf("errno is : %d\n", errno);
    }
    else  
    {
        close(STDOUT_FILENO);
        dup(connfd);
        printf("abcd\n");
        close(connfd);
    }
    close(sockfd);
    
    return 0;
}