#include <iostream>
using namespace std;

int main() 
{
	int a,b,c,d,m;
	double n;
	for (a = 1; a <= 9; a++) {
		for (b = 0; b <= 9; b++) {
			if (a == b) { 
				for (c = 0; c <= 9; c++) {
					if (c != a && c != b) { 
						for (d = 0; d <= 9; d++) {
							if (d != a && d != b && d == c) { 
								if(m = a * 1000 + b * 100 + c * 10 + d){
									  if(m=n*n){
										 cout<<n<<endl;
									  }	  
								  
								}
							    
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

