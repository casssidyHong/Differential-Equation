#include "quick.h"
#include <math.h>


class radix{
public:
    radix(vector<int> v_) : v(v_){
        // maybe ?
    }

    vector<int> sort(){
        // TODO
        return v;
    }

    vector<int> sort_print(){
        // TODO
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