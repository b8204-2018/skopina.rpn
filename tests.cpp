#include "gtest/gtest.h"
#include "src/rpn.h"

using namespace std;

TEST(Exceptions, LeftBracket) {
    string ex("((44 + 66) * 0.3) + 0.0001)");    
    Solver solver;
    EXPECT_THROW(solver.convert(ex), std::invalid_argument);
}

TEST(Exceptions, RightBracket) {
    string ex("(((((((44 + 66) * 0.3) + 0.0001)");
    Solver solver;
    EXPECT_THROW(solver.convert(ex), std::invalid_argument);
}

TEST(Exceptions, Point) {
    string ex("47.66 + 5.");
    Solver solver;
    EXPECT_THROW(solver.convert(ex), std::invalid_argument);
}

TEST(Exceptions, InvalidSymbol) {
    string ex("5 + 6?");
    Solver solver;
    EXPECT_THROW(solver.convert(ex), std::logic_error);
}

TEST(Make_RPN, withoutBrackets){
    string ex("5 * 2 + 10");
    Solver solver;
    string rpn[] = {"5", "5", "2", "*", "10", "+"};
    for (int i = 0; i <= 5; i++){
        EXPECT_EQ(solver.convert(ex)[i], rpn[i]);
    }
}


TEST(Make_RPN, withBrackets){
    string ex("6 + (10 - 4)");
    Solver solver;
    string rpn[] = {"5", "6", "10", "4", "-", "+"};
    for (int i = 0; i <= 5; i++){
        EXPECT_EQ(solver.convert(ex)[i], rpn[i]);
    }
}


TEST(Make_RPN, differentPriorities){
    string ex("(6 + 10 - 4) / (1 + 1 * 2) + 1");
    Solver solver;
    string rpn[] = {"13", "6", "10", "+", "4", "-", "1", "1", "2", "*", "+", "/", "1", "+"};
    for (int i = 0; i <= 13; i++){
        EXPECT_EQ(solver.convert(ex)[i], rpn[i]);
    }
}


TEST(Make_RPN, differentARGC){
    string ex("(6 + 10 - 4) / (~ (1 + 1 * 2)) + 1");
    Solver solver;
    string rpn[] = {"14", "6", "10", "+", "4", "-", "1", "1", "2", "*", "+", "~", "/", "1", "+"};
    for (int i = 0; i <= 13; i++){
        EXPECT_EQ(solver.convert(ex)[i], rpn[i]);
    }
}

TEST(Calculating, withoutBrackets){
string ex("5 * 2 + 10");
Solver solver;
EXPECT_EQ(solver.solution(ex), 20);
}


TEST(Calculating, withBrackets){
    string ex("6 + (10 - 4)");
    Solver solver;
    EXPECT_EQ(solver.solution(ex), 12);
}


TEST(Calculating, differentPriorities){
    string ex("(6 + 10 - 4) / (1 + 1 * 2) + 1");
    Solver solver;
    EXPECT_EQ(solver.solution(ex), 5);
}


TEST(Calculating, differentARGC){
    string ex("(6 + 10 - 4) / (~ (1 + 1 * 2)) + 1");
    Solver solver;
    EXPECT_EQ(solver.solution(ex), -3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}