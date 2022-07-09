// mathematics.cpp:
#include "mathematics.h"

namespace Math
{
    std::normal_distribution<double>::result_type normrnd(const double mean, const double sigma)
    {
        static std::random_device rd;
        static std::mt19937 generator( rd() );

        std::normal_distribution<double> normrand( mean, sigma );
        return normrand( generator );
    }
}
