
#显示所有警告
CFLAG += -Wall -Wextra -std=c++0x
#CFLAG += -O #基本优化
# -g选项，产生供gdb调试用的可执行文件
CC = g++

#INCLUDE = -I./simple/

SRC =test04.cpp

main:$(SRC) 
	$(CC) $(CFLAG)  $(SRC) -o main

test:test.cpp
	$(CC) $(CFLAG)  test.cpp -o main
.PHONY:clean
clean:
	rm -f *.o main

