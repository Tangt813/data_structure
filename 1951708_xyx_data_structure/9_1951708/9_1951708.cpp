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
	string ClassCode;//课程编号
	string ClassName;//课程名字
	int Times;//每星期课时
	int terms;//开课学期
	int pCourseNum ;//先修课程数目
	string pCourses[40];//后继课程数组


};
class System
{
public:
	string CourseTable[8][5][10];//所有学期课程表
	int TERMS = 0;//打印课程表用的当前学期
	Course Courses[38];//存储着所有课程信息
	Course *thisTermCourses=NULL;//当前学习挑选出来的课程
	string workdays[5][10];//单学期课程表
	System()//构造函数，初始化课程表为“自习”
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				workdays[i][j] = "自习";
			}
		}
	}
	void getEnglish(int thisTerm);//获取英语课
	void getChinese();//获取语文课
	void getCourses(int number,int thisTerm);//获取thisTerm课程
	bool get1Course();//获取1个课程
	void AdjustCourses(int i);//调整所有课程的先修课程的数量
	int CodetoNo(string str);//将课程编码转化为数字
	void ArrangeCourses(int number);//分配课程
	int Arrange3(string name);//安排周学时为3的课
	void Arrange4(Course item);//安排周学时为4的课
	void Arrange5(Course item);//安排周学时为5的课
	void Arrange6(Course item);//安排周学时为6的课
	int FindFree2time(int i);//寻找空闲的2连，返回星期X
	int FindFree3time(int i);//寻找空闲的3连，返回星期X
	void saveToFile(ofstream& out);//输出到输出文档
};
void System::saveToFile(ofstream& out)
{
	int terms = 0;
	while (terms<8)
	{
		
		out <<endl<< "[" << "第" << terms + 1 << "学期]" << endl;
		for (int t = 0; t < 60; t++)
			out << "=";
		out << endl<<"                    星期一                    星期二                    星期三                    星期四                    星期五" << endl;
		for (int i = 0; i < 10; i++)
		{
			out << "第" << i + 1 << "节";
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
int System::FindFree2time(int i)//从i日往后找2个空的时间
{
	int j = i;
	i = i + 1 < 5 ? i + 1 : i - 4;
	while (j != i)
	{
		if (workdays[i][0] == "自习" || workdays[i][5] == "自习")//找到，退出
			return i;
		i = i + 1 < 5 ? i + 1 : i - 4;
	}
	i = i + 1 < 5 ? i + 1 : i - 4;
	if (workdays[i][0] == "自习" || workdays[i][5] == "自习")
		return i;
	return i-1;
}
int System::FindFree3time(int i)//从i日往后找3个空闲的时间
{
	int j = i;
	i = i + 1 < 5 ? i + 1 : i - 4;
	while (j != i)
	{
		if (workdays[i][2] == "自习" || workdays[i][7] == "自习")
			return i;
		i = i + 1 < 5 ? i + 1 : i - 4;
	}
	i = i + 1 < 5 ? i + 1 : i - 4;
	if (workdays[i][2] == "自习" || workdays[i][7] == "自习")
		return i;
	return i-1;

}
void System::Arrange6(Course item)//分配周学时为6的课程
{
	bool isdone = 0;
	int i = Arrange3(item.ClassName);//先分匹配3个
	i = (i + 2 - 5)>0 ? (i + 2 - 5) : i + 2;
	if (workdays[i][2] == "自习")
	{
		workdays[i][2] = item.ClassName;
		workdays[i][3] = item.ClassName;
		workdays[i][4] = item.ClassName;
	}
	else if (workdays[i][7] == "自习")
	{
		workdays[i][7] = item.ClassName;
		workdays[i][8] = item.ClassName;
		workdays[i][9] = item.ClassName;
	}
	else
	{
		int date3 = FindFree3time(i);
		if (date3 != i)//找到了
		{
			if (workdays[i][2] == "自习")
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
			cout << "排课失败！" << endl;
			return;
		}
	}
}
void System::Arrange5(Course item)//分配周学时为5的课程
{
	bool isdone = 0;
	int i = Arrange3(item.ClassName);//先分配3个
	i = (i + 2 - 5)>0 ? (i + 2 - 5) : i + 2;
	if (workdays[i][0] == "自习")
	{
		workdays[i][0] = item.ClassName;
		workdays[i][1] = item.ClassName;
		isdone = 1;
	}
	else if (workdays[i][5] == "自习")
	{
		workdays[i][5] = item.ClassName;
		workdays[i][6] = item.ClassName;
		isdone = 1;
	}
	else
	{
		int date2 = FindFree2time(i);
		if (date2 == i)//没有空闲的2个空间，那就找空闲的3个空间但只分配2节课
		{
			int date3 = FindFree3time(i);
			if (date3 != i)//找到了
			{
				if (workdays[i][2] == "自习")
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
				cout << "排课失败！" << endl;
				return;
			}
		}
		else
		{
			if (workdays[i][0] == "自习")
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
void System::Arrange4(Course item)//安排2次2节课
{
	bool isdone = 0;
	for (int i = 0; i < 5; i++)
	{
		if (isdone == 1)
			return;
		if (workdays[i][0] == "自习")
		{
			workdays[i][0] = item.ClassName;
			workdays[i][1] = item.ClassName;
			i = (i + 2 - 5)>0 ? (i + 2 - 5) : i + 2;
			if (workdays[i][0] == "自习")
			{
				workdays[i][0] = item.ClassName;
				workdays[i][1] = item.ClassName;
				isdone = 1;
			}
			else if (workdays[i][5] == "自习")
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
					if (date3 != i)//找到了
					{
						if (workdays[i][2] == "自习")
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
						cout << "排课失败！" << endl;
						return;
					}
				}

				else
				{
					if (workdays[i][0] == "自习")
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

		if (workdays[i][2] == "自习")
		{
			workdays[i][2] = name;
			workdays[i][3] = name;
			workdays[i][4] = name;
			return i;
		}
		else if (workdays[i][7] == "自习")
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
		int times = thisTermCourses[i].Times;//获取周学时
		string name = thisTermCourses[i].ClassName;
		switch (times)//根据周学时进行不同的分配模式
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
	for (int t = 0; t < 10; t++)//写入总课程表
	{
		for (int u = 0; u < 5; u++)
		{
			CourseTable[TERMS][u][t] = workdays[u][t];
			cout << workdays[u][t] << " ";
		}
		cout << endl;
	}
	TERMS++;//学期加1
	for (int t = 0; t < 10; t++)//重置每学期的课表
	{
		for (int u = 0; u < 5; u++)
		{
			workdays[u][t]="自习";
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
			for (int j = 0;  Courses[t].pCourses[j]!="\0"; j++)//循环pCourses;
			{
				if (Courses[t].pCourses[j] == Code)//Courses[t]的先修课程里有Courses[i]
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
		if (Courses[i].pCourseNum >= 0)//先修课程数小于0说明已经选过，不再选
		{
			if (Courses[i].pCourseNum == 0)//先修课程数等于0，可以选择
			{
				int t = 0;
				while (thisTermCourses[t].ClassCode != "0")
				{
					t++;
				}//指向thisTermCourses中未分配的空间
				thisTermCourses[t] = Courses[i];//存入，取1个课程操作结束
				Courses[i].pCourseNum--;
				return 1;
			}
		}
	}
	return 0;
}
void System::getCourses(int number,int thisTerm)
{
	thisTermCourses = new Course[number];//记录当前学期的课程数

	getEnglish(thisTerm);//先取英语
	if (thisTerm == 0)//第一学期的话学语文
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
		cout << "课程数有误！" << endl;
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
		infile >> ClassNum[i];//输入每学期开课数
	if (!chargeCourseNum(ClassNum))//判断开课数是否正确
		return -1;

	System CourseSystem;
	for (int i = 0; i < 38; i++)//写入数据
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
		CourseSystem.getCourses(ClassNum[i],i);//取课程
		CourseSystem.ArrangeCourses(ClassNum[i]);
		delete[] CourseSystem.thisTermCourses;
	}
	ofstream outfile("CourseTableNew.txt", ios::trunc);
	CourseSystem.saveToFile(outfile);
	return 0;
}