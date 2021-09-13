#include<iostream>
#include<stack>
#include<math.h>
using namespace std;
const int maxsize = 50;
int isworry = 0;
class Stack//栈
{
public:
	Stack(int sz);
	~Stack()
	{
		delete[]elements;
	}
	void push(double& x);//压入
	bool pop(double& x);//弹出
	bool gettop(double& x);//取顶值
	bool isempty();//判断栈空
	bool isfull();//判断栈满
	int getsize();//获取元素个数
	void overflow();//栈溢出操作
	void makeempty()//清空栈
	{
		top = -1;
	}
	double* elements;//储存数据
private:

	int top;
	int maxsize;

};

void Stack::push(double& x)
{
	if (isfull())//检查栈满？
	{
		overflow();//溢出操作
	}

	elements[++top] = x;//x压入栈中

}

bool Stack::pop(double& x)
{
	if (isempty())//检查栈空？
	{
		return false;
	}
	x = elements[top--];//x弹出
	return true;
}

bool Stack::gettop(double& x)//获得栈顶元素，不弹出
{
	if (isempty())
	{
		return false;
	}
	x = elements[top];
	return true;
}

bool Stack::isempty()
{
	return (top == -1) ? true : false;
}

bool Stack::isfull()
{
	return (top == maxsize - 1) ? true : false;
}

int Stack::getsize()
{
	return top + 1;
}

const int addsize = 20;//栈溢出时增加的位置

Stack::Stack(int sz) :top(-1), maxsize(sz)
{
	elements = new double[maxsize];
	if (elements == NULL)
	{
		cout << "空间分配失败";
		return;
	}
}

void Stack::overflow()
{
	double* newarray = new double[addsize + maxsize];
	if (newarray == NULL)
	{
		cout << "空间分配失败";
		return;
	}
	for (int i = 0; i <= top; i++)
	{
		newarray[i] = elements[i];
	}
	maxsize = maxsize + addsize;
	delete[]elements;
	elements = newarray;
}


class cal
{
public:
	cal(int sz) :s(sz) {}
	void run(char array[]);//运行表达式求解操作
	void clear();//清空
private:
	Stack s;
	void addoperand(double value);//把数据压入栈中
	bool get2operand(double& left, double& right);//从栈中取出2个数
	bool dooperator(char op);//对2个数进行算数操作
};

bool cal::dooperator(char op)
{

	double left, right, value;
	bool result;
	result = get2operand(left, right);//取操作数
	if (result == true)//取成功
	{
		switch (op)
		{
		case'+':
			value = left + right;
			s.push(value);
			break;
		case'-':
			value = left - right;
			s.push(value);
			break;
		case'*':
			value = left * right;
			s.push(value);
			break;
		case'/':
			if (fabs(right - 0.0) < 0.0001)
			{
				cout << "除数为0，计算错误！" << endl;
				clear();
				return 0;
			}
			else
			{
				value = left / right;
				s.push(value);
				break;
			}
		case'%':
			value = (int)left % (int)right;
			s.push(value);
			break;
		case '^':
			value = pow(left, right);
			s.push(value);
			break;
		}
	}
	else
	{
		clear();//不成功报错退出
		return 0;
	}
		
	return 1;
}

bool cal::get2operand(double& left, double& right)
{
	if (s.isempty() == true)
	{
		cout << "缺少右操作数!" << endl;
		return false;
	}
	s.pop(right);
	if (s.isempty() == true)
	{
		cout << "缺少左操作数!" << endl;
		return false;
	}
	s.pop(left);
	return true;
}

void cal::addoperand(double value)
{
	s.push(value);
}

void cal::run(char array[])
{
	int i = 0;//i循环array读数（array是存储着后序表达式的算式）
	bool minus = 0;//判断是不是﹣单目运算符，然后对数据取相反数
	bool isfirst = 0;//判断是不是单目运算符
	bool well = 1;//判断除数为0的情况
	char ch; double newoperand;
	while (ch = array[i], i++, ch != '=')//每次从array里读出一个ch，i++
	{
		switch (ch)
		{
		case '(':
			cout << "缺少右括号！" << endl;
			return;
		case ')':
			cout << "缺少左括号！" << endl;
			return;
		case ' ':
			break;
		case'!'://ch=！是单目运算符的标志
			isfirst = 1;
			break;
		case'*':
		case'/':
		case'^':
		case'%':
			well=dooperator(ch);//做运算
			if (well == 0)
				return;
			break;
		case'+':
			if (i == 1 || isfirst == 1)//单目运算符不做运算
			{
				isfirst = 0;
				break;
			}
			else//不是单目就运算
			{
				dooperator(ch);
				break;
			}
		case'-':
			if (i == 1 || isfirst == 1)//原理同+，
			{
				minus = 1;//多了个minus，让读进来的数字取相反数
				isfirst = 0;
				break;
			}
			else
			{
				dooperator(ch);
				break;
			}

		default:
			i--;//现在数字是char型，i--，让array[i]重新指向数字，因为后面要读double型
			if (minus == 1)//取相反数
			{
				double t=0;
				while (array[i] >= '0' && array[i] <= '9')
				{
					t *= 10;
					t+=((double)array[i] - '0');
					i++;
				}
				newoperand = -t;
				minus = 0;
			}
			else
			{
				double t = 0;
				while (array[i] >= '0' && array[i] <= '9')
				{
					t *= 10;
					t+=((double)array[i] - '0');
					i++;
				}
				newoperand = t;
			}
			
			addoperand(newoperand);//数字进栈
		}
	}
	cout << (double)s.elements[0];//运算完毕，输出计算结果。
}
void cal::clear()
{
	s.makeempty();
}

bool isdight(char ch)//判断是否是数字
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
int isp(char ch)//栈内的各个字符的权值
{
	switch (ch)
	{
	case'=':
		return 0;
	case'(':
		return 1;
	case'*':
	case'/':
	case'%':
		return 5;
	case'+':
	case'-':
		return 3;
	case')':
		return 9;
	case'^':
		return 7;
	default:
		cout << "错误" << endl;
	
		return-1;
	}
}
int icp(char ch)//栈外的各个字符的权值
{
	switch (ch)
	{
	case'=':
		return 0;
	case'(':
		return 9;
	case '^':
		return 6;
	case'*':
	case'/':
	case'%':
		return 4;
	case'+':
	case'-':
		return 2;
	case')':
		return 1;
	default:
		cout << "错误" << endl;
	
		return-1;
	}
}

bool iscontinue()//是否继续的函数
{
	char choice;
	cout << endl << "是否继续（y，n）？";
	while (1)
	{
		cin >> choice;
		if (!cin.good() || (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N'))
		{
			cout << "输入错误！请重新输入" << endl;
			cin.clear();//重置cin流
			cin.ignore(100, '\n');//清空输入缓冲区
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
		
	}
	return (choice == 'y' || choice == 'Y') ? 1 : 0;
}
int main()
{
	while (1)
	{
		cout << "请输入中序算术表达式，以=结尾！" << endl;
		stack <char>s;
		char array[50];//存储后序表达式
		int i = 0;
		char ch = '=', ch1, op;
		bool isfirst = 1;//单目运算符的判断
		s.push(ch); cin.get(ch);//先把‘#’进栈，然后cin读数据
		while (s.empty() == false)
		{
			
			if (isdight(ch))
			{
				isfirst = 0;
				array[i] = ch;
				i++;
				while (isdight(cin.peek()))
				{
					cin.get(ch);
					array[i] = ch;
					i++;
				}
				array[i] = ' ';
				i++;
				cin.get(ch);
			}
			else if(ch!='+'&&ch!='-'&&ch!='*'&&ch!='/'&&ch!='('&&ch!=')'&&ch!='^'&&ch!='%'&&ch!='=')
			{
				cout << "错误的符号！" << endl;
				if (ch == '\n')
					isworry = 2;
				else
				isworry = 1;
				break;
			}
			else 
			{
				ch1 = s.top();//取栈顶元素
				if ((ch == '-' || ch == '+') && (isfirst == 1))//是单目运算符之后的数字
				{
					array[i] = '!';//单目运算符标志进array数组
					i++;
					array[i] = ch;//加号减号进数组
					i++;
					array[i] = ' ';
					i++;
					cin.get(ch);
				}
				else
				{
					if (ch == '(')//重置单目运算符的判定
						isfirst = 1;
					if (isp(ch1) < icp(ch))//新输入的运算符ch优先级高
					{
						s.push(ch);//进栈
						cin.get(ch);//读入下一个
					}
					else if (isp(ch1) > icp(ch))//优先级低
					{
						op = s.top();//读栈顶元素
						s.pop();//出栈
						array[i] = op;//写入array里
						i++;
						array[i] = ' ';
						i++;
						//cout << op;
					}
					else
					{
						op = s.top();//优先级相等要么是‘=’，要么括号配对
						s.pop();
						if (op == '(')cin.get(ch);
					}
				}
			}
		}
		array[i] = '=';
		/*int t = 0;
		while (array[t] != '=')
		{
			cout << array[t];
			t++;
		}*/
		cal CAL(50);
		if (isworry != 0)
		{
			if (isworry == 1)
			{
				isworry = 0;
				cin.ignore(1000, '\n');
			}
			else
			{
				isworry = 0;
			}
			
		}
		else
		CAL.run(array);//array已经是后序运算符，执行运算操作
		if (!iscontinue())//判断是否继续
		{
			
			break;
		}

	}

}