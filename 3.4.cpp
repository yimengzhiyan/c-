#include<iostream>
using namespace std;
int main()
{
    char ci[100];
    char pl[100];
    int m=0;
    cin.getline(ci,100);
    for(int i=0;ci[i]!='\0';i++)
    {
        if(i%2==0)
        {
            pl[m]=ci[i];
            m=m+1;
        }
    }

    pl[m]='\0';
    cout<<pl<<endl;
    return 0;
}

