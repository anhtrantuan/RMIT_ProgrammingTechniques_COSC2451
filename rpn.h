#ifndef RPN
#define RPN

typedef double (*RPN_FUCTION_POINTER)(double, double);

extern bool errorOccurs;

double rpn_eval(char *exp);

double add(double left, double right);
double subtract(double left, double right);
double multiply(double left, double right);
double divide(double left, double right);
double power(double left, double right);
double max(double left, double right);
double min(double left, double right);
double distance(double left, double right);

#endif