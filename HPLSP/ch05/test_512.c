
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    assert(argc == 2);
    char *host = argv[1];
    // 获得目标主机的地址信息
    struct hostent *hostinfo = gethostbyname(host);
    assert(hostinfo);

    // 获取daytime服务信息
    struct servent *serverinfo = getservbyname("daytime", "tcp");
    assert(serverinfo);
    printf("daytime port is: %d\n", ntohs(serverinfo->s_port));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = serverinfo->s_port;
    // 注意下面的代码，因为h_addr_list本身是使用网络字节序的地址列表，所以
    // 使用其中的IP地址时，无需对目标ip地址转换字节序
    address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    assert(result != -1);

    char buffer[128];
    result = read(sockfd, buffer, sizeof(buffer));
    assert(result > 0);
    buffer[result] = '\0';
    printf("the day time is: %s", buffer);
    close(sockfd);
    
    return 0;
}