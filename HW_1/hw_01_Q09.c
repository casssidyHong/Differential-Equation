#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int arr[6];
    int i;
    for(i=1; i<6; i++)
    {
        scanf("%d,", &arr[i]);
        for(int j=1; j<i; j++)
        {
            int key=0;
            if(arr[i]<arr[j]) //前面的比後面的大
            {
                key=1;
                int temp=arr[j]; //把比較小的數字替換掉
                arr[j]=arr[i];
                for(int k=i; k>j; k--) //把每個數都往後移一格
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
        printf("%d ", arr[i]);
    }
    return 0;
}
