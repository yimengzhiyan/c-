#include <iostream>
#include <cstdio>

using namespace std;

class Imaginary { // 定义 Imaginary 类
private:
	float a, b; // 定义实部和虚部两个私有数据成员 a 和 b
public:
	Imaginary(float x=0, float y=0) : a(x), b(y) {} // 构造函数
	void print() { // 按照“a±bi”格式显示复数的成员函数 print()
		printf("%.0f", a); // 先输出实部 a
		if (b == 0) return; // 如果 b 为 0，直接返回
		if (b > 0) cout << "+"; // 如果 b 大于 0，输出“+”
		printf("%.0fi", b); // 输出虚部 b 和“i”
	}
	friend void Add(Imaginary &x, Imaginary &y); // 声明友元函数 Add() 和 Sub()
	friend void Sub(Imaginary &x, Imaginary &y);
};

void Add(Imaginary &x, Imaginary &y) { // 友元函数 Add()，用于两个复数的加法运算
	Imaginary z(x.a + y.a, x.b + y.b); // 新建一个临时 Imaginary 对象 z，其实部为 x.a+y.a，虚部为 x.b+y.b
	z.print(); // 调用成员函数 print() 显示 z 的值
	cout << endl; // 输出一个换行符
}

void Sub(Imaginary &x, Imaginary &y) { // 友元函数 Sub()，用于两个复数的减法运算
	Imaginary z(x.a - y.a, x.b - y.b); // 新建一个临时 Imaginary 对象 z，其实部为 x.a-y.a，虚部为 x.b-y.b
	z.print(); // 调用成员函数 print() 显示 z 的值
	cout << endl; // 输出一个换行符
}

int main() { // 主函数
	float x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2; // 输入四个数据，分别表示进行运算的两个复数的实部和虚部
	Imaginary imag1(x1, y1), imag2(x2, y2); // 用 x1、y1 和 x2、y2 创建 Imaginary 类对象 imag1 和 imag2
	Add(imag1, imag2); // 调用友元函数 Add() 求两个复数之和，按 a±bi 的格式显示运算结果（a 和 b 均为实数）
	Sub(imag1, imag2); // 调用友元函数 Sub() 求两个复数之差，按 a±bi 的格式显示运算结果（a 和 b 均为实数）
	return 0; // 结束程序
}


