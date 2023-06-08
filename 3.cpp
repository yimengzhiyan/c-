#include<iostream>
using namespace std;
int main()
{
    int a;
    double tb,tw = 0;
    cin>>a;
    tb=tb+50+a/3;
    tw=a/1.2;
    if(tb>tw)
    {
         cout<<"bike"<<endl;
    }
    else if(tb<tw)
    {
        cout<<"walk"<<endl;
    }
    else
    {
        cout<<"all"<<endl;
    }
return 0;
}
