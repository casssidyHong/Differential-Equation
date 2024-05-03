#include <iostream>
#include <cstdlib>

using namespace std;

int m, n;
int arr[1005][1005];
int ans[1005][1005];

void matrix_trans(int m, int n)
{
    int x;
    if(m>=n)
        x=m;
    else
        x=n;
    for(int i=1; i<x+1; i++)
    {
        for(int j=1; j<x+1; j++)
        {
            ans[i][j]=arr[j][i];
        }
    }
    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<m+1; j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

int main(void)
{
    cout << "Please decide the size of an 'm*n' matrix:" << endl;
    cout << "m = ";
    cin >> m;
    cout << "n = ";
    cin >> n;
    cout << "Please input the contain number of the matrix:" << endl;
    for(int i=1; i<m+1; i++)
    {
        for(int j=1; j<n+1; j++)
        {
            cin >> arr[i][j];
        }
    }
    matrix_trans(m, n);
    return 0;
}
