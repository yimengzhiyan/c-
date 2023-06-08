#include<iostream>
#include <cmath>
#include <Eigen/Dense>    // Eigenͷ�ļ���<Eigen/Dense>����Eigen���������еĺ�������
using namespace std;
float foun(int s1,int s2);
int main()
{
    Eigen::MatrixXd m(23,23);
    int x,y;

    for(x=1;x<24;x++)
    {
        for(y=1;y<24;y++)
           m(x-1,y-1)=foun(x,y);
    }
    std::cout << m <<"  " <<std::endl;

}
float foun(int s1,int s2)
{

    struct G
    {
        int d;
        int z1;
        int z2;

    }G[23]={
           {2,1,0},//1
           {2,3,0},//2
           {2,3,0},//3
           {2,3,0},//4
           {2,3,0},//5
           {2,3,0},//6
           {2,3,0},//7
           {2,3,0},//8
           {2,3,0},//9
           {2,2,0},//10
           {3,3,1},//11
           {3,3,1},//12
           {3,3,2},//13
           {3,3,3},//14
           {2,4,0},//15
           {2,4,0},//16
           {2,5,0},//17
           {2,5,0},//18
           {2,5,0},//19
           {2,6,0},//20
           {2,6,0},//21
           {2,7,0},//22
           {2,7,0},//23

    };

    double cop[22][22];
    int n;
    double c,cm;


    s1-=1;
    s2-=1;
    if(G[s1].d == G[s2].d)//��һλ���ּ�������ͬʱ
    {
         if(G[s1].z1 == G[s2].z1)//dͬz1��ͬ
           if(G[s1].z2 == G[s2].z2)//d,z1,z2����ͬ
             {cop[s1][s2]=0.5625;}

           else//d,z1ͬ��z2��ͬ    ��û��������0317
            {
              if(G[s1].z2==1||G[s2].z2==1)//����
                if(G[s1].z2==2||G[s2].z2==2)//G13
                   {c=0.5625;
                   n=2;
                   cm=pow(0.5,n);
                   cop[s1][s2]=c*cm+cm;}
                else
                  {
                  c=0.5625;
                   n=2;
                   cm=pow(0.5,n);
                   cop[s1][s2]=c*cm;}
               else
                   {c=0.5625;
                   n=2;
                   cm=pow(0.5,n);
                   cop[s1][s2]=c*cm;}
            }
         else    //dͬz1��ͬ   15 17
            {c=1;
             n=G[s1].d+G[s2].d-2;
             cm=pow(0.5,n);
             cop[s1][s2]=c*cm;
            }
    }
    else//d��ͬ
    {
      if(G[s1].z1 == G[s2].z1)//d��ͬz1��ͬ,��û��������0317
        {
          if(G[s2].z1==3&&G[s1].z1==3)//G 6 2 3 4...
            if(s1==5||s2==5)//G6
              if(G[s2].z2==1&&G[s1].z2==1)
                {cop[s1][s2]=0.5;}
              else
              {c=0.5625;
               n=2;
               cm=pow(0.5,n);
               cop[s1][s2]=c*cm;}
            else
             {
               c=0.5625;
               n=2;
               cm=pow(0.5,n);
               cop[s1][s2]=c*cm;
             }
           else
           {
             cop[s1][s2]=0.5;
           }

              }




       else//d��ͬ��z1��ͬ,��û��������0317
       {
         c=1;
         n=G[s1].d+G[s2].d-2;
         cm=pow(0.5,n);
         cop[s1][s2]=c*cm;
       }
    }

     return cop[s1][s2];


}
