

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <libgen.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>



#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

// 将文件描述符设置成非阻塞
int setnoblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

// 将文件描述符fd上的EPOLLIN注册到epollfd指示的epoll内核事件表中
// 参数enable_et指定是否对fd启用ET模式
void addfd(int epollfd, int fd, bool enable_et)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et)
    {
        // 使用ET模式
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnoblocking(fd);
}
// LT模式的工作流程
void lt(struct epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; ++i)
    {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addrlength = sizeof(client_addr);
            int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addrlength);
            addfd(epollfd, connfd, false);// 使用LT模式
        }
        else if (events[i].events & EPOLLIN)
        {
            // 只要socket读缓存中还有未读出的数据，这段代码就被触发
            printf("event trigger once\n");
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
            if (ret < 0)
            {
                close(sockfd);
                continue;
            }
            printf("get %d bytes of contents: %s\n", ret, buf);
        }
        else
        {
            printf("something else happened\n");
        }
    }
}

// ET模式的工作流程
void et(struct epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; ++i)
    {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addrlength = sizeof(client_addr);
            int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addrlength);
            addfd(epollfd, connfd, true);// 使用ET模式
        }
        else if (events[i].events & EPOLLIN)
        {
            // 这段代码不会被重复触发，所以使用循环读取，以确保socket读缓冲区中所有数据读出
            printf("event trigger once\n");
            while (1)
            {
                memset(buf, '\0', BUFFER_SIZE);
                int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                if (ret < 0)
                {
                    // 对于非阻塞I/O，下面的条件成立表示数据已经全部读取完毕
                    // 此后，epoll就能再次触发sockfd上的EPOLLIN事件，以驱动下一次读操作
                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                    {
                        printf("read later\n");
                        break;
                    }
                    close(sockfd);
                    break;
                }
                else if(ret == 0)
                {
                    close(sockfd);
                }
                else
                {
                    printf("get %d bytes of contents: %s\n", ret, buf);                       
                }             
            }
        }
        else
        {
            printf("something else happened\n");
        }
    }
}
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip port\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, listenfd, true);

    while (1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0)
        {
            printf("epoll failure\n");
            break;
        }
        //lt(events, ret, epollfd, listenfd); // 使用LT模式
        et(events, ret, epollfd, listenfd); // 使用ET模式
    }

    close(listenfd);

    return 0;
}