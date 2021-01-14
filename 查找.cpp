#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>


////////////////////斐波那契查找
int F[] = {0,1,1,2,3,5,8,13,21,34};
int Fibonacci_Search(int *a, int n, int key){
    int low, high, mid, i, k;
    low = 1;
    high = n;
    k = 0;
    while(n > F[k] - 1){
        k++;
    }
    for (i = n; i < F[k] - 1; ++i){
        a[i] = a[n];
    }
    while (low <= high)
    {
        mid = low + F[k-1] -1;
        if(key < a[mid]){
            high = mid - 1;
            k = k - 1;
        }
        else if (key > a[mid]){
            low = mid + 1;
            k = k - 2;
        }
        else{
            return mid;
        }
    }
    return 0;
    
}