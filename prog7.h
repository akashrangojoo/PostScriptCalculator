#include "/home/cs689/common/689.h"

#ifndef prog7_h
#define prog7_h

void process_token(const string& token, stack<double> &s);
bool unarySign(const char& c, const string& token, const unsigned& i);
bool floatPoint(const string& token);
double getNumber(unsigned& k, const string& token, unsigned& i);
//double getNumber(const char& c, const string& token, unsigned& i, const bool& floatPointFlag);
bool isValidOperator(const char& c);
double operation(const char& c, const double&x, const double& y);
double popStack(stack<double>& s);
void printResult(const stack<double>& s);
void emptyStack(stack<double>& s);
double stringToDouble(string str);



#endif

