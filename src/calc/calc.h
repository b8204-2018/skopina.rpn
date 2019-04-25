#ifndef CALC_CALC_H
#define CALC_CALC_H


#include <string>


#define ADDITION '+'
#define SUBTRACTION '-'
#define MULTIPLICATION '*'
#define DIVISION '/'


using namespace std;


class BasicSolver{
public:
    virtual char getOperationSymbol() = 0;
    virtual double operationResult(double a, double b) = 0;
};

class Additor: public BasicSolver{
public:
    char getOperationSymbol() override{
        return ADDITION;
    }
    double operationResult(double a, double b)override {
        return (a + b);
    }
};

class Subtractor: public BasicSolver{
public:
    char getOperationSymbol() override{
        return SUBTRACTION;
    }
    double operationResult(double a, double b)override {
        return (a - b);
    }
};

class Multiplicator: public BasicSolver{
public:
    char getOperationSymbol() override{
        return MULTIPLICATION;
    }
    double operationResult(double a, double b)override {
        return (a * b);
    }
};

class Divisor: public BasicSolver{
public:
    char getOperationSymbol() override{
        return DIVISION;
    }
    double operationResult(double a, double b)override {
        return (a / b);
    }
};

#endif //CALC_CALC_H
