#include <iostream>
using namespace std;

/*
# # # # # # #
# 0 # 0 0 0 #
# 0 0 # # 0 #
# 0 0 0 # 0 #
# # # 0 0 0 #
# # # # 0 0 #
# # # # # # #
*/
bool isdone = 0;//�Ƿ񵽴��յ�
struct node
{
	int x = 1;
	int y = 1;
	node* next = NULL;
	node* before=NULL;
};
class path
{
	node* head=new node, * current=head;
	
	friend void dfs(int x, int y);
	void show();
public:
	~path()
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

void path::show()
{
	cout << "(" << head->x << "," << head->y << ")";//����������
	current = head->next;
	while (current != NULL)//��������ÿ��һ��������
	{
		cout << "-> (" << current->x << "," << current->y << ")";
		current = current->next;
	}
	return;
}
path p1;
int targetx=5, targety=5;//�յ�����
char map[7][7]; //��ͼ
int value[7][7];//Ȩֵ
void dfs(int x, int y)
{
	if (isdone == 1)//�����յ��˾��˳�
	{
		return;
	}
	int next[4][2] =
	{ 
		{0,1},//������
		{1,0},//������
		{0,-1},//������
		{-1,0} //������
	};//��λ����
	int tx, ty, k;//�ж���һ����λ
	if (x == targetx && y == targety)//�����յ�
	{
		isdone = 1;
		p1.show();//��ӡ·��
		return;
		
	}
	for (k = 0; k < 3; k++)
	{
		//������һ��������
		tx = x + next[k][0];
		ty = y + next[k][1];
		if (tx < 1 || tx>5 || ty < 1 || ty>5)//Խ��
		{
			continue;
		}
		if (map[tx][ty] == '0' && value[tx][ty] == 0)//����һ����ȡ�ķ�λ
		{
			p1.current->next = new node;
			p1.current->next->before = p1.current;
			p1.current = p1.current->next;
			p1.current->x = tx;
			p1.current->y = ty;
			value[tx][ty] = 1;//���������Ѿ��߹�
			dfs(tx, ty);//������һ����
			if (isdone == 0)//��������ɾ�������ڵ㣬�����ǻ���
			{
				node* q = p1.current;
				p1.current = p1.current->before;
				p1.current->next = NULL;
				delete q;
			}
			else
				return;
			

		}
	}
	if (x == 1 && y == 1)//�ߵ�����˵����·���ߣ��޷������յ㣬�ڲ�ȷ�����ʱ���ɽ�2��1��Ϊstartx,starty����
	{
		cout << "������޷������յ㣡" << endl;
		return;
	}
	return;
}
int main()
{
	int i, j;
	cout << "�������Թ�:" << endl;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			cin >> map[i][j];
		}
	}
	cout << "�Թ���ͼ:" << endl;
	cout << "        0��     1��     2��     3��     4��     5��     6��" << endl;
	for (i = 0; i < 7; i++)
	{
		cout << i << "��      ";
		for (j = 0; j < 7; j++)
		{
			cout<< map[i][j];
			cout << "       ";
		}
		cout << endl<<endl;
	}
	value[1][1] = 1;
	
	dfs(1, 1);
}