#include "insertion.h"

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

    void quick_sort_partation_print(int front, int rear){
        // TODO :
        return;
    }

    void quick_sort_partation(int front, int rear){
        // TODO :
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