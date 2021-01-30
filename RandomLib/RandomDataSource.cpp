
#include "RandomDataSource.h"

std::random_device dv;

RandomDataSource::RandomDataSource():
    engine_(dv())
{
}


RandomDataSource::RandomDataSource(unsigned int seed):
    engine_(seed)
{
}

std::mt19937& RandomDataSource::GetEngine()
{
    return engine_;
}


