#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

struct Edge{ // ребро
    int to_;
    int weight_;

    Edge(int to, int weight){
        to_ = to;
        weight_ = weight;
    }
};

struct Node{ //вершина
    int id_;
    vector<Edge> edges;

    Node(int id){
        id_ = id;
    }

    void addEdge(int to, int weight){
        edges.emplace_back(to, weight);
    }

};

void dfs(vector<Node> &graph){
    vector<bool> visited(graph.size(), false);
    stack<int> s;

    for(int i = 0; i < graph.size(); i++){
        if (!visited[i]){
            visited[i] = true;
            s.push(i);

            while (!s.empty()){
                int u = s.top();
                s.pop();
                for (int j = 0; j < graph[u].edges.size(); j++){
                    if(!visited[graph[u].edges[j].to_]){
                        visited[graph[u].edges[j].to_] = true;
                        s.push((graph[u].edges[j].to_));
                    }
                }
            }
        }
    }
}

void bfs(vector<Node> &graph) { // обход в ширину
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    for(int n = 0; n < graph.size(); n++){
        if(!visited[n]) {
            visited[n] = true;
            q.push(n);

            while (!q.empty()) {
                int i = q.front();
                q.pop();
                for (int j = 0; j < (int) graph[i].edges.size(); j++) {
                    int v = graph[i].edges[j].to_;
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
}



void dijkstra_algorithm (vector <Node> &graph, int u){
    vector <vector <int>> mtrx(graph.size(), vector<int> (graph.size(), INT32_MAX));

    for (int i = 0; i < graph.size(); i++){
        for (int j = 0; j < graph[i].edges.size(); j++){
            if (i == j)
                mtrx[i][j] = 0;
            else{
                mtrx[i][graph[i].edges[j].to_] = graph[i].edges[j].weight_;
            }
        }
    }

    vector<int> min_dist(graph.size(), INT32_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    min_dist[u] = 0;

    q.push(make_pair(0, u));
    while (!q.empty()) {
        pair<int, int> v = q.top();
        q.pop();
        if (v.first > min_dist[v.second])
            continue;
        for (int i = 0; i < graph.size(); i++) {
            int to = i;
            int len = mtrx[v.second][i];
            if (min_dist[to] > min_dist[v.second] + len) {
                min_dist[to] = min_dist[v.second] + len;
                q.push(make_pair(min_dist[to], to));
            }
        }
    }
};

void algorithm_floid (vector<Node> &graph, int u){
  vector<vector<int>> mtrx(graph.size(), vector<int>(graph.size(), INT32_MAX));

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].edges.size(); ++j) {
            if (i == j) {
                mtrx[i][j] = 0;
            } else {
                mtrx[i][graph[i].edges[j].to_] = graph[i].edges[j].weight_;
            }
        }
    }

    for (int k = 0; k < graph.size(); k++) {	//Пробегаемся по всем вершинам и ищем более короткий путь через вершину k
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                mtrx[i][j] = min(mtrx[i][j], mtrx[i][k] + mtrx[k][j]);	//Новое значение ребра равно минимальному между старым ребром и суммой ребер
            }
        }
    }
    vector<int>dist = mtrx[u];

};

int main() {

    int count_of_nodes, count_of_edges;
    vector<Node> graph;

    cout << "Enter count of nodes: ";
    cin >> count_of_nodes;

    for (int i = 0; i < count_of_nodes; i++){
        cout << "Enter count of edges at node number " << i << endl;
        cin >> count_of_edges;
        Node el(i);
        for (int j = 1; j <= count_of_edges; j++){
            int id, weight;
            cout << "Enter ID of node for edge number " << j << endl;
            cin >> id;
            cout << "Enter WEIGTH of edge number " << j << endl;
            cin >> weight;
            el.addEdge(id, weight);
        }
        graph.push_back(el);
    }



    return 0;
}
