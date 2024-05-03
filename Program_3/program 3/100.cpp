#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <iomanip>
#include <queue>
#include <math.h>

using namespace std;

int randnum;

class insertion{
public:
    insertion(vector<int> v_) : v(v_){};

    vector<int> sort(){
        for(int i=1;i<v.size();i++){
            insert(i);
        }
        return v;
    }

    vector<int> sort_print(){
        for(int i=1;i<v.size();i++){
            cout << setw(2) <<i << " : ";
            insert(i);
            print_v();
        }
        return v;
    }

    void insert(int idx){
        int temp = v[idx];
        int j = idx-1;
        for(;j>=0 && temp<v[j]; j--){
            v[j+1] = v[j];
        }
        v[j+1] = temp;
    };

    void print_v(){
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << endl;
    }

public:
    vector<int> v;
};

class quick{
public:
    quick(vector<int> v_): v(v_){}

    vector<int> sort(){
        quick_sort_partation(0, v.size()-1);
        return v;
    }

    vector<int> sort_print(){
        quick_sort_partation_print(0, v.size()-1);
        return v;
    }

    void quick_sort_partation_print(int front, int rear)
    {
        // TODO :
        cout << "Before:\n";
        print_v();
        quick_sort_partation(front, rear);
        return;
    }
    
    int partition(int front, int rear)
    {
        if(randnum<=100)
            cout << front << "-" << rear << " :\n";
        int p = v[front];
        
        int count=0;
        for(int i = front+1; i <= rear; i++)
        {
            if(v[i] < p || v[i] == p)
                count ++;
        }
        
        // 把pivot換到正確的位子
        int index = front + count;
        v[front] = v[index];
        v[index] = p;
        
        int i=front;
        int j=rear;
        while(i < index && j > index)
        {
            while (v[i] < p || v[i] == p)
                i++;
            while (v[j] > p)
                j--;
            if (i < index && j > index)
            {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                i++; j--;
            }
        }
        if(randnum<=100)
            print_v();
        return index;
    }

    void quick_sort_partation(int front, int rear){
        // TODO :
        if (front < rear)
        {
            int pivot = partition(front, rear);
            // 左邊
            quick_sort_partation(front, pivot - 1);
            // 右邊
            quick_sort_partation(pivot + 1, rear);
        }

        return;
    }

    void print_v(){
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << endl;
    }

public:
    vector<int> v;
};

class radix{
public:
    
    radix(vector<int> v_) : v(v_){
        // maybe ?
    }
    
    vector<int> sort(){
        // TODO
        int max = 0;
        for(int i = 0; i<randnum; i++)
        {
            if(v[i] > max)
                max = v[i];
        }
        
        queue<int> buckets[10];
        
        int j = 1;
        for(int time= 1; time<sizeof(max); time++)
        {
            if(randnum<=100)
            {
                if(time==1)
                    cout << "First-pass:\n";
                if(time==2)
                    cout << "Second-pass:\n";
                if(time==3)
                    cout << "Third-pass:\n";
            }
            for(int i = 0; i<randnum; i++)
                buckets[(v[i]/j) %10].push(v[i]);
            
            int k = 0;
            for(int i = 0; i<10; i++)
            {
                if(randnum<=100)
                    cout << endl << i << " | ";
                while(!buckets[i].empty()){
                    v[k++] = buckets[i].front();
                    if(randnum<=100)
                    {
                        cout << " --> " << buckets[i].front();
                    }
                    buckets[i].pop();
                }
            }
            j*=10;
            if(randnum<=100)
            {
                cout << "\nresulting chain : ";
                print_v();
            }
        }
        return v;
    }

    vector<int> sort_print(){
        // TODO
        int max = 0;
        for(int i = 0; i<randnum; i++)
        {
            if(v[i] > max)
                max = v[i];
        }
        
        queue<int> buckets[10];
        
        int j = 1;
        for(int time=1; time<sizeof(max); time++)
        {
            if(time==1)
                cout << "First-pass:\n";
            if(time==2)
                cout << "Second-pass:\n";
            if(time==3)
                cout << "Third-pass:\n";
            
            for(int i = 0; i<v.size(); i++){
                buckets[(v[i]/j) %10].push(v[i]);
            }
            
            int k = -1;
            for(int i=0; i<10; i++)
            {
                if(i!=0)
                    cout << endl;
                cout << i << " | ";
                while(!buckets[i].empty())
                {
                    v[++k] = buckets[i].front();
                    cout << " --> " << buckets[i].front();
                    buckets[i].pop();
                }
            }
            j*=10;
            cout << "\nresulting chain : ";
            print_v();
        }
        return v;
    }

    // 可任意新增需要的 member funciton

    void print_v(){
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << endl;
    }

public:
    vector<int> v;
    // maybe ?
};

int main(){
    cout << "DS-OO Program3-Demo\n";
    srand(time(NULL));
    
    cin >> randnum;
    
    if(randnum > 200000)
    {
        cout << "ERROR\n";
        return 0;
    }

    vector<int> nums;
    bool printflag = false;

    if(randnum <= 0){
        nums = {168, 179, 208, 306, 93, 859, 984, 55, 9, 271, 33}; // part1
        printflag = true;
    }else{
        for(int i=0;i<randnum;i++){
            nums.push_back(rand()%999 + 1);
        }
        if(randnum <= 100) printflag = true;
    }

    
    if(printflag){
        cout << "Before : ";
        for(auto s : nums){
            cout << s << ",";
        }
        cout << endl << endl;
    }
    
    double START, END;
    vector<int> sort1, sort2, sort3;
    

    /* insertion sort*/
    cout << "Insertion sort" << ":\n";
    START = clock();
    insertion insertion_(nums);
    //為了使執行速度最快直接分兩個function
    sort1 = printflag ? insertion_.sort_print() : insertion_.sort();
    END = clock();
    cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n\n\n";



    /* quick sort*/
    cout << "Quick sort" << ":\n";
    START = clock();
    quick quick_(nums);
    // 為了使執行速度最快 直接分兩個function
    sort2 = printflag ? quick_.sort_print() : quick_.sort();
    END = clock();
    cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
    // compare with insertion sort result, make sure the ans is correct
    sort1 == sort2 ? cout << "Correct!!\n\n\n" : cout << "Wrong!!\n\n\n";



    /* radix sort*/
    cout << "Radix sort" << ":\n";
    START = clock();
    radix radix_(nums);
    // 為了使執行速度最快 直接分兩個function
    sort3 = printflag ? radix_.sort_print() : radix_.sort();
    END = clock();
    cout << "sorting time : " << (END - START) / CLOCKS_PER_SEC << " s\n";
    // compare with insertion sort result, make sure the ans is correct
    sort1 == sort3 ? cout << "Correct!!\n\n\n" : cout << "Wrong!!\n\n";
}
