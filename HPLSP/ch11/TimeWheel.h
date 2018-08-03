

#ifndef TIME_WHEEL_H
#define TIME_WHEEL_H

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 64

class tw_timer;
// 绑定socket和定时器
struct client_data
{
    struct sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer* timer;
};

// 定时器类
class tw_timer
{
public:
    tw_timer(int rot, int ts)
        : rotation(rot), time_slot(ts), 
        cb_func(NULL), user_data(NULL),
        next(NULL), prev(NULL) {}
public:
    int rotation; // 记录定时器在时间轮转多少圈后生效
    int time_slot; // 记录定时器属于时间轮上哪个槽（对应的链表）
    void (*cb_func)(client_data*); // 定时器回调函数
    client_data* user_data; // 客户数据
    tw_timer* next; // 指向下一个定时器
    tw_timer* prev; // 指向前一个定时器
};

class time_wheel
{
public:
    time_wheel()
        : cur_slot(0)
    {
        for (int i = 0; i < N; ++i)
        {
            // 初始化每个槽的头节点
            slots[i] = NULL;
        }
    }
    ~time_wheel()
    {
        // 遍历每个槽，并销毁其中的定时器
        for (int i = 0; i < N; ++i)
        {
            tw_timer* slotsHead = slots[i];
            while (slotsHead)
            {
                slots[i] = slotsHead->next;
                delete slotsHead;
                slotsHead = slots[i];
            }
        }
    }

    // 根据定时值timeout创建一个定时器，并把它插入到合适的槽中
    tw_timer* add_timer(int timeout)
    {
        if (timeout < 0)
            return NULL;
        
        int ticks = 0;
        // 根据超时时间计算它将在时间轮转动多少滴答后被触发，并将该滴答存储在ticks
        // 如果超时时间小于时间轮的间隔SI，则取为1，否则向下取为 timeout/SI
        if (timeout < SI)
            ticks = 1;
        else
            ticks = timeout/SI;
        // 计算传入的定时时间在时间轮转动多少圈后触发
        int rotation = ticks / N;
        // 计算待插入的定时器应该被插入到哪个槽中
        int ts = (cur_slot + (ticks%N)) % N;
        // 创建新的定时器
        tw_timer* timer = new tw_timer(rotation, ts);

        // 如果第ts个槽中没有定时器，则将新创建的定时器插入其中，并设置为头节点
        if (!slots[ts])
        {
            printf("add timer, rotation is %d, ts is %d, cur_slot is %d\n",
                        rotation, ts, cur_slot);
            slots[ts] timer;
        }
        else // 否则将定时器插入到第ts个槽中
        {
            // 头插法
            timer->next = slots[i];
            slots[ts]->prev = timer;
            slots[ts] = timer;
        }
        return timer;
    }

    // 删除目标定时器
    void del_timer(tw_timer* timer)
    {
        if (!timer)
            return;
        int ts = timer->time_slot;
        // 如果slots[ts]是目标定时器所在槽的头节点，并且就是该目标定时器，则重新设置新的头节点
        if (timer == slots[ts])
        {
            slots[ts] = slots[ts]->next;
            if (slots[ts])
                slots[ts]->prev = NULL;
            delete timer;
        }
        else 
        {
            timer->prev->next = timer->next;
            if (timer->next)
                timer->next->prev = timer->prev;
            delete timer;
        }
    }

    // SI时间到后调用该函数,时间轮向前滚动一个槽时间
    void ticks()
    {
        tw_timer* headSlots = slots[cur_slot];
        printf("current slot is %d \n", cur_slot);
        while (headSlots)
        {
            printf("tick the timer once\n");
            // 如果定时器的rotation值大于0，则它在这一轮不起作用
            if (headSlots->rotation > 0)
            {
                headSlots->rotation--;
                headSlots = headSlots->next;
            }
            else // 否则说明定时器以到期，执行定时回调函数 
            {
                headSlots->cb_func(headSlots->user_data);
                if (headSlots == slots[cur_slot])
                {
                    printf("delete header in cur_slots\n");
                    slots[cur_slot] = headSlots->next;
                    delete headSlots;
                    if (slots[cur_slot])
                        slots[cur_slot]->prev = NULL;
                    headSlots = slots[cur_slot];
                }
                else 
                {
                    headSlots->prev->next = headSlots->next;
                    if (headSlots->next)
                        headSlots->next->prev = headSlots->prev;

                    tw_timer* headSlotsNext = headSlots->next;
                    delete headSlots;
                    headSlots = headSlotsNext; 
                }
            }
        }
    }

private:
     static const int N = 60; // 时间轮上槽的数目
     static const int SI = 1; // 每1s时间轮转动一次，即槽间隔为1s
     tw_timer* slots[N]; // 时间轮的槽，其中每个元素指向一个定时器链表，链表无序
     int cur_slot; // 时间轮的当前槽
};

#endif