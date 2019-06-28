#ifndef OPZ_FROM_JAVA_OPZ_H
#define OPZ_FROM_JAVA_OPZ_H

#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
using namespace std;
class ExpressionParser{
private:
    string operators = "+-*/";
    string delimiters = "() " + operators;
public:
    bool flag =true ;
    bool isDelimiter(string token);
    bool isOperator(string token);
    int priority(string token);
    list<string> parse(string infix);
};
class Calculator{
public:
    double calc(list<string> postfix);

};


#endif //OPZ_FROM_JAVA_OPZ_H
