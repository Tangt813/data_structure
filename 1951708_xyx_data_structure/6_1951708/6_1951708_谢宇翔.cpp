
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
	
	void funcA();//功能A完善家谱
	void funcB();//功能B添加家庭成员
	void funcC();//功能C解散家庭
	void funcD();//功能D改名字
	void freefamily(node* p);//递归解散家庭
	bool find(string want);//在树中找data为want的节点并将current指向它。
	bool parent();//在树中寻找current节点的双亲节点，并将current指向它。
	bool findparent(node* root, node* p);//在以root为根的树中找节点p的双亲节点，并将current指向它
	bool isempty();//检查树非空
	bool find(node* root, string want);//在以root为根的树中找data为want的节点，并将current指向它
public:
	void menu();//菜单
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
	if (root->data == want)//搜索成功
	{
		result = true;
		current = root;
	}
	else//搜索失败
	{
		node* q = root->firstchild;
		while (q != NULL && !(result = find(q, want)))//去长子链遍历
			q = q->bro;//去兄弟链
	}
	return result;
}

bool tree::findparent(node* root, node* p)
{
	node* q = root->firstchild;
	bool succ;
	while (q != NULL && q != p)
	{
		if (succ = findparent(q, p) == 1)//循环兄弟链
			return succ;
		q = q->bro;
	}
	if (q != NULL && q == p)//找到了
	{
		current = root;
		return 1;
	}
	else//没找到
	{
		current = NULL;
		return 0;
	}
}
bool tree::parent()
{
	node* p = current;
	if (current == NULL || current == root)//空树或者根为当前节点，返回0
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
	cout << "请输入要建立家庭的成员名字：";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)//找data为want的节点是否存在
	{
		cout << "族谱无此人!" << endl;
		return;
	}
	int num = 0;
	while (1)
	{
		cout << "请输入" << current->data << "的子女个数:";
		cin >> num;
		if (!cin.good())
		{
			cout << "输入错误请重新输入！" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else if (num <= 0)
		{
			cout << "请输入一个正整数！" << endl;
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	cout << "请依次输入" << current->data << "的子女的名字:";

	for (int i = 0; i < num; i++)//依次输入子女的名字
	{
		if (i == 0)//长子
		{
			current->firstchild = new node;
			if (current->firstchild == NULL)
			{
				cout << "开辟空间失败！" << endl;
				return;
			}
			current = current->firstchild;
			cin >> current->data;
		}
		else//长子的兄弟
		{
			current->bro = new node;
			if (current->bro == NULL)
			{
				cout << "开辟空间失败！" << endl;
				return;
			}
			current = current->bro;
			cin >> current->data;
		}
	}
	//后面的代码是起输出子女名字的功能
	parent();
	cout << current->data << "的第一代子女为：";
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
	cout << "请输入要添加子女的人的名字:";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)
	{
		cout << "族谱无此人!" << endl;
		return;
	}
	cout << "请输入" << want << "新添加的子女的名字:";
	string add;
	cin >> add;
	if (current->firstchild == NULL)//他没有孩子，就把孩子接到长子的位置上
	{
		current->firstchild = new node;
		if (current->firstchild == NULL)
		{
			cout << "开辟空间失败！" << endl;
			return;
		}
		current = current->firstchild;
		current->data = add;

	}
	else//有孩子，就把孩子接在长子的兄弟链上
	{
		current = current->firstchild;
		while (current->bro != NULL)//循环兄弟链
		{
			current = current->bro;
		}
		current->bro = new node;
		if (current->bro == NULL)
		{
			cout << "开辟空间失败！" << endl;
			return;
		}
		current = current->bro;
		current->data = add;
	}
	//输出
	parent();
	current = current->firstchild;
	cout << want << "的第一代子孙是:";
	while (current != NULL)
	{
		cout << current->data << "  ";
		current = current->bro;
	}


}
void tree::funcC()
{
	cout << "请输入要解散家庭的人的姓名:";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)
	{
		cout << "族谱无此人!" << endl;
		return;
	}
	cout << "要解散家庭的人是:" << want;
	parent();
	node* p = current->firstchild;
	node* q;//q储存要删除的节点
	if (p->data == want)//删除的人是长子
	{
		if (current->firstchild->bro == NULL)//没有其他孩子了，就把双亲节点的长子节点置NULL
		{
			current->firstchild = NULL;
		}
		else//还有孩子，长子的兄弟接替
			current->firstchild = current->firstchild->bro;
		q = p;
	}
	else//删除的人不是长子
	{
		while (p->bro->data != want)//循环兄弟链
		{
			p = p->bro;
		}
		if (p->bro->bro == NULL)//要删除的节点无兄弟了
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
void tree::funcD()//改名很简单
{
	cout << "请输入要更改姓名的人的目前名字:";
	string want;
	cin >> want;
	bool isfind = find(want);
	if (isfind == 0)
	{
		cout << "族谱无此人!" << endl;
		return;
	}
	cout << "请输入更改后的名字:";
	string newname;
	cin >> newname;
	current->data = newname;
	cout << want << "已更名为" << newname;
}
void tree::freefamily(node* p)
{

	if (p->firstchild != NULL)//去长子链
	{
		freefamily(p->firstchild);
	}
	if (p->bro != NULL)//去兄弟链
	{
		freefamily(p->bro);
	}
	delete p;
}
void tree::menu()
{
	cout << "**               家谱管理系统              **" << endl;
	cout << "=============================================" << endl;
	cout << "**             请选择以下的操作            **" << endl;
	cout << "**              A---完善家庭               **" << endl;
	cout << "**              B---添加家庭成员           **" << endl;
	cout << "**              C---解散局部成员           **" << endl;
	cout << "**              D---更改家庭成员名字       **" << endl;
	cout << "**              E---退出程序               **" << endl;
	cout << "=============================================" << endl;
	cout << "首先建立一个家谱" << endl;
	cout << "请输入祖先的名字:" << endl;
	root = new node;
	if (root == NULL)
	{
		cout << "开辟空间失败！" << endl;
		return;
	}
	cin >> root->data;
	cout << "此家族的祖先为:" << root->data << endl;

	while (1)
	{
		char choice;
		while (1)
		{
			cout << endl << "请选择要执行的操作：";
			cin >> choice;
			if (!cin.good() || choice < 'A' || choice>'E')
			{
				cout << "输入错误！请重新输入" << endl;
				cin.clear();//重置cin流
				cin.ignore(100, '\n');//清空输入缓冲区
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