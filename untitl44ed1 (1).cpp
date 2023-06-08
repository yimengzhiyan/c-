#include <iostream>

class CDateInfo {
private:
	int year;
	int month;
	int day;
	
public:
	CDateInfo() : year(2000), month(1), day(1) {}
	CDateInfo(int y, int m, int d) : year(y), month(m), day(d) {}
	void SetDate(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
	}
	void GetDate() const {
		std::cout << year << "-" << month << "-" << day << std::endl;
	}
};
int main() {
	CDateInfo date1, date2(2011, 10, 10);
	
	int y, m, d;
	std::cin >> y >> m >> d;
	date1.SetDate(y, m, d);
	
	date1.GetDate();
	date2.GetDate();
	
	return 0;
}


