#ifndef MATHCORE_H
#define MATHCORE_H
#include <cmath>

namespace MathCore
{
    constexpr float EPSILON = 1e-6f;
    constexpr float NEG_EPSILON = -EPSILON;

    // relative closeness
    bool inline is_close(const float& a, const float& b, const float& relative_tolerance = EPSILON) {
        return std::abs(a - b) <=
            (relative_tolerance * std::max(std::abs(a), std::abs(b))
            + std::numeric_limits<float>::min());
    }

    // relative closeness
    bool inline is_close(const float arr1[], const float arr2[], const int& arrays_length = 3) {
        for(unsigned i=0; i < arrays_length; i++)
        {
            if (!is_close(arr1[i], arr2[i])){
                return false;
            }
        }
        return true;
    }

    bool inline floatEQ(const float& a, const float& b)
    {
        const float diff = a - b;
        return diff > NEG_EPSILON && diff < EPSILON;
    }

    bool inline floatNEQ(const float& a, const float& b)
    {
        const float diff = a - b;
        return diff < NEG_EPSILON || diff > EPSILON;
    }

}

#endif //MATHCORE_H
