#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>

#include "graph.h"

using namespace std;

void initialize_single_source(int V, int source, int* dis, int* parent){
    int i;
    for(i=0; i<V; i++){
        dis[i] = MAX_DIST;
        parent[i] = -1;
    }

    dis[source] = 0;
}

// weight: u->v
void relax(int* dis, int* parent, int from, int to, int weight){
    if(dis[to] > dis[from] + weight){
        dis[to] = dis[from] + weight;
        parent[to] = from;
    }
}

bool Bellman_Ford(vector< vector<AdjNode*> > graph, int V, int source, int* dis, int* parent){
    initialize_single_source(V, source, dis, parent);
    int i;
    for(i=0; i<V-1; i++){
        // iterate over all edges
        for(int from=0; from<V; from++){
            vector<AdjNode*> dst_list = graph[from];
            for(int j=0; j<dst_list.size(); j++){
                int to = dst_list[j]->v;
                int weight = dst_list[j]->w;
                relax(dis, parent, from, to, weight);
            }
        }
    }

    for(int from=0; from<V; from++){
        vector<AdjNode*> dst_list = graph[from];
        for(int j=0; j<dst_list.size(); j++){
            int to = dst_list[j]->v;
            int weight = dst_list[j]->w;
            if(dis[to] > dis[from] + weight)
                return false;
        }
    }

    return true;
}

/*
int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("./Bellman_Ford <graph-file-data> <source>");
        exit(0);
    }

    int V;
    // 采用邻接表的方式表示
    vector<vector<AdjNode*> > graph = read_directed_weighted_adjlist(argv[1], V);
    print_adjlist_graph(graph, V);

    int source = atoi(argv[2]);
    assert(source < V && source >= 0);

    int* dis = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    cout << "Calculating shortest paths from: " << source << endl;
    if(! Bellman_Ford(graph, V, source, dis, parent)){
        cout << "There is negative loops in this graph!" << endl;
    }else{
        print_all_destination_paths(parent, V, source);
    }
}*/
