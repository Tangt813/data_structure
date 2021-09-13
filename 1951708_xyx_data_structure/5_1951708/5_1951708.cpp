#include<iostream>
using namespace std;
struct node
{
	int data = 0;
	node* next=NULL;
};

class list
{
public:
	node* head = NULL;
	node*current = NULL;
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

int main()
{
	list L1, L2;//����2������
	int num;
	bool isfirst1 = 1, isfirst2 = 1;
	cout << "��������ͻ�����:(С��1000)" << endl;
	while (1)
	{
		cin >> num;
		if (cin.fail())
		{
			cout << "��������ȷ��ֵ!����������ͻ�����:" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (num <= 0)
		{
			cout << "������������������������ͻ�����:" << endl;
			cin.ignore(1000, '\n');
		}
		else if (num > 1000)
		{
			cout << "������С��1000��������������������ͻ�����:" << endl;
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	
	cout << "���������пͻ��ı��:" << endl;
	int i = 0;
	for (; i < num; i++)
	{
		int no;
		while (1)
		{
			cin >> no;
			if (cin.fail())
			{
				cout << "��������ȷ��ֵ!��Ӵ��󴦿�ʼ��������ͻ����:" << endl;
				cin.clear();
				cin.ignore(1);
				
			}
			else if (no <= 0)
			{
				cout << "����������������Ӵ��󴦿�ʼ��������ͻ����:" << endl;
				cin.ignore(1);
				
			}
			else
				break;
		}
		if (no % 2 == 0)//ż��
		{
			if (isfirst2 == 1)//����ͷ���
			{
				L2.head = new node;
				L2.current = L2.head;
				L2.head->data = no;
				isfirst2 = 0;
			}
			else
			{
				L2.current->next = new node;
				L2.current = L2.current->next;
				L2.current->data = no;
			}
		}
		else//����
		{
			if (isfirst1 == 1)//����ͷ���
			{
				L1.head = new node;
				L1.current = L1.head;
				L1.head->data = no;
				isfirst1 = 0;
			}
			else
			{
				L1.current->next = new node;
				L1.current = L1.current->next;
				L1.current->data = no;
			}
		}
		
		
	}
	i = 0;
	L1.current = L1.head;
	L2.current = L2.head;
	for (; i < num; )
	{

		if (L1.current!= NULL)
		{
			if (i == 0)//���ͷ��㣬�����ո�
			{
				cout  << L1.current->data;
				L1.current = L1.current->next;
				i++;
			}
			else//���ո�
			{
				cout << " " << L1.current->data;
				L1.current = L1.current->next;
				i++;
			}
			
		}
		if (L1.current != NULL)
		{
			cout << " " << L1.current->data;
			L1.current = L1.current->next;
			i++;
		}
		if (L2.current != NULL)
		{
			if (i == 0)
			{
				cout  << L2.current->data;
				L2.current = L2.current->next;
				i++;
			}
			else
			{
				cout << " " << L2.current->data;
				L2.current = L2.current->next;
				i++;
			}
			
		}
		
	}
	return 0;
}