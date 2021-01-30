#pragma once

#include <random>
#include <functional>
#include <map>
#include <any>

class RandomDataSource;

/**
 * @brief 概率事件
*/
struct Event
{
    typedef std::function<void(std::any*)> EventCallback;

    Event() = default;

    Event(unsigned int probability, const EventCallback& event_callback) :
        probability_(probability),
        event_callback_(event_callback)
    {
    }

    /**
     * @brief 事件概率 根据事件的精度决定 若精度为0.1%则事件概率和为1000
    */
    unsigned int probability_;

    /**
     * @brief 事件回调函数
    */

    EventCallback event_callback_;
};

/**
 * @brief 随机事件集合调度类
*/
class RandomEngine
{
public:

    /**
     * @brief 创建 随机事件集合调度类
     * @param data_source 随机数源
     * @param probability_sum 随机事件概率和 根据事件的精度决定 若精度为0.1%则事件概率和为1000
    */
    RandomEngine(RandomDataSource * data_source, unsigned int probability_sum);

    /**
     * @brief 添加随机事件
     * @param event_name 唯一随机事件名
     * @param event 随机事件
    */
    void Add(const std::string& event_name, const Event& event);

    /**
     * @brief 检查概率和 并 初始化 随机事件集合调度类
     * @return false 概率和不等于probability_sum true 概率检查通过并初始化
    */
    bool Check();

    /**
     * @brief 随机调度一次事件 使用自定义参数
     * @param arg 
    */
    void RandomCall(std::any* arg);

private:

    RandomDataSource* data_source_;

    unsigned int probability_sum_;

    std::uniform_int_distribution<unsigned int> dist_;

    std::map<std::string, Event> event_map_;

    /**
     * @brief 从随机数引擎获得随机数
     * @return 
    */
    unsigned int GetRandomUnsignedInt();

    /**
     * @brief 检查事件概率和
     * @return true检查通过
    */
    bool CheckProbabilitySum();

    const Event& GetEventRandom();
};