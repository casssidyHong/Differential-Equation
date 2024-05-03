#include<iostream>
#include <list>
using namespace std;
 
class Graph{
    int V; // # of vertices
    list<int> *adj;

public:
    Graph(int);

    void addEdge(int, int);
    void printBFS(int);
};

Graph::Graph(int x){
    this->V = x;
    adj = new list<int>[V];
}

void Graph::addEdge(int x, int y){
    adj[x].push_back(y);
}

void Graph::printBFS(int first){
    bool *visited = new bool[V];
    for(int i=0; i<V; i++) visited[i] = false;

    list<int> queue;

    visited[first] = true;
    queue.push_back(first);

    list<int>::iterator i;

    while(!queue.empty()){
        int current = queue.front();
        cout << current << " ";
        queue.pop_front();

        for(i = adj[current].begin(); i != adj[current].end(); ++i){
            if(!visited[*i]){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    cout << "\n";
}

int main(){
    Graph g(7);
    g.addEdge(1, 2); g.addEdge(1, 3);
    g.addEdge(2, 1); g.addEdge(2, 4); g.addEdge(2, 5);
    g.addEdge(3, 1); g.addEdge(3, 5);
    g.addEdge(4, 2); g.addEdge(4, 5); g.addEdge(4, 6);
    g.addEdge(5, 2); g.addEdge(5, 3); g.addEdge(5, 4); g.addEdge(5, 6);
    g.addEdge(6, 4); g.addEdge(6, 5);

    Graph f(6);
    f.addEdge(0, 3); f.addEdge(0, 2); f.addEdge(0, 1);
    f.addEdge(1, 4);
    f.addEdge(2, 4); f.addEdge(2, 5);
    f.addEdge(3, 4); f.addEdge(3, 4);
    
    int start = 0;
    cout << "Topological Order starting from " << start << "\n";
//    f.printBFS(start);
    
//
//    int start = 1;
//    cout << "Breadth First Search starting from " << start << "\n";
//    g.printBFS(start);
//
//    start = 2;
//    cout << "Breadth First Search starting from " << start << "\n";
//    g.printBFS(start);
   
    return 0;
}

