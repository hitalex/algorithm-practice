#include <iostream>
#include <map>
#include <cassert>

using namespace std;

template<class T>
class MinHeap{
private:
    T* A;
    int size;
    // mapping: node index to internal array index
    map<int, int> node2heap;
    // mapping: internal array index to node index
    map<int, int> heap2node;

private:
    // rebuild the heap
    // Note: stat is the internal array index, this is also a private function
    // this is a top-down approach
    void min_heapify(int start){
        // assume array implementation
        int left = 2 * start;
        int right = left + 1;
        int smallest = start;
        if(left <= this->size && get_key(A[left]) < get_key(A[start])){
            smallest = left;
        }else{
            smallest = start;
        }
        if(right <= this->size && get_key(A[right]) < get_key(A[smallest])){
            smallest = right;
        }

        if(smallest != start){
            exchange(smallest, start);
            min_heapify(smallest);
        }
    }

    // exchange element
    void exchange(int child, int parent){
        assert (child > parent);
        // get the node index of the current settings
        int child_nodei = heap2node[child];
        int parent_nodei = heap2node[parent];
        T tmp = A[child];
        A[child] = A[parent];
        A[parent] = tmp;
        // adjust the mapping
        heap2node[child] = parent_nodei;
        heap2node[parent] = child_nodei;
        node2heap[parent_nodei] = child;
        node2heap[child_nodei] = parent;
    }

public:
    MinHeap(int max_elements){
        this->A = (T*)malloc((max_elements+1) * sizeof(T)); // this is 1-based
        this->size = 0;
        this->A[0] = NULL;
    }

    T get_min(){
        return A[1];
    }

    int get_size(){
        return this->size;
    }

    T extract_min(){
        if(this->size <= 0){
            cout << "Error: No elements in heap." << endl;
            return NULL;
        }

        T min_ele = A[1];
        A[1] = A[this->size];

        // delete current mapping
        int nodei = heap2node[this->size];
        node2heap.erase(nodei);
        heap2node.erase(this->size);

        heap2node[1] = nodei;
        node2heap[nodei] = 1;
        this->size --;
        // adjsut the heap
        min_heapify(1);

        return min_ele;
    }

    /*
        Params:
        nodei: the node index
        key: the new key
    */
    void decrease_key(int nodei, int key){
        // first get the index of internal heap array
        int i = node2heap[nodei];
        if(key > get_key(A[i])){
            cout << "Current key is even smaller than the given key." << endl;
        }
        set_key(A[i], key);
        while(i > 1 && get_key(A[i/2]) > get_key(A[i])){
            // swap A[i/2] and A[i]
            //cout << "Exchanging between " << i << " and " << i/2 << endl;
            exchange(i, i/2);
        }
    }

    // e: the element, nodei: node index
    void insert(T e, int nodei){
        this->size ++;
        A[this->size] = e;
        int i = this->size;
        // init the mapping
        heap2node[this->size] = nodei;
        node2heap[nodei] = this->size;
        // similar to decrease_key
        while(i > 1 && get_key(A[i/2]) > get_key(A[i])){
            // swap A[i/2] and A[i]
            exchange(i, i/2);
        }
    }

    void print_node_heap_mapping(){
        cout << "Print node and heap mapping:" << endl;
        int i;
        for(i=1; i<=this->size; i++){
            cout << "Heap index: " << i << " Node index: " << heap2node[i];
            cout << "\tNode index: " << heap2node[i] << " Heap index: " << node2heap[heap2node[i]] << endl;
        }
    }
};
