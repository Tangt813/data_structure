#include<iostream>
using namespace std;
struct Edge
{
	int dest;//边的另一个顶点的位置
	int cost;//边的权值
	Edge* link;//下一个边链的指针
	Edge() { dest = -1; cost = -1; link = NULL; }
	Edge(int num,int weight):dest(num),cost(weight),link(NULL){}
	bool operator!=(Edge& R)const {
		return (dest != R.dest) ? true : false;
	}
};


struct Vertex
{
	char data='\0';
	Edge* adj=NULL;//边链表的头指针
};

struct MSTEdgeNode
{
	int tail, head, key;//头结点的位置，尾节点的位置，边的权值
	MSTEdgeNode():tail(-1),head(-1),key(0){}
	bool operator<=(MSTEdgeNode& R) { return key <= R.key; }
	bool operator>(MSTEdgeNode& R) { return key > R.key; }
};

class MinHeap//最小堆
{
public:
	MinHeap(int sz = 30);
	~MinHeap()
	{
		delete[]heap;
	}
	bool insert(MSTEdgeNode& x);//插入一个节点
	bool removeMin(MSTEdgeNode& x);//移除一个最小的节点
	bool isEmpty()
	{
		return(currentsize == 0) ? true : false;
	}
	bool isFull()
	{
		return (currentsize == maxheapsize) ? true : false;
	}
private:
	MSTEdgeNode* heap;//最小堆里的数据是边节点类
	int currentsize;
	int maxheapsize;
	void siftDown(int start, int m);//由上到下修改顺序
	void siftUp(int start);//由下到上修改顺序
};


class MinSpanTree {//最小生成树
protected:
	
	int maxSize, currentpos;
public:
	MSTEdgeNode* edgevalue;//存储着生成树的节点链
	MinSpanTree(int sz=30):maxSize(sz),currentpos(0){
		edgevalue = new MSTEdgeNode[sz];
	}
	~MinSpanTree()
	{
		delete[]edgevalue;
	}
	void insert(MSTEdgeNode& item);//插入新的连接
	
};


void MinSpanTree::insert(MSTEdgeNode& item)
{
	edgevalue[currentpos].head = item.head;
	edgevalue[currentpos].tail = item.tail;
	edgevalue[currentpos].key = item.key;
	currentpos++;
}
class graph
{
protected:
	int maxVertices;//最大顶点数
	int numEdge;//当前边数
	int numVertices;//当前点数
	const int maxWeight = 9999;
	MinSpanTree MST;//最小生成树

public:
	void menu();
	graph(int sz = 30);
	~graph()
	{
		delete[]NodeTable;
	}
	bool graphIsEmpty()
	{
		if (numEdge == 0)return true;
		else return false;
	}
	bool graphIsFull()//判断图满
	{
		if (numVertices == maxVertices || numEdge == maxVertices * (maxVertices - 1) / 2)return true;
		else return false;
	}
	int getFirstNeighbor(int v);//获取第一个邻接点
	int getNextNeighbor(int v, int now);//获取v的邻接点中now的下一个
	int getWeight(int u, int v);//获取u和v节点之间的边的权值

private:
	Vertex* NodeTable;//邻接表
	bool EdgeExist = 0;//边存在
	int currentpos = 0;//当前位置
	int getVertexPos(char A);//给出顶点vertex在图中的位置
	void CreateNode();//建立顶点
	void AddEdge();//建立边
	void insertEdge(int v1, int v2, int weight);//插入边
	void CreateMintree();//建立最小生成树
	void ShowMintree();//展示最小生成树
};
void graph::ShowMintree()
{
	if (MST.edgevalue[0].head == -1)
	{
		cout << "尚未有最小生成树！" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为:" << endl << endl;
	for (int i = 0; i < numVertices-1; i++)
	{
		cout << NodeTable[MST.edgevalue[i].tail].data << "-<" << MST.edgevalue[i].key << ">->" << NodeTable[MST.edgevalue[i].head].data << "       ";
	}
}
int graph::getWeight(int u, int v)
{
	Edge* t = NodeTable[u].adj;
	while (t != NULL && t->dest != v)//找到t和v之间的边
	{
		t = t->link;
	}
	if (t == NULL)//并无此边
		return -1;
	else
		return t->cost;
}
int graph::getNextNeighbor(int v, int now)
{
	Edge* t = NodeTable[v].adj;
	while (t != NULL && t->dest != now)//找到now节点
		t = t->link;
	if (t == NULL)//没有now节点
		return -1;
	else if (t->link == NULL)//now节点之后已经没有其他节点了
		return -1;
	return t->link->dest;
}
int graph::getFirstNeighbor(int v)
{
	if (NodeTable[v].adj != NULL)
	{
		return NodeTable[v].adj->dest;
	}
	else
		return -1;
}
int graph::getVertexPos(char A)
{
	for (int i = 0; i < numVertices; i++)//找到A节点在数组中的位置
	{
		if (NodeTable[i].data == A)
			return i;
	}
	return -1;
}
graph::graph(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdge = 0;
	NodeTable = new Vertex[maxVertices];
	if (NodeTable == NULL)
	{
		cout << "存储分配错误！" << endl;
		return;
	}
	for (int i = 0; i < maxVertices; i++)//初始化
	{
		NodeTable[i].adj = NULL;
	}
}
void graph::insertEdge(int v1, int v2, int weight)
{//因为已经确认了v1,v2是合法的，所以不用if判定是否合法
	Edge* q, * p = NodeTable[v1].adj;//v1对应的边链表头节点
	while (p != NULL && p->dest != v2)//寻找v2
	{
		p = p->link;
	}
	if (p != NULL)
	{
		cout << "2节点已经有边,无法再建立边！"<<endl;
		return;//v2已经是v1的边了
	}
	
	p = new Edge;
	q = new Edge;
	p->dest = v2, p->cost = weight;
	p->link = NodeTable[v1].adj;
	NodeTable[v1].adj = p;
	q->dest = v1; q->cost = weight;
	q->link = NodeTable[v2].adj;
	NodeTable[v2].adj = q;
	numEdge++; 
	return;
}
void graph::AddEdge()
{
	int Maxnum = numVertices * (numVertices - 1) / 2;
	if (numVertices == 0)
	{
		cout << "图中尚无顶点！" << endl;
		return;
	}
	while (1)
	{
		if (numEdge == Maxnum)//边数到达最大
			return;
		cout << "请输入两个顶点及边:（输入“?”退出，或者到达最大输入数自动退出）";
		char want1, want2;
		cin >> want1>>want2;
		if (want1 == '?')//读到问号
		{
			cin.ignore(1000, '\n');
			return;
		}
			
		int find1 = -1, find2 = -1;//判断是否找到
		for (int i = 0; i < numVertices; i++)
		{
			if (NodeTable[i].data == want1)
				find1 = i;
			else if (NodeTable[i].data == want2)
				find2 = i;
		}
		if (find1 == -1 || find2 ==-1)//只要有一个没找到就报错
		{
			cout << "错误的顶点！请重新输入" << endl;
			cin.ignore(1000, '\n');
			continue;
		}
		else
		{
			int value;
			cin >> value;//输入权值
			if (cin.fail() || value < 0)
			{
				cout << "输入错误，请重新输入!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			else if (value == 0)
			{
				cout << "请输入正整数，请重新输入!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
				
			else
			{
				EdgeExist = 1;
				insertEdge(find1, find2, value);
			}
		}
	}
}
void graph::CreateNode()
{
	int num;
	while (1)
	{
		cout << "请输入顶点的个数:";
		cin >>num;
		if (!cin.good())
		{
			cout << "输入错误！请重新输入" << endl;
			cin.clear();//重置cin流
			cin.ignore(100, '\n');//清空输入缓冲区
		}
		else if (num <= 1)
		{
			cout << "请输入大于1的正整数!"<<endl;
			cin.clear();//重置cin流
			cin.ignore(100, '\n');//清空输入缓冲区
		}
		else
			break;
	}
	numVertices += num;
	cout << "请依次输入各顶点的名称:" << endl;
	for (; currentpos < numVertices; currentpos++)
	{
		cin >> NodeTable[currentpos].data;
	}
}
void graph::CreateMintree()
{
	if (NodeTable[0].data == '\0')
	{
		cout << "无法生成图！因为没有顶点！" << endl;
		return;
	}
	else if (!EdgeExist)
	{
		cout << "无法生成图！因为没有边！" << endl;
		return;
	}
	MSTEdgeNode ed;
	MinHeap H(numEdge);
	int count;
	cout << "请输入起始顶点: ";
	char a;
	int u,v,min=INT_MAX;
	while (1)
	{
		cin >> a;
		u = getVertexPos(a);//u记录a的位置
		if(u==-1)
		{
			cout << "无此顶点请重新输入" << endl;
			cin.ignore(1000, '\n');
			continue;
		}
		else
		{
			bool* Vmst = new bool[numVertices];
			for (int i = 0; i < numVertices; i++)
				Vmst[i] = false;
			Vmst[u] = true;
			count = 1;
			do{
				v = getFirstNeighbor(u);
				while (v != -1)
				{
					if (Vmst[v] == false)//未访问过
					{
						ed.tail = u, ed.head = v;
						ed.key = getWeight(u, v);
						H.insert(ed);//插入堆
					}
					v = getNextNeighbor(u, v);//对其他邻接顶点操作
				}
				while (H.isEmpty() == false && count < numVertices)//构建最小生成树
				{
					H.removeMin(ed);//取出
					if (Vmst[ed.head] == false)
					{
						MST.insert(ed);//插入最小生成树
						u = ed.head;
						Vmst[u] = true;
						count++;
						break;//成功插入一个点，要退出，重新寻找图中距离最小生成树最短的顶点
					}

				}
			} while (count < numVertices);
			delete[]Vmst;
			break;
		}
	}
	
	cout << "构造最小生成树成功！" << endl;
}

void graph::menu()
{
	cout << "**             电网造价模拟系统            **" << endl;
	cout << "=============================================" << endl;
	cout << "**             请选择以下的操作            **" << endl;
	cout << "**              A---创建电网顶点           **" << endl;
	cout << "**              B---添加电网的边           **" << endl;
	cout << "**              C---构造最小生成树         **" << endl;
	cout << "**              D---显示最小生成树         **" << endl;
	cout << "**              E---退出程序               **" << endl;
	cout << "=============================================" << endl;
	
	while (1)
	{
		char choice;
		while (1)
		{
			cout << endl << "请选择操作：";
			cin >> choice;
			if (!cin.good() ||!(( choice >= 'A' && choice<='E')||(choice>='a'&&choice<='e')))
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
			CreateNode();
			break;
		case 'B':
		case 'b':
			AddEdge();
			break;
		case 'C':
		case 'c':
			CreateMintree();
			break;
		case'd':
		case'D':
			ShowMintree();
			break;
		case 'e':
		case'E':
			return;
		}

	}

}


MinHeap::MinHeap(int sz)
{
	maxheapsize = sz;
	currentsize = 0;
	heap = new MSTEdgeNode[sz];
	if(heap==NULL)
	{
		cout << "空间分配失败" << endl;
		return;
	} 
}
void MinHeap::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;//j是i左子女
	int tempkey = heap[i].key;
	int temphead = heap[i].head;
	int temptail = heap[i].tail;//记录数据
	while (j <= m)//检查是否到最后位置
	{
		if (j<m && heap[j].key>heap[j + 1].key)j++;//让j指向2个子女中小的那个
		if (tempkey <= heap[j].key)break;//小，不做调整
		else
		{
			heap[i].key = heap[j].key;
			heap[i].head = heap[j].head;
			heap[i].tail = heap[j].tail;
			i = j; j = i * j + 1;
		}
	}
	heap[i].key = tempkey;
	heap[i].head = temphead;
	heap[i].tail = temptail;

}
void MinHeap::siftUp(int start)
{
	int j = start, i = (j - 1) / 2; 
	int tempkey = heap[j].key;
	int temphead = heap[j].head;
	int temptail = heap[j].tail;
	while (j > 0)//沿着父节点路径向上直达根
	{
		if (heap[i].key <= tempkey)break;//父节点值小，不调整
		else//父节点值大，调整
		{
			heap[j].head = heap[i].head;
			heap[j].tail = heap[i].tail;
			heap[j].key = heap[i].key;
			j = i;
			i = (i - 1) / 2;
		}
		
	}
	heap[j].head = temphead;
	heap[j].tail = temptail;
	heap[j].key = tempkey;

}
bool MinHeap::insert(MSTEdgeNode& x)
{
	if (currentsize == maxheapsize)
	{
		cout << "堆满" << endl;
		return false;
	}
	heap[currentsize].head = x.head;
	heap[currentsize].tail = x.tail;
	heap[currentsize].key = x.key;
	siftUp(currentsize);
	currentsize++;
	return true;
}
bool MinHeap::removeMin(MSTEdgeNode& x)
{
	if (currentsize == 0)
	{
		cout << "堆空" << endl;
		return false;
	}
	x.key = heap[0].key;
	x.head = heap[0].head;
	x.tail = heap[0].tail;//最小数据赋值给x
	heap[0] = heap[currentsize - 1];//最大的值给heap[0]
	currentsize--;
	siftDown(0, currentsize - 1);//再次调整
	return true;
}
int main()
{
	graph T1;
	T1.menu();
}