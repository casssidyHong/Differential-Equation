#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class TopoIterator
{
private:
    int vexNum;
    vector< list<int> > AdjList;
    bool *visit; //0:還沒走, 1:走過了
    
public:
    TopoIterator(int N):vexNum(N)
    {
        AdjList.resize(vexNum);
    };
    
    void AddEdge(int from, int to);
    void print(int Start);
};

void TopoIterator::AddEdge(int from, int to)
{
    AdjList[from].push_back(to);
}

void TopoIterator::print(int Start)
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
    TopoIterator g(6);
    g.AddEdge(0, 3); g.AddEdge(0, 2); g.AddEdge(0, 1);
    g.AddEdge(1, 4);
    g.AddEdge(2, 4); g.AddEdge(2, 5);
    g.AddEdge(3, 4); g.AddEdge(3, 4);

    cout << "The topologiacl order of the example graph is:\n";
    g.print(0);

    return 0;
}
