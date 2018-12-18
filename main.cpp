#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <regex>

#define MAX_W 1000

using namespace std;

int maxFlow = 0;

int **C, **F;
struct Node {
    int inedx;
    Node* parent;
};
struct Edge {
    int sp;
    int ep;
};
void initC(int &PN,int &EN,int type);
Node* bfs(int N);
void updateCF(int N, Node* result);

int main() {
    int num=0,type=0;
    int PN,EN;
    cin>>num;
    for(int q=1;q<=num;++q)
    {
        maxFlow=0;
        cin>>type;
        srand((unsigned)time(NULL));
        initC(PN,EN,type);
        clock_t start, finish;

        //randomInput(C, N);

        start = clock();
        while (1) {
            Node* nodeList = bfs(PN);
            if (nodeList == NULL)
                break;
            updateCF(PN, nodeList);
        }
        finish = clock();

        double duration = double(finish - start) / CLOCKS_PER_SEC;
        cout<<"Case "<<q<<": "<<maxFlow<<endl;
        cout << "需要时间为:" << duration << "s" << endl;
        for (int i=0; i<PN; ++i)
        {
            delete [] C[i];
            delete [] F[i];
        }
        delete [] C;
        delete [] F;

    }
    return 0;
}

Node* bfs(int N) {
    Node* nodeList = new Node[N];
    int* visited = new int[N];
    for (int i=0; i<N; ++i) {
        nodeList[i].inedx = i;
        nodeList[i].parent = NULL;
        visited[i] = 0;
    }
    queue<Node> que;
    que.push(nodeList[0]);
    visited[0] = 1;
    while(!que.empty()) {
        Node node = que.front();
        int idx = node.inedx;
        que.pop();
        for (int j=1; j<N; j++) {
            if (C[idx][j] == 0) continue;
            if (visited[j]) continue;
            visited[j] = 1;
            nodeList[j].parent = &nodeList[idx];
            que.push(nodeList[j]);
            if (j == N-1) {
                delete [] visited;
                return nodeList;
            }
        }
    }
    delete [] nodeList;
    delete [] visited;
    return NULL;
}

void updateCF(int N, Node* result) {
    stack<Edge> path;
    int cfp = MAX_W;
    int idx = N-1;
    while(result[idx].parent) {
        Edge eg;
        eg.ep = idx;
        eg.sp = result[idx].parent->inedx;
        if (C[eg.sp][eg.ep] < cfp)
            cfp = C[eg.sp][eg.ep];
        path.push(eg);
        idx = result[idx].parent->inedx;
    }
    while (!path.empty()) {
        Edge eg = path.top();
        F[eg.sp][eg.ep] += cfp;
        C[eg.sp][eg.ep] -= cfp;
        C[eg.ep][eg.sp] += cfp;
        path.pop();
    }
    maxFlow += cfp;
    delete [] result;

}

void initC(int &PN,int &EN,int type)
{
    regex numR("[0-9]+");
    if(type==1||type==2)
    {
        cin >> PN>>EN;
    } else
    {
        ifstream infile;
        infile.open("C:\\Users\\popo\\CLionProjects\\alg-hw6\\roadNet-CA.txt");
        if ( !infile )
        {
            cout <<  "Error opening "<< endl;
            exit(- 1 );
        }
        string line="";
        getline(infile,line);
        bool flag= true;
        for(sregex_token_iterator it(line.begin(),line.end(),numR),end;it != end;it++){
            if(flag)
            {
                flag=!flag;
                PN=atoi(it->str().c_str());
            }
            else
            {
                flag=!flag;
                EN=atoi(it->str().c_str());
            }
        }
        cout<<PN<<EN<<endl;

        infile.close();
    }

    C = new int*[PN];
    F = new int*[PN];
    for (int i=0; i<PN; ++i)
    {
        C[i] = new int[PN];
        F[i] = new int[PN];
    }
    for (int i=0; i<PN; ++i)
    {
        for (int j=0; j<PN; ++j)
        {
            C[i][j] = 0;
            F[i][j] = 0;
        }
    }
    switch (type)
    {
        case 1:
        {
            for(int i=0;i<EN;++i)
            {
                int sp, ep, w;
                cin >> sp >> ep >> w;
                C[sp-1][ep-1] += w;
            }
            break;
        }
        case 2:
        {
            for(int i=0;i<EN;++i)
            {
                int sp,ep,w;
                sp=rand()%PN;
                ep=rand()%PN;
                if(sp==ep)
                {
                    i--;
                    continue;
                }
                w=(rand()%(MAX_W-1))+1;
                C[sp][ep]+=w;
            }
            break;
        }
        case 3:
        {
            ifstream infile;
            infile.open("C:\\Users\\popo\\CLionProjects\\alg-hw6\\roadNet-CA.txt");
            string line="";
            while (getline(infile,line))
            {
                bool flag= true;
                for(sregex_token_iterator it(line.begin(),line.end(),numR),end;it != end;it++){
                    if(flag)
                    {
                        flag=!flag;

                    }
                    else
                    {
                        flag=!flag;

                    }
                }
            }
            infile.close();
            break;
        }
        default:
            break;

    }
}
