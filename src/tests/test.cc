#include <gtest/gtest.h>

#include "../model/s21_parser.h"
#include "../model/s21_validator.h"
using namespace s21;
TEST(PolishNotationTest, UnaryOperatorTest) {
  PolishNotation pn;
  ASSERT_EQ(pn.process("-1"), -1);
  ASSERT_EQ(pn.process("~1"), -1);
  ASSERT_NEAR(pn.process("cos(0)"), 1.0, 1e-9);
}

TEST(PolishNotationTest, BinaryOperatorTest) {
  PolishNotation pn;
  ASSERT_EQ(pn.process("1+1"), 2);
  ASSERT_EQ(pn.process("2-1"), 1);
  ASSERT_EQ(pn.process("2*2"), 4);
  ASSERT_EQ(pn.process("4/2"), 2);
  ASSERT_EQ(pn.process("5%3"), 2);
  ASSERT_EQ(pn.process("2^3"), 8);
}

TEST(PolishNotationTest, ComplexExpressionTest) {
  PolishNotation pn;
  ASSERT_EQ(pn.process("3+4*2/(1-5)^2"), 3.5);
  EXPECT_NEAR(pn.process("cos(0)+sin(90)"), 1.893997, 0.00001);
  ASSERT_EQ(pn.process("(3+2)*2"), 10);
  EXPECT_NEAR(pn.process("ln(2)+tan(3)"), 0.550600, 0.00001);
  EXPECT_NEAR(pn.process("1e-3/8"), 0.000125, 0.00001);
  EXPECT_NEAR(pn.process("log(100)+5^3-acos(-1)"), 123.858407, 0.00001);
  EXPECT_NEAR(pn.process("((4.23+atan(1))*(5-3^2))/((3+4)*2.3-atan(0))"),
              -1.246061, 0.00001);
  EXPECT_NEAR(
      pn.process(" ((8+asin(0.5))^2-(4*sqrt(16)))/((2+3*asin(1))-sqrt(49))"),
      -196.973454, 0.00001);
  EXPECT_NEAR(pn.process("1e-3-3/1^3"), -2.999, 0.00001);
  EXPECT_NEAR(pn.process("1e-4"), 0.0001, 0.00001);
}

TEST(PolishNotationTest, ExpectCrash) {
  PolishNotation pn;
  EXPECT_THROW(pn.process("abs(3)"), std::runtime_error);
  EXPECT_THROW(pn.process("+-84"), std::runtime_error);
  EXPECT_THROW(pn.process("cos"), std::runtime_error);
  EXPECT_THROW(pn.process("1+"), std::runtime_error);
}

TEST(ValidatorTest, ExpectValidation) {
  Validator exp;
  // bool first_exp = expression.validate("2-3-+");
  EXPECT_TRUE(exp.validate("5-6+cos(2)"));
  EXPECT_FALSE(exp.validate("())"));
  EXPECT_FALSE(exp.validate("1+"));
  EXPECT_FALSE(exp.validate(""));
  EXPECT_FALSE(exp.validate("log3"));
  EXPECT_FALSE(exp.validate("4.83764783256"));
  EXPECT_FALSE(exp.validate("4..7"));
  EXPECT_FALSE(exp.validate("4ee-8"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
