#显示所有警告
CXXFLAGS += -Wall -Wextra -std=c++11
#CXXFLAGS +=  -Werror -Wfatal-errors
#-std=c++0x
#CFLAG += -O #基本优化
# -g选项，产生供gdb调试用的可执行文件
CC = g++

PROJECT = main
SYSLIB = 

OBJDIR = .
#SRCS = $(wildcard ./*.c)
SRCDIR = ch18
SRCS = $(SRCDIR)/mergeSort.cpp



 #指定头文件目录，代码中就不需要把头文
INCLUDE_DIRS = -I. 
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(PROJECT):$(OBJS)
	$(CC) -o $@ $^ $(CXXFLAGS) $(SYSLIB)
#	mv $(OBJS_BASE) $(OBJDIR)                         
$(OBJS):%.o:%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_DIRS)

test:test.cpp
	$(CC) $(CXXFLAGS) test.cpp -o main	
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o  $(SRCDIR)/*.o $(PROJECT)


# SRC = test.cpp 
# SRC += Rational_1.cpp
# SRC += MemoryPool.cpp

# main:$(SRC) 
# 	$(CC) $(CFLAG)  $(SRC) -o main
# test:test.cpp
# 	$(CC) $(CFLAG)  test.cpp -o main	
# .PHONY:clean
# clean:
# 	rm -f *.o main

