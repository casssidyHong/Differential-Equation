#include <iostream>

using namespace std;

int x[5], y[5], z[5];

class Quadratic
{
private:
    int a_sum=0, b_sum=0, c_sum=0;
public:
    Quadratic()
    {
        a_sum = x[1] + x[2];
        b_sum = y[1] + y[2];
        c_sum = z[1] + z[2];
    }
    
    void print()
    {
        cout << a_sum <<"x^2 + " << b_sum << "x + "  << c_sum;
        cout << endl;
    }
};


int main(void)
{
    cout << "Now please enter polynomials 1: ax^2 + bx + c:" << endl;
    cout << "a = ";
    cin >> x[1];
    cout << "b = ";
    cin >> y[1];
    cout << "c = ";
    cin >> z[1];
    cout << "Now please enter polynomials 2: ax^2 + bx + c:" << endl;
    cout << "a = ";
    cin >> x[2];
    cout <<  "b = ";
    cin >> y[2];
    cout <<  "c = ";
    cin >> z[2];
    cout << "The sum of the polynomials is:" << endl;
    Quadratic test;
    test.print();
    
    return 0;
}
