#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

struct double_stack * create_double_stack(int length) {
    struct double_stack * s = (struct double_stack *) malloc(sizeof(struct double_stack));
    s->top = -1;
    s->length = length;
    s->data = (double *) malloc(sizeof(double) * length);
    
    return s;
}

struct operator_stack * create_operator_stack(int length) {
	struct operator_stack * s = (struct operator_stack *) malloc(sizeof(struct operator_stack));
	s->top = -1;
	s->length = length;
	s->data = (char **) malloc(sizeof(char *) * length);

	return s;
}

void free_double_stack(struct double_stack *s) {
    free(s->data);
    free(s);
}

void free_operator_stack(struct operator_stack *s) {
	for (int i = 0; i < s->length; i++) {
		free(s->data[i]);
	}
	free(s->data);
	free(s);
}

void push_double(struct double_stack *s, double value) {
    if (s->top == s->length - 1) {
        resize_double(s, s->length * RESIZE_FACTOR);
    }
    
    s->top++;
    s->data[s->top] = value;
}

void push_operator(struct operator_stack *s, char *value) {
	if (s->top == s->length -1) {
		resize_operator(s, s->length * RESIZE_FACTOR);
	}

	s->top++;
	s->data[s->top] = (char *) malloc(sizeof(char) * (strlen(value) + 1));
	strcpy(s->data[s->top], value);
}

double peek_double(struct double_stack *s) {
    return s->data[s->top];
}

char * peek_opeartor(struct operator_stack *s) {
	return s->data[s->top];
}

double pop_double(struct double_stack *s) {
    s->top--;

    return s->data[s->top + 1];
}

char * pop_operator(struct operator_stack *s) {
	s->top--;

	return s->data[s->top + 1];
}

void resize_double(struct double_stack *s, int new_length) {
    double *old_data = s->data;

    s->data = (double *) malloc(sizeof(double) * new_length);

    for (int i = 0; i <= s->top; i++) {
        s->data[i] = old_data[i];
    }
    
    s->length = new_length;
    free(old_data);
}

void resize_operator(struct operator_stack *s, int new_length) {
	char **old_data = s->data;

	s->data = (char **) malloc(sizeof(char *) * new_length);

	for (int i = 0; i <= s->top; i++) {
		s->data[i] = old_data[i];
	}

	s->length = new_length;
	free(old_data);
}

void print_double_stack(struct double_stack *s) {
    for (int i = 0; i <= s->top; i++) {
        printf("%lf ", s->data[i]);
    }

	printf("\n");
}

void print_operator_stack(struct operator_stack *s) {
	for (int i = 0; i <= s->top; i++) {
		printf("%s", s->data[i]);
	}

	printf("\n");
}

