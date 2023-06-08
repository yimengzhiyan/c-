#include <iostream>
#include <cmath>

using namespace std;

int main() {
	for (int i = 1000; i <= 9999; i++) {
		int first = i / 100;
		int second = i / 10 % 10;
		int third = i / 100 % 10;
		int fourth = i % 10;
		
		if (first == second && third != fourth) {
			int square_root = sqrt(i);
			if (square_root * square_root == i) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}

