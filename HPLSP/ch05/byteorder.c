#include <stdio.h>


// 小端字节序又被称为主机字节序
// 大端字节序－－》网络字节序

// 主机字节序与网络字节序之间的转换函数
// #include <netinet/in.h>
// unsigned long int htonl(unsigned long int hostlong);
// unsigned short int htons(unsigned short int hostshort);
// unsigned long int ntohl(unsigned long int netlong);
// unsigned short int ntohs(unsigned short int netshort);

void byteorder()
{
    union 
    {
        short value;
        char union_bytes[sizeof(short)];
    } test;

    test.value = 0x0102;
    // 大端　高位字节在低地址　　低位字节在高地址
    if ((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    {
        printf("big endian \n");
    }
    // 小端　高位字节在高地址　　低位字节在低地址
    else if ((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
    {
        printf("little endian \n");
    }
    else 
    {
        printf("unknown... \n");
    }
}

int main(void)
{
    printf("check byte order...\n");
    byteorder();
    return 0;
}
