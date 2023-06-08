#include<iostream>
using namespace std;
int main()
{
    int n=1000;
    int a,b,c,d;
    double p;
    do
    {
        a=n/1000;b=n%1000/100;c=n%100/10;d=n%10;
        for(p=1;p<99;p++)
        {
            if(p*p==n&&a==b&&c==d&&a!=d)
            {
                cout<<n<<endl;
                break;
            }
        }
          n++;
    }
    while(n<9999);

        return 0;


}
