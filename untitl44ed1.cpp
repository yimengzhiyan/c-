#include<iostream>
#include<cmath>
using namespace std;

class point
{
private:
	float x,y;
	
public:
	point(float a,float b)
{
	x=a;
	y=b;
}
	
	friend float Distance(point p1,point p2);
};

float Distance(point p1,point p2)
{
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

int main()
{
	float p1_x,p1_y,p2_x,p2_y;
	// 输入四个点
	cin>>p1_x>>p1_y>>p2_x>>p2_y;
	point p1(p1_x,p1_y),p2(p2_x,p2_y);
	cout<<Distance(p1,p2)<<endl;
	return 0;
}

