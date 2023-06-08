#include<iostream>
#include<queue>     //头文件定义了两个跟队列有关的类
using namespace std;
int arr[4][2]={{1,0},{0,1},{-1,0},{0,-1}};    //定义一个四行二列的数组并赋初值；定义四个方向
struct Node{int x;         //x代表目前所在行数
            int y;         //y代表目前所在列数
            int step;         //step代表目前所走步数
            Node(int x1,int y1,int step1):x(x1),y(y1),step(step1){}};    //传参
int BFS(int n,int *puzzle)          //广度优先搜索算法
{
  int *p= new int [n*n];          //申请一个n*n大小的动态整型数组，指针p指向第一个元素
  for(int i=0;i<n*n;++i) p[i]=0;         // 如果没有经过则为0，经过则为1
  queue<Node> q;          //定义一个队列
  Node node(0,0,0);         //从右上角开始，起始为0步
  q.push(node);         //存入起始位置
  while (!q.empty())             //直到空位置，即没有找到目标
  {
      node=q.front();           //node为队列的第一个元素
      q.pop();  //取出
      if (node.x==n-1&&node.y==n-1)            //判断是否找到，找到直接停止
      {
          delete p; return node.step;                //返回步数
      }
      p[node.x*n+node.y]=1;                 //使它成为被访问过的
      for(int i=0;i<4;++i)             //按右下左上顺序搜查
      {
          int x=node.x+arr[i][0];
          int y=node.y+arr[i][1];
          if (x>=0&&y>=0&&x<n&&y<n&&p[x*n+y]==0&&puzzle[x*n+y]==0)    //越界直接排除，不能通过直接排除，访问过直接排除
          {
              p[x*n+y]=1;             //标记
              Node next(x,y,node.step+1);
              q.push(next);           //核心，搜查扩散过程
          }

      }
  }
      delete p;
      return -1;                     //未找到

  }
  int main()
  {
      int n;
      int allstep;
      while(cin>>n)                  //输入迷宫的行列数
      {
          if(n==0){return 0;}
        int *puzzle=new int[n*n];
        for(int i=0; i<n*n;++i)
        {
            cin>>puzzle[i]; //输入迷宫
        }
        if(n==1&&puzzle[0]==1)
        {
            cout<<0<<endl;
            return 0;
        }
        allstep=0;          //给所需初始步数赋值
        allstep=BFS(n,puzzle);
        if(allstep==-1)
        {
            cout<<"0"<<endl;
        }
        else cout<<allstep<<endl;      //记住，目标位置从0，0开始，显示最短路径所需步数
        delete puzzle;
        system ("pause");
      }
      return 0;
  }

