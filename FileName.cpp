#include<bits/stdc++.h>
#include<sstream>
#include<iomanip>
using namespace std;

struct student {
	string id;
	string name;
	int math;
	int chinese;
};

struct Node {
	student data;
	Node* next;
	Node(student s) :data(s), next(nullptr) {}
};

class studentList {
private:
	Node* head;
	int count;

public:
	studentList() {
		head = new Node(student{});
		count = 0;
	}

	~studentList() {
		Node* p = head;
		while (p != nullptr) {
			Node* temp = p;
			p = p->next;
			delete temp;
		}
	}

	bool addStudent(student s) {
		Node* p = head->next;
		while (p != nullptr) {
			if (p->data.id == s.id) {
				return false;
			}
			p = p->next;
		}

		Node* tail = head;
		while (tail->next != nullptr) {
			tail = tail->next;
		}
		tail->next = new Node(s);
		count++;
		return true;
	}

	Node* findStudent(string id) {
		Node* p = head->next;
		while (p != nullptr) {
			if (p->data.id == id) {
				return p;
			}
			p = p->next;
		}
		return nullptr;
	}

	void traverse(function<void(student)>func) {
		Node* p = head->next;
		while (p != nullptr) {
			func(p->data);
			p = p->next;
		}
	}

	bool deleteStudent(string id) {
		Node* pre = head;
		Node* cur = head->next;

		while (cur != nullptr) {
			if (cur->data.id == id) {
				pre->next = cur->next;
				delete cur;
				count--;
				return true;
			}
			pre = cur;
			cur = cur->next;
		}
		return false;
	}

	int getCount() {
		return count;
	}
};

studentList stuList;

void savetoFile() {
	ofstream fout("student.csv");

	if (!fout) {
		cout << "打开文件失败！" << endl;
		return;
	}

	

	stuList.traverse([&](student s) {
		fout << s.id << "," << s.name << "," << s.math << "," << s.chinese << endl;
		});

	fout.close();
	cout << "数据已保存到student.csv中" << endl;
}

void addStudent() {
	
	student s;

	cout << "请输入学生的学号" << endl;
	cin >> s.id;

	
	cout << "请输入学生姓名:" << endl;
	cin >> s.name;

	cout << "请输入学生的数学成绩：" << endl;
	while (!(cin >> s.math) || s.math < 0 || s.math>100) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "输入错误！请输入0-100之间的数字：" << endl;
	}

	cout << "请输入学生的语文成绩：" << endl;
	while (!(cin >>s.chinese) || s.chinese < 0 ||s.chinese>100) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "输入错误！请输入0-100之间的数字：" << endl;
	}

	

	if (stuList.addStudent(s)) {
		cout << "新加入学生成功!" << endl;
	}
	else {
		cout << "该学号已被注册！" << endl;
	}
	
	savetoFile();

}

void searchStudent() {
	cout << "请输入想要查询的学生的学号：" << endl;

	string id;

	cin >> id;
	

	Node *p = stuList.findStudent(id);
	if (p != nullptr) {
		cout << "姓名：" << p->data.name << " 数学：" << p->data.math << " 语文：" << p->data.chinese << endl;
	}
	else {
		cout << "未找到该生！" << endl;
	}
}

void  modifyStudent() {
	string id;


	cout << "请输入你想改成绩的学生的学号：" << endl;
	cin >> id;

	

	Node* p = stuList.findStudent(id);
	int newMath, newChinese;

	if (p == nullptr) {
		cout << "未找到该生信息！" << endl;
		return;
	}
	else {
		cout << p->data.id << "号学生姓名为：" << p->data.name << endl;
		cout << "现在你可以对他的成绩进行修改" << endl;
		cout << "当前成绩：数学：" << p->data.math << " 语文：" << p->data.chinese << endl;

		cout << "请输入新的数学成绩：" << endl;
		while (!(cin >> newMath) || newMath < 0 || newMath>100) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "输入错误！请输入0-100之间的数字：" << endl;
		}

		cout << "请输入新的语文成绩：" << endl;
		while (!(cin >> newChinese) || newChinese < 0 || newChinese>100) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "输入错误！请输入0-100之间的数字：" << endl;
		}

		p->data.math = newMath;
		p->data.chinese = newChinese;

		cout << "成绩修改成功！新的成绩为:数学：" << newMath << " 语文：" << newChinese << endl;
	}
	savetoFile();
}

void deleteStudent() {
	cout << "请输入想要删除的学生的学号：" << endl;

	string id;
	int num = -1;

	cin >> id;

	

	Node* p = stuList.findStudent(id);

	if (p != nullptr) {
		cout << "已找到该生的信息!" << endl;
		cout << "姓名：" << p->data.name << " 数学：" << p->data.math << " 语文：" << p->data.chinese << endl;
		cout << "已找到该学生，是否进行删除(Y/N),删除后不可恢复！" << endl;
		
		string choice;
		cin >> choice;

		if (choice == "Y" || choice == "y") {
			stuList.deleteStudent(id);
			cout << "删除成功！" << endl;
			savetoFile();
			return;
		}
		else {
			cout << "已放弃删除！" << endl;
			return;
		}
	}
	else {
		cout << "未找到该生信息!" << endl;
		return;
	}

	
}

void calcAverage() {
	cout << "请输入要计算平均分的学生学号：" << endl;
	string id;
	cin >> id;

	

	Node* p = stuList.findStudent(id);

	if (p != nullptr) {
		double ave;
		ave = (p->data.math + p->data.chinese) / 2.0;
		cout << fixed << setprecision(2) << "该生的平均分为：" << ave << endl;
		return;
	}
	else {
		cout << "未找到该生的信息！" << endl;
		return;
	}
}

void loadFromFile() {
	ifstream fin("student.csv");

	if (!fin) {
		cout << "暂无历史数据，开始使用新系统！" << endl;
		system("pause");
		return;
	}

	string line, id, name;
	int math, chinese, loadCount = 0;

	while (getline(fin, line)) {
		istringstream iss(line);
		getline(iss, id, ',');
		getline(iss, name, ',');
		iss >> math;
		iss.ignore();
		iss >> chinese;

		

		student s;

		s.id = id;
		s.name = name;
		s.math = math;
		s.chinese = chinese;

		if (stuList.addStudent(s)) {
			loadCount++;
		}
	}

	fin.close();
	cout << "成功加载" << loadCount << "条历史数据！" << endl;
	system("pause");
}

int main() {
	loadFromFile();
	while (1) {
		system("cls");
		cout << "\n===== 成绩管理系统 =====\n";
		cout << "1. 新增学生\n";
		cout << "2. 查询学生\n";
		cout << "3. 修改成绩\n";
		cout << "4. 删除学生\n";
		cout << "5. 计算平均分\n";
		cout << "0. 退出系统\n";
		cout << "请选择（0-5）：";

		int choice;

		while (!(cin >> choice) || choice < 0 || choice > 5) {
			cin.clear(); 
			cin.ignore(1000, '\n');
			cout << "输入错误！请输入0-5之间的整数：" << endl;
		}
		switch (choice) {
		case 1:addStudent(); break;
		case 2:searchStudent(); break;
		case 3:modifyStudent(); break;
		case 4:deleteStudent(); break;
		case 5:calcAverage(); break;
		case 0:
			cout << "确认退出系统吗？(Y/N)：" << endl;
			char quit;
			cin >> quit;
			if (quit == 'Y' || quit == 'y') {
				savetoFile();
				cout << "退出系统！感谢使用~OVO!" << endl;
				return 0;
			}
			else {
				break; 
			}
		default:
			cout << "输入错误，请重新选择！\n";
		}
		system("pause");
		system("cls");
	}
	return 0;
}