// START OF FILE

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int GenerateNumber() {
	srand(time(NULL));
	return (rand() % 100) + 1;
}

int main() {

	// Guess the Number
	int number = 0, input = 0, attempts = 0;
	number = GenerateNumber();
	printf("I have chosen a number between 1 to 100.  Try to guess it!\n");

	while (input == 0) {
		scanf("%d", &input);
		++ attempts;

		if (input > number) {
			printf("Too high.  Try again.\n");
		} else if (input < number) {
			printf("Too low.  Try again.\n");
		} else {
			printf("Excellent!  You guessed the number in %d tries!\n", attempts);
			printf("Would you like to play again (y or n)? ");
			
			char res;
			fflush(stdin);
			scanf("%c", &res);
			if (res == 'n') {
				exit(0);
			} else {
				main();
			}
		}
		input = 0;
	}

	return 0;
}

// END OF FILE
