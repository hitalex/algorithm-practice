#include <iostream>
#include <fstream>

using namespace std;

/*
    包含图处理相关的helper function
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
    cout << endl;
}
