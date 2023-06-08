#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d;
    cin>>a>>b>>c>>d;
       int sum = a + b + c + d;
    if(a>=60&&b>=60&&c>=60&&d>=60)
    {
        if(sum>=340||sum<370)
        {
            cout<< "自费生" <<endl;
        }
        else if(sum>=370)
        {
            cout<<"公费生" <<endl;
        }
    }
    else
    {
        cout<<"没有通过"<<endl;
    }
}
