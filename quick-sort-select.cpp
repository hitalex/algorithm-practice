#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//srand(time(NULL));

// swap elementw between i and j
void swap(int a[], int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

// partition the array
int partition(int a[], int p, int r){
    // use the first element as the pivot value
    int pivot = a[p];
    int i = p;
    for(int j=p+1; j<=r; j++){
        if(a[j] < pivot){
            i ++;
            swap(a, i, j);
        }
    }
    // i可能没变（pivot值最小），或者指向一个小于pivot的值
    // 将pivot值和a[i]交换
    swap(a, i, p);
    return i;
}

// 通过将首个元素和数组内随机位置的数交换，使得pivot值选取更加随机
int randomized_partition(int a[], int p, int r){
    // generate a random number between p and r, both inclusive
    int i = rand() % (r-p+1) + p;
    swap(a, i, p);
    return partition(a, p, r);
}

void quick_sort(int a[], int p , int r){
    int q;
    // if p==r, then a[p..r] has only one element, need not sort
    if(p < r){
        // find the pivot point
        q = randomized_partition(a, p, r);
        quick_sort(a, p, q-1);
        quick_sort(a, q+1, r);
    }
}

// 从数组a[p..r]中选择第i小的元素
// 非递归版本
int randomized_select(int a[], int n, int i){
    int p = 0;
    int r = n - 1;
    while(true){
        int q = randomized_partition(a, p, r);
        int k = q - p + 1; // pivot
        if(k == i)
            return a[q];
        else if(k < i){
            // 应该在右边接着查找
            i = i - k;
            p = q + 1;
        }else{
            // 应该在左边查找
            r = q - 1;
        }
    }
}

void print(int a[], int n){
    for(int i=0; i<n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

int main(){
    int a[] = {2, 8, 7, 1, 3, 5, 6, 4};
    int n = 8;
    quick_sort(a, 0, n-1);
    print(a, n);

    cout  << randomized_select(a, n, 4) << endl;
}
