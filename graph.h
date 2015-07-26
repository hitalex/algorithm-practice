#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

/*
    邻接矩阵的图表示处理
*/

// make a empty graph
int** make_empty_graph(int V){
    int** graph;
    graph = (int**)malloc(V * sizeof(int*));
    int i, j;
    for(i=0; i<V; i++){
        graph[i] = (int*)malloc(V * sizeof(int));
        for(j=0; j<V; j++){
            graph[i][j] = 0;
        }
    }

    return graph;
}

int** read_unweighted_graph(char* path, int& V, bool is_directed){
    cout << "Reading undirected unweighted graph..." << endl;
    fstream fs(path, fstream::in);
    fs >> V; // number of vertices
    int** graph = make_empty_graph(V);

    int v1, v2;
    while(fs >> v1 >> v2){
        assert(v1 >= 0  && v1 < V);
        assert(v2 >= 0  && v2 < V);
        graph[v1][v2] = 1;
        if(!is_directed)
            graph[v2][v1] = 1;
    }

    fs.close();

    return graph;
}

int** read_weighted_graph(char* path, int& V, bool is_directed){
    cout << "Reading undirected weighted graph..." << endl;
    fstream fs(path, fstream::in);
    fs >> V; // number of vertices
    int i, j;
    int** graph = make_empty_graph(V);

    int v1, v2, w;
    while(fs >> v1 >> v2 >> w){
        assert(v1 >= 0  && v1 < V);
        assert(v2 >= 0  && v2 < V);
        graph[v1][v2] = w;
        if(!is_directed)
            graph[v2][v1] = w;
    }

    fs.close();

    return graph;
}

int** read_undirected_unweighted_graph(char* path, int& V){
    return read_unweighted_graph(path, V, false);
}
int** read_directed_unweighted_graph(char* path, int& V){
    return read_unweighted_graph(path, V, true);
}

int** read_undirected_weighted_graph(char* path, int& V){
    return read_weighted_graph(path, V, false);
}
int** read_directed_weighted_graph(char* path, int& V){
    return read_weighted_graph(path, V, true);
}

void print_graph(int** graph, int V){
    cout << "Num. of vertice: " << V << endl;
    int i, j;
    for(i=0; i<V; i++){
        for(j=0; j<V; j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

/*
    Edge list表示方式
*/
struct Edge{
    int from;
    int to;
    int w;
};

vector<Edge*> read_directed_weighted_edgelist(const char* path, int&V){
    vector<Edge*> edgelist;
    fstream f(path, fstream::in);
    f >> V;
    int from, to, w;
    while(f >> from >> to >> w){
        assert(from>=0 && from<V);
        assert(to>=0 && to<V);
        Edge* p = new Edge;
        p->from = from;
        p->to = to;
        p->w = w;
        edgelist.push_back(p);
    }

    return edgelist;
}


/*
    邻接表的图表示
*/

struct AdjNode{
    int v;
    int w;
};

vector< vector<AdjNode*> > read_directed_weighted_adjlist(const char* path, int& V){
    vector< vector<AdjNode*> > adjlist;
    fstream f(path, fstream::in);
    f >> V;
    for(int i=0; i<V; i++){
        vector<AdjNode*> tmp;
        adjlist.push_back(tmp); // 压入空链表
    }
    int from, to, w;
    while(f >> from >> to >> w){
        assert(from>=0 && from<V);
        assert(to>=0 && to<V);
        AdjNode *p = new AdjNode;
        p->v = to;
        p->w = w;
        adjlist[from].push_back(p);
    }

    return adjlist;
}

void print_adjlist_graph(vector<vector<AdjNode*> > graph, int V){
    int i;
    cout << "Num. of vertice: " << V << endl;
    for(i=0; i<V; i++){
        vector<AdjNode*> tolist = graph[i];
        for(int j=0; j<tolist.size(); j++){
            cout << i << " -> " << tolist[j]->v << " with weight: " << tolist[j]->w << endl;
        }
    }
}

/// 关于输出路径的函数

void print_path(int* parent, int s, int v){
    if(s == v){
        cout << s;
    }else{
        if(parent[v] == -1){
            cout << "No path from " << s << " to " << v;
        }else{
            print_path(parent, s, parent[v]);
            cout << " -> " << v;
        }
    }
}

// print paths to all destinations from single source
void print_all_destination_paths(int* parent, int V, int source){
    int i;
    for(i=0; i<V; i++){
        if(i != source){
            cout << "Path from " << source << " to " << i << ": ";
            print_path(parent, source, i);
            cout << endl;
        }
    }
}
