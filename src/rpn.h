#ifndef RPN_RPN_H
#define RPN_RPN_H

#include <string>

using namespace std;

class Solver {
    string* convert(const string& s);
    bool isOperation(char s);
    bool isLeftBracket(char s);
    bool isRightBracket(char s);
    bool isNumber(char s);
    bool isPoint(char s);
    bool priority(char s1, char s2);
public:
    double solution (const string& s);
};


#endif //RPN_RPN_H
