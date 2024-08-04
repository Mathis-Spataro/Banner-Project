#ifndef COLOR_H
#define COLOR_H
#include <MathCore.h>
#include <ostream>

namespace Geometry
{
    class Color
    {
    public:
        // --- Constructors --- //

        Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
        explicit Color(const float (&values)[3]) : r(values[0]), g(values[1]), b(values[2]), a(1.0f) {}
        explicit Color(const float (&values)[4]) : r(values[0]), g(values[1]), b(values[2]), a(values[3]) {}
        Color(const float& red, const float& green, const float& blue) : r(red), g(green), b(blue), a(1.0f) {}
        Color(const float& red, const float& green, const float& blue, const float& alpha) : r(red), g(green), b(blue), a(alpha) {}
        Color(const Color& other) = default;
        Color& operator=(const Color& other) = default;


        // --- data --- //

        float r, g, b, a;


        // --- Comparators --- //

        bool operator == (const Color& other) const {
            return MathCore::floatEQ(r, other.r) &&
                   MathCore::floatEQ(g, other.g) &&
                   MathCore::floatEQ(b, other.b) &&
                   MathCore::floatEQ(a, other.a) ;
        }

        bool operator != (const Color& other) const {
            return MathCore::floatNEQ(r, other.r) ||
                   MathCore::floatNEQ(g, other.g) ||
                   MathCore::floatNEQ(b, other.b) ||
                   MathCore::floatNEQ(a, other.a) ;
        }


        // --- Color and Color Arithmetics --- //

        Color operator+(const Color& other) const {
            return {r + other.r, g + other.g, b + other.b, a + other.a};
        }

        Color operator-(const Color& other) const {
            return {r - other.r, g - other.g, b - other.b, a - other.a};
        }

        Color operator*(const float& scalar) const {
            return {r * scalar, g * scalar, b * scalar, a * scalar};
        }

        friend Color operator*(const float& scalar, const Color& c) {
            return {c.r * scalar, c.g * scalar, c.b * scalar, c.a * scalar};
        }

        Color operator/(const float& scalar) const {
            return {r / scalar, g / scalar, b / scalar, a / scalar};
        }


        // --- Inplace Arithmetics --- //

        Color& operator+=(const Color& other) {
            r += other.r;
            g += other.g;
            b += other.b;
            a += other.a;
            return (*this);
        }

        Color& operator-=(const Color& other) {
            r -= other.r;
            g -= other.g;
            b -= other.b;
            a -= other.a;
            return (*this);
        }

        Color& operator*=(const float& scalar) {
            r *= scalar;
            g *= scalar;
            b *= scalar;
            a *= scalar;
            return (*this);
        }

        Color& operator/=(const float& scalar) {
            r /= scalar;
            g /= scalar;
            b /= scalar;
            a /= scalar;
            return (*this);
        }

    };

    inline std::ostream& operator<<(std::ostream& os, const Color& Color) {
        os << "color(" << Color.r << ", " << Color.g << ", " << Color.b << ", " << Color.a << ")";
        return os;
    }
}


#endif //COLOR_H
