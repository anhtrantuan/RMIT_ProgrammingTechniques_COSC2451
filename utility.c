#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

bool errorOccurs;

const char* OPERATORS[8] = {"**", "*", "/", "+", "-", "#", "_", "||"};
const FUCTION_POINTER FUCTION_POINTERS[8] = {&power, &multiply, &divide, &add, &subtract, &max, &min, &distance};

const char* VARIABLE_NAMES[10] = {"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9"};
double VARIABLES[10] = {0};
bool VARIABLES_STATUS[10] = {false};

int numberOfVariables = 0;

bool isNumeric(char *exp) {
	if (exp == NULL || *exp == '\0' || isspace(*exp)) return false;
    char *p;
    strtod(exp, &p);

    return *p == '\0';
}

bool isOperator(char *exp) {
	for (int i = 0; i < sizeof(OPERATORS) / sizeof(OPERATORS[0]); i++) {
		if (strcmp(exp, OPERATORS[i]) == 0) return true;
	}

	return false;
}

bool isParenthese(char *exp) {
	return strcmp(exp, "(") || strcmp(exp, ")");
}

bool setVariable(char *name, double value) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0) {
			VARIABLES[i] = value;
			VARIABLES_STATUS[i] = true;

			return true;
		}
	}

	return false;
}

bool variableValid(char *name) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0) return true;
	}

	return false;
}

bool variableExists(char *name) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0 && VARIABLES_STATUS[i]) return true;
	}

	return false;
}

double getVariable(char *name) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0) return VARIABLES[i];
	}

	return 0;
}

double add(double left, double right) {
	return left + right;
}

double subtract(double left, double right) {
	return left - right;
}

double multiply(double left, double right) {
	return left * right;
}

double divide(double left, double right) {
	return left / right;
}

double power(double left, double right) {
	return pow(left, right);
}

double max(double left, double right) {
	return fmax(left, right);
}

double min(double left, double right) {
	return fmin(left, right);
}

double distance(double left, double right) {
	return abs(left - right);
}

