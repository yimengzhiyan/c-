/*
代码说明：本代码基于ARIMA模型和基于最小二乘法的多元回归分析，通过给定的31天的样本数据，来预测未来3天的AQI值，并做出空气质量的预警
作者：黄显哲 申瑞辰 李贝卓 符家豪 熊忠书 张杨旸
时间：完成于2023年5月30日
*/
#include<bits/stdc++.h> //使用万能头文件，VS2022需要自行创建
using namespace std;

// 定义结构体，结构体中创建变量，来表示各项指标
struct data {
	int day; // day表示第几天
	double AQI; // 虽然数据中AQI均为整数，但由于最后拟合出的AQI值为小数，所以此处定义为double，最后再强制转化为int
	// 下面定义为double的理由，同上
	double a,b,c,d,e,f,jiangshuiliang,qiya,fengsu,qiwen,shidu;
	// 其中a表示PM10，b表示O3，c表示SO2，d表示PM2.5，e表示NO2，f表示CO
	// jiangshuiliang表示降水量，qiya表示气压，fengsu表示风速，qiwen表示气温，shidu表示湿度
};

// 说明：由于本题所需要的数据过多，我们直接给出，避免输入过程的麻烦，故本题中的数组长度大多固定为31天（可以使用OpenXml库等，直接从表格中读取数据）

void sifenweijvfa(double arr[31][12]) // 函数：四分位距法，用来找到数据中的异常值并将其修改为上下截断点的值
{
	// 先将每一列的正常的天数都初始化为31
	int day[12];
	for(int i=0;i<12;i++)
	{
		day[i]=31;
	}
	
	double NP1[12],NP2[12];
	int np1[12],np2[12];
	// 上面建立一个int，是为了验证是不是整数，NP1和np1是对0.25分位数的，NP2和np2是对0.75分位数的
	double Q1,Q3,R1;

	for(int i=0;i<12;i++)
	{
		for(int j=0;j<31;j++)
		{
			if(arr[j][i]==(-1000))
			{
				// 得到每一个因素的实际样本容量
				day[i]--;
			}
		}
	}
	
	for(int i=0;i<12;i++)
	{
		double a[31];
		for(int j=0;j<31;j++)
		{
			a[j]=arr[j][i];
		}
		
		for(int p=0;p<30;p++)
		{
			for(int q=0;q<30-p;q++)
			{
				double temp=0;
				if(a[q+1]>a[q])
				{
					temp=a[q];
					a[q]=a[q+1];
					a[q+1]=temp;
				}
			}
		}
		
		// 上面已经对每一个因素进行了冒泡排序（由高到低）,所以-1000（缺失值）就在数组的最后面，可以计算得出他们的位置
		
		//NP1是0.25分点，NP2是0.75分点，np1和np2是对NP1和NP2的取整，后续用来验证NP1和NP2是否为整数
		NP1[i]=day[i]*0.25;
		NP2[i]=day[i]*0.75;
		np1[i]=(int)(NP1[i]);
		np2[i]=(int)(NP2[i]);

		if(NP1[i]==np1[i])
		{
			Q1=0.5*(a[np1[i]]+a[np1[i]+1]);
			Q3=0.5*(a[np2[i]]+a[np2[i]+1]);
		}
		else
		{
			Q1=a[np1[i]+1];
			if(NP2[i]==np2[i])
			{
				Q3=0.5*(a[np2[i]]+a[np2[i]+1]);
			}
			else
			{
				Q3=a[np2[i]+1];
			}
		}
		
		R1=Q1-Q3;

		double max,min; // max和min分别为上下截断点，用于替换异常数据
		max=Q3+1.5*R1;
		min=Q1-1.5*R1;
		
		// -1000是我们视为空值的，不能被四分位距法替换，否则影响后续的插值过程
		for(int j=0;j<31;j++)
		{
			if(arr[j][i]!=(-1000))
			{
				if(arr[j][i]>max)
				{
					arr[j][i]=max;
				}
				if(arr[j][i]<min)
				{
					arr[j][i]=min;
				}	
			}
		}
	}
}	

void lagrange(double arr[31][12])  // 该函数为Lagrange插值法，用于缺失值的填充
{
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<31;j++)
		{
			if(arr[j][i]==(-1000))
			{
				double x0[6],y0[6];
				int sum1=0;  // sum1起计数器作用，目的是找到缺失值前的3个数据和缺失值后的3个数据，一共有6个数据
				
				// 在缺失值之前找到3个样本
				for(int k=j-1;k>=0;k--)
				{
					if(arr[k][i]!=(-1000))
					{
						x0[sum1]=k+1;
						y0[sum1]=arr[k][i];
						sum1++;
					}
					if(sum1==3)
					{
						break;
					}
				}
				
				// 在缺失值之后找到3个样本
				for(int k=j+1;k<31;k++)
				{
					if(arr[k][i]!=(-1000))
					{
						x0[sum1]=k+1;
						y0[sum1]=arr[k][i];
						sum1++;
					}
					if(sum1==6)
					{
						break;
					}
				}
			
				//	 注：本方法类似于多项式拟合，用4个样本点数据，可以求出一个三次多项式，5个样本点，可求出一个四次多项式。6个样本点，就是五次多项式
				// 根据在竞赛中的实际操作，我们考虑到时间序列的周期性，又考虑到实际运算过程中的运算量，我们选取了缺失值之前的3天和缺失值之后的3天作为样本点，即一共6个样本点
				
				int n=6; // n为有几个样本点
				double f[n]; // x0指的是我们的6个样本点,y0是6个样本点对应的y值，f数组下标对应的是函数f的下标
				// 根据知乎Lagrange插值法的解法可知，只需要进行5次（n-1）次累乘即可
				// 输入6个样本点的x,y坐标 （输入格式为：x,y一一对应，即输入一个x，就要输入这个x对应的y值）
						if(arr[j][i]==(-1000))
						{
							double x; // x为需要插值地方的x坐标
							x=j+1;
							double sum=0; // 定义sum为不带下标f的初始量，后续进行带下标f的累加
							
							for(int p=0;p<n;p++)  // i就是f函数对应的下标,有几个样本点，就会产生几个多项式。
							{
								double pai=1; // 定义pai为带下标的f的累乘初始量，由于累乘，所以初始量是1，而不是0.（pai这个名字取自累乘的数学符号）
								for(int q=0;q<n;q++)// j对应的就是累乘的次数，由于不乘i=j的情况，所以n-1次循环
								{
									// 判断一下，i和j的关系
									if(p==q) // 如果i与j相等，则j变量进行下一轮循环（跳出一层循环）
									{
										continue;
									}
									else // 如果i与j不相等，就可以进行累乘
									{
										double mother=0,son=0; // 初始化分子分母
										mother=x0[p]-x0[q]; // 由于i不等于j,所以避免了分母为0
										son=x-x0[q];
										pai=pai*(son/mother);
									}
								}
								f[p]=pai;
								// 为了便于后续计算，此处直接计算y(i)*f(i) 此处的括号表示法是对应知乎的公式的，并直接用f[i]来替换
								// 故本程序中最后的f[i]与知乎中带下标的f表示的意义并不同
								f[p]=y0[p]*f[p];
								sum=sum+f[p];
							}
							double ftrue;
							ftrue=sum;
							arr[j][i]=ftrue;
						}
			}
		}
	}
}

void Zscore(double arr[31][12]) // 函数作用：对数据进行Zscore标准化，消除量纲
{
	// 本部分代码都是严格依照公式所展开，所以注释可以不用那么详细，公式在PPT
	int n=31; // 输入样本个数（每一个因素）
	for(int i=0;i<12;i++)
	{
		double sum=0;
		double s=0,temp=0; // s是标准差，temp是收集平方和的中间变量
		for(int j=0;j<31;j++)
		{
			sum+=arr[j][i];
		}
		double ave=0; // 这里的ave表示的是平均值，下划线后的字符则表示ave是哪个变量的ave
		ave=sum/n;
		double sum_s=0;
		for(int j=0;j<31;j++)
		{
			temp=arr[j][i]-ave;
			temp=pow(temp,2);
			sum_s+=temp;
		}
		double ave_s=0;
		ave_s=sum_s/n;
		s=sqrt(ave_s);
		for(int j=0;j<31;j++)
		{
			arr[j][i]=(arr[j][i]-ave)/s;
		}
	}
}

void minmaxguiyi(double arr[31][12]) //函数作用：对规范化的数据进行归一化，使数据更为集中，同时体现了上下截断点
{
	int n=31; // 输入需要处理的样本数量
	for(int i=0;i<12;i++)
	{
		// 找原始数据集中的最大，最小值
		double max=arr[0][i],min=arr[0][i];
		
		for(int j=0;j<n;j++)
		{
			if(max<arr[j][i])
			{
				max=arr[j][i];
			}
			if(min>arr[j][i])
			{
				min=arr[j][i];
			}
		}
		
		// 在这里使用min-max归一化处理 公式在PPT
		double mother=0,son=0;
		mother=max-min;
		
		for(int j=0;j<n;j++)
		{
			son=arr[j][i]-min;
			arr[j][i]=son/mother;
		}
	}
}


double pearsonCorrelation(double X[], double y[]) // 函数作用：对每个因素和AQI之间的Pearson相关系数进行计算
{
	int n=31; // n表示输入样本的个数
	double sum_x=0,sum_y=0;
	
	for(int i=0;i<n;i++)
	{
		// 一个x对应一个y的输入
		sum_x+=X[i];
		sum_y+=y[i];
	}
	
	//同理这里面ave表示的是平均值，下划线后面的字符表示是该ave是哪个变量的ave
	double ave_x=0,ave_y=0;
	ave_x=sum_x/n;
	ave_y=sum_y/n;
	double mother_1=0,mother_2=0,son=0;
	double sum_son=0,sum_mother1=0,sum_mother2=0;
	
	for(int i=0;i<n;i++)
	{
		son=(X[i]-ave_x)/(y[i]-ave_y);
		mother_1=pow((X[i]-ave_x),2);
		mother_2=pow((y[i]-ave_y),2);
		sum_son+=son;
		sum_mother1+=mother_1;
		sum_mother2+=mother_2;
	}
	
	double r_mother=0,r_son=0;
	r_son=son;
	r_mother=sqrt(sum_mother1)*sqrt(sum_mother2);
	double r=0;
	r=r_son/r_mother;
	return r; // 返回Pearson相关系数
}

int * shaixuanyinsu(double arr[11]) //函数作用：根据上面计算的Pearson相关系数，对因素和AQI的相关系数进行排序，并按照给定的标准，选出后续用来预测的因素
{
	int n=11;
	// 取绝对值，因为有些因素和AQI是存在负相关关系的，所以我们需要取绝对值进行比较
	double arr_abs[11];
	for(int i=0;i<n;i++)
	{
		arr_abs[i]=fabs(arr[i]);
	}
	
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			double temp=0;
			if(arr_abs[j+1]>arr_abs[j])
			{
				temp=arr_abs[j];
				arr_abs[j]=arr_abs[j+1];
				arr_abs[j+1]=temp;
			}
		}
	}
	
	string yinsu[11]={"PM10","O3","SO2","PM2.5","NO2","CO","降水量","气压","风速","气温","湿度"};
	int *p=new int[12]; //使用动态数组，在函数的末尾返回该数组
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr_abs[i]==(fabs(arr[j])))
			{
				cout<<"影响AQI指数的因素排名第"<<i+1<<"位的是："<<yinsu[j]<<"，其值为"<<arr[j]<<endl;
			}
		}
	}
	
	int sum=0; //计数器
	double biaozhun=0.2;
	cout<<"根据指定的相关系数阈值，最终选出的因素为：";
	for(int i=0;i<11;i++)
	{
		if(fabs(arr[i])>=0.2)
		{
			cout<<yinsu[i]<<" ";
			p[i]=1;
			sum++;
		}
		else
		{
			p[i]=0;
		}
	}
	p[11]=sum;
	cout<<endl;
	return p;
}

//ARIMA部分包括array_mean函数，array_variance函数，autocorrelation函数，inv_autocorrelation函数以及arima函数
// 定义历史数据长度和预测步数，在后续的ARIMA模型中使用
const int HISTORY_LENGTH=31; // 定义历史数据长度为31
const int FORECAST_LENGTH=3; // 定义预测步长（预测天数）为3

double array_mean(double history[], int length) //函数作用：计算数组平均值 
{
	double sum=0.0;
	for (int i=0;i<length;i++) 
	{
		sum+=history[i];
	}
	return sum/length;
}

double array_variance(double history[], int length) //函数作用：计算数组方差
{
	double mean=array_mean(history, length);
	double variance=0.0;
	
	for (int i=0;i<length;i++) 
	{
		variance+=pow(history[i]-mean,2);
	}
	return variance/length;
}

double autocorrelation(double history[], int length, int lag) //函数作用：计算自相关系数
{
	double mean=array_mean(history, length);
	double variance=array_variance(history, length);
	double numerator=0.0;
	double denominator=0.0;
	for (int i=0;i<length-lag;i++) 
	{
		numerator+=(history[i]-mean)*(history[i+lag]-mean);
	}
	for (int i=0;i<length;i++) 
	{
		denominator+=pow(history[i]-mean,2);
	}
	return numerator/denominator;
}


double inv_autocorrelation(double autocorr) //函数作用：计算自相关系数函数的倒数
{
	return 1.0/(1.0-pow(autocorr,2));
}

double arima(double history[], int length) //函数作用：计算ARIMA模型的参数和预测值
{
	double phi1=autocorrelation(history,length,1);
	double phi2=autocorrelation(history,length,2);
	double theta1=inv_autocorrelation(phi1);
	double forecast=phi1*history[length-1]+phi2*history[length-2]-theta1*(history[length-1]-phi1*history[length-2]);
	return forecast;
}

void OLS(double x[][7], double y[], double* result) //函数作用：基于最小二乘法估计模型参数
{
	int n=31;  // 样本量
	int k=7;  // 自变量个数
	double xishu=2.5; // 设置模型预测系数
	
	// 下面内容为高斯消元法
	// 构造X矩阵和Y向量
	double X[n][k+1]; // 定义静态二维数组X，每行有k+1列（多出一列常数项，即第k+1列为常数项）
	
	for (int i=0;i<n;i++) 
	{
		for (int j=0;j<k;j++) 
		{
			X[i][j]=x[i][j]; // 将输入的x值填充到X矩阵的第i行第j列中
		}
		X[i][k]=1; // 每行最后一列为常数项1
	}
	
	double Y[n]; // 定义静态一维数组Y（因变量）
	
	for (int i=0;i<n;i++) 
	{
		Y[i]=y[i]; // 将输入的y值填充到Y数组中
	}
	
	// 计算X'X矩阵的逆矩阵
	double X_transpose[k+1][n]; // 定义静态二维数组X转置矩阵（k+1行n列）
	
	for (int i=0;i<k+1;i++) 
	{
		for (int j=0;j<n;j++) 
		{
			X_transpose[i][j]=X[j][i]; // 将X矩阵的第i列赋给X转置矩阵的第i行
		}
	}
	double X_transpose_X[k+1][k+1]; // 定义静态二维数组X'X
	
	for (int i=0;i<k+1;i++) 
	{
		for (int j=0;j<k+1;j++) 
		{
			double sum=0.0;
			for (int t=0;t<n;t++) 
			{
				sum+=X_transpose[i][t]*X[t][j]; // 计算X'X矩阵中的每个元素
			}
			X_transpose_X[i][j]=sum; // 将计算结果写入X'X矩阵中
		}
	}
	
	double X_transpose_X_inv[k+1][k+1]; // 定义静态二维数组X'X的逆矩阵
	
	// 计算X'X矩阵的行列式值det，为便于查看，将det的计算过程分成三行
	double det=X_transpose_X[0][0]*(X_transpose_X[1][1]*X_transpose_X[2][2]-X_transpose_X[1][2]*X_transpose_X[2][1])
		      -X_transpose_X[0][1]*(X_transpose_X[1][0]*X_transpose_X[2][2]-X_transpose_X[1][2]*X_transpose_X[2][0])
			  +X_transpose_X[0][2]*(X_transpose_X[1][0]*X_transpose_X[2][1]-X_transpose_X[1][1]*X_transpose_X[2][0]);

	if (det==0.0) 
	{ // 如果行列式为0，则X’X矩阵不可逆，程序结束
		cout << "错误：X’X矩阵不可逆，即数据输入有误" << endl;
		
		exit(1); //因为上述错误，导致后续预测和预警过程均无法执行，故直接退出程序即可，使用exit(1)
	}
	else 
	{ 
		// 如果行列式不为0，则计算X'X矩阵的逆矩阵
		X_transpose_X_inv[0][0]=(X_transpose_X[1][1]*X_transpose_X[2][2]-X_transpose_X[1][2]*X_transpose_X[2][1])/det;
		X_transpose_X_inv[0][1]=(X_transpose_X[0][2]*X_transpose_X[2][1]-X_transpose_X[0][1]*X_transpose_X[2][2])/det;
		X_transpose_X_inv[0][2]=(X_transpose_X[0][1]*X_transpose_X[1][2]-X_transpose_X[0][2]*X_transpose_X[1][1])/det;
		X_transpose_X_inv[1][0]=(X_transpose_X[1][2]*X_transpose_X[2][0]-X_transpose_X[1][0]*X_transpose_X[2][2])/det;
		X_transpose_X_inv[1][1]=(X_transpose_X[0][0]*X_transpose_X[2][2]-X_transpose_X[0][2]*X_transpose_X[2][0])/det;
		X_transpose_X_inv[1][2]=(X_transpose_X[0][2]*X_transpose_X[1][0]-X_transpose_X[0][0]*X_transpose_X[1][2])/det;
		X_transpose_X_inv[2][0]=(X_transpose_X[1][0]*X_transpose_X[2][1]-X_transpose_X[1][1]*X_transpose_X[2][0])/det;
		X_transpose_X_inv[2][1]=(X_transpose_X[0][1]*X_transpose_X[2][0]-X_transpose_X[0][0]*X_transpose_X[2][1])/det;
		X_transpose_X_inv[2][2]=(X_transpose_X[0][0]*X_transpose_X[1][1]-X_transpose_X[0][1]*X_transpose_X[1][0])/det;
		
		// 前三行已经计算了，这里直接赋值为1
		X_transpose_X_inv[3][3]=X_transpose_X_inv[4][4] = X_transpose_X_inv[5][5] = X_transpose_X_inv[6][6]=1; 
	}
	
	// 计算系数向量β
	double beta[k+1][1]; // 定义静态二维数组beta（每行1列）
	for (int i=0;i<k+1;i++) 
	{
		double sum=0.0;
		
		for (int j=0;j<n;j++) 
		{
			sum+=X_transpose[i][j]*Y[j]; // 计算X'Y向量中的每个元素
		}
		
		beta[i][0]=0.0;
		
		for (int j=0;j<k+1;j++) 
		{
			beta[i][0]+=X_transpose_X_inv[i][j]*sum; // 计算系数矩阵中的每个元素
			
			// 将结果保存到result数组中
			for (int i=0;i<k+1;i++) 
			{
				result[i]=beta[i][0]/xishu;
			}
		}
	}
}

void yuce(double arr[]) // 函数作用：将预测得到的AQI值转化为空气质量的预警等级
{
	for (int i=0;i<3;i++)
	{
		cout<<"第"<<i+1<<"天的空气质量为：";
		if(arr[i]>=0&&arr[i]<=50)
		{
			cout<<"优"<<endl;
		}
		if(arr[i]>=51&&arr[i]<=100)
		{
			cout<<"良"<<endl;
		}
		if(arr[i]>=101&&arr[i]<=150)
		{
			cout<<"轻度污染"<<endl;
		}
		if(arr[i]>=151&&arr[i]<=200)
		{
			cout<<"中度污染"<<endl;
		}
		if(arr[i]>=201&&arr[i]<=300)
		{
			cout<<"重度污染"<<endl;
		}
		if(arr[i]>=301)
		{
			cout<<"严重污染"<<endl;
		}
	}
}

int main()
{
// 第一部分：数据预处理（数据清洗）
	// 第一步：先传入数据（在上面定义结构体,在下面输入数据）
	//输入数据部分
	struct data arr[31]=
	{
		{1, 240, 228, 46, 42, 190, 104, 2.1, 0, 1027.4, 0.4, 5.8, 83},
		{2, 230, 221, 53, 44, 180, 108, 2.2, 0, 1025.7, 0.5, 5.7, 82},
		{3, 227, 221, 47, 41, 177, 119, 2.7, 0, 1024.8, 0.3, 5.4, 81},
		{4, 193, 177, 31, 35, 145, 83, 1.8, 0, 1026.3, 2, 8.1, 76},
		{5, 129, 122, 37, 28, 98, 55, 1.5, 999990, 1025.4, 1.4, 6.7,78},
		{6, 117, 91, 54, 16, 88, 60, 1.1, 0, 1025.7, 0.7, 3.9,87},
		{7, 163, 150, 26, 27, 124, 80, 1.6, 0, 1024.6, 0.4, 4.2,88},
		{8, 171, 142, 65, 23, 130, 68, 1.3, 0, 1025.9, 0.6, 5.1,80},
		{9, 169, 160, 86, 43, 129, 74, 1.4, 0, 1028.4, 1.2, 3.5,74},
		{10, 146, 147, 78, 33, 112, 65, 1.2, 0, 1026.7, 1.6, 7.2,64},
		{11, 187, 172, 71, 36, 141, 87, 1.5, 0, 1024.4, 0.8, 5.6,74},
		{12, 131, 165, 50, 41, 100, 95, 1.4, 0, 1018.7, 0.7, 8.2,66},
		{13, 145, 168, 70, 34, 111, 74, 1.4, 0, 1022.7, 1.9, 6.2,63},
		{14, 134, 133, 67, 52, 102, 70, 1.5, 0, 1022.4, 1.7, 3.9,63},
		{15, 116, 135, 35, 58, 88, 85, 1.4, 0, 1015.9, 1.8, 8.2,54},
		{16, 132, 159, 34, 48, 100, 91, 1.5, 999990, 1014, 0.8, 11.8,63},
		{17, 279, 57, 32, 25, 229, 62, 2.1, 1.3, 1020, 2.9, 6.6,86},
		{18, -1000, 32.5, -1000, -1000, 168, -1000, -1000, 0.4, 1020.8, 1.7, 6.4,84},
		{19, 140, 8, -1000, 1, 107, -1000, -1000, 11.5, 1023.8, 5.4, 4.1,91},
		{20, -1000, 5, -1000, -1000, 32, -1000, -1000, 10.5, 1024.5, 2.9, 0.2,94},
		{21, -1000, 25, -1000, -1000, 64, -1000, -1000, 5.5, 1027.1, 2.4, -0.5,94},
		{22, -1000, 58, -1000, -1000, 83, -1000, -1000, 0, 1030.4, 2.3, -0.3,87},
		{23, -1000, 89, -1000, -1000, 132, -1000, -1000, 999990, 1032.8, 2, 1.9,74},
		{24, 161, 4, 28, 16, 122, 54, 1.4, 4.2, 1031.3, 0.9, 1.1,89},
		{25, 138, 39, 18, 18, 105, 54, 1.4, 999990, 1028.9, 1, 2.2,92},
		{26, 153, 61, 47, 16, 117, 47, 1.3, 0, 1030.4, 1.3, 3.4,80},
		{27, 223, 179, 71, 29, 173, 77, 1.8, 0, 1029.7, 0.9, 1.3,85},
		{28, 219, 200, 81, 49, 169, 78, 1.9, 0, 1030.4, 0.8, 1.6,77},
		{29, 160, 161, 97, 36, 122, 85, 1.5, 0, 1024.5, 0.8, 2.4,77},
		{30, 184, 195, 40, 41, 139, 108, 1.7, 0, 1023, 0.7, 2.8,82},
		{31, 213, 185, 70, 53, 163, 65, 1.8, 0, 1029.1, 1.6, 3.6,70}
	};
	// 至此，我们的31组初始数据全部导入
	// 根据查阅资料，我们可以通过安装openxml库从excel中读取数据，但由于方便老师您测试，此处采用笨拙的，输入模式
	// 由于数据量过大，不方便用户自行输入，故如果想要换数据测试，请直接在上面修改，而不是使用cin,scanf等
	
	double arr_data[31][12]; //为便于后续操作步骤，将上述数据（除了时间序号）传入到一个31行12列的二维数组中
	
	for(int i=0;i<31;i++)
	{
		arr_data[i][0]=arr[i].AQI;
		arr_data[i][1]=arr[i].a;
		arr_data[i][2]=arr[i].b;
		arr_data[i][3]=arr[i].c;
		arr_data[i][4]=arr[i].d;
		arr_data[i][5]=arr[i].e;
		arr_data[i][6]=arr[i].f;
		arr_data[i][7]=arr[i].jiangshuiliang;
		arr_data[i][8]=arr[i].qiya;
		arr_data[i][9]=arr[i].fengsu;
		arr_data[i][10]=arr[i].qiwen;
		arr_data[i][11]=arr[i].shidu;
	}
	//至此，数据传入步骤结束
	
	//第二步：使用四分位距法找到异常值，并用上下截点替换
	sifenweijvfa(arr_data);
	
	//第三步：使用拉格朗日插值法对缺失值填补
	lagrange(arr_data);
	
	//第四步：再次使用四分位距法，确保拉格朗日插值法插入的数据正常
	sifenweijvfa(arr_data);
	
	// 定义ceshi数组，保存一个没有经过Zscore标准化和minmax归一化的，但经过两次四分位距法和插值的数据
	double ceshi[31][12];
	
	for(int i=0;i<31;i++)
	{
		for(int j=0;j<12;j++)
		{
			ceshi[i][j]=arr_data[i][j];
		}
	}
	
	// 第五步：对数据进行Zsocre标准化
	Zscore(arr_data);

	//第六步：对数据进行minmax归一化
	minmaxguiyi(arr_data);
	
	//至此第一部分（数据预处理）结束
	
	// 第二部分：相关因素的筛选
	
	//第一步：要先计算后面11个因素对AQI的Pearson相关系数
	double X[31][11];
	double y[31];
	
	for(int i=0;i<31;i++)
	{
		for(int j=1;j<12;j++)
		{
			X[i][j-1]=arr_data[i][j];
		}
		y[i]=arr_data[i][0];
	}
	
	double pearsonCoeff[11];
	
	for(int i=0;i<11;i++)
	{
		int xIndex = i; // 要求解的自变量的索引
		pearsonCoeff[i] = pearsonCorrelation(X[xIndex], y);
	}
	// 至此，peasron相关系数计算完毕
	
	//第二步：依据相关系数对因素进行排序，并选出影响较为显著的因素
	int *p;
	p=shaixuanyinsu(pearsonCoeff);
	int number=0; //number表示我们根据标准选出了多少个因素（number个因素）
	number=p[11];
	string yinsu[11]={"PM10","O3","SO2","PM2.5","NO2","CO","降水量","气压","风速","气温","湿度"};
	string zuizhong[number];
	int sum=0; //计数器,用来重新对列进行编号，方便ARIMA和yuanshi数组的数据传入
	double ARIMA[31][number];
	double yuanshi[31][number];
	
	for(int i=0;i<11;i++)
	{
		if(p[i]==1)
		{
			zuizhong[sum]=yinsu[i];
			
			for(int j=0;j<31;j++)
			{
				ARIMA[j][sum]=arr_data[j][i+1];
				yuanshi[j][sum]=ceshi[j][i+1];
			}
			sum++; // 计数器+1，即列序数+1
		}
	}
	//至此，第二部分（相关因素的筛选完成）
	
	//第三部分：开始预测
	
	//第一步：使用ARIMA模型，预测选出的每一个因素的未来3天的值（预测步长为3）
	double history[HISTORY_LENGTH];
	double shouji[3][number];
	
	for(int k=0;k<number;k++)
	{
		for(int l=0;l<31;l++)
		{
			history[l]=yuanshi[l][k];
		}
		// 对每个预测步骤进行预测
		for (int i=0;i<FORECAST_LENGTH;i++) 
		{
			// 使用ARIMA模型进行预测
			double forecast=arima(history,HISTORY_LENGTH);
			cout<<"未来第"<<i+1<<"天的"<<zuizhong[k]<<"为："<<fabs(forecast)<<endl;
			// 将预测结果插入到历史数据中
			for (int j=0;j<HISTORY_LENGTH-1;j++)
			{
				history[j]=history[j+1];
			}
			history[HISTORY_LENGTH-1]=fabs(forecast);
		}
		
		//收集预测的数据
		for(int m=0;m<3;m++)
		{
			shouji[m][k]=history[28+m];
		}
	}
	
	// 第二步：使用多元回归分析预测未来3天的AQI值
	double x[31][7];
	double yy[31];
	
	for(int i=0;i<31;i++)
	{
		yy[i]=arr_data[i][0];
		for(int j=0;j<number;j++)
		{
			x[i][j]=ARIMA[i][j];
		}
	}
	
	double result[8]; //result数组表示多元回归分析得到的各项系数，最后一项为常数
	OLS(x, yy, result);
	
	// 得到多元回归分析得到的系数
	cout<<"多元回归分析得到的系数如下（最后一个为常数）: ";
	for (int i=0;i<8;i++) 
	{
		cout<<result[i]<<" ";
	}
	cout<<endl;
	
	// 将上面ARIMA模型预测得到的因素值，结合多元回归分析得到的参数，预测未来3天AQI值
	double AQIyuce[3];

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<number;j++)
		{
			AQIyuce[i]+=result[j]*shouji[i][j];
		}
		AQIyuce[i]+=result[7];
		AQIyuce[i]=(int)(AQIyuce[i]);
		cout<<"未来第"<<i+1<<"天的AQI值为："<<AQIyuce[i]<<endl;
	}

	//第四部分：根据上述预测得到的AQI值，发布未来3天的空气质量预警
	yuce(AQIyuce);

	//至此，本程序的目的实现，程序结束
	return 0;
}

