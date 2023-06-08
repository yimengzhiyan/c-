#include <stdio.h>
#include<iostream>
#include <string>
#include<algorithm>
#include <vector>                          
#include <iterator> 
#include<ctime>
#include <windows.h>
//声明命名空间std
using namespace std;
#define MATCH 1
#define DIS_MATCH -1
#define INDEL -3
#define INDEL_CHAR '-'

class ResUnit {		//一次双序列比对后的结果
public:
	string str1;	//原始序列1
	string str2;	//原始序列2
	string res1;	//结果序列1
	string res2;	//结果序列2
	int score;		//序列总得分，反映两个序列的相似程度
	int tag;		//禁止迭代多次
};

class SingleSeq {	//一个序列被整合后的样子
public:
	string str;		//一个序列的原始序列
	string res;		//一个序列被整合后的样子

};

struct BacktrackingUnit {
	int goUp;		//是否向上回溯
	int goLeftUp;	//是否向左上回溯
	int goLeft;		//是否向左回溯
	int score;		//得分矩阵第(i, j)这个单元的分值
};


typedef struct BacktrackingUnit* unitLine;

int max3(int a, int b, int c);
ResUnit traceback(unitLine** item, const int i, const int j, string str1, string str2, string res1, string res2, int n, ResUnit resUnit);
ResUnit NeedlemanWunch(string str1, string str2);

struct SequenceUnit {
	string* str1;	//匹配序列1
	string* str2;	//匹配序列2
	int score;
};

int main() {
	char first[100]  = "0";
	char second[100] = "0";
	//cin >> first >> second;// "GGATCGA""GAATTCAGTTA"
	
	int score1[5][5] = {
		{10,-1,-3,-4,-5},
		{-1,7,-5,-3,-5},
		{-3,-5,9,0,-5},
		{-4,-3,0,8,-5},
		{-5,-5,-5,-5,-5} };
	//char first[100] = "";
	int fi = 0;
	//char second[100] = "";
	int se = 0;
	int h = 0;
	int l = 0;
	int sum = 0;
	//int sum_h = 0;
	//int sum_l = 0;
	int max = 0;
	double max1 = 0;
	cout << "这是一个计算DNA相似度的程序" << endl;
one:
	cout << "请输入第一组DNA序列(100以内,大写)" << endl;
	cin >> first;
	fi = strlen(first);
	for (int i = 0; i < fi; i++) {
		if (first[i] != 'A' && first[i] != 'T' && first[i] != 'G' && first[i] != 'C') {
			cout << "请输入A,T,C,G" << endl;
			goto one;
		}
	}
two:
	cout << "请输入第二组DNA序列(100以内，大写)" << endl;
	cin >> second;
	se = strlen(second);
	for (int j = 0; j < se; j++) {
		if (first[j] != 'A' && first[j] != 'T' && first[j] != 'G' && first[j] != 'C') {
			cout << "请输入A,T,C,G" << endl;
			goto two;
		}
	}
	ResUnit s = NeedlemanWunch(first, second);
	if (fi > se)
		max = fi;
	else
		max = se;
	for (int x = 0; x < max; x++) {

		switch (s.res1[x]) {
		case 'A':
			h = 0;
			break;
		case 'G':
			h = 1;
			break;
		case 'C':
			h = 2;
			break;
		case 'T':
			h = 3;
			break;
		case '-':
			h = 4;
			break;
		//default:
			//cout << "error" << endl;
			//goto one;
		}

		switch (s.res2[x]) {
		case 'A':
			l = 0;
			break;
		case 'G':
			l = 1;
			break;
		case 'C':
			l = 2;
			break;
		case 'T':
			l = 3;
			break;
		case '-':
			l = 4;
			break;
		//default:
			//cout << "error" << endl;
			//goto one;
		}
		max1 = max1 + (score1[h][h] >= score1[l][l] ? score1[h][h] : score1[l][l]);
		sum = sum + score1[h][l];
	}
	cout << s.res1 << endl;
	cout << s.res2 << endl;
	cout << sum / max1 * 100 << "%"<<endl;
	system("pause");
}


/**
比较三种路径之间谁最大

f(i-1,j-1),f(i-1,j)+indel,f(i,j-1)+indel
*/
int max3(int a, int b, int c) {
	int temp = a > b ? a : b;
	return temp > c ? temp : c;
}

/**
比较两个字符类型属于什么，match，dismatch，indel
*/
int myCompare(char a, char b) {
	if (a == b)
		return MATCH;
	else if (a == ' ' || b == ' ')
		return INDEL;
	else
		return DIS_MATCH;
}

ResUnit traceback(unitLine** item, const int i, const int j, string str1, string str2, string res1, string res2, int n, ResUnit resUnit) {
	unitLine temp = item[i][j];
	if (resUnit.tag != 1)
	{
		if (!(i || j)) {   // 到矩阵单元(0, 0)才算结束，这代表初始的两个字符串的每个字符都被比对到了

			resUnit.str1 = str1;
			resUnit.str2 = str2;
			resUnit.res1 = res1;
			resUnit.res2 = res2;
			resUnit.tag = 1;
			return resUnit;
		}
		if (temp->goUp) {    // 向上回溯一格
			res1 = str1[i - 1] + res1;
			res2 = INDEL_CHAR + res2;
			resUnit = traceback(item, i - 1, j, str1, str2, res1, res2, n + 1, resUnit);
		}
		if (temp->goLeftUp) {    // 向左上回溯一格 
			res1 = str1[i - 1] + res1;
			res2 = str2[j - 1] + res2;
			resUnit = traceback(item, i - 1, j - 1, str1, str2, res1, res2, n + 1, resUnit);
		}
		if (temp->goLeft) {    // 向左回溯一格
			res1 = INDEL_CHAR + res1;
			res2 = str2[j - 1] + res2;
			resUnit = traceback(item, i, j - 1, str1, str2, res1, res2, n + 1, resUnit);
		}
		return resUnit;
	}
	else
	{
		return resUnit;
	}

}


ResUnit NeedlemanWunch(string str1, string str2) {
	//字符串str1,str2长度
	const int m = str1.length();
	const int n = str2.length();

	int m1, m2, m3, mm;

	unitLine** unit;

	// 初始化
	if ((unit = (unitLine**)malloc(sizeof(unitLine*) * (m + 1))) == NULL) {
		fputs("Error: Out of space!\n", stderr);
		exit(1);
	}
	for (int i = 0; i <= m; i++) {
		if ((unit[i] = (unitLine*)malloc(sizeof(unitLine) * (n + 1))) == NULL) {
			fputs("Error: Out of space!\n", stderr);
			exit(1);
		}
		for (int j = 0; j <= n; j++) {
			if ((unit[i][j] = (unitLine)malloc(sizeof(struct BacktrackingUnit))) == NULL) {
				fputs("Error: Out of space!\n", stderr);
				exit(1);
			}
			unit[i][j]->goUp = 0;
			unit[i][j]->goLeftUp = 0;
			unit[i][j]->goLeft = 0;
		}
	}
	unit[0][0]->score = 0;
	for (int i = 1; i <= m; i++) {
		unit[i][0]->score = INDEL * i;
		unit[i][0]->goUp = 1;
	}
	for (int j = 1; j <= n; j++) {
		unit[0][j]->score = INDEL * j;
		unit[0][j]->goLeft = 1;
	}


	// 动态规划算法计算得分矩阵每个单元的分值
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			m1 = unit[i - 1][j]->score + INDEL;
			m2 = unit[i - 1][j - 1]->score + myCompare(str1[i - 1], str2[j - 1]);
			m3 = unit[i][j - 1]->score + INDEL;
			mm = max3(m1, m2, m3);
			unit[i][j]->score = mm;
			//判断路径来源
			if (m1 == mm) unit[i][j]->goUp = 1;
			if (m2 == mm) unit[i][j]->goLeftUp = 1;
			if (m3 == mm) unit[i][j]->goLeft = 1;
		}
	}


	//开始回溯
	ResUnit res;
	res.tag = 0;
	res = traceback(unit, m, n, str1, str2, "", "", 0, res);
	res.score = unit[m][n]->score;


	//释放内存
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			free(unit[i][j]);
		}
		free(unit[i]);
	}
	free(unit);

	//返回值
	return res;
}