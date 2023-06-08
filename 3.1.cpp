#include<iostream>
using namespace std;
int main()
{
    int h[10];
    int i=0;
    int h1;
    int sum=0;
    cin>>h1;
    for(i=1;i<10;i++)
    {
        cin>>h[i];
    }

    h1+=30;
    for(i=1;i<11;i++)
    {
        if(h1>=h[i])
        {
            sum+=1;
        }

    }
    cout<<sum<<endl;return 0;
}
