#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int main(void)
{
    int arr[6];
    int i;
    for(i=1; i<6; i++)
    {
        //scanf("%d", arr[i]);
        cin >> arr[i];
        for(int j=1; j<i; j++)
        {
            int key=0;
            if(arr[i]<arr[j])
            {
                key=1;
                int temp=arr[j];
                arr[j]=arr[i];
                for(int k=i; k>j; k--)
                {
                    arr[k]=arr[k-1];
                    if(k==j+1)
                    {
                        arr[k]=temp;
                        break;
                    }
                }
            }
            if(key==1) break;
        }
    }
    for(i=1; i<6; i++)
    {
        //printf("%d ", arr[i]);
        cout << arr[i] << " ";
    }
    return 0;
}
