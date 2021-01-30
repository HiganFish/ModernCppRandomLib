#pragma once

#include <random>

/**
 * @brief 随机数产生引擎, 用于统一随机数产生源
*/
class RandomDataSource
{
public:

    /**
     * @brief 使用真随机数产生种子
    */
    RandomDataSource();

    /**
     * @brief 自定义种子
     * @param seed 种子值
    */
    RandomDataSource(unsigned int seed);

    /**
     * @brief 获取核心的均匀随机数引擎mt19937
     * @return 随机数引擎
    */
    std::mt19937& GetEngine();

    RandomDataSource(const RandomDataSource&) = delete;
    RandomDataSource& operator=(const RandomDataSource&) = delete;
private:

    std::mt19937 engine_;
};
