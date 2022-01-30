// Loop
int Decimal2Binary(int decimal) {

	int binary = 0, mul = 1;
	while (decimal > 0) {
		binary += mul * (decimal % 2);
		decimal /= 2;
		mul *= 10;
	}
	return binary;
}

// Recursive
int Decimal2Binary(int decimal) {
	if (decimal == 0) return 0;
	int remainder = decimal % 2;
	return remainder + 10 * Decimal2Binary(decimal / 2);
}
