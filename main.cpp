//COMSC-210-5068, lab 34, Yang Liu
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct Edge {
    int to;
    int weight;
};

class Graph {
private:
    vector<vector<Edge>> adjList;

public:
    Graph(int vertices) {
        adjList.resize(vertices);
    }

    void addEdge(int from, int to, int weight) {
        adjList[from].push_back({to, weight});
        adjList[to].push_back({from, weight});
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;

        for (int i = 0; i < adjList.size(); ++i) {
            cout << i << " --> ";
            for (const Edge& edge : adjList[i]) {
                cout << "(" << edge.to << ", " << edge.weight << ") ";
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(adjList.size(), false);
        stack<int> s;

        s.push(start);

        cout << "DFS starting from vertex " << start << ":" << endl;

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";

                for (const Edge& edge : adjList[current]) {
                    if (!visited[edge.to]) {
                        s.push(edge.to);
                    }
                }
            }
        }

        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << current << " ";

            for (const Edge& edge : adjList[current]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }

        cout << endl;
    }
};

int main() {
    Graph graph(9);

    graph.addEdge(0, 1, 8);
    graph.addEdge(0, 2, 21);
    graph.addEdge(1, 2, 6);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 7, 11);
    graph.addEdge(2, 8, 8);
    graph.addEdge(3, 4, 9);
    graph.addEdge(5, 6, 10);
    graph.addEdge(5, 7, 15);
    graph.addEdge(5, 8, 5);
    graph.addEdge(6, 7, 3);
    graph.addEdge(6, 8, 7);

    graph.printGraph();
    cout << endl;

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}