#ifndef STACK

#define STACK

#define RESIZE_FACTOR 1.5

struct double_stack {
    int top;
    int length;
    double *data;
};

struct operator_stack {
	int top;
	int length;
	char **data;
};

struct double_stack * create_double_stack(int length);
struct operator_stack * create_operator_stack(int length);

void free_double_stack(struct double_stack *s);
void free_operator_stack(struct operator_stack *s);

void push_double(struct double_stack *s, double value);
void push_operator(struct operator_stack *s, char* value);

double peek_double(struct double_stack *s);
char* peek_operator(struct operator_stack *s);

double pop_double(struct double_stack *s);
char* pop_operator(struct operator_stack *s);

void resize_double(struct double_stack *s, int new_length);
void resize_operator(struct operator_stack *s, int new_length);

void print_double_stack(struct double_stack *s);
void print_operator_stack(struct operator_stack *s);

#endif
