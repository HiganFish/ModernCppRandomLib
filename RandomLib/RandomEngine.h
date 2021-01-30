#pragma once

#include <random>
#include <functional>
#include <map>
#include <any>

class RandomDataSource;

/**
 * @brief �����¼�
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
     * @brief �¼����� �����¼��ľ��Ⱦ��� ������Ϊ0.1%���¼����ʺ�Ϊ1000
    */
    unsigned int probability_;

    /**
     * @brief �¼��ص�����
    */

    EventCallback event_callback_;
};

/**
 * @brief ����¼����ϵ�����
*/
class RandomEngine
{
public:

    /**
     * @brief ���� ����¼����ϵ�����
     * @param data_source �����Դ
     * @param probability_sum ����¼����ʺ� �����¼��ľ��Ⱦ��� ������Ϊ0.1%���¼����ʺ�Ϊ1000
    */
    RandomEngine(RandomDataSource * data_source, unsigned int probability_sum);

    /**
     * @brief �������¼�
     * @param event_name Ψһ����¼���
     * @param event ����¼�
    */
    void Add(const std::string& event_name, const Event& event);

    /**
     * @brief �����ʺ� �� ��ʼ�� ����¼����ϵ�����
     * @return false ���ʺͲ�����probability_sum true ���ʼ��ͨ������ʼ��
    */
    bool Check();

    /**
     * @brief �������һ���¼� ʹ���Զ������
     * @param arg 
    */
    void RandomCall(std::any* arg);

private:

    RandomDataSource* data_source_;

    unsigned int probability_sum_;

    std::uniform_int_distribution<unsigned int> dist_;

    std::map<std::string, Event> event_map_;

    /**
     * @brief ������������������
     * @return 
    */
    unsigned int GetRandomUnsignedInt();

    /**
     * @brief ����¼����ʺ�
     * @return true���ͨ��
    */
    bool CheckProbabilitySum();

    const Event& GetEventRandom();
};