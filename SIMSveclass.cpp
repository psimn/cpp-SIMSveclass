// SIMSveclass.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

void clear(void);
void welcome(void);

void clear(void) {
	system("pause");
	system("cls");
}

void welcome(void) {
	cout << "No Student Info Found!" << endl;
	cout << "Inputting function has been processing...";
	clear();
}

class info {
private:
	unsigned int id;
	string name;
	double cs_mark, eng_mark, sum_mark;
public:
	void set(unsigned int num, string str, double csm, double enm);
	void add(void);
	string getName(void);
	double getCSM(void);
	double getEngM(void);
	double getSumM(void);
};

void info::set(unsigned int num, string str, double csm, double enm) {
	id = num;
	name = str;
	cs_mark = csm;
	eng_mark = enm;
	add();
}

void info::add(void) {
	sum_mark = cs_mark + eng_mark;
}

string info::getName(void) {
	return name;
}

double info::getCSM(void) {
	return cs_mark;
}

double info::getEngM(void) {
	return eng_mark;
}

double info::getSumM(void) {
	return sum_mark;
}


class student {
private:
	vector<info> students;
public:
	~student() {
		students.clear();
	}
	info null(void);
	bool menu(void);
	bool progress(void);
	void input(void);
	void dele(void);
	bool _del(void);
	void find(int func_num);
	vector<info>::iterator search_name(string target);
	vector<info>::iterator compare(double mark);
	void print_name(vector<info>::iterator &iter);
};

info student::null(void) {
	info str;
	str.set(0, "0", -1, -1);
	return str;
}

bool student::menu(void) {
	char check = 'Y';
	while (check != 'E' || check != 'e') {
		cout << "Welcome to SIMS vekver!!!" << endl;
		cout << "1.List All Failded Students' Names" << endl;
		cout << "2.Add Newer" << endl;
		cout << "3.Delete Loser" << endl;
		cout << "4.List All 'Good' Students" << endl;
		cout << "0. Exit" << endl;
		if (progress()) {
			break;
		}
	}
	clear();
	cout << "Thank you for using! :)" << endl;
	return true;
}

bool student::progress(void) {
	int i;
	cin >> i;
	switch (i)
	{
	case 0:
		return true;
	case 1:
		find(i);
		break;
	case 2:
		input();
		break;
	case 3:
		dele();
		break;
	case 4:
		find(i);
		break;
	default:
		break;
	}
	return false;
}

void student::input(void) {
	unsigned int id;
	string name;
	double cs_mark, eng_mark;
	info temp;
	char check = 'Y';
	int count = students.size();
	while (check == 'Y' || check == 'y') {
		cout << "Input ID,NAME,Mark of COMPUTER_SCIENCE and ENGLISH: ";
		cin >> id >> name >> cs_mark >> eng_mark;
		temp.set(id, name, cs_mark, eng_mark);
		if (count != 0) {
			students.insert(compare(temp.getSumM()), temp);
		}
		else {
			students.push_back(temp);
		}
		++count;
		cout << "Y or y to Continue...";
		cin >> check;
	}
	cout << "End of Inputting" << endl;
}

void student::dele(void) {
	if (students.size() != 0) {
		cout << "Input Student name which you wanna delete its information: ";
		if (_del()) {
			cout << "Success!" << endl;
		}
		else {
			cout << "Not Found!!!" << endl;
		}
	}
	else {
		cout << "No Member Exists!!!" << endl;
	}
}

bool student::_del(void) {
	string name;
	cin >> name;
	vector<info>::iterator iter = search_name(name);
	if (iter->getName() != "0") {
		students.erase(iter);
		return true;
	}
	else {
		students.pop_back();
		return false;
	}
}

void student::find(int func_num) {
	switch (func_num)
	{
	case 1:
		for (vector<info>::iterator iter = students.begin(); iter != students.end(); ++iter) {
			bool it_does = false;
			if (iter->getCSM() < 60) {
				cout << "CS ";
				it_does = true;
			}
			if (iter->getEngM() < 60) {
				cout << "ENG ";
				it_does = true;
			}
			if (it_does) {
				print_name(iter);
				cout << endl;
			}
		}
		break;
	case 4:
		for (vector<info>::iterator iter = students.begin(); iter != students.end(); ++iter) {
			if (iter->getSumM() / 2 >= 70 && iter->getSumM() / 2 <= 90) {
				print_name(iter);
				cout << endl;
			}
		}
		break;
	default:
		cout << "That's Not Possible!" << endl;
		break;
	}
}

vector<info>::iterator student::search_name(string target) {
	if (students.size() <= 1) {
		if (target == students.at(0).getName()) {
			vector<info>::iterator iter = students.begin();
			return iter;
		}
		else {
			students.push_back(null());
			return students.end();
		}
	}
	else {
		for (vector<info>::iterator iter = students.begin(); iter != students.end(); ++iter) {
			if (iter->getName() == target) {
				return iter;
			}
		}
		cout << "ERROR!!!" << endl;
		students.push_back(null());
		return students.end();
	}
}

vector<info>::iterator student::compare(double mark) {
	vector<info>::iterator iter;
	for (iter = students.begin(); iter != students.end(); ++iter) {
		if (iter->getSumM() > mark) {
			continue;
		}
		else {
			break;
		}
	}
	return iter;
}

void student::print_name(vector<info>::iterator &iter) {
	cout << iter->getName();
}

int main()
{
	student stu;
	welcome();
	stu.input();
	while (1) {
		if (stu.menu()) {
			return 0;
		}
		clear();
	}
	return 1;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
