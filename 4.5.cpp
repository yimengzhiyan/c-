#include<iostream>
using namespace std;
int fib(int n);
int main()

{
    int n,s;
     cin>>n;
    s=fib(n);
    cout<<s<<endl;
    return 0;
}
int fib(int n)
{
    int sum;
    if(n<2)
    {
       sum=1;
    }
    else
    {
        sum=fib(n-1)+fib(n-2);

    }
    return sum;
}
