#include <iostream>
#include <set> //會自動把裡面的資料排序 由小到大
#include <deque>
#include <random>
#include <time.h>

using namespace std;

int emergency = 0;
int crash = 0;
int now_landing_id = 1;
int now_takeoff_id = 0;
int choosen_plane[5];
bool using_runway[5] = {false};
bool finish[100005] = {false};
int fuel[100005];
int enter[100005];
int leave[100005];
int more[10] = {0}; // 多計算到的飛機數量
int id_to_runway[100005]; // 記錄每個id對應到哪個跑道
set<pair<int,int> > plane_information; // 先比前面在比後面 （活多久先 再看id）
deque<pair<int,int> > landing[10];
deque<int> takeoff[10];

int find_landing(int now_time)
{
    unsigned long a = landing[1].size();
    unsigned long b = landing[2].size();
    unsigned long c = landing[3].size();
    unsigned long d = landing[4].size();
    unsigned long e = landing[5].size();
    unsigned long f = landing[6].size();
    // 有空跑到的話先放進去
    if( a - more[1] == 0 && b - more[2] == 0)
        return 2;
    if( c - more[3] == 0 && d - more[4] == 0)
        return 3;
    if( e - more[5] == 0 && f - more[6] == 0)
        return 4;
    // 如果同個跑道的兩條線加起來<=3 就放進去
    if( a + b - more[1] - more[2] <= 3)
        return 2;
    if( c + d - more[3] - more[4] <= 3)
        return 3;
    if( e + f - more[5] - more[6] <= 3)
        return 4;
    // 如果沒有空跑道 選跑到飛機數最少的進去
    unsigned long min_size = a - more[1];
    int min_runway = 1;
    for(int i=2 ; i<7 ; i++)
    {
        if((int)landing[i].size() - more[i] < min_size)
        {
            min_runway = i;
            min_size = (int)landing[i].size() - more[i];
        }
    }
    if(min_runway == 1)
        return 2;
    if(min_runway == 4)
        return 3;
    if(min_runway == 6)
        return 4;
    return min_runway;
}

int find_takeoff(int now_time)
{
    unsigned long a = landing[1].size();
    unsigned long b = landing[2].size();
    unsigned long c = landing[3].size();
    unsigned long d = landing[4].size();
    unsigned long e = landing[5].size();
    unsigned long f = landing[6].size();
    //
    if((int)takeoff[1].size() <= 5)
        return 1;
    // 看哪個跑道沒有要降落的飛機 先讓它起飛
    if( a - more[1] == 0 && b - more[2] == 0)
        return 2;
    if( c - more[3] == 0 && d - more[4] == 0)
        return 3;
    if( e - more[5] == 0 && f - more[6] == 0)
        return 4;
    // 比第一台飛機的油量 看哪一條的飛機可以活最久 先讓它起飛
    unsigned long max_num = min(landing[1].front().first, landing[2].front().first);
    int max_runway = 2;
    unsigned long num = min(landing[3].front().first, landing[4].front().first);
    if(max_num < num)
    {
        max_num = num;
        max_runway = 3;
    }
    num = min(landing[5].front().first, landing[6].front().first);
    if(max_num < num)
    {
        max_num = num;
        max_runway = 4;
    }
    if(takeoff[1].size() < takeoff[2].size() || takeoff[1].size() < takeoff[3].size() || takeoff[1].size() < takeoff[4].size())
        max_runway = 1;
    return max_runway;
}

int find_emergency_landing_runway()
{
    unsigned long a = landing[1].size();
    unsigned long b = landing[2].size();
    unsigned long c = landing[3].size();
    unsigned long d = landing[4].size();
    unsigned long e = landing[5].size();
    unsigned long f = landing[6].size();
    // 如果跑到上沒有要降落的飛機直接讓他降落在那個跑道上
    if(using_runway[1] != 1)
        return 1;
    if( a - more[1] == 0 && b - more[2] == 0 && using_runway[2] != 1)
        return 2;
    if( c - more[3] == 0 && d - more[4] == 0 && using_runway[3] != 1)
        return 3;
    if( e - more[5] == 0 && f - more[6] == 0 && using_runway[4] != 1)
        return 4;
    // 如果跑到上要降落的飛機數小於等於三直接讓他降落在那個跑道上
    if( a + b - more[1] - more[2] < 4 && using_runway[2] != 1)
        return 2;
    if( c + d - more[3] - more[4] < 4 && using_runway[3] !=1)
        return 3;
    if( e + f - more[5] - more[6] < 4 && using_runway[4] !=1)
        return 4;
    // 跑道沒用到 跑道對應到要降落的兩條線都沒有飛機要降落
    for(int i=2 ; i<5 ; i++)
    {
        if(using_runway[i] != 1 && (int)landing[2*i-3].size() - more[2*i-3] == 0 && landing[2*i-3].size() - more[2*i-3] == 0 )
        {
            return i;
        }
    }
    // 比第一台飛機可以活的時間剩多少 找快死掉的
    int min_num = min(landing[1].front().first, landing[2].front().first);
    int min_id = 2;
    if(using_runway[2])
        min_num = INT_MAX;
    int num =  min(landing[3].front().first, landing[4].front().first);
    if(num < min_num && using_runway[3] != 1)
    {
        num = min_num;
        min_id = 3;
    }
    num =  min(landing[5].front().first, landing[6].front().first);
    if(num < min_num && using_runway[4] != 1)
    {
        num = min_num;
        min_id = 4;
    }
    return min_id;
}

void runway_1(int now_time)
{
    // 如果被用來降落的話就不要管了
    if(using_runway[1] == 1)
        return;
    if(takeoff[1].size())
    {
        finish[takeoff[1].front()] = 1; // 記錄那個飛機是不是被起飛了
        choosen_plane[1] = takeoff[1].front();
        leave[takeoff[1].front()] = now_time;
        takeoff[1].pop_front();
    }
}

void other_runway(int now_time)
{
    for(int i=2 ; i<5 ; i++)
    {
        // 跑道裡面沒東西就不用做事
        if(landing[2*i-3].size() == 0 && landing[2*i-2].size() == 0 && takeoff[i].size() == 0)
            continue;
        // 計算誤差值
        if(landing[2*i-3].size()) // 有飛機要降落
        {
            while(finish[landing[2*i-3].front().second] == 1) // 有飛機迫降 但沒有從queue裡面刪掉
            {
                landing[2*i-3].pop_front(); // 把它移除
                more[2*i-3]--;
                if(landing[2*i-3].size() == 0)
                    break;
            }
        }
        if(landing[2*i-2].size())
        {
            while(finish[landing[2*i-2].front().second] == 1)
            {
                landing[2*i-2].pop_front();
                more[2*i-2]--;
                if(landing[2*i-2].size() == 0)
                    break;
            }
        }
        // 沒有要降落 但有東西要起飛 就直接讓他起飛
        if((landing[2*i-3].size() == 0 && landing[2*i-2].size() == 0) && takeoff[i].size())
        {
            finish[takeoff[i].front()] = 1;
            choosen_plane[i] = takeoff[i].front();
            leave[takeoff[i].front()] = now_time;
            takeoff[i].pop_front();
            continue;
        }
        if(landing[2*i-3].size() == 0 && landing[2*i-2].size() == 0)
            continue;
        // 對應到的其中一條沒有飛機要降落 就讓另外一條的飛機降落
        if(landing[2*i-3].size() == 0)
        {
            choosen_plane[i] = landing[2*i-2].front().second;
            leave[landing[2*i-2].front().second] = now_time;
            finish[landing[2*i-2].front().second] = 1;
            landing[2*i-2].pop_front();
            continue;
        }
        if(landing[2*i-2].size() == 0)
        {
            choosen_plane[i] = landing[2*i-3].front().second;
            leave[landing[2*i-3].front().second] = now_time;
            finish[landing[2*i-3].front().second] = 1;
            landing[2*i-3].pop_front();
            continue;
        }
        // 如果要降落的飛機還可以活超過三次 就先起飛
        int min_num = min(landing[2*i-3].front().first, landing[2*i-2].front().first) - now_time;
        if((min_num - takeoff[i].size() >= 3) && takeoff[i].size())
        {
            finish[takeoff[i].front()] = 1;
            choosen_plane[i] = takeoff[i].front();
            leave[takeoff[i].front()] = now_time;
            takeoff[i].pop_front();
        }
        else
        {
            if(landing[2*i-3].front().first < landing[2*i-2].front().first)
            {
                choosen_plane[i] = landing[2*i-3].front().second;
                leave[landing[2*i-3].front().second] = now_time;
                finish[landing[2*i-3].front().second] = 1;
                landing[2*i-3].pop_front();
            }
            else
            {
                choosen_plane[i] = landing[2*i-2].front().second;
                leave[landing[2*i-2].front().second] = now_time;
                finish[landing[2*i-2].front().second] = 1;
                landing[2*i-2].pop_front();
            }
        }
    }
}

void print_out(int now_time)
{
    cout << endl << "Runway1(-1)" << endl;
    cout << "L1: " << endl << "L2: " << endl << "T: ";
    for(auto it:takeoff[1])
        cout << "(" << it << "), ";
    cout << endl << endl;
    for(int i=2 ; i<5 ; i++)
    {
        cout << "Runway" << i << "(-1)" << endl;
        cout << "L1: ";
        for(auto it:landing[2*i-3])
        {
            cout << "(" << it.second << ", " << it.first - now_time << "), ";

        }
        cout << endl << "L2: ";
        for(auto it:landing[2*i-2])
        {
            cout << "(" << it.second << ", " << it.first - now_time << "), ";
        }
        cout << endl << "T: ";
        for(auto it:takeoff[i])
        {
            cout << "(" << it << "), ";
        }
        cout << endl << endl;
    }
    cout << endl;
}

void step_1(int now_time, int landing_num)
{
    cout << "Step 1:" << endl << "landing plane:";
    for(int i=1 ; i<landing_num+1 ; i++)
    {
        leave[now_landing_id] = -1; //要降落的飛機出去的時間 因為還不知道 所以先設成-1
        enter[now_landing_id] = now_time; //進來的時間是現在的時間
        int rand_fuel = rand()%10 +1;
        fuel[now_landing_id] = rand_fuel; //進來的時候的油量
        cout << "(" << now_landing_id << ", " << rand_fuel << "), ";
        pair<int,int> plane_data;
        plane_data.first = rand_fuel + now_time; //第一個變數是可以活多久
        plane_data.second = now_landing_id; //飛機的編號
        int que_num = find_landing(rand_fuel + now_time); //選要放進去哪個跑道
        id_to_runway[now_landing_id] = que_num;
        landing[que_num].push_back(plane_data);
        plane_information.insert(plane_data);
        now_landing_id += 2;
    }
}

void step_2(int now_time, int takeoff_num)
{
    cout << "Step 2:" << endl << "takeoff plane:";
    for(int i=1 ; i<takeoff_num+1 ; i++)
    {
        leave[now_takeoff_id] = -1;
        enter[now_takeoff_id] = now_time;
        int que_num = find_takeoff(now_time);
        cout << "(" << now_takeoff_id << "), ";
        takeoff[que_num].push_back(now_takeoff_id);
        now_takeoff_id += 2;
    }
}

void step_3(int now_time)
{
    cout << "Step 3:" << endl;
    cout << "emergency plane:";
    int emergency_count = 0;
    while(true)
    {
        // 如果裡面沒有東西的話就跳出迴圈
        if(plane_information.size() == 0)
            break;
        int max_time = plane_information.begin()->first; // 看可以活多久
        int id = plane_information.begin()->second;
        if(finish[id] == 1) // 如果飛機不見了
        {
            plane_information.erase(plane_information.begin()); // 就把它刪掉
            continue;
        }
        if(max_time < now_time+1) // 快要死掉
        {
            emergency++;
            cout << "(" << id << "), ";
            finish[id] = 1;
            more[id_to_runway[id]]++;
            if(emergency_count < 4) // 還可以有飛機降落
            {
                ++emergency_count;
                leave[id] = now_time; // 記錄離開時間
                int runway_num = find_emergency_landing_runway();
                using_runway[runway_num] = 1;
                choosen_plane[runway_num] = id;
            }
            else
            {
                crash++;
            }
            plane_information.erase(plane_information.begin()); // 處理完了 把它刪掉
        }
        else
        {
            break;
        }
    }
}

void step_4(int now_time)
{
    cout << "Runway1(" << choosen_plane[1] << ")" << endl;
    cout << "L1: " << endl << "L2: " << endl << "T: ";
    for(auto it:takeoff[1])
    {
        cout << "(" << it << "), ";
    }
    cout << endl << endl;
    for(int i=2 ; i<5 ; i++){
        cout << "Runway" << i << "(" << choosen_plane[i] << ")";
        cout << endl << "L1: ";
        for(auto it:landing[2*i-3])
            cout << "(" << it.second << ", " << it.first - now_time << "), ";
        cout << endl << "L2: ";
        for(auto it:landing[2*i-2])
            cout << "(" << it.second << ", " << it.first - now_time << "), ";
        cout << endl << "T: ";
        for(auto it:takeoff[i])
            cout << "(" << it << "), ";
        cout << endl << endl;
    }
    cout << endl;
}

void answer()
{
    cout << "average landing wating time: ";
    double sum = 0;
    double div = 0;
    for(int i=1 ; i<now_landing_id+1 ; i=i+2)
    {
        if(leave[i] == EOF)
            continue;
        sum += leave[i] - enter[i];
        div++;
    }
    cout << sum/div << "(s)";
    cout << endl;
    cout << "average takeoff wating time: ";
    sum = 0;
    div = 0;
    for(int i=0 ; i<now_takeoff_id+1 ; i=i+2)
    {
        if(leave[i] == EOF)
            continue;
        sum += leave[i] - enter[i];
        div++;
    }
    cout << sum/div << "(s)";
    cout << endl;
    cout << "average fuel saved: ";
    sum = 0;
    div = 0;
    for(int i=1 ; i<now_landing_id+1 ; i+=2)
    {
        if(leave[i] == EOF)
            continue;
        sum += fuel[i] - (leave[i] - enter[i]);
        div++;
    }
    cout << sum/div << "(s)";
    cout << endl;
    cout << "total plane in emergency: " << emergency << endl;
    cout << "total plane crashed: " << crash << endl;
}

int main()
{
    cout << "How many Time Unit You Want to Simulate: ";
    int n;
    cin >> n;
    srand( static_cast<unsigned int>(time(nullptr)));
    for(int now_time=1 ; now_time<n+1 ; now_time++)
    {
        cout << "Simulation Time: " << now_time;
        cout << endl << endl;
        print_out(now_time);
        for(int i=1 ; i<6 ; i++)
            using_runway[i] = false; //有使用了就改成true 所以初始化設成false
        int landing_num = rand()%5;
        int takeoff_num = rand()%4;
        step_1(now_time, landing_num);
        cout << endl;
        print_out(now_time);
        step_2(now_time, takeoff_num);
        print_out(now_time);
        step_3(now_time);
        cout << endl;
        print_out(now_time);
        cout << "Step 4:" << endl;
        runway_1(now_time);
        other_runway(now_time);
        step_4(now_time);
    }
    cout << "How many Time Unit You Want to Simulate: " << n << endl;
    answer();
}
