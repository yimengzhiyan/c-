#include<iostream>
using namespace std;
int CountDown(int year,int month,int day);
int main()
{

    int year,month,day;
    cin>>year>>month>>day;
    CountDown( year, month, day);
    return 0;
}
int CountDown(int year,int month,int day)
    {
        int x;
        if(year!=2012||(month>7||month==0)||(month==7&&month>27))
        {
            cout<<"error"<<endl;
        }
        else if(month==7&&month>0&&month<=27)
                {
                   x = 27- day;cout<<x<<endl;
                }
                else
                {
                    switch(month)
                    {
                      	case 1:x=31-day+29+31+30+31+30+27;break;
		case 2:x=29-day+31+30+31+30+27;break;
		case 3:x=31-day+30+31+30+27;break;
		case 4:x=30-day+31+30+27;break;
		case 5:x=31-day+30+27;break;
		case 6:x=30-day+27;break;
                    }
                    cout<<x<<endl;
                }
                return x;
    }
