#include <gtest/gtest.h>
#include <Matrix.h>

using namespace Geometry;

// --- ---- CONSTRUCTORS TESTS ---- --- //

TEST(MatrixUT1_Constructors, DefaultConstructor) {
    const Matrix m;
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m.data[i], 0.0f);
    }
}

TEST(MatrixUT1_Constructors, ArrayConstructor) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m(values);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m.data[i], values[i]);
    }
}

TEST(MatrixUT1_Constructors, Array2DConstructor) {
    constexpr float values[4][4]= {{1.0f, 2.0f, 3.0f, 4.0f},
                        {5.0f, 6.0f, 7.0f, 8.0f},
                        {9.0f, 10.0f, 11.0f, 12.0f},
                        {13.0f, 14.0f, 15.0f, 16.0f}};
    const Matrix m(values);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(m.data[i*4 + j], values[i][j]);
        }
    }
}

TEST(MatrixUT1_Constructors, CopyConstructor) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m1(values);
    const Matrix m2(m1);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m1.data[i], m2.data[i]);
    }
}

TEST(MatrixUT2_Operators, AssignmentOperator) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m1(values);
    const Matrix m2 = m1;
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(m1.data[i], m2.data[i]);
    }
}





// --- ---- OPERATORS TESTS ---- --- //

TEST(MatrixUT2_Operators, LeftMultiplication) {
    constexpr float values1[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                         5.0f, 6.0f, 7.0f, 8.0f,
                         9.0f, 10.0f, 11.0f, 12.0f,
                         13.0f, 14.0f, 15.0f, 16.0f};
    constexpr float values2[16] = {17.0f, 18.0f, 19.0f, 20.0f,
                         21.0f, 22.0f, 23.0f, 24.0f,
                         25.0f, 26.0f, 27.0f, 28.0f,
                         29.0f, 30.0f, 31.0f, 32.0f};
    const Matrix m1(values1);
    const Matrix m2(values2);
    constexpr float m1m2[16] = {250.0f, 260.0f, 270.0f, 280.0f,
                     618.0f, 644.0f, 670.0f, 696.0f,
                     986.0f, 1028.0f, 1070.0f, 1112.0f,
                     1354.0f, 1412.0f, 1470.0f, 1528.0f};
    const Matrix result = m1 * m2;
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], m1m2[i]);
    }
}

TEST(MatrixUT2_Operators, RightMultiplication) {
    constexpr float values1[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                         5.0f, 6.0f, 7.0f, 8.0f,
                         9.0f, 10.0f, 11.0f, 12.0f,
                         13.0f, 14.0f, 15.0f, 16.0f};
    constexpr float values2[16] = {17.0f, 18.0f, 19.0f, 20.0f,
                         21.0f, 22.0f, 23.0f, 24.0f,
                         25.0f, 26.0f, 27.0f, 28.0f,
                         29.0f, 30.0f, 31.0f, 32.0f};
    const Matrix m1(values1);
    const Matrix m2(values2);
    constexpr float m2m1[16] = {538.0f, 612.0f, 686.0f, 760.0f,
                             650.0f, 740.0f, 830.0f, 920.0f,
                             762.0f, 868.0f, 974.0f, 1080.0f,
                             874.0f, 996.0f, 1118.0f, 1240.0f};
    const Matrix result = m2 * m1;
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], m2m1[i]);
    }
}

TEST(MatrixUT2_Operators, LeftMultiplicationWithVector) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m(values);
    const Vector v(17.0f, 18.0f, 19.0f, 20.0f);
    constexpr float expected[4] = {190.0f, 486.0f, 782.0f, 1078.0f};
    const Vector result = m * v;
    for (int i = 0; i < 4; i++) {
        EXPECT_FLOAT_EQ(result[i], expected[i]);
    }
}

TEST(MatrixUT2_Operators, RightMultiplicationWithVector) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m(values);
    const Vector v(17.0f, 18.0f, 19.0f, 20.0f);
    constexpr float expected[4] = {538.0f, 612.0f, 686.0f, 760.0f};
    const Vector result = v * m;
    for (int i = 0; i < 4; i++) {
        EXPECT_FLOAT_EQ(result[i], expected[i]);
    }
}





// --- ---- ACCESSORS TESTS ---- --- //

TEST(MatrixUT3_Accessors, ParenthesesGetterOperator) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m(values);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(m(i,j), values[i*4+j]);
        }
    }
}

TEST(MatrixUT3_Accessors, ParenthesesSetterOperator) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    Matrix m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m(i,j) = values[i*4+j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(m(i,j), values[i*4+j]);
        }
    }
}





// --- ---- MATRIX MATHS TESTS ---- --- //

TEST(MatrixUT4_Maths, Transpose) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    const Matrix m(values);
    constexpr float expected[16] = {1.0f, 5.0f, 9.0f, 13.0f,
                     2.0f, 6.0f, 10.0f, 14.0f,
                     3.0f, 7.0f, 11.0f, 15.0f,
                     4.0f, 8.0f, 12.0f, 16.0f};
    const Matrix result = m.Transpose();
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT4_Maths, Inverse) {
    constexpr float values[16] = {5.0f, 6.0f, 6.0f, 8.0f,
                        2.0f, 2.0f, 2.0f, 8.0f,
                        6.0f, 6.0f, 2.0f, 8.0f,
                        2.0f, 3.0f, 6.0f, 7.0f};
    const Matrix m(values);
    constexpr float expected[16] ={-17.0f, -9.0f, 12.0f, 16.0f,
                     17.0F, 35.0f/4.0f, -47.0f/4.0f, -16.0f,
                     -4.0f, -9.0f/4.0f, 11.0f/4.0f, 4.0f,
                     1.0f, 3.0f/4.0f, -3.0f/4.0f, -1.0f};
    const Matrix result = m.Inverse();
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT4_Maths, NotInvertibleAttempt) {
    constexpr float values[16] = {1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
    EXPECT_THROW(Matrix m = Matrix(values).Inverse(), std::runtime_error);
}





// --- ---- COMMON MATRICES BUILDERS TESTS ---- --- //

TEST(MatrixUT5_MatrixBuilders, Identity) {
    constexpr float expected[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix result = Matrix::Identity();
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT5_MatrixBuilders, RotationX) {
    constexpr float angle = M_PI / 4.0f;
    constexpr float expected[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, std::cos(angle), -std::sin(angle), 0.0f,
                    0.0f, std::sin(angle), std::cos(angle), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix result = Matrix::RotationX(angle);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT5_MatrixBuilders, RotationY) {
    constexpr float angle = M_PI / 4.0f;
    constexpr float expected[16] = {std::cos(angle), 0.0f, std::sin(angle), 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    -std::sin(angle), 0.0f, std::cos(angle), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix result = Matrix::RotationY(angle);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT5_MatrixBuilders, RotationZ) {
    constexpr float angle = M_PI / 4.0f;
    constexpr float expected[16] = {std::cos(angle), -std::sin(angle), 0.0f, 0.0f,
                    std::sin(angle), std::cos(angle), 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix result = Matrix::RotationZ(angle);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT5_MatrixBuilders, AxisRotation) {
    constexpr float angle = M_PI / 4.0f;
    const Vector axis(1.0f, 1.0f, 1.0f);
    constexpr float expected[16] = {0.8047379, -0.3106172,  0.5058793, 0.0f,
                                    0.5058793, 0.8047379, -0.3106172, 0.0f,
                                    -0.3106172,  0.5058793,  0.8047379, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix result = Matrix::Rotation(axis, angle);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT5_MatrixBuilders, Translation) {
    constexpr float expected[16] = {1.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 0.0f, 2.0f,
                    0.0f, 0.0f, 1.0f, 3.0,
                    0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix result = Matrix::Translation(1.0f, 2.0f, 3.0f);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}

TEST(MatrixUT5_MatrixBuilders, Scaling) {
    constexpr float expected[16] = {2.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 3.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 4.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f};
    const Matrix result = Matrix::Scaling(2.0f, 3.0f, 4.0f);
    for (int i = 0; i < 16; i++) {
        EXPECT_FLOAT_EQ(result.data[i], expected[i]);
    }
}



