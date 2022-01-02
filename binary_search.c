// 二分查找

#include<stdio.h>
#include<stdlib.h>

int n;

int BinarySearch(int *a, int key)
{
    int front = 1, end = n;
    int mid;
    while(front <= end){
        mid = (front + end) / 2;
        if (a[mid] == key)return mid;
        if(a[mid] < key){
            front = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    return -1;
}

int main()
{
    scanf("%d", &n);
    int *a = (int*)malloc((n + 1) * sizeof(int));
    for(int i = 1; i < n + 1; i++){
        scanf("%d", &a[i]);
    }
    printf("%d", BinarySearch(a, 1));
    return 0;
}