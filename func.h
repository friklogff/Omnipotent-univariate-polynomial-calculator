#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <stack>
#include <ctype.h>
#include <vector>
#include <string.h>
using namespace std;

int instack(string c);
int outstack(string c);
vector<string> InfixToPostfix(string str);
bool operation(string tmp,stack<double> &stk);
double postfix2ans(vector<string> exp);
void test();

#endif // FUNC_H

