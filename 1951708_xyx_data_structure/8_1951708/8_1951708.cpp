#include<iostream>
using namespace std;
struct Edge
{
	int dest;//�ߵ���һ�������λ��
	int cost;//�ߵ�Ȩֵ
	Edge* link;//��һ��������ָ��
	Edge() { dest = -1; cost = -1; link = NULL; }
	Edge(int num,int weight):dest(num),cost(weight),link(NULL){}
	bool operator!=(Edge& R)const {
		return (dest != R.dest) ? true : false;
	}
};


struct Vertex
{
	char data='\0';
	Edge* adj=NULL;//�������ͷָ��
};

struct MSTEdgeNode
{
	int tail, head, key;//ͷ����λ�ã�β�ڵ��λ�ã��ߵ�Ȩֵ
	MSTEdgeNode():tail(-1),head(-1),key(0){}
	bool operator<=(MSTEdgeNode& R) { return key <= R.key; }
	bool operator>(MSTEdgeNode& R) { return key > R.key; }
};

class MinHeap//��С��
{
public:
	MinHeap(int sz = 30);
	~MinHeap()
	{
		delete[]heap;
	}
	bool insert(MSTEdgeNode& x);//����һ���ڵ�
	bool removeMin(MSTEdgeNode& x);//�Ƴ�һ����С�Ľڵ�
	bool isEmpty()
	{
		return(currentsize == 0) ? true : false;
	}
	bool isFull()
	{
		return (currentsize == maxheapsize) ? true : false;
	}
private:
	MSTEdgeNode* heap;//��С����������Ǳ߽ڵ���
	int currentsize;
	int maxheapsize;
	void siftDown(int start, int m);//���ϵ����޸�˳��
	void siftUp(int start);//���µ����޸�˳��
};


class MinSpanTree {//��С������
protected:
	
	int maxSize, currentpos;
public:
	MSTEdgeNode* edgevalue;//�洢���������Ľڵ���
	MinSpanTree(int sz=30):maxSize(sz),currentpos(0){
		edgevalue = new MSTEdgeNode[sz];
	}
	~MinSpanTree()
	{
		delete[]edgevalue;
	}
	void insert(MSTEdgeNode& item);//�����µ�����
	
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
	int maxVertices;//��󶥵���
	int numEdge;//��ǰ����
	int numVertices;//��ǰ����
	const int maxWeight = 9999;
	MinSpanTree MST;//��С������

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
	bool graphIsFull()//�ж�ͼ��
	{
		if (numVertices == maxVertices || numEdge == maxVertices * (maxVertices - 1) / 2)return true;
		else return false;
	}
	int getFirstNeighbor(int v);//��ȡ��һ���ڽӵ�
	int getNextNeighbor(int v, int now);//��ȡv���ڽӵ���now����һ��
	int getWeight(int u, int v);//��ȡu��v�ڵ�֮��ıߵ�Ȩֵ

private:
	Vertex* NodeTable;//�ڽӱ�
	bool EdgeExist = 0;//�ߴ���
	int currentpos = 0;//��ǰλ��
	int getVertexPos(char A);//��������vertex��ͼ�е�λ��
	void CreateNode();//��������
	void AddEdge();//������
	void insertEdge(int v1, int v2, int weight);//�����
	void CreateMintree();//������С������
	void ShowMintree();//չʾ��С������
};
void graph::ShowMintree()
{
	if (MST.edgevalue[0].head == -1)
	{
		cout << "��δ����С��������" << endl;
		return;
	}
	cout << "��С�������Ķ��㼰��Ϊ:" << endl << endl;
	for (int i = 0; i < numVertices-1; i++)
	{
		cout << NodeTable[MST.edgevalue[i].tail].data << "-<" << MST.edgevalue[i].key << ">->" << NodeTable[MST.edgevalue[i].head].data << "       ";
	}
}
int graph::getWeight(int u, int v)
{
	Edge* t = NodeTable[u].adj;
	while (t != NULL && t->dest != v)//�ҵ�t��v֮��ı�
	{
		t = t->link;
	}
	if (t == NULL)//���޴˱�
		return -1;
	else
		return t->cost;
}
int graph::getNextNeighbor(int v, int now)
{
	Edge* t = NodeTable[v].adj;
	while (t != NULL && t->dest != now)//�ҵ�now�ڵ�
		t = t->link;
	if (t == NULL)//û��now�ڵ�
		return -1;
	else if (t->link == NULL)//now�ڵ�֮���Ѿ�û�������ڵ���
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
	for (int i = 0; i < numVertices; i++)//�ҵ�A�ڵ��������е�λ��
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
		cout << "�洢�������" << endl;
		return;
	}
	for (int i = 0; i < maxVertices; i++)//��ʼ��
	{
		NodeTable[i].adj = NULL;
	}
}
void graph::insertEdge(int v1, int v2, int weight)
{//��Ϊ�Ѿ�ȷ����v1,v2�ǺϷ��ģ����Բ���if�ж��Ƿ�Ϸ�
	Edge* q, * p = NodeTable[v1].adj;//v1��Ӧ�ı�����ͷ�ڵ�
	while (p != NULL && p->dest != v2)//Ѱ��v2
	{
		p = p->link;
	}
	if (p != NULL)
	{
		cout << "2�ڵ��Ѿ��б�,�޷��ٽ����ߣ�"<<endl;
		return;//v2�Ѿ���v1�ı���
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
		cout << "ͼ�����޶��㣡" << endl;
		return;
	}
	while (1)
	{
		if (numEdge == Maxnum)//�����������
			return;
		cout << "�������������㼰��:�����롰?���˳������ߵ�������������Զ��˳���";
		char want1, want2;
		cin >> want1>>want2;
		if (want1 == '?')//�����ʺ�
		{
			cin.ignore(1000, '\n');
			return;
		}
			
		int find1 = -1, find2 = -1;//�ж��Ƿ��ҵ�
		for (int i = 0; i < numVertices; i++)
		{
			if (NodeTable[i].data == want1)
				find1 = i;
			else if (NodeTable[i].data == want2)
				find2 = i;
		}
		if (find1 == -1 || find2 ==-1)//ֻҪ��һ��û�ҵ��ͱ���
		{
			cout << "����Ķ��㣡����������" << endl;
			cin.ignore(1000, '\n');
			continue;
		}
		else
		{
			int value;
			cin >> value;//����Ȩֵ
			if (cin.fail() || value < 0)
			{
				cout << "�����������������!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			else if (value == 0)
			{
				cout << "������������������������!" << endl;
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
		cout << "�����붥��ĸ���:";
		cin >>num;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();//����cin��
			cin.ignore(100, '\n');//������뻺����
		}
		else if (num <= 1)
		{
			cout << "���������1��������!"<<endl;
			cin.clear();//����cin��
			cin.ignore(100, '\n');//������뻺����
		}
		else
			break;
	}
	numVertices += num;
	cout << "��������������������:" << endl;
	for (; currentpos < numVertices; currentpos++)
	{
		cin >> NodeTable[currentpos].data;
	}
}
void graph::CreateMintree()
{
	if (NodeTable[0].data == '\0')
	{
		cout << "�޷�����ͼ����Ϊû�ж��㣡" << endl;
		return;
	}
	else if (!EdgeExist)
	{
		cout << "�޷�����ͼ����Ϊû�бߣ�" << endl;
		return;
	}
	MSTEdgeNode ed;
	MinHeap H(numEdge);
	int count;
	cout << "��������ʼ����: ";
	char a;
	int u,v,min=INT_MAX;
	while (1)
	{
		cin >> a;
		u = getVertexPos(a);//u��¼a��λ��
		if(u==-1)
		{
			cout << "�޴˶�������������" << endl;
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
					if (Vmst[v] == false)//δ���ʹ�
					{
						ed.tail = u, ed.head = v;
						ed.key = getWeight(u, v);
						H.insert(ed);//�����
					}
					v = getNextNeighbor(u, v);//�������ڽӶ������
				}
				while (H.isEmpty() == false && count < numVertices)//������С������
				{
					H.removeMin(ed);//ȡ��
					if (Vmst[ed.head] == false)
					{
						MST.insert(ed);//������С������
						u = ed.head;
						Vmst[u] = true;
						count++;
						break;//�ɹ�����һ���㣬Ҫ�˳�������Ѱ��ͼ�о�����С��������̵Ķ���
					}

				}
			} while (count < numVertices);
			delete[]Vmst;
			break;
		}
	}
	
	cout << "������С�������ɹ���" << endl;
}

void graph::menu()
{
	cout << "**             �������ģ��ϵͳ            **" << endl;
	cout << "=============================================" << endl;
	cout << "**             ��ѡ�����µĲ���            **" << endl;
	cout << "**              A---������������           **" << endl;
	cout << "**              B---��ӵ����ı�           **" << endl;
	cout << "**              C---������С������         **" << endl;
	cout << "**              D---��ʾ��С������         **" << endl;
	cout << "**              E---�˳�����               **" << endl;
	cout << "=============================================" << endl;
	
	while (1)
	{
		char choice;
		while (1)
		{
			cout << endl << "��ѡ�������";
			cin >> choice;
			if (!cin.good() ||!(( choice >= 'A' && choice<='E')||(choice>='a'&&choice<='e')))
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
		cout << "�ռ����ʧ��" << endl;
		return;
	} 
}
void MinHeap::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;//j��i����Ů
	int tempkey = heap[i].key;
	int temphead = heap[i].head;
	int temptail = heap[i].tail;//��¼����
	while (j <= m)//����Ƿ����λ��
	{
		if (j<m && heap[j].key>heap[j + 1].key)j++;//��jָ��2����Ů��С���Ǹ�
		if (tempkey <= heap[j].key)break;//С����������
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
	while (j > 0)//���Ÿ��ڵ�·������ֱ���
	{
		if (heap[i].key <= tempkey)break;//���ڵ�ֵС��������
		else//���ڵ�ֵ�󣬵���
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
		cout << "����" << endl;
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
		cout << "�ѿ�" << endl;
		return false;
	}
	x.key = heap[0].key;
	x.head = heap[0].head;
	x.tail = heap[0].tail;//��С���ݸ�ֵ��x
	heap[0] = heap[currentsize - 1];//����ֵ��heap[0]
	currentsize--;
	siftDown(0, currentsize - 1);//�ٴε���
	return true;
}
int main()
{
	graph T1;
	T1.menu();
}