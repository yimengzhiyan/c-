#include<iostream>
using namespace std;
#include<string>
#define MAX 2000
//���ʳƷ��Ϣ�ṹ��

struct FOOD
{
	//ʳƷ����
	string m_Name;
    //����
	string m_Origin;
		//��������;
	string m_Day;
	//����ʱ��
	string m_Time;
	//Ʒ��
	string m_Vari;
	//��������
	string m_Num;
};
//���ʳƷ��ȫ��Ϣ����ϵͳ�ṹ��
struct inforMS
{
	//��Ϣ����ϵͳ�б����ʳƷ��Ϣ����
	struct FOOD foodArray[MAX];
	//��Ϣ����ϵͳ�е�ǰ��¼��ʳƷ����
	int m_Size;
};

//���ʳƷ��Ϣ
void addFOOD(inforMS* infor)
{
	//�ж���Ϣ���Ƿ������������˾Ͳ����������
	if (infor->m_Size == MAX)
	{
		cout << "��Ǹ����Ϣ������,�޷���ӡ���Ҫ��ӣ���������Ϣ��" << endl;
		return;
	}
	else
	{
		//��Ӿ�����ϵ��
		// ʳƷ����
		string Name;
		cout << "����������Ҫ��ӵ�ʳƷ���ƣ�" << endl;
		cin >> Name;
		infor->foodArray[infor->m_Size].m_Name = Name;
		//����
		string Origin;
		cout << "�������ʳƷ�Ĳ��أ�" << endl;
		cin >> Origin;
		infor->foodArray[infor->m_Size].m_Origin = Origin;
		//��������
		string Day;
		cout << "�������ʳƷ���������ڣ�" << endl;
		cout << "����ʽ���գ�2023/05/07��" << endl;
		cin >> Day;
		infor->foodArray[infor->m_Size].m_Day = Day;
		//����ʱ��
		string Time;
		cout << "�������ʳƷ������ʱ�䣺" << endl;
		cout << "�����ո�ʽ��09`23`04)" << endl;
		cin >> Time;
		infor->foodArray[infor->m_Size].m_Time = Time;
		//Ʒ��
		string Vari;
		cout << "������ò�Ʒ��Ʒ����Ϣ��" << endl;
		cin >> Vari;
		infor->foodArray[infor->m_Size].m_Vari = Vari;
		//��������
		string Num;
		cout << "������ò�Ʒ�Ĳ�Ʒ���Σ�" << endl;
		cin >> Num;
		infor->foodArray[infor->m_Size].m_Num = Num;
		//�������ݿ��м�¼��ʳƷ����
	infor->m_Size++;
	cout << "��ӳɹ���" << endl;
	system("pause");
	system("cls");//��������
	}
}
//��ʾ����ʳƷ��Ϣ
void showFOOD(inforMS* infor)
{
	//�ж����ݿ����Ƿ���ʳ����Ϣ
	if (infor->m_Size == 0)
	{
		cout << "��Ǹ����ǰ��ϵͳ��û���κε�ʳ����Ϣ��" << endl;
	}
	else
	{
		for (int i = 0; i < infor->m_Size; i++)
		{
			cout << "ʳƷ��" << infor->foodArray[i].m_Name << "\t";
			cout << "���أ�" << infor->foodArray[i].m_Origin << "\t";
			cout << "�������ڣ�" << infor->foodArray[i].m_Day << "\t";
			cout << "����ʱ�䣺" << infor->foodArray[i].m_Time<< "\t";
			cout << "Ʒ����Ϣ��" << infor->foodArray[i].m_Vari << "\t";
			cout << "�������Σ�" << infor->foodArray[i].m_Num << endl;
		}

	}
	system("pause");
	system("cls");
}
//�����ϵ���Ƿ����
int isExist(inforMS* infor,string Name)
{
	for (int i = 0; i < infor->m_Size; i++)
	{
		if (infor->foodArray[i].m_Name == Name)
		{
			return i;
		}
	}
	return -1;//û�ҵ�����-1
}
void deleteFOOD(inforMS* infor)
{
	cout << "��������Ҫɾ����ʳ������:" << endl;
	string Name;
	cin >> Name;
	//�жϸ�ʳƷ�Ƿ����
	int ret=isExist(infor, Name);
	if(ret!=-1)
	{ 

		for (int i = ret; i < infor->m_Size; i++)
		{
			infor->foodArray[i] = infor->foodArray[i + 1];
		}
		infor->m_Size--;
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		cout << "��ʳƷ�����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}
void showModify()
{
	cout << "��ѡ����Ҫ�޸ĵ���Ŀ��" << endl;
	cout << "1.ʳƷ����" << endl;
	cout << "2.����" << endl;
	cout << "3.��������" << endl;
	cout << "4.����ʱ��" << endl;
	cout << "5.Ʒ����Ϣ" << endl;
	cout << "6.��������" << endl;
	return;
}
//����ʳƷ��Ϣ
void findFOOD(inforMS* infor)
{
	cout << "��������Ҫ���ҵ�ʳƷ���ƣ�" << endl;
	string Name;
	cin >> Name;
	//�ж��Ƿ����
	int ret = isExist(infor, Name);
	if (ret != -1)
	{
		cout << "ʳƷ��" << infor->foodArray[ret].m_Name << "\t";
		cout << "���أ�" << infor->foodArray[ret].m_Origin << "\t";
		cout << "�������ڣ�" << infor->foodArray[ret].m_Day << "\t";
		cout << "����ʱ�䣺" << infor->foodArray[ret].m_Time << "\t";
		cout << "Ʒ����Ϣ��" << infor->foodArray[ret].m_Vari << "\t";
		cout << "�������Σ�" << infor->foodArray[ret].m_Num << endl;
	}
	else
	{
		cout<< "��ʳƷ�����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}
//�޸�ʳƷ��Ϣ
void modifyFOOD(inforMS* infor)
{
	cout << "��������Ҫ�޸���Ϣ��ʳƷ���ƣ�" << endl;
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
				cout << "������ʳƷ�µ����ƣ�" << endl;
				cin >> Name;
				infor->foodArray[ret].m_Name = Name;
			}
				break;
			case 2:
			{
				string Origin;
				cout << "��������ĺ��ʳƷ���أ�" << endl;
				cin >> Origin;
				infor->foodArray[ret].m_Origin = Origin;
			}
				break;
			case 3:
			{
				string Day;
				cout << "��������ĺ��ʳƷ�������ڣ�" << endl;
				cin >> Day;
				infor->foodArray[ret].m_Day = Day;
			}
				break;
			case 4:
			{
				string Time;
				cout << "��������ĺ��ʳƷ����ʱ�䣺" << endl;
				cin >> Time;
				infor->foodArray[ret].m_Time = Time;
			}
				break;
			case 5:
			{
				string Vari;
				cout << "��������ĺ��ʳƷƷ����Ϣ��" << endl;
				cin >> Vari;
				infor->foodArray[ret].m_Vari = Vari;
			}
				break;
			case 6:
			{
				string Num;
				cout << "��������ĺ��ʳƷ���Σ�" << endl;
				cin >> Num;
				infor->foodArray[ret].m_Num=Num;
			}
				break;
			}
	}
	else
	{
		cout << "��ʳƷ�����ڣ�" << endl;
	}
	system("pause");
	system("cls");
}
//���������ϵ��
void cleanFOOD(inforMS* infor)
{
	cout << "��ȷ��Ҫ�������ʳƷ��Ϣ��?" << endl;
	cout << "��գ�0���˳���1��" << endl;
	int sel;
	cin >> sel;
	if (sel = 0)
	{
		infor->m_Size = 0;//���߼����
		cout << "ʳƷ��ȫ��Ϣ����ϵͳ�е�����ʳƷ��Ϣ�����" << endl;
	}
	system("pause");
	system("cls");
}
//�˵����溯������
void showMenu()
{
	cout << "��ӭʹ��ʳƷ��ȫ��Ϣ����ϵͳ����ϵͳ��һ����ʳƷ������Դ" << endl;
	cout << "�洢ԭ������Ϣ����ȷ��ʳƷ��ȫ����Ϣ����ϵͳƽ̨��" << endl;
	cout<<"������ʵ�����¹��ܣ�" << endl;
	cout << "1�����ʳƷ��Ϣ" << endl;
	cout << "2����ʾʳƷ��Ϣ" << endl;
	cout << "3��ɾ��ʳƷ��Ϣ" << endl;
	cout << "4������ʳƷ" << endl;
	cout << "5���޸�ʳƷ��Ϣ" << endl;
	cout << "6�������Ϣ��" << endl;
	cout << "0���˳�ʳƷ��ȫ��Ϣ����ϵͳ" << endl;
}


int main()
{
	//������Ϣ����ϵͳ�ṹ�����
	inforMS infor;
	//��ʼ����Ϣ����ϵͳ�е�ǰ��¼ʳƷ�ĸ���
	infor.m_Size = 0;
	int select = 0;//�����û�ѡ������ı�������ʵ�ֹ��ܵ�ת��
	while (1)//���ڲ˵��Ķ��ѡ���ṩ����
	{
		showMenu();//�˵������ĵĵ���
		cin >> select;
		switch (select)//�û�ʵ�ֲ˵����ܵ�ѡ��
		{
		case 1://1�����ʳƷ��Ϣ
			addFOOD(&infor);//���õ�ַ���ݣ���������ʵ��

			break;
		case 2://2����ʾʳƷ��Ϣ
			showFOOD(&infor);
			break;
		case 3://3��ɾ��ʳƷ��Ϣ
			deleteFOOD(&infor);
	
			break;
		case 4://4������ʳƷ
			findFOOD(&infor);
			break;
		case 5://5���޸�ʳƷ��Ϣ
			modifyFOOD(&infor);
			break;
		case 6://6�������Ϣ��
			cleanFOOD(&infor);
			break;
		case 0://0���˳�ʳƷ��ȫ��Ϣ����ϵͳ
			cout << "��ӭ�´�ʹ��!" << endl;
			system("pause");
			exit(0);
		default:
			break;

		}
	}
	system("pause");
	return 0;
}