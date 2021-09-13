
#include <iostream>
#include<time.h>
#include <stdlib.h>
using namespace std;
int compare_step = 0;
int exchange_step = 0;
void BubbleSort(int* number, int num)
{
	compare_step = 0;
	exchange_step = 0;//置0
	int time1 = clock();
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			compare_step++;
			if (number[i] > number[j])//number[j]小，交换
			{
				exchange_step++;
				int menory = number[j];
				number[j] = number[i];
				number[i] = menory;
			}
		}
	}
	int time2 = clock();
	/*for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;*/
	cout << "冒泡排序所用时间:       " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "冒泡排序比较次数:       " << compare_step << endl;
	cout << "冒泡排序交换次数:       " << exchange_step << endl;
}

void QuickSort(int* number, int left, int right)
{
	if (left > right)
		return;
	int temp = number[left];//存基准值
	int i = left;
	int j = right;
	while (i != j)
	{
		while (number[j] >= temp && i < j)//从右往左找
		{
			j--;
			compare_step++;
		}
		//找到了一个小于temp的number[j]
		while (number[i] <= temp && i < j)
		{
			compare_step++;
			i++;
		}
		//找到了一个大于temp的number[i]
		//交换位置
		if (i < j)
		{
			exchange_step++;
			int t = number[i];
			number[i] = number[j];
			number[j] = t;
		}
	}
	//i==j
	number[left] = number[i];
	number[i] = temp;//基准数放中间
	exchange_step++;
	QuickSort(number, left, i - 1);
	QuickSort(number, i + 1, right);
	return;
}

void ChooseSort(int number[], int num)
{
	compare_step = 0;
	exchange_step = 0;//置0
	int time1 = clock();
	int i = 0;
	int min = INT_MAX, mini = 0;//min取最大值，mini取0；
	for (i = 0; i < num - 1; i++)//0到num-1
	{
		for (int j = i + 1; j < num; j++)//i+1到num
		{
			compare_step++;
			if (number[j] < min)//比min小，min更换，mini记录j
			{
				min = number[j];
				mini = j;
			}
		}
		int t = number[i];
		number[i] = number[mini];
		number[mini] = t;
		//number[t]和最小的number[mini]更换
		exchange_step++;
		min = INT_MAX;
		mini = i + 1;
	}
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "选择排序所用时间:       " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "选择排序比较次数:       " << compare_step << endl;
	cout << "选择排序交换次数:       " << exchange_step << endl;
}

void NumInsert(int* number, int begin, int end)//将begin到end-1的元素后移以为，end的元素插入到begin处
{
	int num = number[end];
	for (; end > begin; end--)
	{
		exchange_step++;
		number[end] = number[end - 1];
	}
	number[begin] = num;
}
void insert(int* number, int num)
{
	compare_step = 0;
	exchange_step = 0;//置0
	int time1 = clock();
	for (int i = 1; i < num; i++)
	{
		for (int t = 0; t < i; t++)
		{
			compare_step++;
			if (number[t] > number[i])
			{
				NumInsert(number, t, i);//插入
				break;
			}
		}
	}
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "直接插入排序所用时间:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "直接插入排序比较次数:       " << compare_step << endl;
	cout << "直接插入排序交换次数:       " << exchange_step << endl;

}

void swap(int* number, int a, int b)
{
	number[a] = number[a] + number[b];
	number[b] = number[a] - number[b];
	number[a] = number[a] - number[b];
}
void Shill(int* number, int num)
{
	exchange_step = 0;
	compare_step = 0;
	int time1 = clock();
	for (int gap = num / 2; gap > 0; gap /= 2)
	{
		//从第gap个元素，逐个对其所在组进行直接插入排序操作
		for (int i = gap; i < num; i++)
		{
			int j = i;

			while (j - gap >= 0 && number[j] < number[j - gap])
			{
				//插入排序采用交换法
				swap(number, j, j - gap);
				exchange_step++;
				j -= gap;
				compare_step++;
			}
			if (j - gap >= 0)
				compare_step++;
		}
	}

	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "希尔排序所用时间:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "希尔排序比较次数:       " << compare_step << endl;
	cout << "希尔排序交换次数:       " << exchange_step << endl;

}
void HeapAdjust(int* number, int i, int length)
{
	int temp = number[i];//取出当前元素
	for (int k = 2 * i + 1; k < length; k = 2 * k + 1)
	{
		compare_step++;
		if (number[k] < number[k + 1] && k + 1 < length)//右节点大
		{
			k++;
		}
		compare_step++;
		if (temp < number[k])//父节点小，子节点赋值给父节点
		{
			exchange_step++;
			number[i] = number[k];
			i = k;
		}
		else
			break;
	}
	number[i] = temp;
}
void HeapSwap(int* number, int i, int j)
{
	exchange_step++;
	int temp = number[j];
	number[j] = number[i];
	number[i] = temp;
}
void HeapSort(int* number, int num)
{
	int time1 = clock();
	for (int i = num / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(number, i, num);
	}//建立堆
	for (int j = num - 1; j >= 0; j--)
	{
		HeapSwap(number, 0, j);
		HeapAdjust(number, 0, j);
	}
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "堆排序所用时间:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "堆排序比较次数:       " << compare_step << endl;
	cout << "堆排序交换次数:       " << exchange_step << endl;
}
void Merge(int* number, int* list, int low, int high)
{
	int s1 = low, s2 = high, t = low, k;
	if (low >= high)
		return;
	int mid = (low + high) / 2;
	Merge(number, list, low, mid);
	Merge(number, list, mid + 1, high);
	for (k = low; k <= mid; k++) {
		list[k] = number[k];
	}
	for (k = mid + 1; k <= high; k++) {
		list[high + mid - k + 1] = number[k];//list里是从low到mid的正序，mid+1到high的逆序
	}
	while (t <= high) {
		exchange_step++;
		compare_step++;
		if (list[s1] < list[s2])
			number[t++] = list[s1++];
		else
			number[t++] = list[s2--];
		//将list里的数据存进number里
	}
	return;
}
void Mergesort(int* number, int num)
{
	int* list = new int[100000];
	int time1 = clock();
	Merge(number, list, 0, num - 1);
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "归并排序所用时间:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "归并排序比较次数:      " << compare_step << endl;
	cout << "归并排序交换次数:      " << exchange_step << endl;
	delete[]list;
}
int maxbit(int* number, int num) //求数据的最大位数
{
	int maxData = number[0];              ///最大数
	/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < num; ++i)
	{
		if (maxData < number[i])
			maxData = number[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}
	return d;

}
void radixsort(int number[], int num) //基数排序
{
	int time1 = clock();
	int d = maxbit(number, num);//求最高位数
	int* tmp = new int[num];
	int* count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < num; j++)
		{
			k = (number[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = num - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (number[j] / radix) % 10;
			tmp[count[k] - 1] = number[j];
			count[k]--;
		}
		for (j = 0; j < num; j++) //将临时数组的内容复制到number中
			number[j] = tmp[j];
		radix = radix * 10;
	}
	int time2 = clock();
	/*for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;*/
	cout << "基数排序所用时间:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	delete[]tmp;
	delete[]count;
}
void copy(int* true_number, int* number, int num)
{
	for (int i = 0; i < num; i++)
	{
		number[i] = true_number[i];
	}
}
int main()
{
	srand((unsigned)time(NULL));
	cout << "**                排序算法比较             **" << endl;
	cout << "=============================================" << endl;
	cout << "**                 1.冒泡排序              **" << endl;
	cout << "**                 2.选择排序              **" << endl;
	cout << "**                 3.直接插入排序          **" << endl;
	cout << "**                 4.希尔排序              **" << endl;
	cout << "**                 5.快速排序              **" << endl;
	cout << "**                 6.堆排序                **" << endl;
	cout << "**                 7.归并排序              **" << endl;
	cout << "**                 8.基数排序              **" << endl;
	cout << "**                 9.退出程序              **" << endl;
	cout << "=============================================" << endl;
	int num;
	cout << "请输入要产生的随机数:" << endl;
	while (1)
	{
		cin >> num;
		if (cin.fail() || num <= 0)
		{
			cout << "输入错误，请重新输入:" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
	int* true_number = new int[num];
	int* number = new int[num];
	for (int i = 0; i < num; i++)
	{
		true_number[i] = rand();
	}
	while (1)
	{
		int choice;
		int time1, time2;
		cout << endl << "请选择排序的算法：     ";
		while (1)
		{
			cin >> choice;
			if (cin.fail() || (choice <= 0 || choice > 9))
			{
				cout << "输入错误，请重新输入:" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else
				break;
		}
		switch (choice)
		{
		case 1:
			copy(true_number, number, num);
			BubbleSort(number, num);
			break;
		case 2:
			copy(true_number, number, num);
			ChooseSort(number, num);
			break;
		case 3:
			copy(true_number, number, num);
			insert(number, num);

			break;
		case 4:
			copy(true_number, number, num);
			Shill(number, num);
			break;
		case 5:
			compare_step = 0;
			exchange_step = 0;
			copy(true_number, number, num);
			time1 = clock();
			QuickSort(number, 0, num - 1);
			time2 = clock();
			/*for (int i = 0; i < num; i++)
				cout << number[i] << " ";
			cout << endl;*/
			cout << "快速排序所用时间:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
			cout << "快速排序比较次数:      " << compare_step << endl;
			cout << "快速排序交换次数:      " << exchange_step << endl;
			break;
		case 6:
			compare_step = 0;
			exchange_step = 0;
			copy(true_number, number, num);
			HeapSort(number, num);
			break;
		case 7:
			compare_step = 0;
			exchange_step = 0;
			copy(true_number, number, num);
			Mergesort(number, num);
			break;
		case 8:
			copy(true_number, number, num);
			radixsort(number, num);
			break;
		case 9:
			return 0;
		default:
			cout << "错误输入！" << endl;
			break;
		}
	}
}