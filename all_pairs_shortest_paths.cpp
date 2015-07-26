#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "graph.h"

using namespace std;

int** allocate_square_matrix(int n, int init_value = NULL){
    int** a = (int**)malloc(n * sizeof(int*));
    for(int i=0; i<n; i++){
        a[i] = (int*)malloc(n * sizeof(int));
        for(int j=0; j<n; j++)
            a[i][j] = init_value;
    }

    return a;
}

// free the matrix
void deallocate_square_matrix(int** a, int n){
    int i;
    for(i=0; i<n; i++){
        free(a[i]);
    }
    free(a);
}

void initialize_all_pairs(int** graph, int V, int** dis, int** parent){
    int i, j;
    for(i=0; i<V; i++){
        for(j=0; j<V; j++){
            dis[i][j] = graph[i][j];
            if(graph[i][j] < MAX_DIST)
                parent[i][j] = i;
        }
        dis[i][i] = 0;
        parent[i][i] = -1;
    }
}

/*
    最终的结算结果会存放入L矩阵
*/
void extend_shortest_paths(int** graph, int V, int** L, int** parent){
    int i,j,k;
    int** L2 = allocate_square_matrix(V, MAX_DIST);
    for(i=0; i<V; i++)
        for(j=0; j<V; j++){
            int tmp = MAX_DIST;
            int tmp_p = -1;
            for(k=0; k<V; k++){
                if(k!=j && L[i][k] + graph[k][j] < tmp){
                    tmp_p = k;
                    tmp = L[i][k] + graph[k][j];
                }
            }
            if(tmp < L[i][j]){
                parent[i][j] = tmp_p;
                L2[i][j] = tmp; // 此时还不可以修改L中的值
            }else{
                // parent值不变
                L2[i][j] = L[i][j];
            }
        }

    for(i=0; i<V; i++)
        for(j=0; j<V; j++)
            L[i][j] = L2[i][j];

    deallocate_square_matrix(L2, V);
}

void slow_all_pairs_shortest_paths(int** graph, int V, int** dis, int** parent){
    // init L(1)
    initialize_all_pairs(graph, V, dis, parent);

    for(int i=2; i<V+1; i++){
        extend_shortest_paths(graph, V, dis, parent);
    }
}

void Floyd_Warshall(int** graph, int V, int** dis, int** parent){
    initialize_all_pairs(graph, V, dis, parent);

    int i, j, k;
    for(k=0; k<V; k++)
        for(i=0; i<V; i++)
            for(j=0; j<V; j++){
                if(dis[i][j] > dis[i][k] + dis[k][j]){ // k is on the path
                    dis[i][j] = dis[i][k] + dis[k][j];
                    parent[i][j] = parent[k][j];
                }else if(dis[i][j] == dis[i][k] + dis[k][j]){
                    /*
                    // 研究在相等时的动作
                    cout << "i = " << i << " j = " << j << " k = " << k << endl;
                    cout << "dis[i][j] = " << dis[i][j] << " ";
                    cout << "dis[i][k] = " << dis[i][k] << " ";
                    cout << "dis[k][j] = " << dis[k][j] << endl;
                    */
                }else{
                    ; // k is not on the shortest path
                }
            }
}


int main(int argc, const char* argv[]){
    if(argc < 2){
        printf("./all_pairs_shortest_paths <graph-file-data>");
        exit(0);
    }

    int V;
    // 采用邻接表的方式表示
    int** graph = read_directed_weighted_graph(argv[1], V);
    int** dis = allocate_square_matrix(V, MAX_DIST);
    int** parent = allocate_square_matrix(V, -1);

    //slow_all_pairs_shortest_paths(graph, V, dis, parent);
    Floyd_Warshall(graph, V, dis, parent);

    print_all_pair_shortest_distance(dis, V);

    print_all_pair_shortest_paths(parent, V);
    cout << "Raw values in parent: " << endl;
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            cout << parent[i][j] << " ";
        }
        cout << endl;
    }
}
