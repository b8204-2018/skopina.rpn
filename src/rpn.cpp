#include <utility>

#include <sstream>
#include <iostream>
#include "rpn.h"

using namespace std;


void OperationsHandler::addOperation(Operation *op) {
    OpList *current = head;
    while (current != nullptr && current->operation.getSign() != op->getSign()){
        current = current->next;
    }
    if (current == nullptr){
        current = new OpList(op);
        current->next = head;
        swap(head, current);
    }
}

void OperationsHandler::fill() {
    addOperation(new Addition);
    addOperation(new Subtraction);
    addOperation(new Multiplication);
    addOperation(new Division);
    addOperation(new Negation);
}

Operation* OperationsHandler::getOp(std::string sign) {
    OpList *current = head;
    while (current != nullptr && current->operation.getSign() != sign){
        current = current->next;
    }
    if (current == nullptr){
        return nullptr;
    }
    return &current->operation;
}

OperationsHandler::~OperationsHandler() {
    OpList *current = head;
    while (head != nullptr){
        current = current->next;
        delete head;
        head = current;
    }
}

template <typename T, typename S>
S Solver::cast(T &a) {
    stringstream stream;
    stream << a;
    S b;
    stream >> b;
    return b;
}


bool Solver::isOperation(std::string s) {
    return (handler.getOp(s) != nullptr);
}

bool Solver::isLeftBracket(const string& s) {
    return (s == "(");
}

bool Solver::isRightBracket(const string& s) {
    return (s == ")");
}

bool Solver::isNumber(char s) {
    return (s >= 0x30 && s <= 0x39);
}

bool Solver::isPoint(char s) {
    return (s == '.');
}

bool Solver::priority(Operation *op1, Operation *op2) {
    return (op1->getOrder() <= op2->getOrder());
}

string* Solver::convert(string s) {
    stack <string> op;
    string rpn [s.length()];
    string temp;
    int i, j(0);
    while (!s.empty()) {
        i = 0;
        while (!s.empty() && s[0] == ' ') {
            s.erase(0, 1);
        }
        if (isNumber(s[i])) {
            while (i < s.length() && isNumber(s[i])) {
                temp += s[i];
                i++;
                if (isPoint(s[i])) { //если вещественное число
                    if (i + 1 < s.length() && isNumber(s[i + 1])) {
                        temp += s.substr(i, 2);
                        i += 2;
                    } else {//не число
                        string err("Invalid symbol ");
                        string symbol(1, s[i]);
                        err += symbol;
                        throw (std::invalid_argument) err.c_str();
                    }
                }
            }
            rpn[j] = temp; //числа всегда добавляются в массив выхода
            j++;
            s.erase(0, temp.length());
            temp.erase();
        } else if (isLeftBracket(string(1, s[i]))){//левая скобка всегда добавляется в стек
            op.push(string(1, s[i]));
            s.erase(0, 1);
        } else if (isRightBracket(string(1, s[i]))){//если правая скобка, то из стека выталкивается все до левой скобки
            while (!op.empty() && !isLeftBracket(op.top())){
                rpn[j] = op.top();
                j++;
                op.pop();
            }
            if (op.empty() || !isLeftBracket(op.top())){
                throw (std::invalid_argument)"Expected '('";
            }
            op.pop();
            s.erase(0, 1);
        } else {
            temp = s.substr(i, s.find(' '));
            if (handler.getOp(temp) != nullptr){
                  if (op.empty() || isLeftBracket(op.top()) || !priority(handler.getOp(op.top()), handler.getOp(temp))){
                      op.push(temp);
                  } else {
                      rpn[j] = op.top();
                      j++;
                      op.pop();
                      op.push(temp);
                  }
                  s.erase(0, temp.length());
                  temp.erase();
            } else {
                  throw std::logic_error ("Invalid expression.");
            }
        }
    }
    while (!op.empty()){//конец выражение - выталкиваем все из стека
        if (isLeftBracket(op.top())){
            throw (std::invalid_argument)"Expected ')'";
        }
        rpn[j] = op.top();
        j++;
        op.pop();
    }
    auto *out = new string [j + 1];
    out[0] = cast<int, string>(j);
    for (i = 1; i <= j; i++){
        out[i] = rpn[i - 1];
    }
    return out;
}


double* Solver::extract(std::stack<double> &result, Operation *operation) {
    auto out = new double [operation->argc()];
    for (int i = operation->argc() - 1; i >= 0; i--){
        out[i] = result.top();
        result.pop();
    }
    return out;
}


double Solver::solution(const string &s) {
    try {
        string *rpn = convert(s);
        stack <double> result;
        int n = cast<string, int>(rpn[0]);
        for (int i = 1; i <= n; i++){
            if (isOperation(rpn[i])){
                Operation *op = handler.getOp(rpn[i]);
                result.push(op->operationResult(extract(result, op)));
            } else {
                result.push(cast<string, double>(rpn[i]));
            }
        }
        delete [] rpn;
        return result.top();
    } catch (std::invalid_argument &err){
        cout << err.what();
    }
}