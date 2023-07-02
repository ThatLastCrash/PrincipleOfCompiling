#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>
#include<fstream>
#define RULE_NUM 5
#define VT_NUM 6
#define VN_NUM 5
using namespace std;

map<string, bool> VT_list;
map<string, bool> VN_list;
map<string, map<string, bool> > first, follow;
map<string, map<string, string> > plist;

typedef struct Rule
{
	string from;
	vector<string> to;
}Rule;
Rule rule[RULE_NUM];

bool AddFirstList(string from, string to)	//把to的first集中所有非空加入from的first集 
{
	int index = 0;
	string X = "";
	bool hasK = 1;
	bool isChanged = 0;
	while (index < to.length() && hasK == 1)
	{
		hasK = 0;
		X = "";
		string s = "";
		s.push_back(to[index]);
		if (VN_list.count(s) == 1)	//开头的这个是非终结符 
		{
			X.push_back(to[index]);
			if (index + 1 < to.length() && to[index + 1] == 1)//是E1或T1 
			{
				X.push_back(to[index + 1]);
				index++;
			}
			map<string, bool>::iterator it;
			for (it = first[X].begin(); it != first[X].end(); it++) {	//将X1……Xj的非空元素加入first[from] 
				string s = it->first;
				if (s == "@")
				{
					if (index == to.length() - 1) {
						if (first[from].count("@") == 0)
						{
							first[from].insert({ "@",1 });//最后一个，加入空
							isChanged = 1;
						}
					}
					hasK = 1;//有空，继续下一个非终结符 
				}
				else
				{
					if (first[from].count(s) == 0)
					{
						first[from].insert({ s,1 });
						isChanged = 1;
					}
				}
			}

		}
		index++;
	}
	return isChanged;
}
bool AddFollowList(string from, string to)//把to的first集中所有非空加入from的follow集 
{
	int index = 0;
	bool isChanged = 0;
	for (int i = 0; i < to.length(); i++)
	{
		string s(1, to[i]);
		if (VT_list.count(s) == 1)
		{
			if (follow[from].count(s) == 0)
			{
				follow[from].insert({ s,1 });
				isChanged = 1;
			}
			return isChanged;
		}
		else	//非终结符 
		{
			map<string, bool>::iterator it;
			bool f = 0;
			for (it = first[s].begin(); it != first[s].end(); it++) {	//将s的first元素加入follow(from) 
				string v = it->first;
				if (follow[from].count(v) == 0 && v != "@")
				{
					follow[from].insert({ v,1 });
					isChanged = 1;
				}
				if (v == "@")//有空 
				{
					f = 1;
				}
			}
			if (f == 0) return isChanged;//没有空就结束 
		}
	}
	return isChanged;
}
bool getK(string to)	//to能否得到一个空 
{
	int index = 0;
	while (index < to.length())
	{
		string v(1, to[index]);
		if (first.count(v) == 0 || (first.count(v) == 1 && first[v].count("@") == 0))//有一个不能，直接退出 
		{
			return 0;
		}
		index++;
	}
	return 1;
}
bool AddFollow(string to, string from)
{
	bool isChanged = 0;
	map<string, bool>::iterator it;
	for (it = follow[from].begin(); it != follow[from].end(); it++) {	//将from的follow元素加入follow(to) 
		string s = it->first;
		if (follow[to].count(s) == 0 && s != "@")
		{
			follow[to].insert({ s,1 });
			isChanged = 1;
		}
	}
	return isChanged;
}
void getFirst()
{
	bool isChanged = 1;
	while (isChanged)
	{
		isChanged = 0;
		for (int i = 0; i < RULE_NUM; i++)
		{
			string from = rule[i].from;
			if (VT_list.count(from) == 1)
			{
				if (first[from].count(from) == 0)
				{
					isChanged = 1;
					first[from].insert({ from,1 }); // 1
				}
			}
			else if (VN_list.count(from) == 1)
			{
				for (int j = 0; j < rule[i].to.size(); j++)
				{
					string to = rule[i].to[j];
					if (to == "@")	//将这个@符号当成空 
					{
						if (first[from].count(to) == 0)
						{
							isChanged = 1;
							first[from].insert({ to,1 }); // 3,将空加入first 
						}
					}
					else if (VT_list.count(string(1, to[0])) == 1)	// 2, to[0]加入first 
					{
						if (first[from].count(string(1, to[0])) == 0)
						{
							isChanged = 1;
							first[from].insert({ string(1,to[0]),1 });
						}
					}
					else
					{
						isChanged = AddFirstList(from, to) ? 1 : isChanged;	// 4, X->X1X2X3…… 
					}
				}
			}

		}
	}
}
void getFollow()
{
	bool isChanged = 1;
	follow["E"].insert({ "#",1 });
	while (isChanged)
	{
		isChanged = 0;
		for (int i = 0; i < RULE_NUM; i++)
		{
			string from = rule[i].from;
			for (int j = 0; j < rule[i].to.size(); j++)
			{
				string to = rule[i].to[j];
				for (int k = 0; k < to.length(); k++)
				{
					string s(1, to[k]);
					if (VN_list.count(s) == 1)	//找到一个非终结符 
					{
						string list = to.substr(k + 1, to.length() - k - 1);
						if (k + 1 != to.length()) //步骤2
						{
							isChanged = AddFollowList(s, list) ? 1 : isChanged;
							if (getK(list) == 1)
							{
								isChanged = AddFollow(s, from) ? 1 : isChanged;
							}
						}
						else	//步骤3 
						{
							isChanged = AddFollow(s, from) ? 1 : isChanged;
						}
					}
				}
			}
		}
	}
}
void Init()
{
	VT_list.insert({ "i",1 });
	VT_list.insert({ "+",1 });
	VT_list.insert({ "*",1 });
	VT_list.insert({ "(",1 });
	VT_list.insert({ ")",1 });
	VT_list.insert({ "#",1 });

	VN_list.insert({ "E",1 });
	VN_list.insert({ "G",1 });
	VN_list.insert({ "T",1 });
	VN_list.insert({ "H",1 });
	VN_list.insert({ "F",1 });

	//VT_list.insert({ "I",1 });
	//VT_list.insert({ "+",1 });
	//VT_list.insert({ "-",1 });
	//VT_list.insert({ "/",1 });
	//VT_list.insert({ "*",1 });
	//VT_list.insert({ "(",1 });
	//VT_list.insert({ ")",1 });
	//VT_list.insert({ "#",1 });

	//VN_list.insert({ "E",1 });
	//VN_list.insert({ "G",1 });
	//VN_list.insert({ "T",1 });
	//VN_list.insert({ "H",1 });
	//VN_list.insert({ "F",1 });
	//VN_list.insert({ "A",1 });
	//VN_list.insert({ "M",1 });
	//构建预测分析表
	map<string, bool>::iterator it, itt;
	for (it = VN_list.begin(); it != VN_list.end(); it++)
	{
		string r = it->first;
		for (itt = VT_list.begin(); itt != VT_list.end(); itt++)
		{
			string l = itt->first;
			plist[r].insert({ l,"" });
		}
	}

	ifstream infile;
	infile.open("data.txt", ios::in);
	if (!infile.is_open())
	{
		cout << "读取文件失败" << endl;
		return;
	}
	string line = "";
	int num = 0;
	while (getline(infile, line))
	{
		int index = line.find("->");
		rule[num].from = line.substr(0, index);
		line = line.substr(index + 2);
		string s = "";
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '|' || i == line.length() - 1)
			{
				if (i == line.length() - 1) s.push_back(line[i]);
				rule[num].to.push_back(s);
				s = "";
			}
			else
			{
				s.push_back(line[i]);
			}
		}
		cout << rule[num].from << " -> ";
		for (int i = 0; i < rule[num].to.size(); i++)
		{
			cout << rule[num].to[i] << " | ";
		}
		cout << endl;
		num++;
	}
	infile.close();
}
bool FirstToPrdList(string from, string to)
{
	bool hasK = 0;
	if (to == "@") return 1;
	for (int i = 0; i < to.length(); i++)
	{
		hasK = 0;
		string s(1, to[i]);
		if (VT_list.count(s) == 1)
		{
			plist[from][s] = from + "->" + to;
			return 0;
		}
		map<string, bool>::iterator it;
		for (it = first[s].begin(); it != first[s].end(); it++)
		{
			string op = it->first;
			if (op == "@") hasK = 1;
			plist[from][op] = from + "->" + to;
		}
		if (hasK == 0) return 0;//不能得到空
	}
	return 1;
}
void FollowToPrdList(string from)
{
	map<string, bool>::iterator it;
	for (it = follow[from].begin(); it != follow[from].end(); it++)
	{
		string s = it->first;
		plist[from][s] = from + "->@";
	}
}
void getPrdList()
{
	for (int i = 0; i < RULE_NUM; i++)
	{
		string from = rule[i].from;
		vector<string> to = rule[i].to;
		for (int j = 0; j < to.size(); j++)
		{
			string s = to[j];
			bool hasK = FirstToPrdList(from, s);
			if (hasK == 1)//用follow
			{
				FollowToPrdList(from);
			}
		}
	}
}
void Error()
{
	cout << "错误" << endl;
}
bool doJudge(string str)
{
	str += "#";
	stack<string> st;
	st.push("#"); st.push("E");
	for (int i = 0; i < str.length(); i++)
	{
		string in(1, str[i]);
		if (str[i] <= '9' && str[i] >= '0') in = "i";
		string tp = st.top();
		st.pop();
		while (VN_list.count(tp) == 1 || tp == "@")
		{
			if (tp == "@")
			{
				tp = st.top();
				st.pop();
				continue;
			}
			string s = plist[tp][in];
			for (int i = s.length() - 1; i >= 0; i--)
			{
				if (s[i] == '>')break;
				st.push(string(1, s[i]));
			}
			tp = st.top();
			st.pop();
		}
		if (VT_list.count(tp) == 1)
		{
			if (tp == in) continue;
			else
			{
				return 0;
			}
		}
	}
	if (st.empty()) return 1;
	else return 0;
}
void doSolve()
{
	ifstream fin;
	fin.open("in.txt", ios::in);
	string str = "";
	while (getline(fin, str))
	{
		cout << str << endl;
		bool f = doJudge(str);
		if (f)
		{
			cout << "正确" << endl;
		}
		else
		{
			Error();
		}
	}
}
int main()
{
	Init();
	getFirst();
	getFollow();
	getPrdList();
	map<string, map<string, bool> >::iterator it;
	map<string, bool>::iterator itt;
	cout << "————————————————————————" << endl;
	for (it = first.begin(); it != first.end(); it++)
	{
		map<string, bool> m;
		m = it->second;
		cout << "First(" << it->first << ")=";
		cout << "{ ";
		for (itt = m.begin(); itt != m.end(); itt++) {
			cout << itt->first << ", ";
		}
		cout << "}" << endl;
	}
	cout << "————————————————————————" << endl;
	for (it = follow.begin(); it != follow.end(); it++)
	{
		map<string, bool> m;
		m = it->second;
		cout << "Follow(" << it->first << ")=";
		cout << "{ ";
		for (itt = m.begin(); itt != m.end(); itt++) {
			cout << itt->first << ", ";
		}
		cout << "}" << endl;
	}
	cout << "————————————————————————" << endl;
	printf("          ");
	for (itt = VT_list.begin(); itt != VT_list.end(); itt++) {
		//printf("%10s", itt->first);
		string s = itt->first;
		printf("%10s", s.c_str());
	}
	cout << endl;
	map<string, map<string, string> >::iterator iter;
	map<string, string>::iterator iterr;
	for (iter = plist.begin(); iter != plist.end(); iter++)
	{
		map<string, string> m;
		m = iter->second;
		printf("%10s", iter->first.c_str());
		for (iterr = m.begin(); iterr != m.end(); iterr++) {
			printf("%10s", iterr->second.c_str());
		}
		cout << endl;
	}
	cout << "————————————————————————" << endl;
	doSolve();
	return 0;
}