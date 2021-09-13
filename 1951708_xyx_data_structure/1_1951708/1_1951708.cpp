
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
	node* head, * current;//headΪ��ͷ�սڵ�
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
		cout << "���޿�����" << endl;
		return;
	}
	int want;
	while (1)
	{
		cout << "������Ҫɾ���Ŀ����Ŀ���:";
		cin >> want;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	node* q = find(want);
	if (q == NULL)
	{
		cout << "�޸ÿ��ŵĿ�����" << endl;
		return;
	}
	else
	{
		cout << "ɾ���Ŀ�����Ϣ��:";

		cout << setiosflags(ios::left) << setw(8) << q->next->NO << setw(8) << q->next->name << setw(8) << q->next->sex << setw(8) << q->next->age << setw(8) << q->next->job << endl;
		node* p = q->next;
		q->next = p->next;
		delete p;
		studentnum--;
	}


}

void list::show(node* p = NULL)
{
	cout << "����    ����    �Ա�    ����    �������" << endl;
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
	cout << "���Ƚ���������Ϣϵͳ��" << endl;
	int num;
	while (1)
	{
		cout << "�����뿼������:";
		cin >> num;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (num <= 0)
		{
			cout << "������һ��������!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');

		}
		else
			break;
	}
	studentnum = num;
	cout << "���������뿼���Ŀ��ţ��������Ա������Լ��������!" << endl;
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
	cout << "������Ҫ�����λ��:";
	while (1)
	{
		cin >> place;
		if (!(place > 0 && place <= studentnum + 1))
		{
			cout << "�����������������!" << endl;
		}
		else
			break;
	}
	cout << "����������Ҫ���뿼���Ŀ��ţ��������Ա������Լ��������!" << endl;

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
		cout << "��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << endl;
		cin >> choice;
		if (!(choice >= 0 && choice < 6))
		{
			cout << "�����������������!" << endl;
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
				cout << "������Ҫ���ҿ����Ŀ���:";
				cin >> want;
				q = find(want);
				if (q == NULL)
				{
					cout << "�޸ÿ��ŵĿ�����" << endl;
					break;
				}
				else
				{
					cout << "���ҵĿ�����Ϣ��:";
					cout << setiosflags(ios::left) << setw(8) << q->next->NO << setw(8) << q->next->name << setw(8) << q->next->sex << setw(8) << q->next->age << setw(8) << q->next->job << endl;

					break;
				}
			case 4:
				cout << "������Ҫ�޸ĵĿ����ĵ�ǰ�Ŀ��ţ�";
				cin >> want;
				q = find(want);
				if (q == NULL)
				{
					cout << "�޸ÿ��ŵĿ�����" << endl;
					break;
				}
				else
				{
					cout << "�������޸ĺ����Ϣ:" << endl;
					cin >> q->next->NO >> q->next->name >> q->next->sex >> q->next->age >> q->next->job;
					cout << "�޸ĺ�Ŀ�����ϢΪ:" << endl;
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