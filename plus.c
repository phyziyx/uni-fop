#include <stdio.h>
#include <stdlib.h>

int main() {

	int rows = 0, i = 0, j = 0;

	printf("Enter rows: ");
	scanf("%d", &rows);

	while (rows < 3 || !(rows % 2)) {
		printf("Only odd number of rows can be entered!  Enter rows: ");
		scanf("%d", &rows);
	}

	for (i = 1; i <= rows; ++ i) {
		if (i == (rows + 1) / 2) {
			for (j = 1; j <= rows; ++ j) {
				printf("*");
			}
		}
		else {
			for (j = 1, k = rows / 2; j <= k; ++ j) {
				printf(" ");
			}
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
