#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "in.h"
#include "rpn.h"
#include "stack.h"
#include "utility.h"

double in_eval(char *exp) {
    int exp_length = strlen(exp), numOfVars = 0;
	struct operator_stack *os = create_operator_stack(exp_length / 2);
    char *token, *copy, *vars[10] = {NULL}, rpn_exp[1024] = "";
    double value = 0;
    
    copy = (char *) malloc(sizeof(char) * exp_length);
    strcpy(copy, exp);

    token = strtok(copy, " ");

	bool previousIsOperator = false,
		 previousIsLeftParenthese = false,
		 varsSet = false;

    while (token != NULL) {
        errorOccurs = true;
		varsSet = false;

        if (isNumeric(token) && sscanf(token, "%lf", &value) > 0) {
			if (!(strlen(rpn_exp) == 0 || previousIsOperator || previousIsLeftParenthese)) return value;

			for (int i = 0; i < numOfVars; i++) {
				setVariable(vars[i], value);
				vars[i] = NULL;
				varsSet = true;
			}

			numOfVars = 0;

            errorOccurs = false;
			previousIsOperator = false;
			previousIsLeftParenthese = false;

			concat_double(rpn_exp, value);
        } else if (variableValid(token)) {
			if (!(strlen(rpn_exp) == 0 || previousIsOperator
						|| previousIsLeftParenthese)) return value;

			char operator = *(token + strlen(token) + 1);

			if (operator == '=') {
				vars[numOfVars++] = token;

				errorOccurs = false;
			} else {
				value = getVariable(token);

				errorOccurs = !variableExists(token);

				concat_double(rpn_exp, value);
			}

			previousIsOperator = false;
			previousIsLeftParenthese = false;
        } else if (isOperator(token) || isParenthese(token)) {
			if ((isOperator(token) && previousIsOperator)
					|| (strcmp(token, ")") == 0 && strlen(rpn_exp) == 0)) return value;
           
			if (numOfVars > 0) return value;

			char *op = NULL;

			if (strcmp(token, "(") == 0) {
				push_operator(os, token);

				previousIsLeftParenthese = true;
			} else if (strcmp(token, ")") == 0) {
				op = peek_operator(os);

				if (strcmp(op, "(") == 0) return value;

				op = pop_operator(os);

				while (strcmp(op, "(") != 0) {
					if (strcmp(op, ")") == 0) return value;

					concat_operator(rpn_exp, op);

					op = pop_operator(os);
				}
				
				previousIsLeftParenthese = false;
			} else {
				int pre1 = -1, pre2 = getOperatorPrecedence(token);
				if (os->top > -1) pre1 = getOperatorPrecedence(peek_operator(os));

				while (pre2 > pre1 && pre1 > 0 && os->top > -1) {
					concat_operator(rpn_exp, pop_operator(os));

					if (os->top > -1) pre1 = getOperatorPrecedence(peek_operator(os));
				}

				push_operator(os, token);

				previousIsOperator = true;
				previousIsLeftParenthese = false;
			}

			errorOccurs = false;
		 } else if (strcmp(token, "=") == 0) {
			 errorOccurs = false;
		 } else {
			 return value;
		 }

		if (errorOccurs) return value;

        token = strtok(NULL, " ");
    }

	while (os->top > -1) concat_operator(rpn_exp, pop_operator(os));

    free(copy);
	free_operator_stack(os);

	if (!(varsSet || errorOccurs)) value = rpn_eval(rpn_exp);

	return value;
}

void concat_double(char *str, double val) {
	char val_str[255];

	sprintf(val_str, "%lf", val);

	concat_rpn(str, val_str);
}

void concat_operator(char *str, char *op) {
	concat_rpn(str, op);
}

void concat_rpn(char *str, char *exp) {
	if (strlen(str) > 0) strcat(str, " ");

	strncat(str, exp, strlen(exp));
}

