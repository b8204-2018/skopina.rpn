#ifndef RPN_RPN_H
#define RPN_RPN_H


#include <stack>
#include <string>
#include "operation.h"


struct OpList{
    Operation &operation;
    struct  OpList *next = nullptr;
    OpList(Operation *op): operation(*op){}
};

class OperationsHandler {
    OpList *head = nullptr;
public:
    void addOperation(Operation *op);
    void fill();
    Operation *getOp(std::string sign);
    ~OperationsHandler();
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
    Solver(){
        handler.fill();
    }
    double solution (const std::string& s);
};


#endif //RPN_RPN_H
