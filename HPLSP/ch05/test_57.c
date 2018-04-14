

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>


#include <libgen.h> // basename()
#include <sys/types.h>
#include <sys/socket.h> // socket()
#include <netinet/in.h> // struct sockaddr_in INET_ADDRSTRLEN
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

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

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connectfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (connectfd < 0)
    {
        printf("Connect errno is: %d\n", errno);
    }
    else  
    {
        char buffer[BUF_SIZE];

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connectfd, buffer, BUF_SIZE-1, 0);
        printf("got %d bytes of normal data '%s' \n", ret, buffer);

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connectfd, buffer, BUF_SIZE-1, MSG_OOB);
        printf("got %d bytes of oob data '%s' \n", ret, buffer);

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connectfd, buffer, BUF_SIZE-1, 0);
        printf("got %d bytes of normal data '%s' \n", ret, buffer);

        close(connectfd);
    }

    close(sock);
    return 0;
}