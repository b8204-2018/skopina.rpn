#include "gtest/gtest.h"
#include "src/rpn.h"

using namespace std;


TEST(InvalidExpression, EmptyString) {
    string ex("");
    Solver s;
    EXPECT_THROW(s.solution(ex), EmptyString);
}

TEST(InvalidExpression, ExtraRightBracket) {
    string ex("(6 + 10 - 4) / (1 + 1 * 2)) + 1");
    Solver s;
    EXPECT_THROW(s.solution(ex), ExpectedLeftBracket);
}

TEST(InvalidExpression, ExtraLeftBracket) {
    string ex("(6 + 10 - 4) / ((1 + 1 * 2) + 1");
    Solver s;
    EXPECT_THROW(s.solution(ex), ExpectedRightBracket);
}

TEST(InvalidExpression, InvalidSymbol) {
    string ex("(6 + 10 - 4) / (1 + 1 * 2.) + 1");
    Solver s;
    EXPECT_THROW(s.solution(ex), InvalidExpression);
    ex = ("(6 + 10 - 4) / (1 + 1 * 2) % + 1");
    EXPECT_THROW(s.solution(ex), InvalidExpression);
}

TEST(InvalidExpression, LackOfOperands) {
    string ex("(6 + 10 - 4) / (1 + 1 * 2) + + 1");
    Solver s;
    EXPECT_THROW(s.solution(ex), LackOfOperands);
}


TEST(Calculation, NoBrackets_EqualPriorities) {
    string ex("6 + 10 - 4");
    Solver s;
    EXPECT_EQ(s.solution(ex), 12);
    ex = "6.2 + 10 - 4";
    EXPECT_EQ(s.solution(ex), 12.2);
}

TEST(Calculation, NoBrackets_NotEqualPriorities) {
    string ex("1 + 1 * 2");
    Solver s;
    EXPECT_EQ(s.solution(ex), 3);
    ex = "1 * 2 + 1";
    EXPECT_EQ(s.solution(ex), 3);

    ex = "1 + 1 * 2.74";
    EXPECT_EQ(s.solution(ex), 3.74);
    ex = "1 * 2 + 1.0";
    EXPECT_EQ(s.solution(ex), 3);
}

TEST(Calculation, Brackets_EqualPriorities) {
    string ex("6 + (10 - 4)");
    Solver s;
    EXPECT_EQ(s.solution(ex), 12);
    ex = "(6 + 10) - 4";
    EXPECT_EQ(s.solution(ex), 12);
    ex = "6 + (10.48 - 4)";
    EXPECT_EQ(s.solution(ex), 12.48);
    ex = "6 - (10 - 4)";
    EXPECT_EQ(s.solution(ex), 0);
    ex = "(6 + 10) - 4.5";
    EXPECT_EQ(s.solution(ex), 11.5);
}

TEST(Calculation, Brackets_NotEqualPriorities) {
    string ex("(1 + 1) * 2");
    Solver s;
    EXPECT_EQ(s.solution(ex), 4);
    ex = "2 * (1 + 1)";
    EXPECT_EQ(s.solution(ex), 4);
    ex = "(1.48 + 1.52) * 2";
    EXPECT_EQ(s.solution(ex), 6);
    ex = "2.5 * (1 + 1)";
    EXPECT_EQ(s.solution(ex), 5);
}


TEST(Calculation, DivisionByZero) {
    string ex("((22 + 17) / 13 + 4) / (42 - 30 - 12)");
    Solver s;
    EXPECT_THROW(s.solution(ex), DivisionByZero);
}

TEST (AddNewOperation, NewOperation){
    class Negation: public Operation{
    public:
        int argc() override {
            return 1;
        }
        const std::string getSign() override{
            return "~";
        }
        int getOrder() override{
            return 200;
        }
        double operationResult(double *val) override{
            return (-1 * val[0]);
        }
    };

    OperationsHandler handler;
    handler.add(new Addition);
    handler.add(new Subtraction);
    handler.add(new Multiplication);
    handler.add(new Division);
    handler.add(new Negation);
    
    Solver solver(handler);
    string ex("(6 + 10 - 4) / ( ~ (1 + 1 * 2) + 1)");
    EXPECT_EQ(solver.solution(ex), -3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}