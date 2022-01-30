// Recursive
int MyFactorial(int number) {

	return (number <= 1)
		? 1
		: number * MyFactorial(number - 1)
	;
}
