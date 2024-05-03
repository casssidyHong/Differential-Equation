#include <iostream>

using namespace std;

class Complex
{
private:
    int real, imgine;
public:
    Complex(int a=0, int b=0)
    {
        real = a;
        imgine = b;
    }
    
    void print()
    {
        cout << real << " + "<< imgine << "i";
    }
};

int main(int argc, const char * argv[])
{
    int a, b;
    cout << "Please input a complex number ai + b" << endl;
    cout << "The real part of the complex number a: " << endl;
    cin >> a;
    cout << "The imaginary part of the complex number b:" << endl;
    cin >> b;
    cout << "Defult number: " ;
    Complex Defult(0,0);
    Defult.print();
    cout << endl <<"Complex number: " ;
    Complex Complex(a, b);
    Complex.print();
    return 0;
}
