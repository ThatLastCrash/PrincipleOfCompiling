#include<iostream>
#include<string> 
#include<cstdio>
#include<fstream>

#define WAITTING 0
//32 keyword
#define VOID 1
#define CHAR 2
#define INT 3
#define FLOAT 4
#define DOUBLE 5
#define SHORT 6
#define LONG 7
#define	SIGNED 8
#define UNSIGNED 9
#define STRUCT 10
#define UNION 11
#define ENUM 12
#define TYPEDEF 13
#define SIZEOF 14
#define AUTO 15
#define STATIC 16
#define REGISTER 17
#define EXTERN 18
#define CONST 19
#define VOLATILE 20
#define RETURN 21
#define CONTINUE 22
#define BREAK 23
#define GOTO 24
#define IF 25
#define ELSE 26
#define SWITCH 27
#define CASE 28
#define DEFAULT 29
#define FOR 30
#define do 31
#define WHILE 32 
//notvalid
#define NOTVALID 404 
//identifier
#define IDENTIFIER 100 
//num
#define INTCONST 200
#define REALCONST 201
//operator
#define ADD 101			//	+
#define SUB 102			//	-
#define MUL 103			//	*
#define DIV 104			//	/
#define MOD 105			//	%
#define LOWWER 106		//	<
#define GREATER 107		//	>
#define EQUAL 108		//	=
#define NOT 109			//	!
#define AND 110			//	&
#define OR 111			//	|
#define COMMA 112		//	,
#define COLON 113		//	:
#define LSquare 114		//	[
#define RSquare 115		//	]
#define LCurly 116		//	{
#define RCurly 117		//	}
#define LParenthesis 118	//	(
#define RParenthesis 118	//	)
#define ADDADD 119		//	++
#define SUBSUB 120		//	--
#define LEQUAL 121		//	<=
#define GEQUAL 122		//	>=
#define EEQUAL 123		//	==
#define NEQUAL 124		//	!=
#define ANDAND 125		//	&&
#define OROR 126		//	||
#define RSHIFT 127		//	>>
#define LSHIFT 128		//	<<
#define ADDEQUAL 129	//	+=
#define SUBEQUAL 130	//	-=
#define MULEQUAL 131	//	*=
#define DIVEQUAL 132	//	/=
#define ANDEQUAL 133	//	&=
#define OREQUAL 134		//	|=
#define POINT 135		//	.
#define GETCHILD 136	//	->
#define SEMICOLON 137	//	;
#define STRINGCONST 138	//	string const
#define CHARCONST 139	//	char const
#define QUOTES 140		//	'
#define DQUOTES 141		//	"
#define MULTIANNOT 142	//	/*
#define ANNOT 143		//	//
using namespace std;
typedef struct R
{
	int type;
	string value;
}R;
string list[32]={"void","char","int","float","double",
				"short","long","signed","unsigned",
				"struct","union","enum",
				"typedef","sizeof","auto","static",
				"register","extern","const","volatile",
				"return","continue","break","goto",
				"if","else","switch","case","default",
				"for","do","while"};
				
void doState0(char c,int &state,R &r);
void doState1(char c,int &state,R &r);
void doState2(char c,int &state,R &r);
void doState3(char c,int &state,R &r);
void doState4(char c,int &state,R &r);
void doState5(char c,int &state,R &r);
void doState6(char c,int &state,R &r);
void doState7(char c,int &state,R &r);
void doState8(char c,int &state,R &r);
void doState9(char c,int &state,R &r);
void doState10(char c,int &state,R &r);
void doState11(char c,int &state,R &r);
void doState12(char c,int &state,R &r);
void doState13(char c,int &state,R &r);
void doState14(char c,int &state,R &r);
void doState15(char c,int &state,R &r);
void doState16(char c,int &state,R &r);
void doState17(char c,int &state,R &r);
void doState18(char c,int &state,R &r);
void doState19(char c,int &state,R &r);
void doState20(char c,int &state,R &r);
void doState21(char c,int &state,R &r);
void doState22(char c,int &state,R &r);
void doState23(char c,int &state,R &r);
void doState24(char c,int &state,R &r);
void doState25(char c,int &state,R &r);
void doState26(char c,int &state,R &r);
void doState27(char c,int &state,R &r);
void doState28(char c,int &state,R &r);
void doState29(char c,int &state,R &r);
void doState30(char c,int &state,R &r);
void doState31(char c,int &state,R &r);
void doState32(char c,int &state,R &r);
void doState33(char c,int &state,R &r);
void doState34(char c,int &state,R &r);
void doState35(char c,int &state,R &r);
void doState36(char c,int &state,R &r);
void doState37(char c,int &state,R &r);
void doState38(char c,int &state,R &r);
void doState39(char c,int &state,R &r);
void doState40(char c,int &state,R &r);
void doState41(char c,int &state,R &r);
void doState42(char c,int &state,R &r);
void doState43(char c,int &state,R &r);
void doState44(char c,int &state,R &r);
void doState45(char c,int &state,R &r);
void doState46(char c,int &state,R &r);
void doState47(char c,int &state,R &r);
void doState48(char c,int &state,R &r);
void doState49(char c,int &state,R &r);
void doState50(char c,int &state,R &r);
void doState51(char c,int &state,R &r);
void doState52(char c,int &state,R &r);
void doState53(char c,int &state,R &r);
void doState54(char c,int &state,R &r);
void doState55(char c,int &state,R &r);
void doState56(char c,int &state,R &r);
void doState57(char c,int &state,R &r);
void doState58(char c,int &state,R &r);
void doState59(char c,int &state,R &r);
void doState60(char c,int &state,R &r);
void doState61(char c,int &state,R &r);
void doState62(char c,int &state,R &r);
void doState63(char c,int &state,R &r);
void doState64(char c,int &state,R &r);
void doState65(char c,int &state,R &r);
void doState66(char c,int &state,R &r);
void doState67(char c,int &state,R &r);
void doState68(char c,int &state,R &r);
void doState69(char c,int &state,R &r);
void doState70(char c,int &state,R &r);
void doState71(char c,int &state,R &r);
bool isLetter(char c)
{
	if(c>='a' && c<='z')return true;
	if(c>='A' && c<='Z') return true;
	return false;
}
bool isNum(char c)
{
	if(c>='0' && c<='9')return true;
	return false;
}
void doState0(char c,int &state,R &r)
{
	r.value+=c;
	r.type=WAITTING;
	if(c=='_' || isLetter(c)==true)
	{
		state=1;
	}
	else if(isNum(c)==true)
	{
		state=3;
	}
	else if(c=='+')
	{
		state=12;
	}
	else if(c=='-')
	{
		state=15;
	}
	else if(c=='*')
	{
		state=18;
//		r.type=MUL;
//		doState18(c,state,r);		
//		state=0;
//		r.type=WAITTING;
//		r.value="";
	}
	else if(c=='/')
	{
		state=19;
//		r.type=DIV;
//		doState19(c,state,r);
//		
//		state=0;
//		r.type=WAITTING;
//		r.value="";
	}
	else if(c=='%')
	{
		state=20;
		r.type=MOD;
		doState20(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='<')
	{
		state=21;
	}
	else if(c=='>')
	{
		state=24;
	}
	else if(c=='=')
	{
		state=27;
	}
	else if(c=='!')
	{
		state=30;
	}
	else if(c=='&')
	{
		state=33;
	}
	else if(c=='|')
	{
		state=36;
	}
	else if(c==',')
	{
		state=39;
		r.type=COMMA;
		doState39(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c==':')
	{
		state=40;
		r.type=COLON;
		doState40(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='[')
	{
		state=41;
		r.type=LSquare;
		doState41(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c==']')
	{
		state=42;
		r.type=RSquare;
		doState42(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='{')
	{
		state=43;
		r.type=LCurly;
		doState43(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='}')
	{
		state=44;
		r.type=RCurly;
		doState44(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='(')
	{
		state=45;
		r.type=LParenthesis;
		doState45(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c==')')
	{
		state=46;
		r.type=RParenthesis;
		doState46(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='.')
	{
		state=60;
		r.type=POINT;
		doState60(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c==';')
	{
		state=61;
		r.type=SEMICOLON;
		doState61(c,state,r);
		
		state=0;
		r.type=WAITTING;
		r.value="";
	}
	else if(c=='\'')
	{
		state=62;
	}
	else if(c=='\"')
	{
		state=65;
	}
	else if(c==' ' || c=='\t' || c=='\n')
	{
		state=0;
		r.value="";
	}
	else
	{
		state=47;
		r.type=NOTVALID;
		doState47(c,state,r);//立即终止 
	}
}
void doState1(char c,int &state,R &r)
{
	if(c=='_' || isLetter(c)==true || isNum(c)==true)
	{
		state=1;
		r.value+=c;
	}
	else
	{
		state=2;
		doState2(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState2(char c,int &state,R &r)
{
	r.type=IDENTIFIER;
	for(int i=0;i<32;i++)
	{
		if(list[i]==r.value)
		{
			r.type=i+1;
			break;
		}
	}
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState3(char c,int &state,R &r)
{
	if(isNum(c)==true)
	{
		state=3;
		r.value+=c;
	}
	else if(c=='.')
	{
		state=4;
		r.value+=c;
	}
	else if(c=='E' || c=='e')
	{
		state=6;
		r.value+=c;
	}
	else
	{
		state=7;
		r.type=INTCONST;
		doState7(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState4(char c,int &state,R &r)
{
	r.value+=c;
	if(isNum(c)==true)
	{
		state=5;
	}
	else
	{
		state=8;
		r.type=NOTVALID;
		doState8(c,state,r);//立刻终止 
	}
}
void doState5(char c,int &state,R &r)
{
	if(isNum(c)==true)
	{
		state=5;
		r.value+=c;
	}
	else if(c=='E' || c=='e')
	{
		state=6;
		r.value+=c;
	}
	else
	{
		state=11;
		r.type=REALCONST;
		doState11(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState6(char c,int &state,R &r)
{
	r.value+=c;
	if(isNum(c)==true)
	{
		state=10;
	}
	else if(c=='+' || c=='-')
	{
		state=9;
	}
	else
	{
		state=8;
		r.type=NOTVALID;
		doState8(c,state,r);//立刻终止 
	}
}
void doState7(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState8(char c,int &state,R &r)
{
	cout<<"实数格式不对"<<endl;
	exit(0); 
}
void doState9(char c,int &state,R &r)
{
	r.value+=c;
	if(isNum(c)==true)
	{
		state=10;	
	} 
	else
	{
		state=8;
		r.type=NOTVALID;
		doState8(c,state,r);//立刻终止 
	}
}
void doState10(char c,int &state,R &r)
{
	if(isNum(c)==true)
	{
		state=10;
		r.value+=c;	
	} 
	else
	{
		state=11;
		r.type=REALCONST;
		doState11(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState11(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState12(char c,int &state,R &r)
{
	if(c=='+')
	{
		state=13;
		r.type=ADDADD;
		r.value+=c;
		doState13(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
//		doState0(c,state,r);
	}
	else if(c=='=')		//	+=
	{
		state=50;
		r.type=ADDEQUAL;
		r.value+=c;
		doState50(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=14;
		r.type=ADD;
		doState14(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState13(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState14(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState15(char c,int &state,R &r)
{
	if(c=='-')
	{
		state=16;
		r.type=SUBSUB;
		r.value+=c;
		doState16(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='=')		//	-= 
	{
		state=51;
		r.type=SUBEQUAL;
		r.value+=c;
		doState51(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
//	else if(c=='>')		//	-> 
//	{
//		state=57;
//		r.type=GETCHILD;
//		r.value+=c;
//		doState57(c,state,r);
//		
//		r.type=WAITTING;
//		r.value="";
//		state=0;
//	}
	else
	{
		state=17;
		r.type=SUB;
		doState17(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState16(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState17(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState18(char c,int &state,R &r)
{
	if(c=='=')		//	*=
	{
		state=52;
		r.type=MULEQUAL;
		r.value+=c;
		doState52(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else			//	*
	{
		state=58;
		r.type=MUL;
		doState58(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState19(char c,int &state,R &r)
{
	if(c=='=')		//	/=
	{
		state=53;
		r.type=DIVEQUAL;
		r.value+=c;
		doState53(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='*')
	{
		state=67;
		r.type=MULTIANNOT;
		r.value+=c;
	}
	else if(c=='/')
	{
		state=70;
		r.type=ANNOT;
		r.value+=c;
	}
	else
	{
		state=59;
		r.type=DIV;
		doState59(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState20(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState21(char c,int &state,R &r)
{
	if(c=='=')
	{
		state=22;
		r.type=LEQUAL;
		r.value+=c;
		doState22(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='<')		//	<< 
	{
		state=48;
		r.type=LSHIFT;
		r.value+=c;
		doState48(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=23;
		r.type=LOWWER;
		doState23(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState22(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState23(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState24(char c,int &state,R &r)
{
	if(c=='=')
	{
		state=25;
		r.type=GEQUAL;
		r.value+=c;
		doState25(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='>')		//	>> 
	{
		state=49;
		r.type=RSHIFT;
		r.value+=c;
		doState49(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=26;
		r.type=GREATER;
		doState26(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState25(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState26(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState27(char c,int &state,R &r)
{
	if(c=='=')
	{
		state=28;
		r.type=EEQUAL;
		r.value+=c;
		doState28(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=29;
		r.type=EQUAL;
		doState29(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState28(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState29(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState30(char c,int &state,R &r)
{
	if(c=='=')
	{
		state=31;
		r.type=NEQUAL;
		r.value+=c;
		doState31(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=32;
		r.type=NOT;
		doState32(c,state,r);
		
		r.type=WAITTING;
		r.value="";
//		r.value+=c;
		doState0(c,state,r);
	}
}
void doState31(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState32(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState33(char c,int &state,R &r)
{
	if(c=='&')
	{
		state=34;
		r.type=ANDAND;
		r.value+=c;
		doState34(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='=')
	{
		state=54;
		r.type=ANDEQUAL;
		r.value+=c;
		doState54(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=35;
		r.type=AND;
		doState35(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState34(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState35(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState36(char c,int &state,R &r)
{
	if(c=='|')
	{
		state=37;
		r.type=OROR;
		r.value+=c;
		doState37(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='=')
	{
		state=55;
		r.type=OREQUAL;
		r.value+=c;
		doState55(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=38;
		r.type=OR;
		doState38(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		doState0(c,state,r);
	}
}
void doState37(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState38(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState39(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState40(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState41(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState42(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState43(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState44(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState45(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState46(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState47(char c,int &state,R &r)
{
	cout<<"非法字符"<<r.value<<endl;
	exit(0); 
}
void doState48(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState49(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState50(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState51(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState52(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState53(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState54(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState55(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState56(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState57(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState58(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState59(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState60(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState61(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState62(char c,int &state,R &r)
{
	if(c=='\'')
	{
		state=64;
		r.type=CHARCONST;
		r.value+=c;
		doState64(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else if(c=='\\')
	{
		state=72;
		r.value+=c;
	}
	else
	{
		state=63;
		r.value+=c;
	}
}
void doState63(char c,int &state,R &r)
{
	if(c=='\'')
	{
		state=64;
		r.type=CHARCONST;
		r.value+=c;
		doState64(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=47;
		r.type=NOTVALID;
		doState47(c,state,r);
	}
}
void doState64(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState65(char c,int &state,R &r)
{
	if(c=='\"')
	{
		state=66;
		r.type=STRINGCONST;
		r.value+=c;
		doState66(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=65;
		r.value+=c;
	}
}
void doState66(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState67(char c,int &state,R &r)
{
	if(c=='*')
	{
		state=68;
		r.value+=c;
	}
	else
	{
		state=67;
		r.value+=c;
	}
}
void doState68(char c,int &state,R &r)
{
	if(c=='/')
	{
		state=69;
		r.value+=c;
		doState69(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=67;
		r.value+=c;
	}
}
void doState69(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState70(char c,int &state,R &r)
{
	if(c=='\n')
	{
		state=71;
		doState71(c,state,r);
		
		r.type=WAITTING;
		r.value="";
		state=0;
	}
	else
	{
		state=70;
		r.value+=c;
	}
}
void doState71(char c,int &state,R &r)
{
	cout<<"("<<r.type<<","<<r.value<<")"<<endl;
}
void doState72(char c,int &state,R &r)
{
	if(c=='\'' || c=='\"' || c=='\\' ||
		c=='a' || c=='b' || c=='f' ||
		c=='n' || c=='r' || c=='t' ||	c=='v')
	{
		state=63;
		r.value+=c;
	}
	else
	{
		state=47;
		r.type=NOTVALID;
		doState47(c,state,r);
	}
}
int main()
{
	ifstream infile;
	infile.open(".//data.txt");
	if (!infile.is_open())
	{
		cout << "读取文件失败" << endl;
		return 0;
	}
	string s;
	R r;
	int state=0;
	while (getline(infile,s))
	{
		s+='\n';
		for(int i=0;i<s.length();i++)
		{
//			cout<<state<<" "<<s[i]<<endl;
			switch(state)
			{
				case 0:
					doState0(s[i],state,r);
					break;
				case 1:
					doState1(s[i],state,r);
					break;
				case 3:
					doState3(s[i],state,r);
					break;
				case 4:
					doState4(s[i],state,r);
					break;
				case 5:
					doState5(s[i],state,r);
					break;
				case 6:
					doState6(s[i],state,r);
					break;
				case 9:
					doState9(s[i],state,r);
					break;
				case 10:
					doState10(s[i],state,r);
					break;
				case 12:
					doState12(s[i],state,r);
					break;
				case 15:
					doState15(s[i],state,r);
					break;
				case 18:
					doState18(s[i],state,r);
					break;
				case 19:
					doState19(s[i],state,r);
					break;
				case 21:
					doState21(s[i],state,r);
					break;
				case 24:
					doState24(s[i],state,r);
					break;
				case 27:
					doState27(s[i],state,r);
					break;
				case 30:
					doState30(s[i],state,r);
					break;
				case 33:
					doState33(s[i],state,r);
					break;
				case 36:
					doState36(s[i],state,r);
					break;
				case 62:
					doState62(s[i],state,r);
					break;
				case 63:
					doState63(s[i],state,r);
					break;
				case 65:
					doState65(s[i],state,r);
					break;
				case 67:
					doState67(s[i],state,r);
					break;
				case 68:
					doState68(s[i],state,r);
					break;
				case 70:
					doState70(s[i],state,r);
					break;
				case 72:
					doState72(s[i],state,r);
					break;
				default: cout<<"state error"<<endl;break;
			} 
		}
	}
	return 0;
}




