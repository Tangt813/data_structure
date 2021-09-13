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
bool isdone = 0;//是否到达终点
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
	cout << "(" << head->x << "," << head->y << ")";//将起点先输出
	current = head->next;
	while (current != NULL)//不是起点后，每过一个点就输出
	{
		cout << "-> (" << current->x << "," << current->y << ")";
		current = current->next;
	}
	return;
}
path p1;
int targetx=5, targety=5;//终点坐标
char map[7][7]; //地图
int value[7][7];//权值
void dfs(int x, int y)
{
	if (isdone == 1)//到了终点了就退出
	{
		return;
	}
	int next[4][2] =
	{ 
		{0,1},//向右走
		{1,0},//向下走
		{0,-1},//向左走
		{-1,0} //向上走
	};//方位数组
	int tx, ty, k;//判断下一个方位
	if (x == targetx && y == targety)//到了终点
	{
		isdone = 1;
		p1.show();//打印路径
		return;
		
	}
	for (k = 0; k < 3; k++)
	{
		//计算下一个点坐标
		tx = x + next[k][0];
		ty = y + next[k][1];
		if (tx < 1 || tx>5 || ty < 1 || ty>5)//越界
		{
			continue;
		}
		if (map[tx][ty] == '0' && value[tx][ty] == 0)//到了一个可取的方位
		{
			p1.current->next = new node;
			p1.current->next->before = p1.current;
			p1.current = p1.current->next;
			p1.current->x = tx;
			p1.current->y = ty;
			value[tx][ty] = 1;//标记这个点已经走过
			dfs(tx, ty);//尝试下一个点
			if (isdone == 0)//到这里是删除本个节点，这里是回溯
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
	if (x == 1 && y == 1)//走到这里说明无路可走，无法到达终点，在不确定起点时，可将2个1改为startx,starty即可
	{
		cout << "此起点无法到达终点！" << endl;
		return;
	}
	return;
}
int main()
{
	int i, j;
	cout << "请输入迷宫:" << endl;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			cin >> map[i][j];
		}
	}
	cout << "迷宫地图:" << endl;
	cout << "        0列     1列     2列     3列     4列     5列     6列" << endl;
	for (i = 0; i < 7; i++)
	{
		cout << i << "行      ";
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