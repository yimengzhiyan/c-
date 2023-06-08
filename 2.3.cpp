#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    double a=2,b=1,c;
    int i, n;
    double sum=0;
    cin>>n;
    for(i=1;i<n;i++)
    {
        sum=sum+a/b;
        c=b;
        b=a;
        a=a+c;

    }
    cout<<fixed<<setprecision(4)<<sum<<endl;
    return 0;
}
