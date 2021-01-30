#include <iostream>

#include "RandomEngine.h"
#include "RandomDataSource.h"

int times[3] = {0, 0, 0};

void EventCallbackA(std::any* arg)
{
    times[0] += std::any_cast<int>(*arg);
}

void EventCallbackB(std::any* arg)
{
    times[1] += std::any_cast<int>(*arg);
}

void EventCallbackC(std::any* arg)
{
    times[2] += std::any_cast<int>(*arg);
}

int main()
{
    // 随机数源
    RandomDataSource source;

    // 随机事件集合 概率精度为1% 概率和为70
    RandomEngine engine(&source, 70);


    // 事件A 概率为 1/70
    Event eventa(1, EventCallbackA);
    engine.Add("A", eventa);
    // 事件B 概率为 40/70
    engine.Add("B", { 40, EventCallbackB });
    // 事件C 概率为 29/70
    engine.Add("C", { 29, EventCallbackC });

    // 检查定义的概率和70 1 + 40 + 29
    if (!engine.Check())
    {
        exit(-1);
    }

    // 回调函数参数, 可用于从回调函数中带回返回内容 或者 传入参数
    int rate = 1;
    std::any arg = rate;

    // 随机70W次事件调度
    for (int i = 0; i < 70 * 10000; ++i)
    {
        engine.RandomCall(&arg);
    }

    /**
    * $ 9973
    * $ 398933
    * $ 291094
    */
    for (int i = 0; i < 3; ++i)
    {
        std::cout << times[i] << std::endl;
    }

    return 0;
}