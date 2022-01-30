// Recursive
// Prints the sum of the first X numbers
int MySum(int number) {

	return (number > 0)
		? MySum(number - 1) + number
		: number
	;
}
