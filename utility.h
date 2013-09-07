#ifndef UTILITY

#define UTILITY

typedef double (*FUCTION_POINTER)(double, double);

extern const FUCTION_POINTER FUCTION_POINTERS[8];

extern bool errorOccurs;

extern const char* OPERATORS[8];

bool isNumeric(char *exp);

int getNumberOfOperators();

bool isOperator(char *exp);

bool isParenthese(char *exp);

int getOperatorPrecedence(char *exp);

bool setVariable(char *name, double value);

bool variableValid(char *name);

bool variableExists(char *name);

double getVariable(char *name);

double add(double left, double right);
double subtract(double left, double right);
double multiply(double left, double right);
double divide(double left, double right);
double power(double left, double right);
double max(double left, double right);
double min(double left, double right);
double distance(double left, double right);

#endif
