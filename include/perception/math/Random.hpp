#pragma once

#include <random>
#include <cstdint>

namespace perception::math
{
/**
 * @brief Thin wrapper class around std::mt19937 random number generator
 * to create unformly distributed real & integer random numbers.
 */
class Random
{
public:
    /**
     * @brief Default constructor
     */
    Random()
      : m_engine(std::random_device{}())
    {
    }

    /**
     * @brief Constructor to build random number generator with
     * specified seed value. Marked explicit to force use of uint32_t 
     * input parameter
     */
    explicit Random(uint32_t seed)
      : m_engine(seed)
    {
    }

    /**
     * @brief Return a random integer within specified min/max. If 
     * observing a collection of these numbers they will be unformily
     * distributed
     */
    inline int Uniform_int(int min, int max)
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(m_engine);
    }

    /**
     * @brief Return a random double within specifed min/max. If 
     * observing a collection of these numbers they will be unformily
     * distributed
     */
    inline double Uniform(double min, double max)
    {
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(m_engine);
    }

    /**
     * @brief Return a random double falling withing the specified mean and 
     * standard deviation - following a gaussian distribution.
     */
    inline double Gaussian(double mean, double std_deviation)
    {
        std::normal_distribution<double> distribution(mean, std_deviation);
        return distribution(m_engine);
    }

private:
    /**
     * @brief Merssene Twister random number generator engine
     */
    std::mt19937 m_engine;
};
}