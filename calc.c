#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include "rpn.h"
#include "stack.h"

int main (int argc, char *argv[]) {
	char *str;
	int length = 255, option;
	bool batchOn, echoOn, invalid;

	str = malloc(sizeof(char) * length);

	batchOn = false;
	echoOn = false;
	invalid = false;

	while ((option = getopt(argc, argv, "be")) != -1) {
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
			|| (argc == 2 && !(strcmp(argv[1], "rpn") == 0 || strcmp(argv[1], "in") == 0))
			|| (argc == 3 && !(strcmp(argv[2], "rpn") == 0 || strcmp(argv[2], "in") == 0))
			|| (argc == 4 && !(strcmp(argv[3], "rpn") == 0 || strcmp(argv[3], "in") == 0))
			|| argc > 4) {
		printf("Usage: calc [options] rpn|in\n");
		printf("\nCalculator modes:\n");
		printf("    rpn\tReverse polish notation\n");
		printf("    in\tInorder\n");
		printf("\nOptions:\n");
		printf("    -b\tBatch mode: No prompt will be printed\n");
		printf("    -e\tEcho mode: Input will be printed immediately after read\n");
	} else {
		while (1) {
			if (strcmp(argv[argc - 1], "rpn") == 0) {
				if (batchOn) printf("s3255350>>> ");

				fgets(str, length, stdin);

				double value = rpn_eval(str);
				
				if (echoOn) printf("%s", str);
				
				if (strlen(str) > 0) {
					if (batchOn) {
						printf("s3255350>>> ");
					}

					if (errorOccurs) {
						printf("Invalid RPN expression!\n");
					} else {
						printf("%.4lf\n", value);
					}
				}
			} else if (strcmp(argv[argc - 1], "in") == 0) {
				printf("inorder\n");
			}
		}

		free(str);
	}

	return EXIT_SUCCESS;
}