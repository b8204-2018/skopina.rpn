#include "rpn.h"
#include <stack>
#include "calc/calc.h"
#include <sstream>


#include <iostream>


bool Solver::isOperation(char s) {
    return (s == ADDITION || s == SUBTRACTION || s == MULTIPLICATION || s == DIVISION);
}

bool Solver::isLeftBracket(char s) {
    return (s == '(');
}

bool Solver::isRightBracket(char s) {
    return (s == ')');
}

bool Solver::isNumber(char s) {
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 10; i++){
        if (s == numbers[i]){
            return true;
        }
    }
    return false;
}

bool Solver::isPoint(char s) {
    return (s == '.');
}

bool Solver::priority(char s1, char s2) {
    if ((s1 == MULTIPLICATION || s1 == DIVISION) && (s2 == ADDITION || s2 == SUBTRACTION)){
            return true;
    }
    if ((s1 == ADDITION || s1 == SUBTRACTION) && (s2 == MULTIPLICATION || s2 == DIVISION)){
        return false;
    }
    if ((s1 == ADDITION || s1 == SUBTRACTION) && (s2 == ADDITION || s2 == SUBTRACTION)){
        return true;
    }
    if ((s1 == MULTIPLICATION || s1 == DIVISION) && (s2 == MULTIPLICATION || s2 == DIVISION)){
        return true;
    }
}

string* Solver::convert(const string& s) {
    stack <char> operations;
    string rpn [s.length()];
    string number;
    int i(0), j(0);
    while (i < s.length() - 1){
        while (s[i] == ' '){
            i++;
        }
        if (isNumber(s[i])){
            while (i < s.length() && isNumber(s[i])){
                number += s[i];
                i++;
                if (isPoint(s[i])){ //если вещественное число
                    if (i + 1 < s.length() && isNumber(s[i + 1])){
                        number += s.substr(i, 2);
                        i += 2;
                    } else {//не число
                        string err("Invalid symbol ");
                        string symbol (1, s[i]);
                        err = err + symbol;
                        throw (std::invalid_argument)err.c_str();
                    }
                }
            }
            rpn[j] = number; //числа всегда добавляются в массив выхода
            j++;
            number.erase();
        } else if (isOperation(s[i])){
            /*
             * если стек операций пуст - добавление
             * если последняя в стеке - левая скобка, добавляем
             * если последняя операция в стеке имеет приоритет ниже текущей, добавляем в стек
             * */
            if (operations.empty() || isLeftBracket(operations.top()) || !priority(operations.top(), s[i])){
                operations.push(s[i]);
                i++;
            } else {//выталкиваем из стека в массив выхода последнюю операцию, а текущую помещаем в стек
                rpn[j] = string(1, operations.top());
                j++;
                operations.pop();
                operations.push(s[i]);
                i++;
            }
        } else if (isLeftBracket(s[i])){//левая скобка всегда добавляется в стек
            operations.push(s[i]);
            i++;
        } else if (isRightBracket(s[i])){//если правая скобка, то из стека выталкивается все до левой скобки
            bool leftBracket(false);
            while (!operations.empty() && !isLeftBracket(operations.top())){
                rpn[j] = string(1, operations.top());
                j++;
                operations.pop();
            }
            if (operations.empty() || !isLeftBracket(operations.top())){
                throw (std::invalid_argument)"Expected '('";
            }
            operations.pop();
            i++;
        } else {//если встречен некорректный символ
            string err("Invalid symbol ");
            string symbol (1, s[i]);
            err = err + symbol;
            throw (std::invalid_argument)err.c_str();
        }
    }
    while (!operations.empty()){//конец выражение - выталкиваем все из стека
        rpn[j] = string(1, operations.top());
        j++;
        operations.pop();
    }
    auto *out = new string [j + 1];
    stringstream str;
    str << j;
    str >> out[0];
    for (i = 1; i <= j; i++){
        out[i] = rpn[i - 1];
    }
    return out;
}


double Solver::solution(const string &s) {
    try {
        string *rpn = convert(s);
        Additor add;
        Subtractor sub;
        Divisor div;
        Multiplicator mul;
        BasicSolver *arr[] = {&add, &sub, &div, &mul};
        stack <double> result;
        stringstream stream;
        stream << rpn[0];
        int n;
        stream >> n;
        stream.clear();
        int i(1);
        while (i <= n) {
            if (isOperation(rpn[i][0])) {
                int j(0);
                while (rpn[i][0] != arr[j]->getOperationSymbol()) { j++; }
                double a(result.top());
                result.pop();
                double b(result.top());
                result.pop();
                result.push(arr[j]->operationResult(b, a));
            } else {
                double x;
                stream << rpn[i];
                stream >> x;
                stream.clear();
                result.push(x);
            }
            i++;
        }
        return result.top();
    } catch (std::invalid_argument &err){
        cout << err.what();
    }
}