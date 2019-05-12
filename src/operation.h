#ifndef CALC_CALC_H
#define CALC_CALC_H

#include "exeptions.h"

#define ADDITION "+"
#define SUBTRACTION "-"
#define MULTIPLICATION "*"
#define DIVISION "/"

#define ADD_SUB_ORDER 150
#define MUL_DIV_ORDER 100

#define BINARY 2


class Operation{
public:
    virtual const  std::string getSign() = 0;
    virtual int argc() = 0;
    virtual int getOrder() = 0;
    virtual double operationResult(double *val) = 0;
};

class BinaryOp: public Operation{
public:
    int argc() final {
        return BINARY;
    }
};

class Addition: public BinaryOp{
public:
    const std::string getSign() override{
        return ADDITION;
    }
    int getOrder() override{
        return ADD_SUB_ORDER;
    }
    double operationResult(double *val) override{
        return (val[0] + val[1]);
    }
};

class Subtraction: public BinaryOp{
public:
    const std::string getSign() override{
        return SUBTRACTION;
    }
    int getOrder() override{
        return ADD_SUB_ORDER;
    }
    double operationResult(double *val) override{
        return (val[0] - val[1]);
    }
};

class Multiplication: public BinaryOp{
public:
    const std::string getSign() override{
        return MULTIPLICATION;
    }
    int getOrder() override{
        return MUL_DIV_ORDER;
    }
    double operationResult(double *val) override{
        return (val[0] * val[1]);
    }
};

class Division: public BinaryOp{
public:
   const std::string getSign() override{
        return DIVISION;
    }
    int getOrder() override{
        return MUL_DIV_ORDER;
    }
    double operationResult(double *val) override{
       if (val[1] == 0){
           throw DivisionByZero();
       }
       return (val[0] / val[1]);
    }
};


#endif //CALC_CALC_H
