
#include <iostream>
#include<time.h>
#include <stdlib.h>
using namespace std;
int compare_step = 0;
int exchange_step = 0;
void BubbleSort(int* number, int num)
{
	compare_step = 0;
	exchange_step = 0;//��0
	int time1 = clock();
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			compare_step++;
			if (number[i] > number[j])//number[j]С������
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
	cout << "ð����������ʱ��:       " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "ð������Ƚϴ���:       " << compare_step << endl;
	cout << "ð�����򽻻�����:       " << exchange_step << endl;
}

void QuickSort(int* number, int left, int right)
{
	if (left > right)
		return;
	int temp = number[left];//���׼ֵ
	int i = left;
	int j = right;
	while (i != j)
	{
		while (number[j] >= temp && i < j)//����������
		{
			j--;
			compare_step++;
		}
		//�ҵ���һ��С��temp��number[j]
		while (number[i] <= temp && i < j)
		{
			compare_step++;
			i++;
		}
		//�ҵ���һ������temp��number[i]
		//����λ��
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
	number[i] = temp;//��׼�����м�
	exchange_step++;
	QuickSort(number, left, i - 1);
	QuickSort(number, i + 1, right);
	return;
}

void ChooseSort(int number[], int num)
{
	compare_step = 0;
	exchange_step = 0;//��0
	int time1 = clock();
	int i = 0;
	int min = INT_MAX, mini = 0;//minȡ���ֵ��miniȡ0��
	for (i = 0; i < num - 1; i++)//0��num-1
	{
		for (int j = i + 1; j < num; j++)//i+1��num
		{
			compare_step++;
			if (number[j] < min)//��minС��min������mini��¼j
			{
				min = number[j];
				mini = j;
			}
		}
		int t = number[i];
		number[i] = number[mini];
		number[mini] = t;
		//number[t]����С��number[mini]����
		exchange_step++;
		min = INT_MAX;
		mini = i + 1;
	}
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "ѡ����������ʱ��:       " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "ѡ������Ƚϴ���:       " << compare_step << endl;
	cout << "ѡ�����򽻻�����:       " << exchange_step << endl;
}

void NumInsert(int* number, int begin, int end)//��begin��end-1��Ԫ�غ�����Ϊ��end��Ԫ�ز��뵽begin��
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
	exchange_step = 0;//��0
	int time1 = clock();
	for (int i = 1; i < num; i++)
	{
		for (int t = 0; t < i; t++)
		{
			compare_step++;
			if (number[t] > number[i])
			{
				NumInsert(number, t, i);//����
				break;
			}
		}
	}
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "ֱ�Ӳ�����������ʱ��:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "ֱ�Ӳ�������Ƚϴ���:       " << compare_step << endl;
	cout << "ֱ�Ӳ������򽻻�����:       " << exchange_step << endl;

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
		//�ӵ�gap��Ԫ�أ�����������������ֱ�Ӳ����������
		for (int i = gap; i < num; i++)
		{
			int j = i;

			while (j - gap >= 0 && number[j] < number[j - gap])
			{
				//����������ý�����
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
	cout << "ϣ����������ʱ��:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "ϣ������Ƚϴ���:       " << compare_step << endl;
	cout << "ϣ�����򽻻�����:       " << exchange_step << endl;

}
void HeapAdjust(int* number, int i, int length)
{
	int temp = number[i];//ȡ����ǰԪ��
	for (int k = 2 * i + 1; k < length; k = 2 * k + 1)
	{
		compare_step++;
		if (number[k] < number[k + 1] && k + 1 < length)//�ҽڵ��
		{
			k++;
		}
		compare_step++;
		if (temp < number[k])//���ڵ�С���ӽڵ㸳ֵ�����ڵ�
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
	}//������
	for (int j = num - 1; j >= 0; j--)
	{
		HeapSwap(number, 0, j);
		HeapAdjust(number, 0, j);
	}
	int time2 = clock();
	for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;
	cout << "����������ʱ��:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "������Ƚϴ���:       " << compare_step << endl;
	cout << "�����򽻻�����:       " << exchange_step << endl;
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
		list[high + mid - k + 1] = number[k];//list���Ǵ�low��mid������mid+1��high������
	}
	while (t <= high) {
		exchange_step++;
		compare_step++;
		if (list[s1] < list[s2])
			number[t++] = list[s1++];
		else
			number[t++] = list[s2--];
		//��list������ݴ��number��
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
	cout << "�鲢��������ʱ��:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
	cout << "�鲢����Ƚϴ���:      " << compare_step << endl;
	cout << "�鲢���򽻻�����:      " << exchange_step << endl;
	delete[]list;
}
int maxbit(int* number, int num) //�����ݵ����λ��
{
	int maxData = number[0];              ///�����
	/// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
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
void radixsort(int number[], int num) //��������
{
	int time1 = clock();
	int d = maxbit(number, num);//�����λ��
	int* tmp = new int[num];
	int* count = new int[10]; //������
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //ÿ�η���ǰ��ռ�����
		for (j = 0; j < num; j++)
		{
			k = (number[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
		for (j = num - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (number[j] / radix) % 10;
			tmp[count[k] - 1] = number[j];
			count[k]--;
		}
		for (j = 0; j < num; j++) //����ʱ��������ݸ��Ƶ�number��
			number[j] = tmp[j];
		radix = radix * 10;
	}
	int time2 = clock();
	/*for (int i = 0; i < num; i++)
		cout << number[i] << " ";
	cout << endl;*/
	cout << "������������ʱ��:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
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
	cout << "**                �����㷨�Ƚ�             **" << endl;
	cout << "=============================================" << endl;
	cout << "**                 1.ð������              **" << endl;
	cout << "**                 2.ѡ������              **" << endl;
	cout << "**                 3.ֱ�Ӳ�������          **" << endl;
	cout << "**                 4.ϣ������              **" << endl;
	cout << "**                 5.��������              **" << endl;
	cout << "**                 6.������                **" << endl;
	cout << "**                 7.�鲢����              **" << endl;
	cout << "**                 8.��������              **" << endl;
	cout << "**                 9.�˳�����              **" << endl;
	cout << "=============================================" << endl;
	int num;
	cout << "������Ҫ�����������:" << endl;
	while (1)
	{
		cin >> num;
		if (cin.fail() || num <= 0)
		{
			cout << "�����������������:" << endl;
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
		cout << endl << "��ѡ��������㷨��     ";
		while (1)
		{
			cin >> choice;
			if (cin.fail() || (choice <= 0 || choice > 9))
			{
				cout << "�����������������:" << endl;
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
			cout << "������������ʱ��:      " << (time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
			cout << "��������Ƚϴ���:      " << compare_step << endl;
			cout << "�������򽻻�����:      " << exchange_step << endl;
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
			cout << "�������룡" << endl;
			break;
		}
	}
}