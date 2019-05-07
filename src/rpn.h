#ifndef RPN_RPN_H
#define RPN_RPN_H


#include <vector>
#include <stack>
#include <string>
#include "operation.h"
#include "exeptions.h"

class HandlerCreator;

class OperationsHandler {
    std::vector<Operation*> op;
public:
    Operation *getOp(std::string sign);
    friend HandlerCreator;
};


class HandlerCreator {
protected:
    OperationsHandler handler;
public:
    void add(Operation *operation);
    virtual OperationsHandler create() = 0;
};

class DefaultHandler: public HandlerCreator {
public:
    OperationsHandler create();
};


class Solver {
    OperationsHandler handler;

    template <typename T, typename S>
    S cast(T &a);
    bool isOperation(std::string s);
    bool isLeftBracket(const std::string& s);
    bool isRightBracket(const std::string& s);
    bool isNumber(char s);
    bool isPoint(char s);
    bool priority(Operation *op1, Operation *op2);
    double *extract (std::stack<double> &result, Operation *operation);
    std::string* convert(std::string s);
public:
    Solver();
    Solver(OperationsHandler &h);
    double solution (const std::string& s);
};


#endif //RPN_RPN_H
