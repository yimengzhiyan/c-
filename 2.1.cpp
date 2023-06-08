#include<iostream>
using namespace std;
int main()
{
    int arr[6];
    int sum,i;
    for(i=0;i<6;i++)
    {
        cin>>arr[i];
    }
    for(i=1;i<6;i++)
    {
        if(arr[i]<arr[0])
        {
            sum+=arr[i];
        }
    }
    cout<<sum<<endl;
    return 0;
}
