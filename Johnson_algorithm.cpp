#include <iostream>
#include <vector>

#include "graph.h"
#include "priority_queue.h"

using namespace std;

extern bool Bellman_Ford(vector< vector<AdjNode*> > graph, int V, int source, int* dis, int* parent);
extern void Dijkstra_adjlist(vector<vector<AdjNode*> >graph, int V, int source, int* dis, int* parent);

// 根据节点数量，申请空间
int** allocate_square_matrix(int n, int init_value){
    int** a;
    a = (int**)malloc(n * sizeof(int*));
    int i;
    for(i=0; i<n; i++){
        a[i] = (int*)malloc(n * sizeof(int));
    }

    return a;
}

void deallocate_square_matrix(int** a, int n){
    int i;
    for(i=0; i<n; i++){
        free(a[i]);
    }
    free(a);
}

// 保持和Bellman_Ford具有相同的接口
void Johnson_algorithm(vector<vector<AdjNode*> > graph, int original_V, int** final_dis, int** final_parent){
    // 增加一个s节点
    int V = original_V + 1;
    int* dis = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    int i, j;
    // 对于新加入的s节点，扩展graph邻接矩阵
    vector<AdjNode*> tolist;
    for(i=1; i<V; i++){
        AdjNode* p = new AdjNode;
        p->v = i; // 目标节点
        p->w = 0; // 权值全部为0
        tolist.push_back(p);
    }
    graph.insert(graph.begin(), tolist);
    // 其他AdjNode中的v也需要更新
    for(i=1; i<V; i++){
        for(j=0; j<graph[i].size(); j++){
            graph[i][j]->v += 1;
        }
    }
    cout << "After adding a start node..." << endl;
    print_adjlist_graph(graph, V);

    // s为初始点
    if(! Bellman_Ford(graph, V, 0, dis, parent)){
        cout << "There is negative looop in graph! " << endl;
        return ;
    }
    cout << "After Bellman_Ford, the shortest distance is: " << endl;
    print_shortest_distance(dis, V);

    // 重新设置graph权重
    for(int i=0; i<V; i++){
        for(int j=0; j<graph[i].size(); j++){
            int u = i; // 出发节点
            int v = graph[i][j]->v; // 目标节点index
            graph[i][j]->w += (dis[u] - dis[v]); // 最后需要调整过来
        }
    }

    cout << "Running Dijkstra algorithm..." << endl;
    // 对于每个节点，运行Dijkstra算法
    int* tmp_dis = (int*)malloc(V * sizeof(int));
    int* tmp_parent = (int*)malloc(V * sizeof(int));
    for(int s=0; s<original_V; s++){
        cout << "Source node index: " << s + 1 << endl;
        // 需要注意：之前的节点编号比现在小1
        Dijkstra_adjlist(graph, V, s+1, tmp_dis, tmp_parent);
        for(int i=0; i<original_V; i++){
            final_dis[s][i] = tmp_dis[i+1] + dis[i+1] - dis[s+1];
            final_parent[s][i] = tmp_parent[i+1] - 1;
        }
    }

    for(int i=1; i<V; i++){
        for(int j=0; j<graph[i].size(); j++){
            graph[i][j]->v -= 1;
        }
    }
    // 将s节点的关系删除
    graph.erase(graph.begin());

    free(tmp_dis);
    free(tmp_parent);
    free(dis);
    free(parent);
}

int main(int argc, const char* argv[]){
    if(argc < 2){
        printf("./Johnson_algorithm <graph-file-data>");
        exit(0);
    }

    int V;
    // 采用邻接表的方式表示
    vector<vector<AdjNode*> > graph = read_directed_weighted_adjlist(argv[1], V);
    int** dis = allocate_square_matrix(V, MAX_DIST);
    int** parent = allocate_square_matrix(V, -1);

    Johnson_algorithm(graph, V, dis, parent);

    print_all_pair_shortest_distance(dis, V);
    print_all_pair_shortest_paths(parent, V);

    deallocate_square_matrix(dis, V);
    deallocate_square_matrix(parent, V);
}
