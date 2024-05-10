#pragma once
#include <random>
#include <cstdint>

class Rand
{
private:
    std::mt19937 mt;
    std::random_device rd;

public:
    Rand() { mt.seed(rd()); }

    void seed()
    {
        mt.seed(rd());
    }
    void seed(const std::uint_fast32_t seed_)
    {
        mt.seed(seed_);
    }

    unsigned int trueRand()
    {
        return rd();
    }
    std::uint_fast32_t operator()()
    {
        return mt();
    }
    std::int_fast32_t operator()(const std::int_fast32_t max_)
    {
        std::uniform_int_distribution<> uid(0, ((max_ > 0) ? (std::int_fast32_t)max_ - 1 : 0));
        return uid(mt);
    }
};
static thread_local Rand rnd;