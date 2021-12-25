#include <stdio.h>
#include <stdlib.h>

int main() {

	int rows = 0, idx = 0, row = 0;

	printf("Enter rows: ");
	scanf("%d", &rows);

	while (rows < 3 || !(rows % 2)) {
		printf("Only odd number of rows can be entered!  Enter rows: ");
		scanf("%d", &rows);
	}

	for (row = 1; row < rows; row += 2) {
		for (idx = (rows - row) / 2; idx > 0; -- idx) {
			printf(" ");
		}
		for (idx = 1; idx <= row; idx ++) {
			printf("*");
		}
		printf("\n");
	}

	for (row = rows; row > 0; row -= 2) {
		for (idx = (rows - row) / 2; idx > 0; -- idx) {
			printf(" ");
		}
		for (idx = 1; idx <= row; idx ++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
