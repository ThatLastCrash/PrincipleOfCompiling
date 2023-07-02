#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#define STATE_LEN 100
#define DSTATE_LEN 100
#define MSTATE_LEN 100
using namespace std;
int STATE_NUM = 1;
int DSTATE_NUM = 0;
int MSTATE_NUM = 0;
typedef struct Edge
{
	int to;
	char value;
}Edge;
typedef struct State	//NFA
{
	int no;				//状态的序号 
	vector<Edge> edge;	//边 
	vector<int> Estate;	//一条或多条空边能到达的状态集 
	bool isExist[100];
	int f;				//0为开始，1为终止 
}State;
State state[STATE_LEN];

typedef struct DState	//DFA
{
	vector<int> list;	//状态集,是NFA中的状态 
	bool isExist[100];
	vector<Edge> edge;	//边 
	int f;				//0为开始，1为终止 
}DState;
DState dstate[DSTATE_LEN];

typedef struct MState	//MFA
{
	vector<int> list;	//状态集，是DFA中的状态 
	bool isExist[100];
	vector<Edge> edge;	//边 
	int f;				//0为开始，1为终止 
}MState;
MState mstate[MSTATE_LEN];


bool isLetterOrNum(char c)			//判断是不是合法的，数字或字母 
{
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= '0' && c <= '9') return true;
	return false;
}
void ChangeEnd(int end, int k)//原先所有指向end的都改成指向k 
{
	for (int i = 0; i <= STATE_NUM; i++)
	{
		for (int j = 0; j < state[i].edge.size(); j++)
		{
			int to = state[i].edge[j].to;
			char value = state[i].edge[j].value;
			if (to == end)
			{
				state[i].edge[j].to = k;
			}
		}
	}
}
void ZZToNFA(string s, int start, int end, vector<string> &str);
void SplitZZ(string s, vector<string> &str)
{
	int cnt = 0, left = 0, right = 0;
	int from = 0, to = s.length() - 1;
	for (int i = from; i <= to; i++)
	{
		if (s[i] == '(')
		{
			if (cnt == 0)left = i;
			cnt++;
		}
		else if (s[i] == ')')
		{
			cnt--;
			if (cnt == 0)
			{
				if (i + 1 <= to && s[i + 1] == '*')
				{
					right = i + 1;
					string news = s.substr(left, right - left + 1);
					str.push_back(news);
					i++;
				}
				else
				{
					right = i;
					string news = s.substr(left + 1, right - left);//去掉括号 
					str.push_back(news);
				}
			}
		}
		else if (cnt == 0)
		{
			if (isLetterOrNum(s[i]))
			{
				if (i + 1 <= to && s[i + 1] == '*')//单个字符闭包 
				{
					string news = "*";
					news = s[i] + news;
					str.push_back(news);
					i++;
				}
				else
				{
					string news = "";
					news += s[i];
					str.push_back(news);
				}
			}
			else
			{
				string news = "";
				news += '|';
				str.push_back(news);
			}
		}
	}
}
void ConnectZZ(int left, int right, int start, int end, vector<string> &str)//把str中left到right连接起来 
{
	int startstate = start, endstate = end;
	for (int i = left; i <= right; i++)
	{
		int size = str[i].size();
		if (size == 1)//单个字符 
		{
			char value = str[i][0];


			if (i == right) endstate = end;	//如果是最后一个，结束状态应该是end，否则为新增的状态 
			else
			{
				STATE_NUM++;
				endstate = STATE_NUM;
			}

			state[startstate].edge.push_back(Edge{ endstate,value });
			startstate = STATE_NUM;
		}
		else if (str[i][size - 1] == '*')//是闭包 
		{
			STATE_NUM++;
			state[startstate].edge.push_back(Edge{ STATE_NUM,'#' });//加一条空边
			startstate = STATE_NUM;
			vector<string> newstr;
			string news = "";
			if (str[i][0] == '(') news = str[i].substr(1, size - 3);//取闭包内部的东西 
			else news = str[i].substr(0, size - 1);//取闭包内部的东西 
			ZZToNFA(news, STATE_NUM, STATE_NUM, newstr);//对子字符串进行处理,子字符串起始终止都为新增的状态

			if (i == right)
			{
				endstate = end;	//如果是最后一个，结束状态应该是end，否则再增加一个状态 
			}
			else
			{
				STATE_NUM++;
				endstate = STATE_NUM;
			}
			state[startstate].edge.push_back(Edge{ endstate,'#' });//加一条空边

			startstate = endstate;
		}
		else
		{

			if (i == right) endstate = end;	//如果是最后一个，结束状态应该是end，否则为新增的状态 
			else
			{
				STATE_NUM++;
				endstate = STATE_NUM;
			}

			vector<string> newstr;
			ZZToNFA(str[i], startstate, endstate, newstr);//对子字符串进行处理 
			startstate = STATE_NUM;
		}
	}
}
void OrZZ(string str, int start, int end)
{
	int startstate = start, endstate = end;
	int size = str.size();
	if (size == 1)//单个字符 
	{
		char value = str[0];
		state[startstate].edge.push_back(Edge{ endstate,value });
	}
	else if (str[size - 1] == '*')//是闭包 
	{
		STATE_NUM++;
		state[startstate].edge.push_back(Edge{ STATE_NUM,'#' });//加一条空边

		vector<string> newstr;
		string news = "";
		if (str[0] == '(') news = str.substr(1, size - 3);//取闭包内部的东西 
		else news = str.substr(0, size - 1);//取闭包内部的东西 

		ZZToNFA(news, STATE_NUM, STATE_NUM, newstr);//对子字符串进行处理,子字符串起始终止都为新增的状态

		state[STATE_NUM].edge.push_back(Edge{ endstate,'#' });//加一条空边

	}
	else
	{
		vector<string> newstr;
		ZZToNFA(str, startstate, endstate, newstr);//对子字符串进行处理 
	}
}
//(a|b)(a|b|c)*
void ZZToNFA(string s, int start, int end, vector<string> &str)	//转换函数
{
	int left = 0, right = 0;
	SplitZZ(s, str);//先划分
	for (int i = 0; i < str.size(); i++)//先连接后或 
	{
		if (str[i] == "|")
		{
			right = i - 1;
			if (left != right)//需要连接 
			{
				ConnectZZ(left, right, start, end, str);
			}
			else//只有一个，直接或
			{
				OrZZ(str[left], start, end);
			}
			left = i + 1;
		}
		else if (i + 1 == str.size())//最后一个 
		{
			right = i;
			if (left != right)//需要连接 
			{
				ConnectZZ(left, right, start, end, str);
			}
			else//只有一个，直接或
			{
				OrZZ(str[left], start, end);
			}
		}
	}
}
int isRepeated(bool f[])	//判断之前的状态集是否已经有了 
{
	for (int j = 0; j <= DSTATE_NUM; j++)
	{
		bool k = 0;
		for (int i = 0; i < 100; i++)
		{
			if (dstate[j].isExist[i] != f[i])
			{
				k = 1;
				break;
			}
		}
		if (k == 0)
		{
			return j;
		}
	}
	return -1;
}
void NFAToDFA()
{
	for (int k = 0; k <= STATE_NUM; k++)		//预处理每个状态经过一条或多条空边能到达的状态 
	{
		vector<int> v;
		v.push_back(k);
		for (int j = 0; j < v.size(); j++)
		{
			int now = v[j];
			for (int i = 0; i < state[now].edge.size(); i++)	//把当前状态的所有空边加进来 
			{
				char value = state[now].edge[i].value;
				int to = state[now].edge[i].to;
				bool isExist = state[k].isExist[to];
				if (value == '#' && isExist == 0)	//不存在，且是空边就加入 
				{
					v.push_back(to);
					state[k].Estate.push_back(to);
					state[k].isExist[to] = 1;	//标记存在，记录当前状态集中都有哪些状态 
				}
			}
		}

	}
	
	dstate[DSTATE_NUM].list.push_back(0);	//初始状态为0，加入
	dstate[DSTATE_NUM].isExist[0] = 1;	//标记存在
	dstate[DSTATE_NUM].f = 1;				//初始状态 
	for (int i = 0; i < state[0].Estate.size(); i++)
	{
		int nstate = state[0].Estate[i];
		dstate[DSTATE_NUM].list.push_back(nstate);//初始状态集 
		dstate[DSTATE_NUM].isExist[nstate] = 1;
		if (state[nstate].f == -1)
		{
			dstate[DSTATE_NUM].f = 2;	//特殊，又是开始又是终止 
		}
	}

	for (int i = 0; i <= DSTATE_NUM; i++)	//遍历 
	{
		vector<vector<int> > v(40, vector<int>(0, 0));	// 10个数字26个字母 
		for (int j = 0; j < dstate[i].list.size(); j++)	//遍历当前状态集 
		{
			int now = dstate[i].list[j]; 				//取出其中的一个状态 
			for (int k = 0; k < state[now].edge.size(); k++)	//遍历当前状态的边，并把字符表对应产生的状态集保存 
			{
				int to = state[now].edge[k].to;
				char value = state[now].edge[k].value;
				if (value >= '0' && value <= '9')
				{
					int index = value - '0';
					v[index].push_back(to);
				}
				else if (value != '#')
				{
					int index = value - 'a' + 10;
					v[index].push_back(to);
				}
			}
		}

		//遍历产生的状态集，重复的就不加
		bool f[100] = { 0 };
		for (int k = 0; k < 36; k++)
		{
			for (int m = 0; m < 100; m++) f[m] = 0;
			for (int m = 0; m < v[k].size(); m++)
			{
				int s = v[k][m];
				f[s] = 1;
				for (int p = 0; p < state[s].Estate.size(); p++)//把s能经过空边到达的状态集加进来 
				{
					int newp = state[s].Estate[p];
					f[newp] = 1;
				}
			}
			if (v[k].size() != 0)
			{
				char c;
				if (k < 10)	c = k + '0';
				else	c = k - 10 + 'a';

				int getState = isRepeated(f);
				if (getState == -1)	//没重复，添加新的状态集
				{
					DSTATE_NUM++;
					for (int m = 0; m < 100; m++)
					{
						if (f[m])
						{
							dstate[DSTATE_NUM].list.push_back(m);
							dstate[DSTATE_NUM].isExist[m] = 1;
							if (state[m].f == -1) dstate[DSTATE_NUM].f = -1;//包含终止状态就是终止状态 
						}
					}
					dstate[i].edge.push_back(Edge{ DSTATE_NUM,c });
				}
				else
				{
					dstate[i].edge.push_back(Edge{ getState,c });
				}

			}
		}
	}
}
void DFAToMFA()
{
	for (int i = 0; i <= DSTATE_NUM; i++)		//遍历输出DFA
	{
		//以是不是终止状态划分
		if (dstate[i].f == 2)
		{
			mstate[0].list.push_back(i);
			mstate[0].isExist[i] = 1;
			mstate[1].list.push_back(i);
			mstate[1].isExist[i] = 1;
			continue;
		}
		if (dstate[i].f == -1)
		{
			mstate[1].list.push_back(i);
			mstate[1].isExist[i] = 1;
		}
		else
		{
			mstate[0].list.push_back(i);
			mstate[0].isExist[i] = 1;
		}

	}
	MSTATE_NUM = 1;
	for (int i = 0; i <= MSTATE_NUM; i++)
	{
		for (int j = 10; j < 12; j++)
		{
			int len = mstate[i].list.size();
			if (len == 1) continue;//单独一个直接跳过 

			char value;
			if (j < 10) value = j + '0';
			else value = j - 10 + 'a';

			vector<int> leftv, rightv;
			int splitState = -1;

			for (int k = 0; k < len; k++)	//遍历状态集中的所有状态 
			{
				int now = mstate[i].list[k];	//当前取出的状态 
				for (int m = 0; m < dstate[now].edge.size(); m++)//遍历该状态的所有边 
				{
					char v = dstate[now].edge[m].value;
					int to = dstate[now].edge[m].to;
					if (value == v)
					{
						if (splitState == -1)
						{
							splitState = to;
							leftv.push_back(now);
						}
						else if (dstate[splitState].f==-1 && dstate[to].f==-1)
						{
							leftv.push_back(now);
						}
						else if (splitState != to)		//可以划分成左右两个 
						{
							rightv.push_back(now);
						}
						else if (splitState == to)
						{
							leftv.push_back(now);
						}
						break;
					}
				}
			}
			if (leftv.size() == 0) continue;	//不用分 
			if (rightv.size() == 0) continue; 	//不用分
			while (!mstate[i].list.empty())//清空当前 
			{
				mstate[i].isExist[mstate[i].list.back()];
				mstate[i].list.pop_back();
			}
			for (int k = 0; k < leftv.size(); k++)
			{
				int news = leftv[k];
				mstate[i].list.push_back(news);
				mstate[i].isExist[news] = 1;
			}
			MSTATE_NUM++;
			for (int k = 0; k < rightv.size(); k++)
			{
				int news = rightv[k];
				mstate[MSTATE_NUM].list.push_back(news);
				mstate[MSTATE_NUM].isExist[news] = 1;
			}
		}
	}
	int DFA_map[100] = { 0 };//存储DFA的某个状态位于MFA的第几个状态集 
	for (int i = 0; i <= MSTATE_NUM; i++)
	{
		for (int j = 0; j < mstate[i].list.size(); j++)
		{
			int nows = mstate[i].list[j];
			DFA_map[nows] = i;
			if (dstate[nows].f == 1 || dstate[nows].f == 2) mstate[i].f = dstate[nows].f;
			if (dstate[nows].f == -1 || dstate[nows].f == 2) mstate[i].f = dstate[nows].f;
		}
	}
	for (int i = 0; i <= MSTATE_NUM; i++)
	{
		int nows = mstate[i].list[0];//取第一个作为代表 
		for (int j = 0; j < dstate[nows].edge.size(); j++)
		{
			char value = dstate[nows].edge[j].value;
			int to = dstate[nows].edge[j].to;
			int p = DFA_map[to];//得到to在MFA中的位置
			mstate[i].edge.push_back(Edge{ p,value });
		}
	}
}
int main()
{
	string str;
	vector<string> s;
	cout << "请输入正则表达式:";
	cin>>str;
	//	str="(a|b)*a(a|b)";			//给出要转换的正则表达式 
//	str = "(a|b)a(a|b|c)*";
//	str = "a((a|b)*|ab*a)*b"; //a((a|b)*|ab*a)*b


	state[0].f = 1;//开始状态
	state[1].f = -1;//终止状态 
	ZZToNFA(str, 0, 1, s);	//转换函数


	cout << "——————NFA——————" << endl;
	for (int i = 0; i <= STATE_NUM; i++)		//遍历输出NFA
	{
		cout << "状态：" << i;
		if (state[i].f == 1) cout << "——初始状态——";
		if (state[i].f == -1) cout << "——终止状态——";
		cout << endl;
		for (int j = 0; j < state[i].edge.size(); j++)
		{
			cout << i << "  —" << state[i].edge[j].value << "—>  " << state[i].edge[j].to << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "——————DFA——————" << endl;
	NFAToDFA();
	for (int i = 0; i <= DSTATE_NUM; i++)		//遍历输出DFA
	{
		cout << "状态：" << i << "——";
		if (dstate[i].f == 1 || dstate[i].f == 2) cout << "初始状态( ";
		else if (dstate[i].f == -1 || dstate[i].f == 2) cout << "终止状态( ";
		else cout << "(";
		for (int j = 0; j < dstate[i].list.size(); j++)
		{
			cout << dstate[i].list[j] << " ";
		}
		cout << ")" << endl;
		for (int j = 0; j < dstate[i].edge.size(); j++)
		{
			cout << i << "  —" << dstate[i].edge[j].value << "—>  " << dstate[i].edge[j].to << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "——————MFA——————" << endl;
	DFAToMFA();
	for (int i = 0; i <= MSTATE_NUM; i++)		//遍历输出DFA
	{
		cout << "状态：" << i << "——";
		if (mstate[i].f == 1 || mstate[i].f == 2) cout << "初始状态( ";
		else if (mstate[i].f == -1 || mstate[i].f == 2) cout << "终止状态( ";
		else cout << "(";
		for (int j = 0; j < mstate[i].list.size(); j++)
		{
			cout << mstate[i].list[j] << " ";
		}
		cout << ")" << endl;
		for (int j = 0; j < mstate[i].edge.size(); j++)
		{
			cout << i << "  —" << mstate[i].edge[j].value << "—>  " << mstate[i].edge[j].to << endl;
		}
		cout << endl;
	}


	ofstream outfile_NFA("./NFA.txt");
	outfile_NFA << STATE_NUM << endl;
	for (int i = 0; i <= STATE_NUM; i++)
	{
		outfile_NFA << i << "," << state[i].f << endl;
	}
	for (int i = 0; i <= STATE_NUM; i++)		//遍历输出NFA
	{
		for (int j = 0; j < state[i].edge.size(); j++)
		{
			outfile_NFA << i << "," << state[i].edge[j].to << "," << state[i].edge[j].value << endl;
		}
	}

	ofstream outfile_DFA("./DFA.txt");
	outfile_DFA << DSTATE_NUM << endl;
	for (int i = 0; i <= DSTATE_NUM; i++)
	{
		outfile_DFA << i << "," << dstate[i].f << endl;
	}
	for (int i = 0; i <= DSTATE_NUM; i++)		//遍历输出NFA
	{
		for (int j = 0; j < dstate[i].edge.size(); j++)
		{
			outfile_DFA << i << "," << dstate[i].edge[j].to << "," << dstate[i].edge[j].value << endl;
		}
	}

	ofstream outfile_MFA("./MFA.txt");
	outfile_MFA << MSTATE_NUM << endl;
	for (int i = 0; i <= MSTATE_NUM; i++)
	{
		outfile_MFA << i << "," << mstate[i].f << endl;
	}
	for (int i = 0; i <= MSTATE_NUM; i++)		//遍历输出NFA
	{
		for (int j = 0; j < mstate[i].edge.size(); j++)
		{
			outfile_MFA << i << "," << mstate[i].edge[j].to << "," << mstate[i].edge[j].value << endl;
		}
	}

	outfile_NFA.close();
	outfile_DFA.close();
	outfile_MFA.close();
	return 0;
}
