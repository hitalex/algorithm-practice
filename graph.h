#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#define MAX_DIST 10000

using namespace std;

/*
    邻接矩阵的图表示处理
*/

// make a empty graph
int** make_empty_graph(int V);

int** read_unweighted_graph(const char* path, int& V, bool is_directed);
int** read_weighted_graph(const char* path, int& V, bool is_directed);

int** read_undirected_unweighted_graph(const char* path, int& V);
int** read_directed_unweighted_graph(const char* path, int& V);
int** read_undirected_weighted_graph(const char* path, int& V);
int** read_directed_weighted_graph(const char* path, int& V);

void print_graph(int** graph, int V);

/*
    Edge list表示方式
*/
struct Edge{
    int from;
    int to;
    int w;
};

vector<Edge*> read_directed_weighted_edgelist(const char* path, int&V);


/*
    邻接表的图表示
*/

struct AdjNode{
    int v;
    int w;
};

vector< vector<AdjNode*> > read_directed_weighted_adjlist(const char* path, int& V);

void print_adjlist_graph(vector<vector<AdjNode*> > graph, int V);

/// 关于输出路径的函数

void print_path(int* parent, int s, int v);

// print paths to all destinations from single source
void print_all_destination_paths(int* parent, int V, int source);

void print_all_pair_shortest_paths(int** parent, int V);

void print_shortest_distance(int* dis, int V);
void print_all_pair_shortest_distance(int** dis, int V);

#endif
