#include <iostream>
#include <list>
#include <queue>

using namespace std;

void T(vector<int> adj[], int first, int second)
{
    adj[first].push_back(second);
    adj[second].push_back(first);
}

bool BFS(vector<int> adj[], int from, int to, int num, int distance[])
{
    list<int> queue;
    bool visited[num];
    for(int i=0; i<num; i++){
        visited[i] = false;
        distance[i] = INT_MAX;
    }
    
    visited[from] = true;
    distance[from] = 0;
    queue.push_back(from);

    while(!queue.empty()){
        int temp = queue.front();
        queue.pop_front();
        for(int i = 0; i < adj[temp].size(); i++){
            if(visited[adj[temp][i]] == false){
                visited[adj[temp][i]] = true;
                distance[adj[temp][i]] = distance[temp] + 1;
                queue.push_back(adj[temp][i]);
                if(adj[temp][i] == to)
                    return true;
            }
        }
    }
    return false;
}
 
void distance(vector<int> adj[], int v, int remaing_vertice, int num)
{
    int dist[num];
    if(BFS(adj, v, remaing_vertice, num, dist) == false){
        cout << "ERROR";
        return;
    }
    vector<int> path;
    cout << "Shortest path from " << remaing_vertice << " to v: " << dist[remaing_vertice];
}

int main()
{
    int num = 8;
    vector<int> adj[num];
    // assume that the length between every two nodes is 1
    T(adj, 0, 1);
    T(adj, 0, 3);
    T(adj, 1, 2);
    T(adj, 3, 4);
    T(adj, 3, 7);
    T(adj, 4, 5);
    T(adj, 4, 6);
    T(adj, 4, 7);
    T(adj, 5, 6);
    T(adj, 6, 7);
    int v = 0; //root
    for(int remaing_vertice=1; remaing_vertice<8; remaing_vertice++)
    {
        distance(adj, v, remaing_vertice, num);
        cout << endl;
    }
    return 0;
}
