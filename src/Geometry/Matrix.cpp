#include <iostream>
#include <Matrix.h>
#include <MathCore.h>
#include <valarray>

namespace Geometry {

    static bool InvertMatrix(const Matrix& mat, Matrix& invMat) {  // From MESA implementation of the GLU library. Adjugate method.
        float inv[16];

        inv[0] = mat.data[5]  * mat.data[10] * mat.data[15] -
                 mat.data[5]  * mat.data[11] * mat.data[14] -
                 mat.data[9]  * mat.data[6]  * mat.data[15] +
                 mat.data[9]  * mat.data[7]  * mat.data[14] +
                 mat.data[13] * mat.data[6]  * mat.data[11] -
                 mat.data[13] * mat.data[7]  * mat.data[10];

        inv[4] = -mat.data[4]  * mat.data[10] * mat.data[15] +
                  mat.data[4]  * mat.data[11] * mat.data[14] +
                  mat.data[8]  * mat.data[6]  * mat.data[15] -
                  mat.data[8]  * mat.data[7]  * mat.data[14] -
                  mat.data[12] * mat.data[6]  * mat.data[11] +
                  mat.data[12] * mat.data[7]  * mat.data[10];

        inv[8] = mat.data[4]  * mat.data[9] * mat.data[15] -
                 mat.data[4]  * mat.data[11] * mat.data[13] -
                 mat.data[8]  * mat.data[5] * mat.data[15] +
                 mat.data[8]  * mat.data[7] * mat.data[13] +
                 mat.data[12] * mat.data[5] * mat.data[11] -
                 mat.data[12] * mat.data[7] * mat.data[9];

        inv[12] = -mat.data[4]  * mat.data[9] * mat.data[14] +
                   mat.data[4]  * mat.data[10] * mat.data[13] +
                   mat.data[8]  * mat.data[5] * mat.data[14] -
                   mat.data[8]  * mat.data[6] * mat.data[13] -
                   mat.data[12] * mat.data[5] * mat.data[10] +
                   mat.data[12] * mat.data[6] * mat.data[9];

        float det = mat.data[0] * inv[0] + mat.data[1] * inv[4] + mat.data[2] * inv[8] + mat.data[3] * inv[12];

        if (std::fabs(det) < MathCore::EPSILON)
            return false;   // no need to compute the rest if the matrix is not invertible (det = 0)

        inv[1] = -mat.data[1]  * mat.data[10] * mat.data[15] +
                  mat.data[1]  * mat.data[11] * mat.data[14] +
                  mat.data[9]  * mat.data[2] * mat.data[15] -
                  mat.data[9]  * mat.data[3] * mat.data[14] -
                  mat.data[13] * mat.data[2] * mat.data[11] +
                  mat.data[13] * mat.data[3] * mat.data[10];

        inv[5] = mat.data[0]  * mat.data[10] * mat.data[15] -
                 mat.data[0]  * mat.data[11] * mat.data[14] -
                 mat.data[8]  * mat.data[2] * mat.data[15] +
                 mat.data[8]  * mat.data[3] * mat.data[14] +
                 mat.data[12] * mat.data[2] * mat.data[11] -
                 mat.data[12] * mat.data[3] * mat.data[10];

        inv[9] = -mat.data[0]  * mat.data[9] * mat.data[15] +
                  mat.data[0]  * mat.data[11] * mat.data[13] +
                  mat.data[8]  * mat.data[1] * mat.data[15] -
                  mat.data[8]  * mat.data[3] * mat.data[13] -
                  mat.data[12] * mat.data[1] * mat.data[11] +
                  mat.data[12] * mat.data[3] * mat.data[9];

        inv[13] = mat.data[0]  * mat.data[9] * mat.data[14] -
                  mat.data[0]  * mat.data[10] * mat.data[13] -
                  mat.data[8]  * mat.data[1] * mat.data[14] +
                  mat.data[8]  * mat.data[2] * mat.data[13] +
                  mat.data[12] * mat.data[1] * mat.data[10] -
                  mat.data[12] * mat.data[2] * mat.data[9];

        inv[2] = mat.data[1]  * mat.data[6] * mat.data[15] -
                 mat.data[1]  * mat.data[7] * mat.data[14] -
                 mat.data[5]  * mat.data[2] * mat.data[15] +
                 mat.data[5]  * mat.data[3] * mat.data[14] +
                 mat.data[13] * mat.data[2] * mat.data[7] -
                 mat.data[13] * mat.data[3] * mat.data[6];

        inv[6] = -mat.data[0]  * mat.data[6] * mat.data[15] +
                  mat.data[0]  * mat.data[7] * mat.data[14] +
                  mat.data[4]  * mat.data[2] * mat.data[15] -
                  mat.data[4]  * mat.data[3] * mat.data[14] -
                  mat.data[12] * mat.data[2] * mat.data[7] +
                  mat.data[12] * mat.data[3] * mat.data[6];

        inv[10] = mat.data[0]  * mat.data[5] * mat.data[15] -
                  mat.data[0]  * mat.data[7] * mat.data[13] -
                  mat.data[4]  * mat.data[1] * mat.data[15] +
                  mat.data[4]  * mat.data[3] * mat.data[13] +
                  mat.data[12] * mat.data[1] * mat.data[7] -
                  mat.data[12] * mat.data[3] * mat.data[5];

        inv[14] = -mat.data[0]  * mat.data[5] * mat.data[14] +
                   mat.data[0]  * mat.data[6] * mat.data[13] +
                   mat.data[4]  * mat.data[1] * mat.data[14] -
                   mat.data[4]  * mat.data[2] * mat.data[13] -
                   mat.data[12] * mat.data[1] * mat.data[6] +
                   mat.data[12] * mat.data[2] * mat.data[5];

        inv[3] = -mat.data[1] * mat.data[6] * mat.data[11] +
                  mat.data[1] * mat.data[7] * mat.data[10] +
                  mat.data[5] * mat.data[2] * mat.data[11] -
                  mat.data[5] * mat.data[3] * mat.data[10] -
                  mat.data[9] * mat.data[2] * mat.data[7] +
                  mat.data[9] * mat.data[3] * mat.data[6];

        inv[7] = mat.data[0] * mat.data[6] * mat.data[11] -
                 mat.data[0] * mat.data[7] * mat.data[10] -
                 mat.data[4] * mat.data[2] * mat.data[11] +
                 mat.data[4] * mat.data[3] * mat.data[10] +
                 mat.data[8] * mat.data[2] * mat.data[7] -
                 mat.data[8] * mat.data[3] * mat.data[6];

        inv[11] = -mat.data[0] * mat.data[5] * mat.data[11] +
                   mat.data[0] * mat.data[7] * mat.data[9] +
                   mat.data[4] * mat.data[1] * mat.data[11] -
                   mat.data[4] * mat.data[3] * mat.data[9] -
                   mat.data[8] * mat.data[1] * mat.data[7] +
                   mat.data[8] * mat.data[3] * mat.data[5];

        inv[15] = mat.data[0] * mat.data[5] * mat.data[10] -
                  mat.data[0] * mat.data[6] * mat.data[9] -
                  mat.data[4] * mat.data[1] * mat.data[10] +
                  mat.data[4] * mat.data[2] * mat.data[9] +
                  mat.data[8] * mat.data[1] * mat.data[6] -
                  mat.data[8] * mat.data[2] * mat.data[5];

        det = 1.0f / det;

        for (int i = 0; i < 16; i++)
            invMat.data[i] = inv[i] * det;

        return true;
    }

    // === === ==== === === //
    // --- Constructors --- //
    // === === ==== === === //

    Matrix::Matrix()
    : data(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
    {}

    Matrix::Matrix(const float (&values)[16]) : data{} {
        std::copy(std::begin(values), std::end(values), std::begin(data));
    }

    Matrix::Matrix(const float (&values)[4][4]) : data{} {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i*4 + j] = values[i][j];
            }
        }
    }

    Matrix::Matrix(const Matrix& other) : data{} {
        std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
    }

    // === ==== ==== === //
    // --- Operators --- //
    // === ==== ==== === //

    Matrix& Matrix::operator=(const Matrix& other) {
        if (this != &other) {
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result(i,j) += data[i*4 + k] * other.data[k*4 + j];
                }
            }
        }
        result(0, 0) = data[0] * other.data[0] + data[1] * other.data[4] + data[2] * other.data[8] + data[3] * other.data[12];
        return result;
    }

    Vector Matrix::operator*(const Vector& vec) const {
        return {
            data[0] * vec.x() + data[1] * vec.y() + data[2] * vec.z() + data[3] * vec.w(),
            data[4] * vec.x() + data[5] * vec.y() + data[6] * vec.z() + data[7] * vec.w(),
            data[8] * vec.x() + data[9] * vec.y() + data[10] * vec.z() + data[11] * vec.w(),
            data[12] * vec.x() + data[13] * vec.y() + data[14] * vec.z() + data[15] * vec.w()
        };
    }

    Vector operator*(const Vector& vtx, const Matrix& mat) {
        return {
            mat.data[0] * vtx.x() + mat.data[4] * vtx.y() + mat.data[8] * vtx.z() + mat.data[12] * vtx.w(),
            mat.data[1] * vtx.x() + mat.data[5] * vtx.y() + mat.data[9] * vtx.z() + mat.data[13] * vtx.w(),
            mat.data[2] * vtx.x() + mat.data[6] * vtx.y() + mat.data[10] * vtx.z() + mat.data[14] * vtx.w(),
            mat.data[3] * vtx.x() + mat.data[7] * vtx.y() + mat.data[11] * vtx.z() + mat.data[15] * vtx.w()
        };
    }


    // === === ==== === === //
    // --- Matrix maths --- //
    // === === ==== === === //

    Matrix Matrix::Transpose() const {
        Matrix transposed;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                transposed(i, j) = data[j * 4 + i];
            }
        }
        return transposed;
    }

    Matrix Matrix::Inverse() const {
        Matrix inversed;
        if (InvertMatrix(*this, inversed))
            return inversed;
        throw std::runtime_error("Matrix is not invertible");
    }

    // === ==== ===== ==== === //
    // --- Common matrices --- //
    // === ==== ===== ==== === //

    Matrix Matrix::Identity() {
        return Matrix({1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f});
    }

    Matrix Matrix::RotationX(const float& angle) {
        const float cosTheta = std::cos(angle);
        const float sinTheta = std::sin(angle);
        return Matrix({1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, cosTheta, -sinTheta, 0.0f,
                      0.0f, sinTheta, cosTheta, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f});
    }

    Matrix Matrix::RotationY(const float& angle) {
        const float cosTheta = std::cos(angle);
        const float sinTheta = std::sin(angle);
        return Matrix({cosTheta, 0.0f, sinTheta, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      -sinTheta, 0.0f, cosTheta, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f});
    }

    Matrix Matrix::RotationZ(const float& angle) {
        const float cosTheta = std::cos(angle);
        const float sinTheta = std::sin(angle);
        return Matrix({cosTheta, -sinTheta, 0.0f, 0.0f,
                      sinTheta, cosTheta, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f});
    }

    Matrix Matrix::Rotation(const Vector& axis, const float& angle) {
        const Vector u = axis.normalized();
        const float ux = u.x();
        const float uy = u.y();
        const float uz = u.z();
        const float cosTheta = std::cos(angle);
        const float oneMinCosTheta = 1.0f - cosTheta;
        const float sinTheta = std::sin(angle);
        Matrix rotation_matrix;
        rotation_matrix.data[0] = cosTheta + (ux * ux * oneMinCosTheta);
        rotation_matrix.data[1] = (ux * uy * oneMinCosTheta) - (uz * sinTheta);
        rotation_matrix.data[2] = (ux * uz * oneMinCosTheta) + (uy * sinTheta);

        rotation_matrix.data[4] = (ux * uy * oneMinCosTheta) + (uz * sinTheta);
        rotation_matrix.data[5] = cosTheta + (uy * uy * oneMinCosTheta);
        rotation_matrix.data[6] = (uy * uz * oneMinCosTheta) - (ux * sinTheta);

        rotation_matrix.data[8] = (ux * uz * oneMinCosTheta) - (uy * sinTheta);
        rotation_matrix.data[9] = (uy * uz * oneMinCosTheta) + (ux * sinTheta);
        rotation_matrix.data[10] = cosTheta + (uz * uz * (1 - cosTheta));

        rotation_matrix.data[15] = 1.0f;
        return rotation_matrix;
    }

    Matrix Matrix::Translation(const float& tx, const float& ty, const float& tz) {
            return Matrix({1.0f, 0.0f, 0.0f, tx,
                      0.0f, 1.0f, 0.0f, ty,
                      0.0f, 0.0f, 1.0f, tz,
                      0.0f, 0.0f, 0.0f, 1.0f});
    }

    // /!\ : effective only if object is centered around the origin.
    Matrix Matrix::Scaling(const float& sx, const float& sy, const float& sz) {
        return Matrix({sx, 0.0f, 0.0f, 0.0f,
                      0.0f, sy, 0.0f, 0.0f,
                      0.0f, 0.0f, sz, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f});
    }

    Matrix Matrix::Perspective(const float& fov_y, const float& near, const float& far)
    {
        const float aspect = 1.0f; // dev
        return Matrix({1/(std::tan(fov_y/2)*aspect), 0.0f, 0.0f, 0.0f,
                      0.0f, 1/(std::tan(fov_y/2)), 0.0f, 0.0f,
                      0.0f, 0.0f, -((far + near)/(far - near)), -((2 * far * near)/(far - near)),
                      0.0f, 0.0f, -1.0f, 0.0f});
    }


} // namespace Geometry

