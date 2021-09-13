
#include <iostream>
#include<cstring>
#include<iomanip>
using namespace std;

struct node
{
	int NO = 0;
	string name;
	string sex;
	int age = 0;
	string job;
	node* next = NULL;
};

class list
{
public:
	node* head, * current;//head为表头空节点
	int studentnum = 0;
	list()
	{
		head = new node, current = NULL;
	}
	~list()
	{
		node* p = head;
		node* q = p;
		while (p->next != NULL)
		{
			p = p->next;
			delete q;
			q = p;
		}
		delete q;
	}

	void build();
	void menu();
	void insert();
	void show(node* p);
	void tjdelete();
	node* find(int want);
};

node* list::find(int want)
{

	current = head;
	while (current->next != NULL)
	{
		if (current->next->NO == want)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void list::tjdelete()
{
	current = head->next;
	if (current == NULL)
	{
		cout << "已无考生！" << endl;
		return;
	}
	int want;
	while (1)
	{
		cout << "请输入要删除的考生的考号:";
		cin >> want;
		if (!cin.good())
		{
			cout << "输入错误！请重新输入" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	node* q = find(want);
	if (q == NULL)
	{
		cout << "无该考号的考生！" << endl;
		return;
	}
	else
	{
		cout << "删除的考生信息是:";

		cout << setiosflags(ios::left) << setw(8) << q->next->NO << setw(8) << q->next->name << setw(8) << q->next->sex << setw(8) << q->next->age << setw(8) << q->next->job << endl;
		node* p = q->next;
		q->next = p->next;
		delete p;
		studentnum--;
	}


}

void list::show(node* p = NULL)
{
	cout << "考号    姓名    性别    年龄    报考类别" << endl;
	if (p == NULL)
	{
		current = head->next;
		while (current != NULL)
		{
			cout << setiosflags(ios::left) << setw(8) << current->NO << setw(8) << current->name << setw(8) << current->sex << setw(8) << current->age << setw(8) << current->job << endl;
			current = current->next;
		}
	}
	else
	{
		current = head->next;

		while (current->NO != p->NO)
		{
			current = current->next;
		}
		//cout << current->NO << current->name << current->sex << current->age << current->job << endl;
		cout << setiosflags(ios::left) << setw(8) << current->NO << setw(8) << current->name << setw(8) << current->sex << setw(8) << current->age << setw(8) << current->job << endl;

	}
}

void list::build()
{
	cout << "首先建立考生信息系统！" << endl;
	int num;
	while (1)
	{
		cout << "请输入考生人数:";
		cin >> num;
		if (!cin.good())
		{
			cout << "输入错误！请重新输入" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (num <= 0)
		{
			cout << "请输入一个正整数!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');

		}
		else
			break;
	}
	studentnum = num;
	cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别!" << endl;
	current = head;
	for (int i = 0; i < num; i++)
	{
		current->next = (node*)new node;
		current = current->next;
		cin >> current->NO >> current->name >> current->sex >> current->age >> current->job;
	}
	show();
}



void list::insert()
{
	int place;
	cout << "请输入要插入的位置:";
	while (1)
	{
		cin >> place;
		if (!(place > 0 && place <= studentnum + 1))
		{
			cout << "输入错误，请重新输入!" << endl;
		}
		else
			break;
	}
	cout << "请依次输入要插入考生的考号，姓名，性别，年龄以及报考类别!" << endl;

	current = head;
	for (int i = 0; i < place - 1; i++)
	{
		current = current->next;
	}
	node* p = new node;
	cin >> p->NO >> p->name >> p->sex >> p->age >> p->job;
	p->next = current->next;
	current->next = p;
	studentnum++;
	show();

}

void list::menu()
{

	int choice;
	int want;
	node* q;
	while (1)
	{
		cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
		cin >> choice;
		if (!(choice >= 0 && choice < 6))
		{
			cout << "输入错误，请重新输入!" << endl;
		}
		else
			switch (choice)
			{
			case 1:
				insert();
				break;
			case 2:
				tjdelete();
				break;
			case 3:
				cout << "请输入要查找考生的考号:";
				cin >> want;
				q = find(want);
				if (q == NULL)
				{
					cout << "无该考号的考生！" << endl;
					break;
				}
				else
				{
					cout << "查找的考生信息是:";
					cout << setiosflags(ios::left) << setw(8) << q->next->NO << setw(8) << q->next->name << setw(8) << q->next->sex << setw(8) << q->next->age << setw(8) << q->next->job << endl;

					break;
				}
			case 4:
				cout << "请输入要修改的考生的当前的考号：";
				cin >> want;
				q = find(want);
				if (q == NULL)
				{
					cout << "无该考号的考生！" << endl;
					break;
				}
				else
				{
					cout << "请输入修改后的信息:" << endl;
					cin >> q->next->NO >> q->next->name >> q->next->sex >> q->next->age >> q->next->job;
					cout << "修改后的考生信息为:" << endl;
					cout << setiosflags(ios::left) << setw(8) << q->next->NO << setw(8) << q->next->name << setw(8) << q->next->sex << setw(8) << q->next->age << setw(8) << q->next->job << endl;

					break;
				}
			case 5:
				show();
			case 0:
				return;

			}
	}


}

int main()
{
	list L1;
	L1.build();
	L1.menu();
}