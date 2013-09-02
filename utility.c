#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

bool errorOccurs;

const char* OPERATORS[8] = {"+", "-", "*", "/", "**", "#", "_", "||"};
const char* VARIABLE_NAMES[10] = {"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9"};
double VARIABLES[10] = {0};

int numberOfVariables = 0;

bool isNumeric(char *exp) {
	if (exp == NULL || *exp == '\0' || isspace(*exp)) return false;
    char *p;
    strtod(exp, &p);

    return *p == '\0';
}

bool setVariable(char *name, double value) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0) {
			VARIABLES[i] = value;

			return true;
		}
	}

	return false;
}

bool variableExists(char *name) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0) return true;
	}

	return false;
}

double getVariable(char *name) {
	for (int i = 0; i < 10; i++) {
		if (strcmp(VARIABLE_NAMES[i], name) == 0) return VARIABLES[i];
	}

	return 0;
}
