#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "in.h"
#include "rpn.h"
#include "stack.h"
#include "utility.h"

double in_eval(char *exp) {
    // create a stack based on the length of the expression
    // this is just a guess of the space we are going to need
    // the stack will automatically increase its size if necessary
    int exp_length = strlen(exp), numOfVars = 0;
    /* struct double_stack *ds = create_double_stack(exp_length / 2); */
	struct operator_stack *os = create_operator_stack(exp_length / 2);
    char *token, *copy, *vars[10] = {NULL}, rpn_exp[255] = "";
    double value = 0;
    
    // we need to make a copy of the expression to not "destroy" it while
    // we parse it
    copy = (char *) malloc(sizeof(char) * exp_length);
    strcpy(copy, exp);

    // tokenise the copy of the expression based on space characters
    token = strtok(copy, " ");

	/* bool previousIsOperator; */

    // while there is another token to process
    while (token != NULL) {
        errorOccurs = true;
		/* previousIsOperator = false; */

        // sscanf is like scanf, but works on strings instead of stdin
        // if the token is an value
        if (isNumeric(token) && sscanf(token, "%lf", &value) > 0) {
			for (int i = 0; i < numOfVars; i++) {
				setVariable(vars[i], value);
				vars[i] = NULL;
			}

			numOfVars = 0;

            errorOccurs = false;

            // push the result back on the stack
            /* push_double(ds, value); */
        } else if (variableValid(token)) {
			char operator = *(token + strlen(token) + 1);

			if (operator == '=') {
				vars[numOfVars++] = token;

				errorOccurs = false;
			} else {
				value = getVariable(token);

				errorOccurs = !variableExists(token);

				// push the result back on stack
				/* push_double(ds, value); */
			}
        } else if (isOperator(token) || isParenthese(token)) {
            // the token is not an value, therefore it must be an operator or parenthese (hopefully)
           
            // pop the right and left operands
            /* right = pop_double(s); */
            /* left = pop_double(s); */

            /* if (previousIsOperator && s->top < -1) { */
            /*     token = NULL; */
            /*     continue; */
            /* } */

            // evaluate the operator on left and right
            /* for (int i = 0; i < sizeof(OPERATORS) / sizeof(OPERATORS[0]); i++) { */
            /* 	if (strcmp(token, OPERATORS[i]) == 0) { */
            /* 		value = (*FUCTION_POINTERS[i])(left, right); */

            /* 		errorOccurs = false; */
					/* previousIsOperator = true; */
            /* 	} */
            /* } */

            // push the result back on the stack
            /* push_double(s, value); */
		 } else if (strcmp(token, "=") != 0) {
			 token = NULL;
			 continue;
		 }

		if (errorOccurs) return value;

        // get the next token
        // strtok has a state: when called with NULL as the first argument,
        // it will continue to tokenise the previous string given to it
        token = strtok(NULL, " ");
    }

    /* value = pop_double(ds); */

    /* if (s->top != -1) errorOccurs = true; */

    free(copy);
    /* free_double_stack(ds); */
	free_operator_stack(os);

	value = rpn_eval(rpn_exp);

    /* return value; */
	return value;
}

void concat_double(char *str, double val) {
	char val_str[255];

	sprintf(val_str, "%.6lf", val);

	strncat(str, val_str, strlen(val_str));
}

void concat_operator(char *str, char *op) {
	strncat(str, op, strlen(op));
}

