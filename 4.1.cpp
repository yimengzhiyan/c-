#include<iostream>
using namespace std;
bool wanshu(int n)
{
    int i;
    int sum=0;
    for(i=1;i<n;i++)
    {
        if(n%i==0)
            sum+=i;
    else
    {
    continue;
    }
    if(n==sum)
    {
        return true;
    }
    else
    {
        return false;
    }
    }

}

int main()
{
    int x;
cin>>x;
if(wanshu(x))
{
    cout<<"true"<<endl;
}
else
{
    cout<<"false"<<endl;
}
}
