#include <iostream>
#include <string>

using namespace std;

void pal(string a)
{
    string b;
    unsigned long int n;
    n=a.size();
    for(unsigned long int i=0, j=n-1; i<n; i++, j--)
    {
        b[j]=a[i];
    }
    int key=0;
    for(int i=0; i<n; i++)
    {
        if(a[i] != b[i])
        {
            key=1;
            break;
        }
    }
    if(key==1)
    {
        cout << "This isn't a palindrome.";
    }
    else
        cout << "This is a palindrome.";
}

int main(void)
{
    string a, b;
    cout << "Please type a word you'll like to test:" << endl;
    cin >> a;
    pal(a);
    return 0;
}

