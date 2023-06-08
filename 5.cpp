#include<iostream>
using namespace std;
int main()
{
    double a,b;
char c;
    cin>>a>>b>>c;
    switch (c)
    {
    case '+':
        cout<<a+b<<endl;
        break;
    case '-':
        cout<<a-b<<endl;
        break;
    case '*':
        cout<<a * b<<endl;
        break;
    case '/':
        if(b == 0)
        {
            cout<<"error"<<endl;
        }
        else
        {
            cout<<a/b<<endl;
        }
        break;
        default:
        cout<<"operate error"<<endl;
        break;
    }

        return 0;

}
