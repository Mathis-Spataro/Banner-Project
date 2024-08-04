#include <cmath>
#include <gtest/gtest.h>
#include <Vector.h>

using namespace Geometry;

// --- ---- CONSTRUCTORS TESTS ---- --- //

TEST(VectorUT1_Constructors, DefaultConstructor) {
    const Vector v = Vector();
    constexpr float expected_pos[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT1_Constructors, ArrayOf3FloatsConstructor) {
    constexpr float pos[3] = {0.1, 0.2, 1.3};
    const Vector v(pos);
    constexpr float expected_pos[4] = {0.1, 0.2, 1.3, 0.0};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT1_Constructors, ArrayOf4FloatsConstructor) {
    constexpr float pos[4] = {0.1, 0.2, 1.3, 1.4};
    const Vector v(pos);
    constexpr float expected_pos[4] = {0.1, 0.2, 1.3, 1.4};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT1_Constructors, ThreeFloatsConstructor) {
    const Vector v(0.1, 0.2, 1.3);
    constexpr float expected_pos[4] = {0.1, 0.2, 1.3, 0.0};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT1_Constructors, FourFloatsConstructor) {
    const Vector v(0.1, 0.2, 1.3, 1.4);
    constexpr float expected_pos[4] = {0.1, 0.2, 1.3, 1.4};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT1_Constructors, CopyConstructor)
{
    Vector v1(1.5, 1.6, 1.7);
    const Vector v2(v1);
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], v2.pos[i]);
    }
    v1.pos[0] += 1.0f;
    EXPECT_NE(v1.pos[0], v2.pos[0]);
}

TEST(VectorUT1_Constructors, EqualSignOperator)
{
    Vector v1(1.5, 1.6, 1.7);
    const Vector v2 = v1;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], v2.pos[i]);
    }
    v1.pos[0] += 1.0f;
    EXPECT_NE(v1.pos[0], v2.pos[0]);
}

TEST(VectorUT1_Constructors, SpecialFloatValues) {
    const Vector v_nan(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
    EXPECT_TRUE(std::isnan(v_nan.x()));
    EXPECT_TRUE(std::isnan(v_nan.y()));
    EXPECT_TRUE(std::isnan(v_nan.z()));

    const Vector v_inf(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    EXPECT_TRUE(std::isinf(v_inf.x()));
    EXPECT_TRUE(std::isinf(v_inf.y()));
    EXPECT_TRUE(std::isinf(v_inf.z()));

    const Vector v_neg_inf(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    EXPECT_TRUE(std::isinf(v_neg_inf.x()));
    EXPECT_TRUE(std::isinf(v_neg_inf.y()));
    EXPECT_TRUE(std::isinf(v_neg_inf.z()));
}





// --- ---- ACCESSORS TESTS ---- --- //

TEST(VectorUT2_Accessors, BracketsOperator) {
    Vector v(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);

    v[0] = 4.0f;
    v[1] = 5.0f;
    v[2] = 6.0f;

    EXPECT_FLOAT_EQ(v[0], 4.0f);
    EXPECT_FLOAT_EQ(v[1], 5.0f);
    EXPECT_FLOAT_EQ(v[2], 6.0f);
}

TEST(VectorUT2_Accessors, Getters) {
    Vector v(2.0f, 3.0f, 4.0f);

    EXPECT_FLOAT_EQ(v.x(), 2.0f);
    EXPECT_FLOAT_EQ(v.y(), 3.0f);
    EXPECT_FLOAT_EQ(v.z(), 4.0f);
    EXPECT_FLOAT_EQ(v.w(), 0.0f);

    Vector v2(0.1, 0.2, 0.3, 0.4);

    EXPECT_FLOAT_EQ(v2.x(), 0.1f);
    EXPECT_FLOAT_EQ(v2.y(), 0.2f);
    EXPECT_FLOAT_EQ(v2.z(), 0.3f);
    EXPECT_FLOAT_EQ(v2.w(), 0.4f);
}

TEST(VectorUT2_Accessors, Setters) {
    Vector v;

    v.x() = 1.0f;
    v.y() = 2.0f;
    v.z() = 3.0f;
    v.w() = 4.0f;

    constexpr float expected_pos[4] = {1, 2, 3, 4};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}





// --- ---- (IN)EQUALITIES TESTS ---- --- //

TEST(VectorUT3_Equalities, EqualityOperator) {
    const Vector v1(1.0f, 2.0f, 3.0f);
    const Vector v2(1.0f, 2.0f, 3.0f);
    const Vector v3(4.0f, 5.0f, 6.0f);

    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v2 == v1);
    EXPECT_FALSE(v1 == v3);
}

TEST(VectorUT3_Equalities, InequalityOperator) {
    const Vector v1(1.0f, 2.0f, 3.0f);
    const Vector v2(4.0f, 5.0f, 6.0f);
    const Vector v3(1.0f, 2.0f, 3.0f);

    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v2 != v1);
    EXPECT_FALSE(v1 != v3);
}





// --- ---- ARITHMETICS TESTS ---- --- //

TEST(VectorUT4_Arithmetics, Addition) {
    const Vector v1(1.0, 2.0, 3.0);
    const Vector v2(-2.0, 4.0, 6.5);
    constexpr float expected_pos[4] = {-1.0, 6.0, 9.5, 0.0};

    Vector v = v1 + v2;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }

    v = v2 + v1;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT4_Arithmetics, Substraction) {
    const Vector v1(1.0, 2.0, 3.0);
    const Vector v2(-2.0, 4.0, 1.5);
    constexpr float expected_pos[4] = {3.0, -2.0, 1.5, 0.0};

    const Vector v = v1 - v2;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT4_Arithmetics, Negation)
{
    const Vector v0(1.0, 2.0, -3.0);
    constexpr float expected_pos[4] = {-1.0, -2.0, 3.0, 0.0};
    const Vector v = -v0;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT4_Arithmetics, ScalarMultiplication) {
    const Vector v(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr float scalar = 2.5f;
    constexpr float expected[4] = {2.5f, 5.0f, 7.5f, 10.0f};
    const Vector mult1 = v * scalar;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(mult1.pos[i], expected[i]);
    }
    const Vector mult2 = scalar * v;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(mult2.pos[i], expected[i]);
    }
}

TEST(VectorUT4_Arithmetics, ScalarDivision) {
    const Vector v1(2.0f, 4.0f, 6.0f, 8.0f);
    constexpr float scalar = 2.0f;
    constexpr float expected[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    const Vector div = v1 / scalar;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(div[i], expected[i]);
    }
}





// --- ---- INPLACE ARITHMETICS TESTS ---- --- //

TEST(VectorUT5_InplaceArithmetics, VectorInplaceAddition)
{
    Vector v1(1.0, 2.0, 3.0);
    const Vector v2(-2.0, 4.0, 6.5);
    constexpr float expected_pos[4] = {-1.0, 6.0, 9.5, 0.0};

    v1 += v2;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT5_InplaceArithmetics, VectorInplaceSubstraction)
{
    Vector v1(1.0, 2.0, 3.0);
    const Vector v2(-2.0, 4.0, 1.5);
    constexpr float expected_pos[4] = {3.0, -2.0, 1.5, 0.0};

    v1 -= v2;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT5_InplaceArithmetics, VectorInplaceScalarMultiplication)
{
    Vector v1(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr float expected_pos[4] = {2.5f, 5.0f, 7.5f, 10.0f};
    v1 *= 2.5f;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], expected_pos[i]);
    }
}

TEST(VectorUT5_InplaceArithmetics, VectorInplaceScalarDivision) {
    Vector v1(2.0f, 4.0f, 6.0f, 8.0f);
    constexpr float expected_pos[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    v1 /= 2.0f;
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], expected_pos[i]);
    }
}





// --- ---- VECTOR MATHS TESTS ---- --- //

TEST(VectorUT6_Maths, NormFunction) {
    // Test with a vector of all zeros
    const Vector v1(0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(v1.norm(), 0.0f);

    // Test with a unit vector
    const Vector v2(1.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(v2.norm(), 1.0f);

    // Test with a general case vector
    const Vector v3(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr float expected_v3_norm = std::sqrt(14.0f);
    EXPECT_FLOAT_EQ(v3.norm(), expected_v3_norm);
}

TEST(VectorUT6_Maths, NormalizedFunction) {
    // Test with a vector of all zeros
    const Vector v1 = Vector(0.0f, 0.0f, 0.0f).normalized();
    constexpr float expected_v1_pos[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1.pos[i], expected_v1_pos[i]);
    }
    // Test with a unit vector
    const Vector v2 = Vector(0.0f, 1.0f, 0.0f, 1.0).normalized();
    constexpr float expected_v2_pos[4] = {0.0f, 1.0f, 0.0f, 1.0f};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v2.pos[i], expected_v2_pos[i]);
    }
    // Test with a vector of non-zero values
    const Vector v3 = Vector(1.0f, 2.0f, 3.0f, 4.0f).normalized();
    const float expected_v3_pos[4] = {1.0f/std::sqrt(14.0f), 2.0f/std::sqrt(14.0f), 3.0f/std::sqrt(14.0f), 4.0f/std::sqrt(14.0f)};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v3.pos[i], expected_v3_pos[i]);
    }
}

TEST(VectorUT6_Maths, dotFunction) {
    // Test with a vector of all zeros
    const Vector v1(0.0f, 0.0f, 0.0f);
    const Vector v2(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v1.dot(v2), 0.0f);

    // Test with two orthogonal unit vectors
    const Vector v3(0.0f, 1.0f, 0.0f, 1.0f);
    const Vector v4(1.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(v3.dot(v4), 0.0f);

    // Test with the same vector
    const Vector v5(1.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(v5.dot(v5), 1.0f);

    // Test with two colinear vectors
    const Vector v6(0.0f, 1.0f, 2.0f, 1.0f);
    const Vector v7(0.0f, 0.5f, 1.0f, 0.0f);
    EXPECT_FLOAT_EQ(v6.dot(v7), 2.5f);

    // Test with two general case vectors
    const Vector v8(1.0f, 2.0f, 3.0f, 1.4f);
    const Vector v9(4.0f, 5.5f, -6.0f, 0.2f);
    EXPECT_FLOAT_EQ(v8.dot(v9), -3.0f);
}

TEST(VectorUT6_Maths, crossFunction) {
    // Test with a vector of all zeros
    const Vector v_null(0.0f, 0.0f, 0.0f);
    const Vector v2(1.0f, 2.0f, 3.0f, 4.0f);
    const Vector v1v2 = v_null.cross(v2);
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v1v2.pos[i], v_null.pos[i]);
    }

    // Test with two orthogonal unit vectors
    const Vector v3(0.0f, 1.0f, 0.0f, 1.0f);
    const Vector v4(1.0f, 0.0f, 0.0f, 1.0f);
    const Vector v3v4 = v3.cross(v4);
    constexpr float expected_v3v4_pos[4] = {0.0, 0.0, -1, 0.0f};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v3v4.pos[i], expected_v3v4_pos[i]);
    }

    // Test with the same vector
    const Vector v5(1.0f, 0.0f, 0.0f, 0.0f);
    const Vector v5v5 = v5.cross(v5);
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v5v5.pos[i], v_null.pos[i]);
    }

    // Test with two colinear vectors
    const Vector v6(0.0f, 1.0f, 2.0f, 1.0f);
    const Vector v7(0.0f, 0.5f, 1.0f, 0.0f);
    const Vector v6v7 = v6.cross(v7);
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v6v7.pos[i], v_null.pos[i]);
    }

    // Test with two general case vectors
    const Vector v8(1.0f, 2.0f, 3.0f, 1.4f);
    const Vector v9(4.0f, 5.5f, -6.0f, 0.2f);
    const Vector v8v9 = v8.cross(v9);
    constexpr float expected_v8v9_pos[4] = {-28.5, 18, -2.5, 0.0f};
    for(int i=0; i<4; i++) {
        EXPECT_FLOAT_EQ(v8v9.pos[i], expected_v8v9_pos[i]);
    }
}



// --- ---- STREAMS TESTS ---- --- //

TEST(VectorUT5_Streams, OutputStreamOperator) {
    const Vector v(1.0, 2.0, 3.0, 4.0);
    std::ostringstream os;
    os << v;
    const std::string output = os.str();
    const std::string expected = "vec(1, 2, 3, 4)";
    EXPECT_EQ(output, expected);
}

