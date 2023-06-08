#include<iostream>
using namespace std;
int main()
{
    float x,y;
    while(1)
    {
cin>>x>>y;
        if(x<=1&&x>=-1&&y<=1&&y>=-1)
        {
            cout<<"yes"<<endl;
        }
        else if(x==0&&y==0)
        {
            cout<<"yes"<<endl;
            break;
        }

        else

        {
            cout<<"no"<<endl;
        }
    }

}
