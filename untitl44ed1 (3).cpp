#include <iostream>

class Calculator {
private:
	float a;
	float b;
	float resultAdd;
	float resultSub;
	float resultMul;
	float resultDiv;
	
public:
	Calculator(float x, float y) : a(x), b(y) {}
	void add() {
		resultAdd = a + b;
	}
	void subtract() {
		resultSub = a - b;
	}
	void multiply() {
		resultMul = a * b;
	}
	void divide() {
		resultDiv = a / b;
	}
	void displayResults() const {
		std::cout << a << "+" << b << "=" << resultAdd << std::endl;
		std::cout << a << "-" << b << "=" << resultSub << std::endl;
		std::cout << a << "*" << b << "=" << resultMul << std::endl;
		std::cout << a << "/" << b << "=" << resultDiv << std::endl;
	}
};
int main() {
	float a, b;
	std::cin >> a >> b;
	
	Calculator cal(a, b);
	cal.add();
	cal.subtract();
	cal.multiply();
	cal.divide();
	cal.displayResults();
	
	return 0;
}


