#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <queue>

#include "graph.h"

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

/*
实现 bfs、dfs、topological-sort,SCC
*/

void breath_first_search(int** graph, int V, int start, int* dis, int* parent, int* color){
    int i;
    for(i=0; i<V; i++){
        if(i != start){
            color[i] = WHITE;
            dis[i] = -1;
            parent[i] = -1;
        }
    }

    dis[start] = 0;
    color[start] = GREY;
    parent[start] = -1; // no parent
    queue<int> Q;
    Q.push(start);
    while(! Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i=0; i<V; i++){
            if(graph[u][i] == 1 && color[i] == WHITE){
                Q.push(i);
                dis[i] = dis[u] + 1;
                parent[i] = u;
                color[i] = GREY;
            }
        }
        color[u] = BLACK;
    }
}

// 递归调用函数
void dfs_visit(int curr, int** graph, int V, int* parent, int* color, int* enter, int* finish, int* ptime){
    *ptime += 1;
    enter[curr] = *ptime;
    color[curr] = GREY;
    int i;
    for(i=0; i<V; i++){
        if(graph[curr][i] == 1 && color[i] == WHITE){
            parent[i] = curr;
            dfs_visit(i, graph, V, parent, color, enter, finish, ptime);
        }
    }
    *ptime += 1;
    finish[curr] = *ptime;
    color[curr] = BLACK;
}

void deep_first_search(int** graph, int V, int* parent, int* color, int* enter, int* finish){
    int i;
    for(i=0; i<V; i++){
        parent[i] = -1;
        color[i] = WHITE;
    }

    int time = 0;
    for(i=0; i<V; i++){
        if(color[i] == WHITE)
            dfs_visit(i, graph, V, parent, color, enter, finish, &time);
    }
}

int main(int argc, char const *argv[]) {
    int V;
    int** graph;

    graph = read_unweighted_graph("graph.txt", V, false);

    //print_graph(graph, V);

    int* dis = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    int* color = (int*)malloc(V * sizeof(int));
    int* enter = (int*)malloc(V * sizeof(int));
    int* finish = (int*)malloc(V * sizeof(int));

    //breath_first_search(graph, V, 1, dis, parent, color);

    deep_first_search(graph, V, parent, color, enter, finish);

    print_path(parent, 1, 3);

    return 0;
}
