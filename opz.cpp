#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
#include "opz.h"

using namespace std;

bool ExpressionParser::isDelimiter(string token) {
    if (token.length() != 1) return false;
    for (int i = 0; i < delimiters.length(); i++) {
        if (token[0] == delimiters[i]) return true;
    }
    return false;
}

bool ExpressionParser::isOperator(string token) {
    if (token == ("u-")) return true;
    for (int i = 0; i < operators.length(); i++) {
        if (token[0] == operators[i]) return true;
    }
    return false;
}

int ExpressionParser::priority(string token) {
    if (token == "(") return 1;
    if ((token == "+") || (token == "-")) return 2;
    if ((token == "*") || (token == "/")) return 3;
    return 4;
}

list<string> ExpressionParser::parse(string infix) {
    list<string> postfix;
    deque<string> stack1;
    //StringTokenizer tokenizer = new StringTokenizer(infix, delimiters, true);
    string prev = "";

    //char infix1[infix.size() + 1];
    //strcpy(infix1, infix.c_str());
    string currs;
    int i = 0;

    char curr = infix[i];
    while (curr != 0) {
        curr = infix[i];
        i++;
        if (isOperator(prev) && isOperator(currs.assign(1, curr))) {
            flag = false;
            throw logic_error("Некорректное выражение.");
        }
        if (curr == 0)continue;
        if (currs.assign(1, curr) == " ") continue;
        if (isDelimiter(currs.assign(1, curr))) {
            if (currs.assign(1, curr) == "(") stack1.push_back(currs.assign(1, curr));
            else if (currs.assign(1, curr) == ")") {
                while (stack1.front() != "(") {
                    postfix.push_back(stack1.front());
                    stack1.pop_front();
                    if (stack1.size() == 0) {
                        flag = false;
                        throw logic_error("Скобки не согласованы.");
                    }
                }
                stack1.pop_front();
            } else {


                while ((stack1.size() != 0) && (priority(currs.assign(1, curr)) <= priority(stack1.front()))) {
                    postfix.push_back(stack1.front());
                    stack1.pop_front();
                }


                stack1.push_front(currs.assign(1, curr));
            }

        } else {
            /*string buff="";
            while (isdigit(curr)!=false){
                buff+=curr;
                curr=infix[i];
                i++;
            }*/
            postfix.push_back(currs.assign(1, curr));
        }
        prev = curr;
    }


    while (stack1.size() != 0) {
        if (isOperator(stack1.front())) {
            postfix.push_back(stack1.front());
            stack1.pop_front();
        } else {
        	flag = false;
            throw logic_error ("Скобки не согласованы.");
       
            
        }
    }
    //string buff=buff.assign(postfix.begin(),postfix.rend())
    return postfix;
}


double Calculator::calc(list<string> postfix) {
    stack<double> stack;
    for (string x : postfix) {
        const char *buff = x.c_str();
        if (x.c_str() != NULL) {
            if (x == ("+")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(a + b);
            } else if (x == ("-")) {
                double b = stack.top();
                stack.pop();
                double a = stack.top();
                stack.push(a - b);
            } else if (x == ("*")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(a * b);
            } else if (x == ("/")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();

                stack.push(b / a);
            } else stack.push(stod(x));
        }
    }
    double result = stack.top();
    stack.pop();
    return result;
}

