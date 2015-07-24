#include <iostream>
#include <climits>
#include <queue>
#include <map>
#include <cassert>

#include "graph.h"

#define MAX_ELEMENTS 100

using namespace std;

struct Node{
    int index;
    int dis; // distance from source
    int parent; // parent node
};

int get_key(Node* p){
    return p->dis;
}

void set_key(Node* p, int key){
    p->dis = key;
}

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

void Dijkstra_shortest_path(int** graph, int V, int source, Node** node_array){
    // init single source
    int i;
    for(i=0; i<V; i++){
        Node* p = new Node;
        node_array[i] = p;
        p->index = i;
        p->dis = INT_MAX; // unreachable
        p->parent = -1; // no parent
    }

    node_array[source]->dis = 0;
    // init priority_queue
    MinHeap<Node*> Q(MAX_ELEMENTS);
    for(i=0; i<V; i++){
        Q.insert(node_array[i], i);
    }
    Q.print_node_heap_mapping();

    while(Q.get_size() > 0){
        Node* u = Q.extract_min();
        cout << "Selecting node: " << u->index << endl;
        int j;
        for(j=0; j<V; j++){
            // TODO: assume all weight is positive
            if(graph[u->index][j] > 0 && node_array[j]->dis > u->dis + graph[u->index][j]){
                cout << "Check neighbour: " << j << endl;
                // set parent
                node_array[j]->parent = u->index;
                // adjust the heap
                Q.decrease_key(j, u->dis + graph[u->index][j]);
                //Q.print_node_heap_mapping();
            }
        }
    }
}

void print_shortest_path(Node** node_array, int V, int source, int target){
    if(source == target){
        cout << source;
    }else{
        if(node_array[target]->parent == -1){
            cout << "Error: no path from " << source << " to " << target;
        }else{
            int parent = node_array[target]->parent;
            print_shortest_path(node_array, V, source, parent);
            cout << " -> " << target;
        }
    }
}

void test_heap(){
    MinHeap<Node*> h(MAX_ELEMENTS);
    int a[] = {5, 3, 17, 10, 84, 19, 6, 22, 9};
    for(int i=0; i<9; i++){
        Node* p = new Node;
        p->dis = a[i];
        h.insert(p, i);
    }

    while(h.get_size() > 0){
        Node* p = h.extract_min();
        cout << p->dis << " ";
    }
    cout << endl;
}

int main(){
    int V;
    int** graph;

    graph = read_directed_weighted_graph("graph-directed-weighted.txt", V);
    print_graph(graph, V);

    int source = 0;
    Node** node_array = (Node**)malloc(V * sizeof(Node*));
    Dijkstra_shortest_path(graph, V, 0, node_array);

    print_shortest_path(node_array, V, 0, 2);
}
