#include <iostream>
using namespace std;
struct node
{
	int data = 0;
	node* next = NULL;
};

class list
{
	node* head = new node, * current = head;
public:
	void get();
	friend void intersection(list &S1, list &S2, list& S3);//交集
	friend void show(list &s);
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
};

void list::get()
{
	
	while (1)
	{
		int i;
		while (1)
		{
			cin >> i;
			if (!cin.good())
			{
				cout << "输入错误！请重新输入" << endl;
				current = head;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
				break;
		}
		if(current->next==NULL)
		current->next = new node;
		current = current->next;
		current->data = i;
		if (i == -1)
		{
			break;
		}

	}
}

void intersection(list &s1, list &s2,list &s3)
{
	s1.current = s1.head->next;
	s2.current = s2.head->next;
	while (s1.current->data != -1 && s2.current->data != -1)
	{
		if (s1.current->data < s2.current->data)
		{
			s1.current = s1.current->next;
		}
		else if (s1.current->data > s2.current->data)
		{
			s2.current = s2.current->next;
		}
		else
		{
			s3.current->next = new node;
			s3.current = s3.current->next;
			s3.current->data = s1.current->data;
			s1.current = s1.current->next;
			s2.current = s2.current->next;
		}
	}

}

void show(list &s)
{
	s.current = s.head->next;
	if (s.current == NULL)//空集
	{
		cout << "NULL" << endl;
	}
	while (s.current != NULL)
	{
		if (s.current != s.head->next)
		{
			cout << " ";
		}
		cout << s.current->data;
		s.current = s.current->next;
	}
	
}
int main()
{
	cout << "请输入2个非降序序列:(以-1结束)" << endl;
	list S1, S2 ,S3;
	S1.get();
	S2.get();
	intersection(S1, S2,S3);
	show(S3);
}