#include <cstring>
#include <iostream>

class Student {
private:
	char name[11];
	int gender;
	unsigned age;
	
public:
	Student() : gender(0), age(0) {}
	void SetName(const char* n) {
		std::strcpy(name, n);
	}
	void SetGender(int g) {
		gender = g;
	}
	void SetAge(unsigned a) {
		age = a;
	}
	void GetName(char* n) const {
		std::strcpy(n, name);
	}
	int GetGender() const {
		return gender;
	}
	unsigned GetAge() const {
		return age;
	}
};
int main() {
	Student Zhang_San;
	char* name0 = new char[11];
	std::cin >> name0;
	int iSex, iOld;
	std::cin >> iSex >> iOld;
	Zhang_San.SetName(name0);
	Zhang_San.SetGender(iSex);
	Zhang_San.SetAge(iOld);
	
	char* name1 = new char[11];
	Zhang_San.GetName(name1);
	std::cout << "Zhang_San's name is " << name1 << std::endl;
	std::cout << "Zhang_San's gender is " << Zhang_San.GetGender() << std::endl;
	std::cout << "Zhang_San's age is " << Zhang_San.GetAge() << std::endl;
	
	delete[] name0;
	delete[] name1;
	return 0;
}


