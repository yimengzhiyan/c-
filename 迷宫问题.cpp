#include<iostream>
#include<queue>     //ͷ�ļ������������������йص���
using namespace std;
int arr[4][2]={{1,0},{0,1},{-1,0},{0,-1}};    //����һ�����ж��е����鲢����ֵ�������ĸ�����
struct Node{int x;         //x����Ŀǰ��������
            int y;         //y����Ŀǰ��������
            int step;         //step����Ŀǰ���߲���
            Node(int x1,int y1,int step1):x(x1),y(y1),step(step1){}};    //����
int BFS(int n,int *puzzle)          //������������㷨
{
  int *p= new int [n*n];          //����һ��n*n��С�Ķ�̬�������飬ָ��pָ���һ��Ԫ��
  for(int i=0;i<n*n;++i) p[i]=0;         // ���û�о�����Ϊ0��������Ϊ1
  queue<Node> q;          //����һ������
  Node node(0,0,0);         //�����Ͻǿ�ʼ����ʼΪ0��
  q.push(node);         //������ʼλ��
  while (!q.empty())             //ֱ����λ�ã���û���ҵ�Ŀ��
  {
      node=q.front();           //nodeΪ���еĵ�һ��Ԫ��
      q.pop();  //ȡ��
      if (node.x==n-1&&node.y==n-1)            //�ж��Ƿ��ҵ����ҵ�ֱ��ֹͣ
      {
          delete p; return node.step;                //���ز���
      }
      p[node.x*n+node.y]=1;                 //ʹ����Ϊ�����ʹ���
      for(int i=0;i<4;++i)             //����������˳���Ѳ�
      {
          int x=node.x+arr[i][0];
          int y=node.y+arr[i][1];
          if (x>=0&&y>=0&&x<n&&y<n&&p[x*n+y]==0&&puzzle[x*n+y]==0)    //Խ��ֱ���ų�������ͨ��ֱ���ų������ʹ�ֱ���ų�
          {
              p[x*n+y]=1;             //���
              Node next(x,y,node.step+1);
              q.push(next);           //���ģ��Ѳ���ɢ����
          }

      }
  }
      delete p;
      return -1;                     //δ�ҵ�

  }
  int main()
  {
      int n;
      int allstep;
      while(cin>>n)                  //�����Թ���������
      {
          if(n==0){return 0;}
        int *puzzle=new int[n*n];
        for(int i=0; i<n*n;++i)
        {
            cin>>puzzle[i]; //�����Թ�
        }
        if(n==1&&puzzle[0]==1)
        {
            cout<<0<<endl;
            return 0;
        }
        allstep=0;          //�������ʼ������ֵ
        allstep=BFS(n,puzzle);
        if(allstep==-1)
        {
            cout<<"0"<<endl;
        }
        else cout<<allstep<<endl;      //��ס��Ŀ��λ�ô�0��0��ʼ����ʾ���·�����貽��
        delete puzzle;
        system ("pause");
      }
      return 0;
  }

