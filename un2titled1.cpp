#include <iostream>
using namespace std;

int main() {
	double s = 0, h, h1;
	cin >> h;
	h1 = h;
	for (int i = 1; i <= 5; i++) {
		s += h; // 统计落地时经过的路程
		h /= 2;
		if (i == 5) {
			s += 2 * h; // 最后一次反弹需要计算高度差，乘以2得总路程
		}
		else {
			s += 2 * h; // 其他次数的反弹，落地和反弹加在一起相当于经过了2*h的路程
		}
	}
	cout << s << " " << h / 2 << endl; // 最后反弹一次，高度等于h的一半
	return 0;
}

