#include <gtest/gtest.h>
#include <Color.h>

using namespace Geometry;

// --- ---- CONSTRUCTORS TESTS ---- --- //

TEST(ColorUT1_Constructors, DefaultConstructor) {
    const Color c = Color();
    EXPECT_FLOAT_EQ(c.r, 0.0f);
    EXPECT_FLOAT_EQ(c.g, 0.0f);
    EXPECT_FLOAT_EQ(c.b, 0.0f);
    EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColorUT1_Constructors, Array3Constructor) {
    constexpr float values[3] = {0.2f, 0.5f, 0.9f};
    const Color c(values);
    EXPECT_FLOAT_EQ(c.r, 0.2f);
    EXPECT_FLOAT_EQ(c.g, 0.5f);
    EXPECT_FLOAT_EQ(c.b, 0.9f);
    EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColorUT1_Constructors, Array4Constructor) {
    constexpr float values[4] = {0.2f, 0.5f, 0.9f, 0.98f};
    const Color c(values);
    EXPECT_FLOAT_EQ(c.r, 0.2f);
    EXPECT_FLOAT_EQ(c.g, 0.5f);
    EXPECT_FLOAT_EQ(c.b, 0.9f);
    EXPECT_FLOAT_EQ(c.a, 0.98f);
}

TEST(ColorUT1_Constructors, ThreeValuesConstructor) {
    const Color c(0.2f, 0.5f, 0.9f);
    EXPECT_FLOAT_EQ(c.r, 0.2f);
    EXPECT_FLOAT_EQ(c.g, 0.5f);
    EXPECT_FLOAT_EQ(c.b, 0.9f);
    EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColorUT1_Constructors, FourValuesConstructor) {
    const Color c(0.2f, 0.5f, 0.9f, 0.98f);
    EXPECT_FLOAT_EQ(c.r, 0.2f);
    EXPECT_FLOAT_EQ(c.g, 0.5f);
    EXPECT_FLOAT_EQ(c.b, 0.9f);
    EXPECT_FLOAT_EQ(c.a, 0.98f);
}

TEST(ColorUT1_Constructors, CopyConstructor) {
    const Color c1 = Color(0.2f, 0.5f, 0.9f, 0.98f);
    const Color c2(c1);
    EXPECT_FLOAT_EQ(c2.r, 0.2f);
    EXPECT_FLOAT_EQ(c2.g, 0.5f);
    EXPECT_FLOAT_EQ(c2.b, 0.9f);
    EXPECT_FLOAT_EQ(c2.a, 0.98f);
}

TEST(ColorUT1_Constructors, EqualSignConstructor) {
    const Color c1 = Color(0.2f, 0.5f, 0.9f, 0.98f);
    const Color c2 = c1;
    EXPECT_FLOAT_EQ(c2.r, 0.2f);
    EXPECT_FLOAT_EQ(c2.g, 0.5f);
    EXPECT_FLOAT_EQ(c2.b, 0.9f);
    EXPECT_FLOAT_EQ(c2.a, 0.98f);
}





// --- ---- ACCESSORS TESTS ---- --- //

TEST(ColorUT2_Accessors, Getters) {
    Color c(1, 2, 3, 4);
    EXPECT_FLOAT_EQ(c.r, 1);
    EXPECT_FLOAT_EQ(c.g, 2);
    EXPECT_FLOAT_EQ(c.b, 3);
    EXPECT_FLOAT_EQ(c.a, 4);
}

TEST(ColorUT2_Accessors, Setters) {
    Color c;
    c.r = 1;
    c.g = 2;
    c.b = 3;
    c.a = 4;
    EXPECT_FLOAT_EQ(c.r, 1);
    EXPECT_FLOAT_EQ(c.g, 2);
    EXPECT_FLOAT_EQ(c.b, 3);
    EXPECT_FLOAT_EQ(c.a, 4);
}





// --- ---- (IN)EQUALITIES TESTS ---- --- //

TEST(ColorUT3_Equalities, EqualityOperator) {
    const Color c1(1, 2, 3);
    const Color c2(1, 2, 3);
    const Color c3(4, 5, 6);

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c2 == c1);
    EXPECT_FALSE(c1 == c3);
}

TEST(ColorUT3_Equalities, InequalityOperator) {
    const Color c1(1, 2, 3);
    const Color c2(1, 2, 3);
    const Color c3(4, 5, 6);

    EXPECT_TRUE(c1 != c3);
    EXPECT_TRUE(c3 != c1);
    EXPECT_FALSE(c1 != c2);
}





// --- ---- ARITHMETICS TESTS ---- --- //

TEST(ColorUT4_Arithmetics, Addition) {
    const Color c1(1, 2, 3, 4);
    const Color c2(5, 6, 7, 8);
    const Color sum = c1 + c2;
    EXPECT_FLOAT_EQ(sum.r, 6.0f);
    EXPECT_FLOAT_EQ(sum.g, 8.0f);
    EXPECT_FLOAT_EQ(sum.b, 10.0f);
    EXPECT_FLOAT_EQ(sum.a, 12.0f);
}

TEST(ColorUT4_Arithmetics, Substraction) {
    const Color c1(4, 6, 8, 10);
    const Color c2(1, 2, 3, 4);
    const Color diff = c1 - c2;
    EXPECT_FLOAT_EQ(diff.r, 3.0f);
    EXPECT_FLOAT_EQ(diff.g, 4.0f);
    EXPECT_FLOAT_EQ(diff.b, 5.0f);
    EXPECT_FLOAT_EQ(diff.a, 6.0f);
}

TEST(ColorUT4_Arithmetics, ScalarMultiplication) {
    const Color c1(1, 2, 3, 4);
    Color mult = c1 * 2;
    EXPECT_FLOAT_EQ(mult.r, 2.0f);
    EXPECT_FLOAT_EQ(mult.g, 4.0f);
    EXPECT_FLOAT_EQ(mult.b, 6.0f);
    EXPECT_FLOAT_EQ(mult.a, 8.0f);

    mult = 2 * mult;
    EXPECT_FLOAT_EQ(mult.r, 4.0f);
    EXPECT_FLOAT_EQ(mult.g, 8.0f);
    EXPECT_FLOAT_EQ(mult.b, 12.0f);
    EXPECT_FLOAT_EQ(mult.a, 16.0f);
}

TEST(ColorUT4_Arithmetics, ScalarDivision) {
    const Color c1(1, 2, 3, 4);
    const Color div = c1 / 2;
    EXPECT_FLOAT_EQ(div.r, 0.5f);
    EXPECT_FLOAT_EQ(div.g, 1.0f);
    EXPECT_FLOAT_EQ(div.b, 1.5f);
    EXPECT_FLOAT_EQ(div.a, 2.0f);
}





// --- ---- ARITHMETICS TESTS ---- --- //

TEST(ColorUT4_InplaceArithmetics, Addition) {
    Color c1(1, 2, 3, 4);
    const Color c2(5, 6, 7, 8);
    c1 += c2;
    EXPECT_FLOAT_EQ(c1.r, 6.0f);
    EXPECT_FLOAT_EQ(c1.g, 8.0f);
    EXPECT_FLOAT_EQ(c1.b, 10.0f);
    EXPECT_FLOAT_EQ(c1.a, 12.0f);
}

TEST(ColorUT4_InplaceArithmetics, Substraction) {
    Color c1(4, 6, 8, 10);
    const Color c2(1, 2, 3, 4);
    c1 -= c2;
    EXPECT_FLOAT_EQ(c1.r, 3.0f);
    EXPECT_FLOAT_EQ(c1.g, 4.0f);
    EXPECT_FLOAT_EQ(c1.b, 5.0f);
    EXPECT_FLOAT_EQ(c1.a, 6.0f);
}

TEST(ColorUT4_InplaceArithmetics, ScalarMultiplication) {
    Color c1(1, 2, 3, 4);
    c1 *= 2.0f;
    EXPECT_FLOAT_EQ(c1.r, 2.0f);
    EXPECT_FLOAT_EQ(c1.g, 4.0f);
    EXPECT_FLOAT_EQ(c1.b, 6.0f);
    EXPECT_FLOAT_EQ(c1.a, 8.0f);
}

TEST(ColorUT4_InplaceArithmetics, ScalarDivision) {
    Color c1(1, 2, 3, 4);
    c1 /= 2.0f;
    EXPECT_FLOAT_EQ(c1.r, 0.5f);
    EXPECT_FLOAT_EQ(c1.g, 1.0f);
    EXPECT_FLOAT_EQ(c1.b, 1.5f);
    EXPECT_FLOAT_EQ(c1.a, 2.0f);
}


// --- ---- STREAMS TESTS ---- --- //

TEST(ColorUT5_Streams, OutputStreamOperator) {
    const Color c(1, 2, 3, 4);
    std::ostringstream os;
    os << c;
    const std::string output = os.str();
    const std::string expected = "color(1, 2, 3, 4)";
    EXPECT_EQ(output, expected);
}





