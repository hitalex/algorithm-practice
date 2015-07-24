#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;

// merge two array: a[p..q] and q[q+1 .. r]
void merge(int a[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int* b = (int*)malloc((n1+1) * sizeof(int));
    int* c = (int*)malloc((n2+1) * sizeof(int));
    int i, j, k;
    for(i=0; i<n1; i++)
        b[i] = a[p + i];
    for(i=0; i<n2; i++)
        c[i] = a[q + 1 + i];
    b[n1] = INT_MAX;
    c[n2] = INT_MAX;

    i = 0; // pointer to b
    j = 0; // pointer to c
    for(k=p; k<=r; k++){
        if(b[i] <= c[j]){
            a[k] = b[i];
            i ++;
        }else{
            a[k] = c[j];
            j ++;
        }
    }
}

void merge_sort(int a[], int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
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

    merge_sort(a, 0, n-1);

    print(a, n);
    return 0;
}
