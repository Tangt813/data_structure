#include<iostream>
using namespace std;
int money = 0;
class Huffman
{
public:
	int weight;//Ȩֵ	
	int parent;//˫�׽��
	int lchild;
	int rchild;//���Һ���
	Huffman()//���캯��
	{
		this->weight = 0;
		this->parent = -1;
		this->lchild = -1;
		this->rchild = -1;
	}
};
void find2min(Huffman* huffman, int n,int& min1, int& min2)
{
	for (int i = 0; i < n; i++)//���һ�û˫�׵Ľڵ�
	{
		if (huffman[i].parent == -1)
		{
			min1 = i;
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (huffman[i].parent == -1 && huffman[i].weight < huffman[min1].weight)
		{
			min1 = i;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (huffman[i].parent == -1 && i != min1)
		{
			min2 = i;
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (huffman[i].parent == -1 &&
			huffman[min2].weight > huffman[i].weight &&
			i != min1)
		{
			min2 = i;
		}
	}
}
void createhuffman(Huffman* huffman, int num, int array[])
{
	for (int i = 0; i < num; i++)
	{
		huffman[i].weight = array[i];
	}
	for (int i = num; i < 2 * num - 1; i++)
	{
		int min1 = 0;
		int min2 = 0;
		find2min(huffman, i,min1, min2);
		huffman[i].weight = huffman[min1].weight + huffman[min2].weight;
		huffman[i].lchild = min1;
		huffman[i].rchild = min2;
		huffman[min1].parent = i;
		huffman[min2].parent = i;
	}
}

void caltree(Huffman* huffman)
{
	for (int i = 0; huffman[i].weight > 0; i++)
	{
		if (huffman[i].lchild != -1 && huffman[i].rchild != -1)
		{
			money += huffman[i].weight;
		}
	}
}
int main()
{
	int num;
	
	while (1)
	{
		cout << "������ľͷ�ж��ٶ�:(С�ڵ���10000)" << endl;
		cin >> num;//����
		if (!cin.good())
		{
			cout << "����������������룡" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else if (num <= 0||num>10000)
		{
			cout << "������һ������0С��10000��������" << endl;
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	cout << "������ÿ��ľͷ�ĳ���:" << endl;
	int* array = new int[num];
	for (int i = 0; i < num; i++)//����ÿ�γ���
	{
		//cin >> array[i];
		while (1)
		{
			cin >> array[i];
			if (cin.fail())
			{
				cout << "��������ȷ��ֵ!��Ӵ��󴦿�ʼ��������ľͷ����:" << endl;
				cin.clear();
				cin.ignore(1);

			}
			else if (array[i] <= 0)
			{
				cout << "����������������Ӵ��󴦿�ʼ��������ľͷ����:" << endl;
				cin.ignore(1);

			}
			else
				break;
		}
	}
	Huffman* huffman = new Huffman[2 * num - 1];
	if (num == 1)
	{
		cout << "����Ҫ�����ٽ��:";
		cout <<array[0];
	}
	else
	{
		createhuffman(huffman, num, array);
		caltree(huffman);
		cout << "����Ҫ�����ٽ��:";
		cout << money;
	}
	delete[]array;
	delete[]huffman;
}