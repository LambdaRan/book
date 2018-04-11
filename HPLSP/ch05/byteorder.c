#include <stdio.h>

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
