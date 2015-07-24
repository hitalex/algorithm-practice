#include <iostream>
#define N 9

using namespace std;

struct Node{
    int key;
    struct Node* next;
};

Node* bucket[N];

// the hash function
int hash_func(int key){
    return key % 9;
}

Node* chained_hash_insert(int key){
    int h = hash_func(key);
    Node* p = new Node;
    p->key = key;
    p->next = NULL;

    if(bucket[h] == NULL){
        bucket[h] = p;
    }else{
        // insert befor current head
        p->next = bucket[h];
        bucket[h] = p;
    }

    return p;
}

Node* chained_hash_search(int key){
    int h = hash_func(key);
    Node* p = bucket[h];
    while(p != NULL){
        if(p->key == key)
            break;
        else
            p = p->next;
    }

    return p;
}

Node* chained_hash_delete(int key){
    int h = hash_func(key);
    Node *pre, *p;
    pre = NULL; //pre of p
    p = bucket[h];
    if(p == NULL) // empty list
        return NULL;

    while(p != NULL){
        if(p->key  == key)
            break;
        else{
            pre = p;
            p = p->next;
        }
    }

    if(p == NULL) // not found
        return NULL;

    if(pre == NULL){
        bucket[h] = NULL;
        return p;
    }else{
        pre->next = p->next;
        return p;
    }
}

void print_hash_table(){
    int i;
    for(i=0; i<N; i++){
        cout << "No. " << i << " bucket: ";
        if(bucket[i] == NULL){
            cout << "NULL" << endl;
        }else{
            Node* p = bucket[i];
            while(p != NULL){
                cout << p->key << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
}

int main(){
    int a[] = {5, 28, 19, 15, 20, 33, 12, 17, 10};
    int n = 9;
    int i;
    // init the bucket
    for(i=0; i<N; i++){
        bucket[i] = NULL; // no head pointers
    }

    for(i=0; i<n; i++){
        chained_hash_insert(a[i]);
    }

    print_hash_table();

    return 1;
}
