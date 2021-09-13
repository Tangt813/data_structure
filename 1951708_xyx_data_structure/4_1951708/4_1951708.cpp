#include<iostream>
#include<stack>
#include<math.h>
using namespace std;
const int maxsize = 50;
int isworry = 0;
class Stack//ջ
{
public:
	Stack(int sz);
	~Stack()
	{
		delete[]elements;
	}
	void push(double& x);//ѹ��
	bool pop(double& x);//����
	bool gettop(double& x);//ȡ��ֵ
	bool isempty();//�ж�ջ��
	bool isfull();//�ж�ջ��
	int getsize();//��ȡԪ�ظ���
	void overflow();//ջ�������
	void makeempty()//���ջ
	{
		top = -1;
	}
	double* elements;//��������
private:

	int top;
	int maxsize;

};

void Stack::push(double& x)
{
	if (isfull())//���ջ����
	{
		overflow();//�������
	}

	elements[++top] = x;//xѹ��ջ��

}

bool Stack::pop(double& x)
{
	if (isempty())//���ջ�գ�
	{
		return false;
	}
	x = elements[top--];//x����
	return true;
}

bool Stack::gettop(double& x)//���ջ��Ԫ�أ�������
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

const int addsize = 20;//ջ���ʱ���ӵ�λ��

Stack::Stack(int sz) :top(-1), maxsize(sz)
{
	elements = new double[maxsize];
	if (elements == NULL)
	{
		cout << "�ռ����ʧ��";
		return;
	}
}

void Stack::overflow()
{
	double* newarray = new double[addsize + maxsize];
	if (newarray == NULL)
	{
		cout << "�ռ����ʧ��";
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
	void run(char array[]);//���б��ʽ������
	void clear();//���
private:
	Stack s;
	void addoperand(double value);//������ѹ��ջ��
	bool get2operand(double& left, double& right);//��ջ��ȡ��2����
	bool dooperator(char op);//��2����������������
};

bool cal::dooperator(char op)
{

	double left, right, value;
	bool result;
	result = get2operand(left, right);//ȡ������
	if (result == true)//ȡ�ɹ�
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
				cout << "����Ϊ0���������" << endl;
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
		clear();//���ɹ������˳�
		return 0;
	}
		
	return 1;
}

bool cal::get2operand(double& left, double& right)
{
	if (s.isempty() == true)
	{
		cout << "ȱ���Ҳ�����!" << endl;
		return false;
	}
	s.pop(right);
	if (s.isempty() == true)
	{
		cout << "ȱ���������!" << endl;
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
	int i = 0;//iѭ��array������array�Ǵ洢�ź�����ʽ����ʽ��
	bool minus = 0;//�ж��ǲ��ǩ���Ŀ�������Ȼ�������ȡ�෴��
	bool isfirst = 0;//�ж��ǲ��ǵ�Ŀ�����
	bool well = 1;//�жϳ���Ϊ0�����
	char ch; double newoperand;
	while (ch = array[i], i++, ch != '=')//ÿ�δ�array�����һ��ch��i++
	{
		switch (ch)
		{
		case '(':
			cout << "ȱ�������ţ�" << endl;
			return;
		case ')':
			cout << "ȱ�������ţ�" << endl;
			return;
		case ' ':
			break;
		case'!'://ch=���ǵ�Ŀ������ı�־
			isfirst = 1;
			break;
		case'*':
		case'/':
		case'^':
		case'%':
			well=dooperator(ch);//������
			if (well == 0)
				return;
			break;
		case'+':
			if (i == 1 || isfirst == 1)//��Ŀ�������������
			{
				isfirst = 0;
				break;
			}
			else//���ǵ�Ŀ������
			{
				dooperator(ch);
				break;
			}
		case'-':
			if (i == 1 || isfirst == 1)//ԭ��ͬ+��
			{
				minus = 1;//���˸�minus���ö�����������ȡ�෴��
				isfirst = 0;
				break;
			}
			else
			{
				dooperator(ch);
				break;
			}

		default:
			i--;//����������char�ͣ�i--����array[i]����ָ�����֣���Ϊ����Ҫ��double��
			if (minus == 1)//ȡ�෴��
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
			
			addoperand(newoperand);//���ֽ�ջ
		}
	}
	cout << (double)s.elements[0];//������ϣ������������
}
void cal::clear()
{
	s.makeempty();
}

bool isdight(char ch)//�ж��Ƿ�������
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
int isp(char ch)//ջ�ڵĸ����ַ���Ȩֵ
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
		cout << "����" << endl;
	
		return-1;
	}
}
int icp(char ch)//ջ��ĸ����ַ���Ȩֵ
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
		cout << "����" << endl;
	
		return-1;
	}
}

bool iscontinue()//�Ƿ�����ĺ���
{
	char choice;
	cout << endl << "�Ƿ������y��n����";
	while (1)
	{
		cin >> choice;
		if (!cin.good() || (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N'))
		{
			cout << "�����������������" << endl;
			cin.clear();//����cin��
			cin.ignore(100, '\n');//������뻺����
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
		cout << "�����������������ʽ����=��β��" << endl;
		stack <char>s;
		char array[50];//�洢������ʽ
		int i = 0;
		char ch = '=', ch1, op;
		bool isfirst = 1;//��Ŀ��������ж�
		s.push(ch); cin.get(ch);//�Ȱѡ�#����ջ��Ȼ��cin������
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
				cout << "����ķ��ţ�" << endl;
				if (ch == '\n')
					isworry = 2;
				else
				isworry = 1;
				break;
			}
			else 
			{
				ch1 = s.top();//ȡջ��Ԫ��
				if ((ch == '-' || ch == '+') && (isfirst == 1))//�ǵ�Ŀ�����֮�������
				{
					array[i] = '!';//��Ŀ�������־��array����
					i++;
					array[i] = ch;//�Ӻż��Ž�����
					i++;
					array[i] = ' ';
					i++;
					cin.get(ch);
				}
				else
				{
					if (ch == '(')//���õ�Ŀ��������ж�
						isfirst = 1;
					if (isp(ch1) < icp(ch))//������������ch���ȼ���
					{
						s.push(ch);//��ջ
						cin.get(ch);//������һ��
					}
					else if (isp(ch1) > icp(ch))//���ȼ���
					{
						op = s.top();//��ջ��Ԫ��
						s.pop();//��ջ
						array[i] = op;//д��array��
						i++;
						array[i] = ' ';
						i++;
						//cout << op;
					}
					else
					{
						op = s.top();//���ȼ����Ҫô�ǡ�=����Ҫô�������
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
		CAL.run(array);//array�Ѿ��Ǻ����������ִ���������
		if (!iscontinue())//�ж��Ƿ����
		{
			
			break;
		}

	}

}