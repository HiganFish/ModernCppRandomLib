#include <cassert>

#include "RandomDataSource.h"
#include "RandomEngine.h"

RandomEngine::RandomEngine(RandomDataSource * data_source, unsigned int probability_sum):
    data_source_(data_source),
    probability_sum_(probability_sum),
    dist_(1, probability_sum)
{

}

void RandomEngine::Add(const std::string& event_name, const Event& event)
{
    event_map_[event_name] = event;
}

bool RandomEngine::Check()
{
    if (!CheckProbabilitySum())
    {
        return false;
    }
}

void RandomEngine::RandomCall(std::any* arg)
{
    const Event& event = GetEventRandom();

    event.event_callback_(arg);
}

unsigned int RandomEngine::GetRandomUnsignedInt()
{
    assert(data_source_);
    
    return dist_(data_source_->GetEngine());
}

bool RandomEngine::CheckProbabilitySum()
{
    int sum_temp = 0;

    for (const auto&[event_name, event] : event_map_)
    {
        sum_temp += event.probability_;
    }

    return sum_temp == probability_sum_;
}

const Event& RandomEngine::GetEventRandom()
{
    unsigned int value = GetRandomUnsignedInt();

    for (const auto& [event_name, event] : event_map_)
    {
        if (value > event.probability_)
        {
            value -= event.probability_;
        }
        else
        {
            return event;
        }
    }
}
