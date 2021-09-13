
#include <iostream>
#include <cstring>
using namespace std;

struct node
{
	string data;
	node* firstchild = NULL;
	node* bro = NULL;
};

class tree
{
	node* root, * current;
	
	void funcA();//����A���Ƽ���
	void funcB();//����B��Ӽ�ͥ��Ա
	void funcC();//����C��ɢ��ͥ
	void funcD();//����D������
	void freefamily(node* p);//�ݹ��ɢ��ͥ
	bool find(string want);//��������dataΪwant�Ľڵ㲢��currentָ������
	bool parent();//������Ѱ��current�ڵ��˫�׽ڵ㣬����currentָ������
	bool findparent(node* root, node* p);//����rootΪ���������ҽڵ�p��˫�׽ڵ㣬����currentָ����
	bool isempty();//������ǿ�
	bool find(node* root, string want);//����rootΪ����������dataΪwant�Ľڵ㣬����currentָ����
public:
	void menu();//�˵�
	~tree() {};
};



bool tree::isempty()
{
	if (root == NULL)
	{
		return 1;
	}
	return 0;
}

bool tree::find(node* root, string want)
{
	bool result = false;
	if (root->data == want)//�����ɹ�
	{
		result = true;
		current = root;
	}
	else//����ʧ��
	{
		node* q = root->firstchild;
		while (q != NULL && !(result = find(q, want)))//ȥ����������
			q = q->bro;//ȥ�ֵ���
	}
	return result;
}

bool tree::findparent(node* root, node* p)
{
	node* q = root->firstchild;
	bool succ;
	while (q != NULL && q != p)
	{
		if (succ = findparent(q, p) == 1)//ѭ���ֵ���
			return succ;
		q = q->bro;
	}
	if (q != NULL && q == p)//�ҵ���
	{
		current = root;
		return 1;
	}
	else//û�ҵ�
	{
		current = NULL;
		return 0;
	}
}
bool tree::parent()
{
	node* p = current;
	if (current == NULL || current == root)//�������߸�Ϊ��ǰ�ڵ㣬����0
	{
		current = NULL;
		return 0;
	}
	return findparent(root, p);
}
bool tree::find(string want)
{
	if (isempty())
		return false;
	return find(root, want);

}
void tree::funcA()
{
	cout << "������Ҫ������ͥ�ĳ�Ա���֣�";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)//��dataΪwant�Ľڵ��Ƿ����
	{
		cout << "�����޴���!" << endl;
		return;
	}
	int num = 0;
	while (1)
	{
		cout << "������" << current->data << "����Ů����:";
		cin >> num;
		if (!cin.good())
		{
			cout << "����������������룡" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else if (num <= 0)
		{
			cout << "������һ����������" << endl;
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	cout << "����������" << current->data << "����Ů������:";

	for (int i = 0; i < num; i++)//����������Ů������
	{
		if (i == 0)//����
		{
			current->firstchild = new node;
			if (current->firstchild == NULL)
			{
				cout << "���ٿռ�ʧ�ܣ�" << endl;
				return;
			}
			current = current->firstchild;
			cin >> current->data;
		}
		else//���ӵ��ֵ�
		{
			current->bro = new node;
			if (current->bro == NULL)
			{
				cout << "���ٿռ�ʧ�ܣ�" << endl;
				return;
			}
			current = current->bro;
			cin >> current->data;
		}
	}
	//����Ĵ������������Ů���ֵĹ���
	parent();
	cout << current->data << "�ĵ�һ����ŮΪ��";
	current = current->firstchild;
	cout << current->data << "  ";
	while (current->bro != NULL)
	{
		current = current->bro;
		cout << current->data << "  ";
	}
}
void tree::funcB()
{
	cout << "������Ҫ�����Ů���˵�����:";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)
	{
		cout << "�����޴���!" << endl;
		return;
	}
	cout << "������" << want << "����ӵ���Ů������:";
	string add;
	cin >> add;
	if (current->firstchild == NULL)//��û�к��ӣ��ͰѺ��ӽӵ����ӵ�λ����
	{
		current->firstchild = new node;
		if (current->firstchild == NULL)
		{
			cout << "���ٿռ�ʧ�ܣ�" << endl;
			return;
		}
		current = current->firstchild;
		current->data = add;

	}
	else//�к��ӣ��ͰѺ��ӽ��ڳ��ӵ��ֵ�����
	{
		current = current->firstchild;
		while (current->bro != NULL)//ѭ���ֵ���
		{
			current = current->bro;
		}
		current->bro = new node;
		if (current->bro == NULL)
		{
			cout << "���ٿռ�ʧ�ܣ�" << endl;
			return;
		}
		current = current->bro;
		current->data = add;
	}
	//���
	parent();
	current = current->firstchild;
	cout << want << "�ĵ�һ��������:";
	while (current != NULL)
	{
		cout << current->data << "  ";
		current = current->bro;
	}


}
void tree::funcC()
{
	cout << "������Ҫ��ɢ��ͥ���˵�����:";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)
	{
		cout << "�����޴���!" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ������:" << want;
	parent();
	node* p = current->firstchild;
	node* q;//q����Ҫɾ���Ľڵ�
	if (p->data == want)//ɾ�������ǳ���
	{
		if (current->firstchild->bro == NULL)//û�����������ˣ��Ͱ�˫�׽ڵ�ĳ��ӽڵ���NULL
		{
			current->firstchild = NULL;
		}
		else//���к��ӣ����ӵ��ֵܽ���
			current->firstchild = current->firstchild->bro;
		q = p;
	}
	else//ɾ�����˲��ǳ���
	{
		while (p->bro->data != want)//ѭ���ֵ���
		{
			p = p->bro;
		}
		if (p->bro->bro == NULL)//Ҫɾ���Ľڵ����ֵ���
		{
			q = p->bro;
			p->bro = NULL;
		}
		else
		{
			q = p->bro;
			p->bro = p->bro->bro;
		}

	}
	if (q->firstchild != NULL)
		freefamily(q->firstchild);
	delete q;
}
void tree::funcD()//�����ܼ�
{
	cout << "������Ҫ�����������˵�Ŀǰ����:";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)
	{
		cout << "�����޴���!" << endl;
		return;
	}
	cout << "��������ĺ������:";
	string newname;
	cin >> newname;
	current->data = newname;
	cout << want << "�Ѹ���Ϊ" << newname;
}
void tree::freefamily(node* p)
{

	if (p->firstchild != NULL)//ȥ������
	{
		freefamily(p->firstchild);
	}
	if (p->bro != NULL)//ȥ�ֵ���
	{
		freefamily(p->bro);
	}
	delete p;
}
void tree::menu()
{
	cout << "**               ���׹���ϵͳ              **" << endl;
	cout << "=============================================" << endl;
	cout << "**             ��ѡ�����µĲ���            **" << endl;
	cout << "**              A---���Ƽ�ͥ               **" << endl;
	cout << "**              B---��Ӽ�ͥ��Ա           **" << endl;
	cout << "**              C---��ɢ�ֲ���Ա           **" << endl;
	cout << "**              D---���ļ�ͥ��Ա����       **" << endl;
	cout << "**              E---�˳�����               **" << endl;
	cout << "=============================================" << endl;
	cout << "���Ƚ���һ������" << endl;
	cout << "���������ȵ�����:" << endl;
	root = new node;
	if (root == NULL)
	{
		cout << "���ٿռ�ʧ�ܣ�" << endl;
		return;
	}
	cin >> root->data;
	cout << "�˼��������Ϊ:" << root->data << endl;

	while (1)
	{
		char choice;
		while (1)
		{
			cout << endl << "��ѡ��Ҫִ�еĲ�����";
			cin >> choice;
			if (!cin.good() || choice < 'A' || choice>'E')
			{
				cout << "�����������������" << endl;
				cin.clear();//����cin��
				cin.ignore(100, '\n');//������뻺����
			}
			else
				break;
		}
		switch (choice)
		{
		case 'A':
		case 'a':
			funcA();
			break;
		case 'B':
		case 'b':
			funcB();
			break;
		case 'C':
		case 'c':
			funcC();
			break;
		case'd':
		case'D':
			funcD();
			break;
		case 'e':
		case'E':
			return;
		}

	}



}
int main()
{
	tree T;
	T.menu();

}