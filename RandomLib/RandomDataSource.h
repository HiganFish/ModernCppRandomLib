#pragma once

#include <random>

/**
 * @brief �������������, ����ͳһ���������Դ
*/
class RandomDataSource
{
public:

    /**
     * @brief ʹ�����������������
    */
    RandomDataSource();

    /**
     * @brief �Զ�������
     * @param seed ����ֵ
    */
    RandomDataSource(unsigned int seed);

    /**
     * @brief ��ȡ���ĵľ������������mt19937
     * @return ���������
    */
    std::mt19937& GetEngine();

    RandomDataSource(const RandomDataSource&) = delete;
    RandomDataSource& operator=(const RandomDataSource&) = delete;
private:

    std::mt19937 engine_;
};
