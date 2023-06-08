#include<iostream>
using namespace std;
#include<string>
#define MAX 2000
//设计食品信息结构体

struct FOOD
{
	//食品名称
	string m_Name;
    //产地
	string m_Origin;
		//生产日期;
	string m_Day;
	//生产时间
	string m_Time;
	//品种
	string m_Vari;
	//生产批次
	string m_Num;
};
//设计食品安全信息管理系统结构体
struct inforMS
{
	//信息管理系统中保存的食品信息数组
	struct FOOD foodArray[MAX];
	//信息管理系统中当前记录的食品数量
	int m_Size;
};

//添加食品信息
void addFOOD(inforMS* infor)
{
	//判断信息库是否已满，若满了就不再允许添加
	if (infor->m_Size == MAX)
	{
		cout << "抱歉，信息库已满,无法添加。若要添加，请清理信息。" << endl;
		return;
	}
	else
	{
		//添加具体联系人
		// 食品名称
		string Name;
		cout << "请输入您想要添加的食品名称：" << endl;
		cin >> Name;
		infor->foodArray[infor->m_Size].m_Name = Name;
		//产地
		string Origin;
		cout << "请输入该食品的产地：" << endl;
		cin >> Origin;
		infor->foodArray[infor->m_Size].m_Origin = Origin;
		//生产日期
		string Day;
		cout << "请输入该食品的生产日期：" << endl;
		cout << "（格式参照：2023/05/07）" << endl;
		cin >> Day;
		infor->foodArray[infor->m_Size].m_Day = Day;
		//生产时间
		string Time;
		cout << "请输入该食品的生产时间：" << endl;
		cout << "（参照格式：09`23`04)" << endl;
		cin >> Time;
		infor->foodArray[infor->m_Size].m_Time = Time;
		//品种
		string Vari;
		cout << "请输入该产品的品种信息：" << endl;
		cin >> Vari;
		infor->foodArray[infor->m_Size].m_Vari = Vari;
		//生产批次
		string Num;
		cout << "请输入该产品的产品批次：" << endl;
		cin >> Num;
		infor->foodArray[infor->m_Size].m_Num = Num;
		//更新数据库中记录的食品数量
	infor->m_Size++;
	cout << "添加成功！" << endl;
	system("pause");
	system("cls");//清屏操作
	}
}
//显示所有食品信息
void showFOOD(inforMS* infor)
{
	//判断数据库中是否有食物信息
	if (infor->m_Size == 0)
	{
		cout << "抱歉，当前的系统中没有任何的食物信息。" << endl;
	}
	else
	{
		for (int i = 0; i < infor->m_Size; i++)
		{
			cout << "食品：" << infor->foodArray[i].m_Name << "\t";
			cout << "产地：" << infor->foodArray[i].m_Origin << "\t";
			cout << "生产日期：" << infor->foodArray[i].m_Day << "\t";
			cout << "生产时间：" << infor->foodArray[i].m_Time<< "\t";
			cout << "品种信息：" << infor->foodArray[i].m_Vari << "\t";
			cout << "生产批次：" << infor->foodArray[i].m_Num << endl;
		}

	}
	system("pause");
	system("cls");
}
//检测联系人是否存在
int isExist(inforMS* infor,string Name)
{
	for (int i = 0; i < infor->m_Size; i++)
	{
		if (infor->foodArray[i].m_Name == Name)
		{
			return i;
		}
	}
	return -1;//没找到返回-1
}
void deleteFOOD(inforMS* infor)
{
	cout << "请输入您要删除的食物名称:" << endl;
	string Name;
	cin >> Name;
	//判断该食品是否存在
	int ret=isExist(infor, Name);
	if(ret!=-1)
	{ 

		for (int i = ret; i < infor->m_Size; i++)
		{
			infor->foodArray[i] = infor->foodArray[i + 1];
		}
		infor->m_Size--;
		cout << "删除成功！" << endl;
	}
	else
	{
		cout << "该食品不存在！" << endl;
	}
	system("pause");
	system("cls");
}
void showModify()
{
	cout << "请选择你要修改的项目：" << endl;
	cout << "1.食品名称" << endl;
	cout << "2.产地" << endl;
	cout << "3.生产日期" << endl;
	cout << "4.生产时间" << endl;
	cout << "5.品种信息" << endl;
	cout << "6.生产批次" << endl;
	return;
}
//查找食品信息
void findFOOD(inforMS* infor)
{
	cout << "请输入你要查找的食品名称：" << endl;
	string Name;
	cin >> Name;
	//判断是否存在
	int ret = isExist(infor, Name);
	if (ret != -1)
	{
		cout << "食品：" << infor->foodArray[ret].m_Name << "\t";
		cout << "产地：" << infor->foodArray[ret].m_Origin << "\t";
		cout << "生产日期：" << infor->foodArray[ret].m_Day << "\t";
		cout << "生产时间：" << infor->foodArray[ret].m_Time << "\t";
		cout << "品种信息：" << infor->foodArray[ret].m_Vari << "\t";
		cout << "生产批次：" << infor->foodArray[ret].m_Num << endl;
	}
	else
	{
		cout<< "该食品不存在！" << endl;
	}
	system("pause");
	system("cls");
}
//修改食品信息
void modifyFOOD(inforMS* infor)
{
	cout << "请输入你要修改信息的食品名称：" << endl;
	string Name;
	cin >> Name;
	int ret = isExist(infor, Name);
	if (ret != -1)
	{
		
		
			showModify();
			int select;
			cin >> select;
			switch (select)
			{
			case 1:
			{
				string Name;
				cout << "请输入食品新的名称：" << endl;
				cin >> Name;
				infor->foodArray[ret].m_Name = Name;
			}
				break;
			case 2:
			{
				string Origin;
				cout << "请输入更改后的食品产地：" << endl;
				cin >> Origin;
				infor->foodArray[ret].m_Origin = Origin;
			}
				break;
			case 3:
			{
				string Day;
				cout << "请输入更改后的食品生产日期：" << endl;
				cin >> Day;
				infor->foodArray[ret].m_Day = Day;
			}
				break;
			case 4:
			{
				string Time;
				cout << "请输入更改后的食品生产时间：" << endl;
				cin >> Time;
				infor->foodArray[ret].m_Time = Time;
			}
				break;
			case 5:
			{
				string Vari;
				cout << "请输入更改后的食品品种信息：" << endl;
				cin >> Vari;
				infor->foodArray[ret].m_Vari = Vari;
			}
				break;
			case 6:
			{
				string Num;
				cout << "请输入更改后的食品批次：" << endl;
				cin >> Num;
				infor->foodArray[ret].m_Num=Num;
			}
				break;
			}
	}
	else
	{
		cout << "该食品不存在！" << endl;
	}
	system("pause");
	system("cls");
}
//清空所有联系人
void cleanFOOD(inforMS* infor)
{
	cout << "你确定要清空所有食品信息吗?" << endl;
	cout << "清空：0；退出：1；" << endl;
	int sel;
	cin >> sel;
	if (sel = 0)
	{
		infor->m_Size = 0;//做逻辑清空
		cout << "食品安全信息管理系统中的所有食品信息已清空" << endl;
	}
	system("pause");
	system("cls");
}
//菜单界面函数创建
void showMenu()
{
	cout << "欢迎使用食品安全信息管理系统，该系统是一个对食品进行溯源" << endl;
	cout << "存储原材料信息，以确保食品安全的信息管理系统平台。" << endl;
	cout<<"您可以实现以下功能：" << endl;
	cout << "1、添加食品信息" << endl;
	cout << "2、显示食品信息" << endl;
	cout << "3、删除食品信息" << endl;
	cout << "4、查找食品" << endl;
	cout << "5、修改食品信息" << endl;
	cout << "6、清空信息库" << endl;
	cout << "0、退出食品安全信息管理系统" << endl;
}


int main()
{
	//创建信息管理系统结构体变量
	inforMS infor;
	//初始化信息管理系统中当前记录食品的个数
	infor.m_Size = 0;
	int select = 0;//创建用户选择输入的变量，以实现功能的转换
	while (1)//对于菜单的多次选择提供可能
	{
		showMenu();//菜单函数的的调用
		cin >> select;
		switch (select)//用户实现菜单功能的选择
		{
		case 1://1、添加食品信息
			addFOOD(&infor);//利用地址传递，可以修饰实参

			break;
		case 2://2、显示食品信息
			showFOOD(&infor);
			break;
		case 3://3、删除食品信息
			deleteFOOD(&infor);
	
			break;
		case 4://4、查找食品
			findFOOD(&infor);
			break;
		case 5://5、修改食品信息
			modifyFOOD(&infor);
			break;
		case 6://6、清空信息库
			cleanFOOD(&infor);
			break;
		case 0://0、退出食品安全信息管理系统
			cout << "欢迎下次使用!" << endl;
			system("pause");
			exit(0);
		default:
			break;

		}
	}
	system("pause");
	return 0;
}