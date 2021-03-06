#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "in.h"
#include "rpn.h"
#include "stack.h"

bool errorOccurs;

int main (int argc, char *argv[]) {
	int length = 1024, option;
	char str[length];
	bool batchOn, echoOn, invalid, isRPN, isIn;

	batchOn = false;
	echoOn = false;
	invalid = false;

	while ((option = getopt(argc - 1, argv, "be")) != -1) {
		switch(option) {
			case 'b':
				batchOn = true;
				break;
			case 'e':
				echoOn = true;
				break;
			default:
				invalid = true;
				break;
		}
	}

	if (invalid || argc == 1
			|| (argc == 2 && !(strcmp(argv[1], "--rpn") == 0 || strcmp(argv[1], "--in") == 0))
			|| (argc == 3 && !(strcmp(argv[2], "--rpn") == 0 || strcmp(argv[2], "--in") == 0))
			|| (argc == 4 && !(strcmp(argv[3], "--rpn") == 0 || strcmp(argv[3], "--in") == 0))
			|| argc > 4) {
		printf("Usage: calc [options] --rpn|--in\n");
		printf("\nCalculator modes:\n");
		printf("    --rpn\tReverse polish notation\n");
		printf("    --in\tInorder\n");
		printf("\nOptions:\n");
		printf("    -b\tBatch mode: No prompt will be printed\n");
		printf("    -e\tEcho mode: Input will be printed immediately after read\n");
	} else {
		isRPN = strcmp(argv[argc - 1], "--rpn") == 0;
		isIn = strcmp(argv[argc - 1], "--in") == 0;

		while (1) {
			if (batchOn && isatty(STDIN_FILENO)) printf("s3255350>>> ");

			char *input = fgets(str, length, stdin);
			if (input == NULL || input == (char *) EOF)	break;

			if (!(strlen(str) == 0 || strcmp(str, "\n") == 0 || strcmp(str, "\r\n") == 0)) {
				if (strlen(str) > 0) {
					if (str[strlen(str) - 2] == '\r') str[strlen(str) - 2] = '\0';
					if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

					if (batchOn) {
						printf("s3255350>>> ");
					}

					double value = 0;
					if (isRPN) {
						value = rpn_eval(str);
					} else if (isIn) {
						value = in_eval(str);
					}
			
					if (errorOccurs) {
						if (isRPN) {
							printf("Invalid RPN expression!\n");
						} else if (isIn) {
							printf("Invalid Inorder expression!\n");
						}
					} else {
						if (echoOn) printf("%s = ", str);
						printf("%lf\n", value);
					}
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
