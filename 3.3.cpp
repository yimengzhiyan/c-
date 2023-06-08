#include<iostream>
using namespace std;
int main()
{
    int k;
    int j=0;
    cin>>k;
    int num[81];
    for(int i=0;i<=k-1;i++)
    {
        cin>>num[i];
    }
    while( j<k)
    {
        if(j!=0&&j!=k-1)
        {
            if((num[j]>num[j-1])&&(num[j]>num[j+1])||(num[j]<num[j-1])&&(num[j]<num[j+1]))
                cout<<j<<' ';
        }
        if(j==0&&(num[j]!=num[j+1])&&k>=2)
        {

        cout<<0<<' ';
        }
        if(j==k-1&&(num[j]!=num[j-1])&&k>=2)
            {
                cout<<k-1<<' ';
            }
    }   j++;
     return 0;
}
