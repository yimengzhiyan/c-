#include<iostream>
using namespace std;
int main()
{
 double h0,H;
 int i;
 double h = 0,s=0;
 cin>>h0;
 H=h0;
 for(i=1;i<6;i++)
 {
     s+=2*H;
     h=H/2;
     H=h;
 }
 s-=h0;
cout<<s<<""<<h<<endl;
return 0;

}
