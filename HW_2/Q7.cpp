#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class graph
{
private:
    int vexNum;
    vector< list<int> > AdjList;
    bool *visit; //0:還沒走, 1:走過了
    
public:
    graph(int N):vexNum(N)
    {
        AdjList.resize(vexNum);
    };
    
    void AddEdge(int from, int to);
    void BFS(int Start);
};

void graph::AddEdge(int from, int to)
{
    AdjList[from].push_back(to);
}

void graph::BFS(int Start)
{
    visit = new bool[vexNum];
    //先初始化每個位子都還沒走過
    for (int i = 0; i < vexNum; i++)
        visit[i] = 0;
    
    queue<int> q;
    
    int s = Start;
    for (int j = 0; j < vexNum; j++)
    {
        if (visit[s] == 0) //還沒走過
        {
            visit[s] = 1;
            q.push(s);
            while (!q.empty())
            {
                int n = q.front(); //新的搜尋起點
                cout << n << " ";
                for (list<int>::iterator k = AdjList[n].begin(); k != AdjList[n].end(); k++)
                {
                    if (visit[*k] == 0) //找到的vertex還沒走過
                    {
                        visit[*k] = 1;
                        q.push(*k); //把vertex推進queue
                    }
                }
                q.pop(); //把u移出queue
            }
        }
        //檢查有沒有沒被走到的
        s = j;
    }
}

int main()
{
    graph g(7);
    g.AddEdge(0, 1); g.AddEdge(0, 2); g.AddEdge(0, 3);
    g.AddEdge(1, 0); g.AddEdge(1, 4); g.AddEdge(1, 5);
    g.AddEdge(2, 0); g.AddEdge(2, 6); g.AddEdge(2, 7);
    g.AddEdge(3, 0); g.AddEdge(3, 6);
    g.AddEdge(4, 1); g.AddEdge(4, 5);
    g.AddEdge(5, 1); g.AddEdge(5, 4);
    g.AddEdge(6, 2); g.AddEdge(6, 3);

    cout << "The order of breadth-first search in this graph:\n";
    g.BFS(0);

    return 0;
}
