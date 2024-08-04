#ifndef MATRIX_H
#define MATRIX_H
#include <Vector.h>

namespace Geometry {

    class Matrix {
    public:
        // --- Constructors --- //

        Matrix();
        explicit Matrix(const float (&values)[16]);
        explicit Matrix(const float (&values)[4][4]);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);


        // --- Data --- //

        alignas(64) float data[16]; // x64_86 specific. Row major order.


        // --- Operators --- //

        [[nodiscard]] Matrix operator*(const Matrix& other) const;
        [[nodiscard]] Vector operator*(const Vector& vec) const;
        friend Vector operator*(const Vector& vtx, const Matrix& mat);  // can't no discard a friend class and want to keep the order of arguments.


        // --- Accessors --- //

        [[nodiscard]] const float& operator () (const int& i, const int& j) const { return data[i*4 + j]; }
        float &operator () (const int& i, const int& j) { return data[i*4 + j]; }


        // --- Matrix maths --- //

        [[nodiscard]] Matrix Transpose() const;
        [[nodiscard]] Matrix Inverse() const;


        // --- Common matrices --- //

        [[nodiscard]] static Matrix Identity();
        [[nodiscard]] static Matrix RotationX(const float& angle);
        [[nodiscard]] static Matrix RotationY(const float& angle);
        [[nodiscard]] static Matrix RotationZ(const float& angle);
        [[nodiscard]] static Matrix Rotation(const Vector& axis, const float& angle);
        [[nodiscard]] static Matrix Translation(const float& tx, const float& ty, const float& tz);
        // /!\ : effective only if object is centered around the origin.
        [[nodiscard]] static Matrix Scaling(const float& sx, const float& sy, const float& sz);
        [[nodiscard]] static Matrix Perspective(const float& fov_y, const float& near, const float& far);

    };


} // Geometry

#endif //MATRIX_H
