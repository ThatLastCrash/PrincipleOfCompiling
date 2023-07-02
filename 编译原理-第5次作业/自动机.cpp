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
	int no;				//״̬����� 
	vector<Edge> edge;	//�� 
	vector<int> Estate;	//һ��������ձ��ܵ����״̬�� 
	bool isExist[100];
	int f;				//0Ϊ��ʼ��1Ϊ��ֹ 
}State;
State state[STATE_LEN];

typedef struct DState	//DFA
{
	vector<int> list;	//״̬��,��NFA�е�״̬ 
	bool isExist[100];
	vector<Edge> edge;	//�� 
	int f;				//0Ϊ��ʼ��1Ϊ��ֹ 
}DState;
DState dstate[DSTATE_LEN];

typedef struct MState	//MFA
{
	vector<int> list;	//״̬������DFA�е�״̬ 
	bool isExist[100];
	vector<Edge> edge;	//�� 
	int f;				//0Ϊ��ʼ��1Ϊ��ֹ 
}MState;
MState mstate[MSTATE_LEN];


bool isLetterOrNum(char c)			//�ж��ǲ��ǺϷ��ģ����ֻ���ĸ 
{
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= '0' && c <= '9') return true;
	return false;
}
void ChangeEnd(int end, int k)//ԭ������ָ��end�Ķ��ĳ�ָ��k 
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
					string news = s.substr(left + 1, right - left);//ȥ������ 
					str.push_back(news);
				}
			}
		}
		else if (cnt == 0)
		{
			if (isLetterOrNum(s[i]))
			{
				if (i + 1 <= to && s[i + 1] == '*')//�����ַ��հ� 
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
void ConnectZZ(int left, int right, int start, int end, vector<string> &str)//��str��left��right�������� 
{
	int startstate = start, endstate = end;
	for (int i = left; i <= right; i++)
	{
		int size = str[i].size();
		if (size == 1)//�����ַ� 
		{
			char value = str[i][0];


			if (i == right) endstate = end;	//��������һ��������״̬Ӧ����end������Ϊ������״̬ 
			else
			{
				STATE_NUM++;
				endstate = STATE_NUM;
			}

			state[startstate].edge.push_back(Edge{ endstate,value });
			startstate = STATE_NUM;
		}
		else if (str[i][size - 1] == '*')//�Ǳհ� 
		{
			STATE_NUM++;
			state[startstate].edge.push_back(Edge{ STATE_NUM,'#' });//��һ���ձ�
			startstate = STATE_NUM;
			vector<string> newstr;
			string news = "";
			if (str[i][0] == '(') news = str[i].substr(1, size - 3);//ȡ�հ��ڲ��Ķ��� 
			else news = str[i].substr(0, size - 1);//ȡ�հ��ڲ��Ķ��� 
			ZZToNFA(news, STATE_NUM, STATE_NUM, newstr);//�����ַ������д���,���ַ�����ʼ��ֹ��Ϊ������״̬

			if (i == right)
			{
				endstate = end;	//��������һ��������״̬Ӧ����end������������һ��״̬ 
			}
			else
			{
				STATE_NUM++;
				endstate = STATE_NUM;
			}
			state[startstate].edge.push_back(Edge{ endstate,'#' });//��һ���ձ�

			startstate = endstate;
		}
		else
		{

			if (i == right) endstate = end;	//��������һ��������״̬Ӧ����end������Ϊ������״̬ 
			else
			{
				STATE_NUM++;
				endstate = STATE_NUM;
			}

			vector<string> newstr;
			ZZToNFA(str[i], startstate, endstate, newstr);//�����ַ������д��� 
			startstate = STATE_NUM;
		}
	}
}
void OrZZ(string str, int start, int end)
{
	int startstate = start, endstate = end;
	int size = str.size();
	if (size == 1)//�����ַ� 
	{
		char value = str[0];
		state[startstate].edge.push_back(Edge{ endstate,value });
	}
	else if (str[size - 1] == '*')//�Ǳհ� 
	{
		STATE_NUM++;
		state[startstate].edge.push_back(Edge{ STATE_NUM,'#' });//��һ���ձ�

		vector<string> newstr;
		string news = "";
		if (str[0] == '(') news = str.substr(1, size - 3);//ȡ�հ��ڲ��Ķ��� 
		else news = str.substr(0, size - 1);//ȡ�հ��ڲ��Ķ��� 

		ZZToNFA(news, STATE_NUM, STATE_NUM, newstr);//�����ַ������д���,���ַ�����ʼ��ֹ��Ϊ������״̬

		state[STATE_NUM].edge.push_back(Edge{ endstate,'#' });//��һ���ձ�

	}
	else
	{
		vector<string> newstr;
		ZZToNFA(str, startstate, endstate, newstr);//�����ַ������д��� 
	}
}
//(a|b)(a|b|c)*
void ZZToNFA(string s, int start, int end, vector<string> &str)	//ת������
{
	int left = 0, right = 0;
	SplitZZ(s, str);//�Ȼ���
	for (int i = 0; i < str.size(); i++)//�����Ӻ�� 
	{
		if (str[i] == "|")
		{
			right = i - 1;
			if (left != right)//��Ҫ���� 
			{
				ConnectZZ(left, right, start, end, str);
			}
			else//ֻ��һ����ֱ�ӻ�
			{
				OrZZ(str[left], start, end);
			}
			left = i + 1;
		}
		else if (i + 1 == str.size())//���һ�� 
		{
			right = i;
			if (left != right)//��Ҫ���� 
			{
				ConnectZZ(left, right, start, end, str);
			}
			else//ֻ��һ����ֱ�ӻ�
			{
				OrZZ(str[left], start, end);
			}
		}
	}
}
int isRepeated(bool f[])	//�ж�֮ǰ��״̬���Ƿ��Ѿ����� 
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
	for (int k = 0; k <= STATE_NUM; k++)		//Ԥ����ÿ��״̬����һ��������ձ��ܵ����״̬ 
	{
		vector<int> v;
		v.push_back(k);
		for (int j = 0; j < v.size(); j++)
		{
			int now = v[j];
			for (int i = 0; i < state[now].edge.size(); i++)	//�ѵ�ǰ״̬�����пձ߼ӽ��� 
			{
				char value = state[now].edge[i].value;
				int to = state[now].edge[i].to;
				bool isExist = state[k].isExist[to];
				if (value == '#' && isExist == 0)	//�����ڣ����ǿձ߾ͼ��� 
				{
					v.push_back(to);
					state[k].Estate.push_back(to);
					state[k].isExist[to] = 1;	//��Ǵ��ڣ���¼��ǰ״̬���ж�����Щ״̬ 
				}
			}
		}

	}
	
	dstate[DSTATE_NUM].list.push_back(0);	//��ʼ״̬Ϊ0������
	dstate[DSTATE_NUM].isExist[0] = 1;	//��Ǵ���
	dstate[DSTATE_NUM].f = 1;				//��ʼ״̬ 
	for (int i = 0; i < state[0].Estate.size(); i++)
	{
		int nstate = state[0].Estate[i];
		dstate[DSTATE_NUM].list.push_back(nstate);//��ʼ״̬�� 
		dstate[DSTATE_NUM].isExist[nstate] = 1;
		if (state[nstate].f == -1)
		{
			dstate[DSTATE_NUM].f = 2;	//���⣬���ǿ�ʼ������ֹ 
		}
	}

	for (int i = 0; i <= DSTATE_NUM; i++)	//���� 
	{
		vector<vector<int> > v(40, vector<int>(0, 0));	// 10������26����ĸ 
		for (int j = 0; j < dstate[i].list.size(); j++)	//������ǰ״̬�� 
		{
			int now = dstate[i].list[j]; 				//ȡ�����е�һ��״̬ 
			for (int k = 0; k < state[now].edge.size(); k++)	//������ǰ״̬�ıߣ������ַ����Ӧ������״̬������ 
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

		//����������״̬�����ظ��ľͲ���
		bool f[100] = { 0 };
		for (int k = 0; k < 36; k++)
		{
			for (int m = 0; m < 100; m++) f[m] = 0;
			for (int m = 0; m < v[k].size(); m++)
			{
				int s = v[k][m];
				f[s] = 1;
				for (int p = 0; p < state[s].Estate.size(); p++)//��s�ܾ����ձߵ����״̬���ӽ��� 
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
				if (getState == -1)	//û�ظ�������µ�״̬��
				{
					DSTATE_NUM++;
					for (int m = 0; m < 100; m++)
					{
						if (f[m])
						{
							dstate[DSTATE_NUM].list.push_back(m);
							dstate[DSTATE_NUM].isExist[m] = 1;
							if (state[m].f == -1) dstate[DSTATE_NUM].f = -1;//������ֹ״̬������ֹ״̬ 
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
	for (int i = 0; i <= DSTATE_NUM; i++)		//�������DFA
	{
		//���ǲ�����ֹ״̬����
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
			if (len == 1) continue;//����һ��ֱ������ 

			char value;
			if (j < 10) value = j + '0';
			else value = j - 10 + 'a';

			vector<int> leftv, rightv;
			int splitState = -1;

			for (int k = 0; k < len; k++)	//����״̬���е�����״̬ 
			{
				int now = mstate[i].list[k];	//��ǰȡ����״̬ 
				for (int m = 0; m < dstate[now].edge.size(); m++)//������״̬�����б� 
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
						else if (splitState != to)		//���Ի��ֳ��������� 
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
			if (leftv.size() == 0) continue;	//���÷� 
			if (rightv.size() == 0) continue; 	//���÷�
			while (!mstate[i].list.empty())//��յ�ǰ 
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
	int DFA_map[100] = { 0 };//�洢DFA��ĳ��״̬λ��MFA�ĵڼ���״̬�� 
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
		int nows = mstate[i].list[0];//ȡ��һ����Ϊ���� 
		for (int j = 0; j < dstate[nows].edge.size(); j++)
		{
			char value = dstate[nows].edge[j].value;
			int to = dstate[nows].edge[j].to;
			int p = DFA_map[to];//�õ�to��MFA�е�λ��
			mstate[i].edge.push_back(Edge{ p,value });
		}
	}
}
int main()
{
	string str;
	vector<string> s;
	cout << "������������ʽ:";
	cin>>str;
	//	str="(a|b)*a(a|b)";			//����Ҫת����������ʽ 
//	str = "(a|b)a(a|b|c)*";
//	str = "a((a|b)*|ab*a)*b"; //a((a|b)*|ab*a)*b


	state[0].f = 1;//��ʼ״̬
	state[1].f = -1;//��ֹ״̬ 
	ZZToNFA(str, 0, 1, s);	//ת������


	cout << "������������NFA������������" << endl;
	for (int i = 0; i <= STATE_NUM; i++)		//�������NFA
	{
		cout << "״̬��" << i;
		if (state[i].f == 1) cout << "������ʼ״̬����";
		if (state[i].f == -1) cout << "������ֹ״̬����";
		cout << endl;
		for (int j = 0; j < state[i].edge.size(); j++)
		{
			cout << i << "  ��" << state[i].edge[j].value << "��>  " << state[i].edge[j].to << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "������������DFA������������" << endl;
	NFAToDFA();
	for (int i = 0; i <= DSTATE_NUM; i++)		//�������DFA
	{
		cout << "״̬��" << i << "����";
		if (dstate[i].f == 1 || dstate[i].f == 2) cout << "��ʼ״̬( ";
		else if (dstate[i].f == -1 || dstate[i].f == 2) cout << "��ֹ״̬( ";
		else cout << "(";
		for (int j = 0; j < dstate[i].list.size(); j++)
		{
			cout << dstate[i].list[j] << " ";
		}
		cout << ")" << endl;
		for (int j = 0; j < dstate[i].edge.size(); j++)
		{
			cout << i << "  ��" << dstate[i].edge[j].value << "��>  " << dstate[i].edge[j].to << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "������������MFA������������" << endl;
	DFAToMFA();
	for (int i = 0; i <= MSTATE_NUM; i++)		//�������DFA
	{
		cout << "״̬��" << i << "����";
		if (mstate[i].f == 1 || mstate[i].f == 2) cout << "��ʼ״̬( ";
		else if (mstate[i].f == -1 || mstate[i].f == 2) cout << "��ֹ״̬( ";
		else cout << "(";
		for (int j = 0; j < mstate[i].list.size(); j++)
		{
			cout << mstate[i].list[j] << " ";
		}
		cout << ")" << endl;
		for (int j = 0; j < mstate[i].edge.size(); j++)
		{
			cout << i << "  ��" << mstate[i].edge[j].value << "��>  " << mstate[i].edge[j].to << endl;
		}
		cout << endl;
	}


	ofstream outfile_NFA("./NFA.txt");
	outfile_NFA << STATE_NUM << endl;
	for (int i = 0; i <= STATE_NUM; i++)
	{
		outfile_NFA << i << "," << state[i].f << endl;
	}
	for (int i = 0; i <= STATE_NUM; i++)		//�������NFA
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
	for (int i = 0; i <= DSTATE_NUM; i++)		//�������NFA
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
	for (int i = 0; i <= MSTATE_NUM; i++)		//�������NFA
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
