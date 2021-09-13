#include <iostream>
#include<fstream>
#include <string>
#include<iomanip>
using namespace std;
int ClassNum[8] ;

class Course
{
public:
	Course(string ClassCode="0", string ClassName="0",int Times=0,int terms=0)
	{
		this->ClassCode = ClassCode;
		this->ClassName = ClassName;
		this->Times = Times;
		this->terms = terms;
		pCourseNum = 0;
		for (int i = 0; i < 40; i++)
		{
			pCourses[i] = "\0";
		}
	}
public:
	string ClassCode;//�γ̱��
	string ClassName;//�γ�����
	int Times;//ÿ���ڿ�ʱ
	int terms;//����ѧ��
	int pCourseNum ;//���޿γ���Ŀ
	string pCourses[40];//��̿γ�����


};
class System
{
public:
	string CourseTable[8][5][10];//����ѧ�ڿγ̱�
	int TERMS = 0;//��ӡ�γ̱��õĵ�ǰѧ��
	Course Courses[38];//�洢�����пγ���Ϣ
	Course *thisTermCourses=NULL;//��ǰѧϰ��ѡ�����Ŀγ�
	string workdays[5][10];//��ѧ�ڿγ̱�
	System()//���캯������ʼ���γ̱�Ϊ����ϰ��
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				workdays[i][j] = "��ϰ";
			}
		}
	}
	void getEnglish(int thisTerm);//��ȡӢ���
	void getChinese();//��ȡ���Ŀ�
	void getCourses(int number,int thisTerm);//��ȡthisTerm�γ�
	bool get1Course();//��ȡ1���γ�
	void AdjustCourses(int i);//�������пγ̵����޿γ̵�����
	int CodetoNo(string str);//���γ̱���ת��Ϊ����
	void ArrangeCourses(int number);//����γ�
	int Arrange3(string name);//������ѧʱΪ3�Ŀ�
	void Arrange4(Course item);//������ѧʱΪ4�Ŀ�
	void Arrange5(Course item);//������ѧʱΪ5�Ŀ�
	void Arrange6(Course item);//������ѧʱΪ6�Ŀ�
	int FindFree2time(int i);//Ѱ�ҿ��е�2������������X
	int FindFree3time(int i);//Ѱ�ҿ��е�3������������X
	void saveToFile(ofstream& out);//���������ĵ�
};
void System::saveToFile(ofstream& out)
{
	int terms = 0;
	while (terms<8)
	{
		
		out <<endl<< "[" << "��" << terms + 1 << "ѧ��]" << endl;
		for (int t = 0; t < 60; t++)
			out << "=";
		out << endl<<"                    ����һ                    ���ڶ�                    ������                    ������                    ������" << endl;
		for (int i = 0; i < 10; i++)
		{
			out << "��" << i + 1 << "��";
			if (i < 9)
				out << "           ";
			else
				out << "         ";
			for (int j = 0; j < 5; j++)
			{
				out << setiosflags(ios::left) << setw(27) << CourseTable[terms][j][i];
			}
			out << endl;
		}
		terms++;
	}
	
}
int System::FindFree2time(int i)//��i��������2���յ�ʱ��
{
	int j = i;
	i = i + 1 < 5 ? i + 1 : i - 4;
	while (j != i)
	{
		if (workdays[i][0] == "��ϰ" || workdays[i][5] == "��ϰ")//�ҵ����˳�
			return i;
		i = i + 1 < 5 ? i + 1 : i - 4;
	}
	i = i + 1 < 5 ? i + 1 : i - 4;
	if (workdays[i][0] == "��ϰ" || workdays[i][5] == "��ϰ")
		return i;
	return i-1;
}
int System::FindFree3time(int i)//��i��������3�����е�ʱ��
{
	int j = i;
	i = i + 1 < 5 ? i + 1 : i - 4;
	while (j != i)
	{
		if (workdays[i][2] == "��ϰ" || workdays[i][7] == "��ϰ")
			return i;
		i = i + 1 < 5 ? i + 1 : i - 4;
	}
	i = i + 1 < 5 ? i + 1 : i - 4;
	if (workdays[i][2] == "��ϰ" || workdays[i][7] == "��ϰ")
		return i;
	return i-1;

}
void System::Arrange6(Course item)//������ѧʱΪ6�Ŀγ�
{
	bool isdone = 0;
	int i = Arrange3(item.ClassName);//�ȷ�ƥ��3��
	i = (i + 2 - 5)>0 ? (i + 2 - 5) : i + 2;
	if (workdays[i][2] == "��ϰ")
	{
		workdays[i][2] = item.ClassName;
		workdays[i][3] = item.ClassName;
		workdays[i][4] = item.ClassName;
	}
	else if (workdays[i][7] == "��ϰ")
	{
		workdays[i][7] = item.ClassName;
		workdays[i][8] = item.ClassName;
		workdays[i][9] = item.ClassName;
	}
	else
	{
		int date3 = FindFree3time(i);
		if (date3 != i)//�ҵ���
		{
			if (workdays[i][2] == "��ϰ")
			{
				workdays[i][2] = item.ClassName;
				workdays[i][3] = item.ClassName;
				workdays[i][4] = item.ClassName;
				isdone = 1;
			}
			else
			{
				workdays[i][7] = item.ClassName;
				workdays[i][8] = item.ClassName;
				workdays[i][9] = item.ClassName;
				isdone = 1;
			}
		}
		else
		{
			cout << "�ſ�ʧ�ܣ�" << endl;
			return;
		}
	}
}
void System::Arrange5(Course item)//������ѧʱΪ5�Ŀγ�
{
	bool isdone = 0;
	int i = Arrange3(item.ClassName);//�ȷ���3��
	i = (i + 2 - 5)>0 ? (i + 2 - 5) : i + 2;
	if (workdays[i][0] == "��ϰ")
	{
		workdays[i][0] = item.ClassName;
		workdays[i][1] = item.ClassName;
		isdone = 1;
	}
	else if (workdays[i][5] == "��ϰ")
	{
		workdays[i][5] = item.ClassName;
		workdays[i][6] = item.ClassName;
		isdone = 1;
	}
	else
	{
		int date2 = FindFree2time(i);
		if (date2 == i)//û�п��е�2���ռ䣬�Ǿ��ҿ��е�3���ռ䵫ֻ����2�ڿ�
		{
			int date3 = FindFree3time(i);
			if (date3 != i)//�ҵ���
			{
				if (workdays[i][2] == "��ϰ")
				{
					workdays[i][2] = item.ClassName;
					workdays[i][3] = item.ClassName;
					isdone = 1;
				}
				else
				{
					workdays[i][7] = item.ClassName;
					workdays[i][8] = item.ClassName;
					isdone = 1;
				}
			}
			else
			{
				cout << "�ſ�ʧ�ܣ�" << endl;
				return;
			}
		}
		else
		{
			if (workdays[i][0] == "��ϰ")
			{
				workdays[i][0] = item.ClassName;
				workdays[i][1] = item.ClassName;
				isdone = 1;
			}
			else
			{
				workdays[i][5] = item.ClassName;
				workdays[i][6] = item.ClassName;
				isdone = 1;
			}
		}
	}
}
void System::Arrange4(Course item)//����2��2�ڿ�
{
	bool isdone = 0;
	for (int i = 0; i < 5; i++)
	{
		if (isdone == 1)
			return;
		if (workdays[i][0] == "��ϰ")
		{
			workdays[i][0] = item.ClassName;
			workdays[i][1] = item.ClassName;
			i = (i + 2 - 5)>0 ? (i + 2 - 5) : i + 2;
			if (workdays[i][0] == "��ϰ")
			{
				workdays[i][0] = item.ClassName;
				workdays[i][1] = item.ClassName;
				isdone = 1;
			}
			else if (workdays[i][5] == "��ϰ")
			{
				workdays[i][5] = item.ClassName;
				workdays[i][6] = item.ClassName;
				isdone = 1;
			}
			else
			{
				int date2 = FindFree2time(i);
				if (date2 == i)
				{
					int date3 = FindFree3time(i);
					if (date3 != i)//�ҵ���
					{
						if (workdays[i][2] == "��ϰ")
						{
							workdays[i][2] = item.ClassName;
							workdays[i][3] = item.ClassName;
							isdone = 1;
						}
						else
						{
							workdays[i][7] = item.ClassName;
							workdays[i][8] = item.ClassName;
							isdone = 1;
						}
					}
					else
					{
						cout << "�ſ�ʧ�ܣ�" << endl;
						return;
					}
				}

				else
				{
					if (workdays[i][0] == "��ϰ")
					{
						workdays[i][0] = item.ClassName;
						workdays[i][1] = item.ClassName;
						isdone = 1;
					}
					else
					{
						workdays[i][5] = item.ClassName;
						workdays[i][6] = item.ClassName;
						isdone = 1;
					}
				}
			}
		}
	}
}
int System::Arrange3(string name)
{

	for (int i = 0; i < 5; i++)
	{

		if (workdays[i][2] == "��ϰ")
		{
			workdays[i][2] = name;
			workdays[i][3] = name;
			workdays[i][4] = name;
			return i;
		}
		else if (workdays[i][7] == "��ϰ")
		{
			workdays[i][7] = name;
			workdays[i][8] = name;
			workdays[i][9] = name;
			return i;
		}
	}

	return -1;
}
void System::ArrangeCourses(int number)
{
	for (int i = 0; i < number; i++)
	{
		int times = thisTermCourses[i].Times;//��ȡ��ѧʱ
		string name = thisTermCourses[i].ClassName;
		switch (times)//������ѧʱ���в�ͬ�ķ���ģʽ
		{
		case 3:
			Arrange3(name);
			break;
		case 4:
			Arrange4(thisTermCourses[i]);
			break;
		case 5:
			Arrange5(thisTermCourses[i]);
			break;
		case 6:
			Arrange6(thisTermCourses[i]);
			break;
		}
	}
	for (int t = 0; t < 10; t++)//д���ܿγ̱�
	{
		for (int u = 0; u < 5; u++)
		{
			CourseTable[TERMS][u][t] = workdays[u][t];
			cout << workdays[u][t] << " ";
		}
		cout << endl;
	}
	TERMS++;//ѧ�ڼ�1
	for (int t = 0; t < 10; t++)//����ÿѧ�ڵĿα�
	{
		for (int u = 0; u < 5; u++)
		{
			workdays[u][t]="��ϰ";
		}
		
	}
	cout << endl;
}
int System::CodetoNo(string str)
{
	for (int i = 0; i < 38; i++)
	{
		if (Courses[i].ClassCode == str)
			return i;
	}
	return -1;
}
void System::AdjustCourses(int i)
{
	string Code = Courses[i].ClassCode;
	for (int t = 0; t < 29; t++)
	{
		if (Courses[t].pCourseNum <= 0)
			continue;
		else
		{
			for (int j = 0;  Courses[t].pCourses[j]!="\0"; j++)//ѭ��pCourses;
			{
				if (Courses[t].pCourses[j] == Code)//Courses[t]�����޿γ�����Courses[i]
				{
					
					Courses[t].pCourseNum--;
					break;
				}
			}
		}
	}
}
void System::getEnglish(int thisTerm)
{
	thisTermCourses[0] = Courses[29 + thisTerm];
	Courses[29 + thisTerm].pCourseNum--;
}
void System::getChinese()
{
	thisTermCourses[1] = Courses[37];
	(Courses[37].pCourseNum)--;
}
bool System::get1Course()
{
	for (int i = 0; i < 29; i++)
	{
		if (Courses[i].pCourseNum >= 0)//���޿γ���С��0˵���Ѿ�ѡ��������ѡ
		{
			if (Courses[i].pCourseNum == 0)//���޿γ�������0������ѡ��
			{
				int t = 0;
				while (thisTermCourses[t].ClassCode != "0")
				{
					t++;
				}//ָ��thisTermCourses��δ����Ŀռ�
				thisTermCourses[t] = Courses[i];//���룬ȡ1���γ̲�������
				Courses[i].pCourseNum--;
				return 1;
			}
		}
	}
	return 0;
}
void System::getCourses(int number,int thisTerm)
{
	thisTermCourses = new Course[number];//��¼��ǰѧ�ڵĿγ���

	getEnglish(thisTerm);//��ȡӢ��
	if (thisTerm == 0)//��һѧ�ڵĻ�ѧ����
		getChinese();
	for (int t = (thisTerm == 0 ? (number - 2) : (number - 1)); t > 0; t--)
	{
		get1Course();
	}
	for (int t = 0; t < number; t++)
	{
		AdjustCourses( CodetoNo(thisTermCourses[t].ClassCode));
	}
}
bool chargeCourseNum(int* ClassNum)
{
	int num = 0;
	for (int i = 0; i < 8; i++)
	{
		num += ClassNum[i];
	}
	if (num != 38)
	{
		cout << "�γ�������" << endl;
		return 0;
	}
	else
		return 1;
}
int main()
{
	ifstream infile("courses.txt", ios::in);
	if (!infile) {
		cout << "No File" << endl;
	}
	for (int i = 0; i <8; i++)
		infile >> ClassNum[i];//����ÿѧ�ڿ�����
	if (!chargeCourseNum(ClassNum))//�жϿ������Ƿ���ȷ
		return -1;

	System CourseSystem;
	for (int i = 0; i < 38; i++)//д������
	{
		infile >> CourseSystem.Courses[i].ClassCode;
		infile >> CourseSystem.Courses[i].ClassName;
		infile >> CourseSystem.Courses[i].Times;
		infile >> CourseSystem.Courses[i].terms;
		int t = 0;
		while(infile.peek() != '\n')
		{
			string pCourse;
			infile >> pCourse;
			CourseSystem.Courses[i].pCourses[t]=pCourse;
			t++;
			CourseSystem.Courses[i].pCourseNum++;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		CourseSystem.getCourses(ClassNum[i],i);//ȡ�γ�
		CourseSystem.ArrangeCourses(ClassNum[i]);
		delete[] CourseSystem.thisTermCourses;
	}
	ofstream outfile("CourseTableNew.txt", ios::trunc);
	CourseSystem.saveToFile(outfile);
	return 0;
}