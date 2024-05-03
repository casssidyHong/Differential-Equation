#include <iostream>
#include <algorithm>
# include <vector>

using namespace std;

int main(void)
{
    int n, k;
    cout << "Please input an array a[n]!" << endl << "n = ";
    cin >> n;
    vector<int> vec;
    cout << "Please input the array number:" << endl;
    for(int i=0; i<n; i++)
    {
        cin >> k;
        vec.push_back(k);
    }
    cout << "The number of occurences of '"<< vec[0] << "' in the array is: ";
    cout << count(vec.begin(), vec.end(), vec[0]) << endl;
    return 0;
}
