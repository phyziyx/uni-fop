int operand_1, operand_2;
	float result;
	char operator = '#';
	while (operator != '\0') {
		printf("Type your mathematical equation.  Type '0 # 0' to exit.  Operations: + - * /:\n");
		scanf("%d %c %d", &operand_1, &operator, &operand_2);
		fflush(stdin);
		switch (operator) {
			case '+': {
				result = operand_1 + operand_2;
				break;
			}
			case '-': {
				result = operand_1 - operand_2;
				break;
			}
			case '*': {
				result = operand_1 * operand_2;
				break;
			}
			case '/': {
				if (operand_2 == 0) {
					printf("You can not divide a number by 0.\n");
					operator = '\0';
				} else {
					result = operand_1 / operand_2;
				}
				break;
			}
			case '#': {
				operator = '\0';
				break;
			}
			default: {
				printf("\nInvalid operator entered!");
				break;
			}
		}

		if (operator != '\0') {
			printf("%d %c %d = %0.1f\n", operand_1, operator, operand_2, result);
		}
	}
