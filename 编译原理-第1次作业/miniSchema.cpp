#include<iostream>
#include<stack>
#include<string>
#include<stdlib.h>
#include<map> 
#include<string.h>
#include <algorithm>
#define endl '\n'
using namespace std;
map<string,int> m;//变量列表 
bool isLegal(char c);

//根据操作符运算 
int cal(int x,int y,int type)
{
//	cout<<"x="<<x<<" y="<<y<<" type="<<(char)type<<endl;
	switch(type)
	{
		case '+':
			return x+y;
		case '-':
			return x-y;
		case '*':
			return x*y;
		case '/':
			return x/y;
		case '>':
			return x>y;
		case '<':
			return x>y;
		case '=':
			return x==y;
		case 'A':
			return x>y || x==y;//大于等于 
		case 'B':
			return x<y || x==y;//小于等于 
		case 'C':
			return x!=y;//不等于
		default:
			return -1;
	}

}
//取数 
int getNum(string s,int *p)
{
	int num=0;
	for(int i=*p;i<s.length();(*p)++,i=*p)
	{
		if(s[i]<='9' && s[i]>='0')
			num=num*10+(s[i]-'0');
		else
			break;
	}
	return num;
}
int getOp(string s,int *p)
{
	int i=*p,op=0;
	if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')//算数符号 
	{
		op=s[i];
	}
	else if(s[i]=='>')
	{
		if(s[i+1]=='=')//大于等于 
		{
			op='A';
		}
		else//大于 
		{
			op=s[i];
		} 
	}
	else if(s[i]=='<')
	{
		if(s[i+1]=='=')//小于等于 
		{
			op='B';
		}
		else//小于 
		{
			op=s[i];
		} 
	}
	else if(s[i]=='=')//等于 
	{
		op=s[i];
	}
	else if(s[i]=='!' && s[i+1]=='=')//不等于 
	{
		op='C';
	}
	else if(s[i]==':' && s[i+1]=='=')//赋值
	{
		op='D';	
	} 
	return op;
}
//处理子列表 
int getValue(string s,int *p)
{
	int ans=0,x=0x3f3f3f3f,y=0x3f3f3f3f,op=0;
	string key="";
	for(int i=*p;i<s.length();(*p)++,i=*p)
	{
//		cout<<"s[i]="<<s[i]<<" p="<<*p<<" "<<s.length()<<endl;
		if(s[i]=='(')//处理某个子列表 
		{
			(*p)++;
			i=*p;
			//取操作符 
			while(s[i]==' ')
			{
				(*p)++;
				i=*p;
			}
			op=getOp(s,p); 
				
			//取操作数 
			(*p)++;
			i=*p;
			if(op=='A' || op=='B' || op=='C' || op=='D')//运算符有两位 
			{
				(*p)++;
				i=*p;
			}
			while(s[i]==' ')
			{
				(*p)++;
				i=*p;
			}
			while(s[i]!=')')//取完当前子列表 
			{
				//特判赋值语句
				if(op=='D')
				{
//					cout<<(i<s.length())<<" "<<isLegal(s[i])<<" "<<s[i]<<endl;
					while(i<s.length() && isLegal(s[i]))
					{
						key=key+s[i];
						i++;
						(*p)++;
					}
					while(s[i]==' ')
					{
						(*p)++;
						i=*p;
					}
					y=getValue(s,p);
					m[key]=y;
					ans=y;
					break;
				}
				else//其他语句 
				{
					if(x==0x3f3f3f3f) x=getValue(s,p);
					else
					{
						y=getValue(s,p);
						ans=cal(x,y,op);
						x=ans;y=0x3f3f3f3f;//继续取下一个操作数 
					}
					i=*p;
					while(s[i]==' ')
					{
						(*p)++;
						i=*p;
					}					
				}
			}
		} 
		if(s[i]==')')
		{
			(*p)++;
			i=*p;
			while(s[i]==' ')
			{
				(*p)++;
				i=*p;
			}
			break;
		}
		//取某个操作数 
		if(s[i]<='9' && s[i]>='0')
		{
			ans=getNum(s,p);
			break;
		}
		//取某个变量
		while(i<s.length() && isLegal(s[i]))
		{
			key=key+s[i];
			i++;
			(*p)++;
		}
		if(key!="")
		{
			return m[key];
		}
	}
	return ans;
}
//算术运算 
int doCal(string s)
{
	int p=0;
	int ans=getValue(s,&p);
	return ans;
}
bool isLegal(char c)
{
	if(c<='9'  && c>='0')
	{
		return 1;
	}
	if(c<='z' && c>='a')
	{
		return 1;
	}
	if(c<='Z' && c>='A')
	{
		return 1;
	}
	if(c=='_')
	{
		return 1;
	}
	return 0;
}
//输入
void doInput(string s)
{
	string strmention="";
	int left=0,right=0;
	string keylist[64];
	int listlen=0;
	
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='\"')
		{
			if(left==0) left=i;
			else
			{
				right=i;
				strmention=s.substr(left+1,right-left-1);//取出提示串 
			}
		}
		if(right!=0)//处理后面的变量 
		{
			string key="";
			while(i<s.length() && isLegal(s[i]))
			{
				key=key+s[i];
				i++;
			}
			if(key!="")keylist[listlen++]=key;//变量列表 
		}
	}
	cout<<strmention<<" ";
	for(int i=0;i<listlen;i++)
	{
		int value=0;
		cin>>value;
		m[keylist[i]]=value;
	}
	getchar(); 
}
//输出
void  doOutput(string s)
{
	int i=0;
	i=s.find("output")+6;
	for(i=i;i<s.length();i++)
	{
		if(s[i]==' ')continue;
		while(i<s.length() && s[i]=='(')
		{
			int ans=0,p=0;
			ans=0;p=i;
			ans=getValue(s,&p);
			i=p;
			cout<<ans<<" ";
		}
		if(i>=s.length())break;
		string key="";
		while(i<s.length() && isLegal(s[i]))
		{
			key=key+s[i];
			i++;
		}
		if(key=="")break;
		if(m.count(key))//变量列表中有 
		{
			cout<<key<<":"<<m.find(key)->second<<" ";
		}
		else
		{
			cout<<key<<":"<<"null"<<" ";
		}
	}
	cout<<endl;
}
int main()
{
	string s;
	while(1)
	{
		cout<<"->";
		getline(cin,s);
		//全部小写
		transform(s.begin(),s.end(),s.begin(),::tolower); 
		if(s.find("input")!=-1)
		{
			doInput(s);
		}
		else if(s.find("output")!=-1)
		{
			doOutput(s);
		}
		else if(s!="")
		{
			cout<<doCal(s)<<endl;
		}
	}
	return 0;
}
