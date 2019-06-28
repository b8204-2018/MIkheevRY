#include <iostream>
#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
#include "opz.h"
using namespace std;
int main() {

    string s = "( 22 + 55 * 22 ) /  12";
    ExpressionParser n ;
    Calculator calculator;
    list<string> expression;
    try {
         expression= n.parse(s);
    }catch(logic_error e) {
        cout << e.what()<<endl;
    }
    bool flag = n.flag;
    if (flag) {
        for (string x : expression) {cout<<x;}
        cout<<endl;
        cout<<calculator.calc(expression);
    }

    return 0;
}