#include<iostream>
using namespace std;
int main()
{
    int i;
    double score[100];
    double max=0,min=0,sum=0,ava=0;
    for(i=1;i<=6;i++)
    {
        cin>>score[i];
    }
    max=score[1];min=score[1];
    for(int j=1;j<=6;j++)
    {
        if (score[j]>max)
        max=score[i];

    }
    for(int k=1;k<=6;k++)
    {
        if (score[k]<min)
        min=score[k];

    }
      for(i=1;i<=6;i++)
      {
           sum+=score[i];
      }
   sum=sum-max-min;
   ava=sum/4;
   cout<<ava<<endl;
   return 0;
}
