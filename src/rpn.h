#ifndef RPN_RPN_H
#define RPN_RPN_H


#include <map>
#include <stack>
#include <string>
#include "operation.h"
#include "exeptions.h"


class OperationsHandler {
    std::map<std::string, Operation*> op;
public:
    void add(Operation *operation);
    Operation *getOp(std::string sign);
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
