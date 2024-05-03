#include <iostream>
#include <list>
#include <vector>
using namespace std;
 
class TopoIterator{
    int V; // # of vertices
    list<int> *adj;
    vector<int> indegree;
    
public:
    TopoIterator(int);

    void addEdge(int, int);
    void Topo();
};

TopoIterator::TopoIterator(int x){
    this->V = x;
    adj = new list<int>[V];
    
    for (int i = 0; i < V; i++) indegree.push_back(0);
}

void TopoIterator::addEdge(int x, int y){
    adj[x].push_back(y);
    indegree[y]++;
}

void TopoIterator::Topo(){
    bool *visited = new bool[V];
    int first = 0;
    for(int i=0; i<V; i++) {
        visited[i] = false;
        if(indegree[i] == 0) first = i;
    }

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
    
    TopoIterator f(6);
    f.addEdge(0, 3); f.addEdge(0, 2); f.addEdge(0, 1);
    f.addEdge(1, 4);
    f.addEdge(2, 4); f.addEdge(2, 5);
    f.addEdge(3, 4); f.addEdge(3, 4);
    
    cout << "Topological Order: ";
    f.Topo();
    
    return 0;
}

