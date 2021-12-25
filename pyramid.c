#include <stdio.h>
#include <stdlib.h>

int main() {

	int rows = 0, stars = 0, i = 0, space = 0;
	printf("Enter rows: ");
	scanf("%d", &rows);

	while (rows <= 0) {
		printf("Insert valid number of rows!  Enter rows: ");
		scanf("%d", &rows);
	}

	for (i = 1; i <= rows; ++ i, stars = 0) {
		for (space = rows - i; space > 0; -- space) {
			printf(" ");
		}
		while (stars ++ != 2 * i - 1) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
