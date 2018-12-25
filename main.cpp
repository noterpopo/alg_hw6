// AlgHw6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <regex>
#include <map>

#define MAX_W 1000
#define MAX_PN 2000000

using namespace std;
class Edge
{
public:
	int sp;
	int ep;
	int max_weighe;
	int cur_weight;
	Edge() {}
	Edge(int s, int e, int mw,int cw)
	{
		sp = s;
		ep = e;
		max_weighe = mw;
		cur_weight=cw;
	}
};
vector<Edge> edges;
vector<int> G[MAX_PN];
int a[MAX_PN];
int p[MAX_PN];

void init(int PN)
{
    for(int i=0;i<PN;++i)
    {
        G[i].clear();
    }
    edges.clear();
}
void addEdge(int sp,int ep,int we)
{
    edges.push_back(Edge(sp,ep,we,0));
    edges.push_back(Edge(ep,sp,0,0));
    G[sp].push_back(edges.size()-2);
    G[ep].push_back(edges.size()-1);
}

int findMaxFlow(int sp,int ep)
{
    int flow=0;
    while (true)
    {
        memset(a,0, sizeof(a));
        queue<int> Q;
        Q.push(sp);
        a[sp]=MAX_W;
        while(!Q.empty())
        {
            int x=Q.front();
            Q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge& e=edges[G[x][i]];
                if(!a[e.ep]&&e.max_weighe>e.cur_weight)
                {
                    p[e.ep]=G[x][i];
                    a[e.ep]=min(a[x],e.max_weighe-e.cur_weight);
                    Q.push(e.ep);
                }
            }
            if(a[ep])
                break;
        }
        if(!a[ep])
            break;
        for(int i=ep;i!=sp;i=edges[p[i]].sp)
        {
            edges[p[i]].cur_weight+=a[ep];
            edges[p[i]^1].cur_weight-=a[ep];
        }
        flow+=a[ep];
    }
    return flow;
}

int maxFlow = 0;


void initC(int &PN, int &EN, int type);

int main() {
	int num = 0, type = 0;
	int PN, EN;
	cin >> num;
	for (int q = 1; q <= num; ++q)
	{
		maxFlow = 0;
		cin >> type;
		srand((unsigned)time(NULL));
		initC(PN, EN, type);
		time_t start, finish;

		//randomInput(C, N);

		time(&start);
		maxFlow=findMaxFlow(0,PN-1);
		time(&finish);

		double duration = double(finish - start) / CLOCKS_PER_SEC;
		cout << "Case " << q << ": " << maxFlow << endl;
		cout << "需要时间为:" << duration << "s" << endl;

	}
	return 0;
}

void initC(int &PN, int &EN, int type)
{
	regex numR("[0-9]+");
	if (type == 1 || type == 2)
	{
		cin >> PN >> EN;
	}
	else
	{
		ifstream infile;
		infile.open("C:\\Users\\popo\\CLionProjects\\alg-hw6\\roadNet-CA.txt");
		if (!infile)
		{
			cout << "Error opening " << endl;
			exit(-1);
		}
		string line = "";
		getline(infile, line);
		bool flag = true;
		for (sregex_token_iterator it(line.begin(), line.end(), numR), end; it != end; it++) {
			if (flag)
			{
				flag = !flag;
				PN = atoi(it->str().c_str());
			}
			else
			{
				flag = !flag;
				EN = atoi(it->str().c_str());
			}
		}
		cout << PN << " " << EN << endl;

		infile.close();
	}

	init(PN);
	switch (type)
	{
	case 1:
	{
		for (int i = 0; i < EN; ++i)
		{
			int sp, ep, w;
			cin >> sp >> ep >> w;
			addEdge(sp-1,ep-1,w);
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < EN; ++i)
		{
			int sp, ep, w;
			sp = rand() % PN;
			ep = rand() % PN;
			if (sp == ep)
			{
				i--;
				continue;
			}
			w = (rand() % (MAX_W - 1)) + 1;
            addEdge(sp,ep,w);
		}
		break;
	}
	case 3:
	{
		ifstream infile;
		infile.open("C:\\Users\\popo\\CLionProjects\\alg-hw6\\roadNet-CA.txt");
		string line = "";
		int count = 0;
		time_t start, finish;
		time(&start);
		while (getline(infile, line))
		{
			int sp, ep;
			infile >> sp >> ep;
            addEdge(sp,ep,1);

		}
		time(&finish);
		cout << finish - start << endl;
		infile.close();
		break;
	}
	default:
		break;

	}
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
