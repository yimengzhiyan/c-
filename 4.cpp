#include<iostream>
#include<iomanip>
using namespace std;
int main()
{

    float pt;
    cin>>pt;
    float cost = 0;
    if(pt>0&&pt<=3)
    {
        cout<<"cost 5"<<endl;
    }
    else if(pt>3)
    {

        cost = cost + 5 + (pt - 3)* 2;
        if(cost>40)
        {
            cout<<"cost"<<40<<endl;
        }
        else
        {
            cout<<"cost"<<cost<<endl;
        }
    }
    else
        {
        cout<<"error"<<endl;
        }

    return 0;
}
