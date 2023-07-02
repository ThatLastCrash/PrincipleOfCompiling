#include<iostream>
using namespace std;
char sym;
void E();
void E1();
void T();
void T1();
void F();
bool getsymbol();
void error();
void isOK();

void E() {
	T();
	E1();
}
void E1() {
	bool f=0;
	if(sym== '+') {
		getsymbol();
		T();
		E1();
	}
}
void T() {
	F();
	T1();
}
void T1() {
	if(sym== '*') {
		getsymbol();
		F();
		T1();
	}
}
void F() {
	bool f=0;
	if(sym== 'i')
	{
		f=getsymbol();
		if(f==0)
		{
			isOK();
		} 
	}
	else  if(sym== '(' ) {
		f=getsymbol();
		if(f==0) error();
		
		E();
		if(sym== ')' )
		{
			f=getsymbol();
			if(f==0)
			{
				isOK();
			} 
		}
		else{
			error();
		} 
	} else
		error();
}
bool getsymbol()
{
	cin>>sym;
	if(sym==';')
	{
		return 0;
	} 
	return 1;
}
void isOK()
{
	cout<<"ÕýÈ·"<<endl;
	exit(0);
}
void error()
{
	cout<<"´íÎó"<<endl; 
	exit(0);
}
int main() {
	getsymbol();
	E();
	if(sym!=';')error();
	return 0;
}

