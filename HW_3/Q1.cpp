#include <iostream>
#define INF 1e9

using namespace std;

int dis[10], first[10], second[10], length[10];
int check;

struct edge{
    int first;
    int second;
    int length;
};

edge edge[10];

void BellmanFord(int n, int m){
    for(int j=1; j<n; ++j){  // 最多鬆弛n-1輪
        check = 0;  // 標記在本輪鬆弛中陣列dis是否發生更新
        for(int i=1; i<=m; ++i){
            if(dis[edge[i].first] != INF && dis[edge[i].first] + edge[i].length < dis[edge[i].second]){  // relax
                dis[edge[i].second] = dis[edge[i].first] + edge[i].length;
                check = 1;
            }
        }
        if(check == 0)
            break;
    }
}

int main(){
    int n, m; //n 頂點個數, m 邊的條數
    //cin >> n >> m;
    n=5;
    m=5;
    
    edge[1].first = 1;
    edge[1].second = 2;
    edge[1].length = -3;
    
    edge[2].first = 1;
    edge[2].second = 5;
    edge[2].length = 5;
    
    edge[3].first = 2;
    edge[3].second = 3;
    edge[3].length = 2;
    
    edge[4].first = 3;
    edge[4].second = 4;
    edge[4].length = 3;
    
    edge[5].first = 4;
    edge[5].second = 5;
    edge[5].length = 2;
    
    /*for(int i = 1; i<=m; ++i)
    {
        cin >> first[i] >> second[i] >> length[i];
    }*/

    // 初始化 源點為1號頂點
    for(int i=1; i<=n; ++i){
        dis[i] = INF;
    }
    dis[1] = 0;

    BellmanFord(n, m);
    
    cout << "各個點到點1的最短距離：\n\n";
    for(int i=1; i<=n; i++){
        cout << i << "到點1的最短距離為:" << dis[i];
        cout << endl;
    }
    
    return 0;
}
