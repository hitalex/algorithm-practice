#include <iostream>
#include <climits>
#include <cassert>
#include <cstdlib>

#include "graph.h"
#include "priority_queue.h"

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

void Dijkstra_array(int** graph, int V, int source, Node** node_array){
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
    //Q.print_node_heap_mapping();

    while(Q.get_size() > 0){
        Node* u = Q.extract_min();
        cout << "Selecting node: " << u->index << endl;
        int j;
        for(j=0; j<V; j++){
            // TODO: assume all weight is positive
            if(graph[u->index][j] > 0 && node_array[j]->dis > u->dis + graph[u->index][j]){
                //cout << "Check neighbour: " << j << endl;
                // set parent
                node_array[j]->parent = u->index;
                // adjust the heap
                Q.decrease_key(j, u->dis + graph[u->index][j]);
                //Q.print_node_heap_mapping();
            }
        }
    }
}

// 采用邻接表实现的Dijkstra算法
void Dijkstra_adjlist(vector<vector<AdjNode*> >graph, int V, int source, int* dis, int* parent){
    vector<Node*> node_array;
    int i;
    for(i=0; i<V; i++){
        Node* p = new Node;
        p->index = i;
        p->dis = MAX_DIST; // unreachable
        p->parent = -1; // no parent
        node_array.push_back(p);
    }
    node_array[source]->dis = 0;

    // init priority_queue
    MinHeap<Node*> Q(MAX_ELEMENTS);
    for(i=0; i<V; i++){
        Q.insert(node_array[i], i);
    }
    //Q.print_node_heap_mapping();

    while(Q.get_size() > 0){
        Node* from = Q.extract_min();
        cout << "Selecting node: " << from->index << endl;
        int j;
        for(j=0; j<graph[from->index].size(); j++){
            int to_index = graph[from->index][j]->v;
            Node* to = node_array[to_index];
            //cout << "Check neighbour: " << to->index << endl;
            if(to->dis > from->dis + graph[from->index][j]->w){
                // set parent
                to->parent = from->index;
                // adjust the heap
                Q.decrease_key(to->index, from->dis + graph[from->index][j]->w);
                //Q.print_node_heap_mapping();
            }
        }
    }

    for(i=0; i<V; i++){
        dis[i] = node_array[i]->dis;
        parent[i] = node_array[i]->parent;
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

/*
int main(int argc, const char* argv[]){
    if(argc < 3){
        printf("./Dijkstra <graph-file-data> <source>");
        exit(0);
    }

    int V;
    int source = atoi(argv[2]);
    int* dis = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));


    int** graph = read_directed_weighted_graph(argv[1], V);
    print_graph(graph, V);

    Node** node_array = (Node**)malloc(V * sizeof(Node*));
    Dijkstra_array(graph, V, 0, node_array);
    // 从node_array中读取dis和parent信息
    for(int i=0; i<V; i++){
        dis[i] = node_array[i]->dis;
        parent[i] = node_array[i]->parent;
    }
    print_all_destination_paths(parent, V, source);


    //vector<vector<AdjNode*> > graph = read_directed_weighted_adjlist(argv[1], V);
    //print_adjlist_graph(graph, V);

    //Dijkstra_adjlist(graph, V, source, dis, parent);
    //print_all_destination_paths(parent, V, source);


    cout << "shortest distance from " << source << ":" << endl;
    for(int i=0; i<V; i++){
        cout << dis[i] << " ";
    }
    cout << endl;
}*/
