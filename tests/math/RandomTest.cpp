#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>

#include "perception/math/Random.hpp"


TEST(RandomTest, UniformWithinBounds)
{
    perception::math::Random random(42);

    const double min = -10.0;
    const double max = 10.0;

    for (std::size_t i = 0; i < 1000; ++i)
    {
        double value = random.Uniform(min, max);

        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}


TEST(RandomTest, UniformWithPositiveBounds)
{
    perception::math::Random random(42);

    const double min = 5.0;
    const double max = 10.0;

    for (std::size_t i = 0; i < 1000; ++i)
    {
        double value = random.Uniform(min, max);

        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}


TEST(RandomTest, UniformWithNegativeBounds)
{
    perception::math::Random random(42);

    const double min = -10.0;
    const double max = -5.0;

    for (std::size_t i = 0; i < 1000; ++i)
    {
        double value = random.Uniform(min, max);

        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}


TEST(RandomTest, UniformSameBounds)
{
    perception::math::Random random(42);

    const double value = random.Uniform(5.0, 5.0);

    EXPECT_DOUBLE_EQ(value, 5.0);
}


TEST(RandomTest, UniformIntWithinBounds)
{
    perception::math::Random random(42);

    const int min = -10;
    const int max = 10;

    for (std::size_t i = 0; i < 1000; ++i)
    {
        int value = random.Uniform_int(min, max);

        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}


TEST(RandomTest, UniformIntSameBounds)
{
    perception::math::Random random(42);

    const int value = random.Uniform_int(5, 5);

    EXPECT_EQ(value, 5);
}


TEST(RandomTest, UniformIntCanGenerateBothBounds)
{
    perception::math::Random random(42);

    const int min = 0;
    const int max = 10;

    bool found_min = false;
    bool found_max = false;

    for (std::size_t i = 0; i < 10000; ++i)
    {
        int value = random.Uniform_int(min, max);

        if (value == min)
        {
            found_min = true;
        }

        if (value == max)
        {
            found_max = true;
        }

        if (found_min && found_max)
        {
            break;
        }
    }

    EXPECT_TRUE(found_min);
    EXPECT_TRUE(found_max);
}


TEST(RandomTest, GaussianSamplesHaveExpectedMean)
{
    perception::math::Random random(42);

    const double mean = 10.0;
    const double stddev = 2.0;

    const std::size_t sample_count = 10000;

    double sum = 0.0;

    for (std::size_t i = 0; i < sample_count; ++i)
    {
        sum += random.Gaussian(mean, stddev);
    }

    const double sample_mean = sum / sample_count;

    EXPECT_NEAR(sample_mean, mean, 0.1);
}


TEST(RandomTest, GaussianSamplesHaveExpectedStandardDeviation)
{
    perception::math::Random random(42);

    const double mean = 10.0;
    const double stddev = 2.0;

    const std::size_t sample_count = 10000;

    double sum = 0.0;

    for (std::size_t i = 0; i < sample_count; ++i)
    {
        sum += random.Gaussian(mean, stddev);
    }

    const double sample_mean = sum / sample_count;

    double squared_difference_sum = 0.0;

    for (std::size_t i = 0; i < sample_count; ++i)
    {
        double value = random.Gaussian(mean, stddev);
        double difference = value - sample_mean;

        squared_difference_sum += difference * difference;
    }

    const double variance = squared_difference_sum / sample_count;
    const double sample_stddev = std::sqrt(variance);

    EXPECT_NEAR(sample_stddev, stddev, 0.1);
}


TEST(RandomTest, SameSeedProducesSameSequence)
{
    perception::math::Random random_a(42);
    perception::math::Random random_b(42);

    for (std::size_t i = 0; i < 100; ++i)
    {
        EXPECT_DOUBLE_EQ(
            random_a.Uniform(-10.0, 10.0),
            random_b.Uniform(-10.0, 10.0));
    }
}


TEST(RandomTest, DifferentSeedsProduceDifferentSequence)
{
    perception::math::Random random_a(42);
    perception::math::Random random_b(123);

    bool found_difference = false;

    for (std::size_t i = 0; i < 100; ++i)
    {
        if (random_a.Uniform(-10.0, 10.0) !=
            random_b.Uniform(-10.0, 10.0))
        {
            found_difference = true;
            break;
        }
    }

    EXPECT_TRUE(found_difference);
}

