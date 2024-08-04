#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>
#include <MathCore.h>

namespace Geometry {

    class Vector {
    public :
        // --- Constructors --- //

        Vector() : pos(0.0f, 0.0f, 0.0f, 0.0f) {}

        explicit Vector(const float (&values)[3]) : pos(values[0], values[1], values[2], 0.0f) {}
        explicit Vector(const float (&values)[4]) : pos(values[0], values[1], values[2], values[3]) {}

        Vector(const float& x, const float& y, const float& z) : pos(x, y, z, 0.0f) {}
        Vector(const float& x, const float& y, const float& z, const float& w) : pos(x, y, z, w) {}

        Vector(const Vector& other) = default;
        Vector& operator=(const Vector& other) = default;


        // --- Data --- //

        alignas(16) float pos[4];


        // --- Accessors --- //

        const float& operator [] (const int& i) const { return pos[i]; }
        float& operator [] (const int& i) { return pos[i]; }

        [[nodiscard]] const float& x() const { return pos[0]; }
        float& x() { return pos[0]; }
        [[nodiscard]] const float& y() const { return pos[1]; }
        float& y() { return pos[1]; }
        [[nodiscard]] const float& z() const { return pos[2]; }
        float& z() { return pos[2]; }
        [[nodiscard]] const float& w() const { return pos[3]; }
        float& w() { return pos[3]; }


        // --- Comparators --- //
        // For relative closeness use MathCore::is_close().
        // inf, -inf and NaN not supported by == and != operators.

        bool operator == (const Vector& other) const {
            return MathCore::floatEQ(pos[3], other.pos[3]) &&
                   MathCore::floatEQ(pos[2], other.pos[2]) &&
                   MathCore::floatEQ(pos[1], other.pos[1]) &&
                   MathCore::floatEQ(pos[0], other.pos[0]) ;
        }

        bool operator != (const Vector& other) const {
            return MathCore::floatNEQ(pos[3], other.pos[3]) ||
                   MathCore::floatNEQ(pos[2], other.pos[2]) ||
                   MathCore::floatNEQ(pos[1], other.pos[1]) ||
                   MathCore::floatNEQ(pos[0], other.pos[0]) ;
        }


        // --- Arithmetics --- //

        Vector operator + (const Vector& other) const {
            return {pos[0] + other.pos[0], pos[1] + other.pos[1], pos[2] + other.pos[2]};
        }

        Vector operator - (const Vector& other) const {
            return {pos[0] - other.pos[0], pos[1] - other.pos[1], pos[2] - other.pos[2]};
        }

        Vector operator - () const {
            return {-pos[0], -pos[1], -pos[2]};
        }

        Vector operator * (const float& scalar) const {
            return {pos[0] * scalar, pos[1] * scalar, pos[2] * scalar, pos[3] * scalar};
        }

        friend Vector operator * (const float& scalar, const Vector& v) {
            return {v.pos[0] * scalar, v.pos[1] * scalar, v.pos[2] * scalar, v.pos[3] * scalar};
        }

        Vector operator / (const float& scalar) const {
            return {pos[0] / scalar, pos[1] / scalar, pos[2] / scalar, pos[3] / scalar};
        }


        // --- inplace arithmetics --- //

        Vector& operator += (const Vector& other) {
            this->pos[0] += other.pos[0];
            this->pos[1] += other.pos[1];
            this->pos[2] += other.pos[2];
            this->pos[3] += other.pos[3];
            return *this;
        }

        Vector& operator -= (const Vector& other) {
            this->pos[0] -= other.pos[0];
            this->pos[1] -= other.pos[1];
            this->pos[2] -= other.pos[2];
            this->pos[3] -= other.pos[3];
            return *this;
        }

        Vector& operator *= (const float& scalar) {
            this->pos[0] *= scalar;
            this->pos[1] *= scalar;
            this->pos[2] *= scalar;
            this->pos[3] *= scalar;
            return *this;
        }

        Vector& operator /= (const float& scalar) {
            this->pos[0] /= scalar;
            this->pos[1] /= scalar;
            this->pos[2] /= scalar;
            this->pos[3] /= scalar;
            return *this;
        }
        


        // --- Vector maths --- //

        [[nodiscard]] float norm() const {
            return sqrtf(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
        }

        [[nodiscard]] Vector normalized() const {
            float const magnitude = sqrtf(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
            if (magnitude < MathCore::EPSILON) {
                // Avoid division by zero, return a copy of the zero vector.
                return {0.0, 0.0, 0.0};
            }
            return {pos[0]/magnitude, pos[1]/magnitude, pos[2]/magnitude, pos[3]/magnitude};
        }

        [[nodiscard]] float dot(const Vector& other) const {
            return pos[0] * other.pos[0] + pos[1] * other.pos[1] + pos[2] * other.pos[2];
        }

        [[nodiscard]] Vector cross(const Vector& other) const {
            return {
                pos[1] * other.pos[2] - pos[2] * other.pos[1],
                pos[2] * other.pos[0] - pos[0] * other.pos[2],
                pos[0] * other.pos[1] - pos[1] * other.pos[0],
                0.0f
            };
        }

        [[nodiscard]] Vector perspectiveDivision() const {
            if (MathCore::floatEQ(pos[3], 1.0f) || MathCore::floatEQ(pos[3], 0.0f))
                return Vector(pos);
            return {pos[0] / pos[3], pos[1] / pos[3], pos[2] / pos[3], 1.0f};
        }

    };  // Vector

    inline std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "vec(" << vector.pos[0] << ", " << vector.pos[1] << ", " << vector.pos[2] << ", " << vector.pos[3] << ")";
        return os;
    }

} // Geometry

#endif //VECTOR_H
