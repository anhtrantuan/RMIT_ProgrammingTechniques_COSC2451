#ifndef UTILITY

#define UTILITY

extern bool errorOccurs;

extern const char* OPERATORS[8];

bool isNumeric(char *exp);

bool isOperator(char *exp);

bool setVariable(char *name, double value);

bool variableValid(char *name);

bool variableExists(char *name);

double getVariable(char *name);

#endif
