#ifndef RPN_EXEPTIONS_H
#define RPN_EXEPTIONS_H


#include <string>


class Exception{
    std::string error;
public:
    Exception(std::string error): error(error){}
    const char* getError() { return error.c_str();}
};


class ExpectedLeftBracket: public Exception {
public:
    ExpectedLeftBracket():Exception("Expected '('"){}
};


class ExpectedRightBracket: public Exception {
public:
    ExpectedRightBracket():Exception("Expected ')'"){}
};


class InvalidExpression: public Exception {
public:
    InvalidExpression():Exception("Invalid expression."){}
};


class LackOfOperands: public Exception {
public:
    LackOfOperands():Exception("Lack of operands."){}
};


class DivisionByZero: public Exception{
public:
    DivisionByZero():Exception("Division by zero."){};
};


class EmptyString: public Exception{
public:
    EmptyString():Exception("Empty string."){};
};


#endif //RPN_EXEPTIONS_H
