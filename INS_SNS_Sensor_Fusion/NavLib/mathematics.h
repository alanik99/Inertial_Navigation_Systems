// mathematics.h:
#pragma once

#include <random>

namespace Math
{
    std::normal_distribution<double>::result_type normrnd(const double mean, const double sigma);
}

