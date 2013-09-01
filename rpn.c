#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "rpn.h"
#include "stack.h"

bool errorOccurs;

const char* RPN_OPERATORS[8] = {"+", "-", "*", "/", "**", "#", "_", "||"};
const RPN_FUCTION_POINTER RPN_FUCTION_POINTERS[8] = {&add, &subtract, &multiply, &divide, &power, &max, &min, &distance};

double rpn_eval(char *exp) {
	errorOccurs = true;

    // create a stack based on the length of the expression
    // this is just a guess of the space we are going to need
    // the stack will automatically increase its size if necessary
    int exp_length = strlen(exp);
    struct stack *s = create_stack(exp_length / 2);
    char *token, *copy;
    double value, left, right;
    
    // we need to make a copy of the expression to not "destroy" it while
    // we parse it
    copy = malloc(sizeof(char) *exp_length);
    strcpy(copy, exp);

    // tokenise the copy of the expression based on space characters
    token = strtok(copy, " ");

    // while there is another token to process
    while (token != NULL) {
        // sscanf is like scanf, but works on strings instead of stdin
        // if the token is an value       
        if (sscanf(token, "%lf", &value) > 0) {
            // push the value on the stack
            push(s, value);

            errorOccurs = false;
        } else {
            // the token is not an value, therefore it must be an operator (hopefully)
           
            // pop the right and left operands
            right = pop(s);
            left = pop(s);
            if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = '\0';

            // evaluate the operator on left and right
            for (int i = 0; i < sizeof(RPN_OPERATORS) / sizeof(RPN_OPERATORS[0]); i++) {
            	if (strcmp(token, RPN_OPERATORS[i]) == 0) {
            		value = (*RPN_FUCTION_POINTERS[i])(left, right);

            		errorOccurs = false;
            	}
            }

            // push the result back on the stack
            push(s, value);
        }

        // get the next token
        // strtok has a state: when called with NULL as the first argument,
        // it will continue to tokenise the previous string given to it
        token = strtok(NULL, " ");
        //print_stack(s);
    }

    value = pop(s);
    free(copy);
    free_stack(s);

    return value;
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