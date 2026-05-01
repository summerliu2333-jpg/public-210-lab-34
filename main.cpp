//COMSC-210-5068, lab 34, Yang Liu
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <limits>
using namespace std;

struct Edge {
    int to;
    int danger;
};

class GameMap {
private:
    vector<vector<Edge>> adjList;
    vector<string> locations;

public:
    GameMap() {
        locations = {
            "Spawn Camp",
            "Old Bridge",
            "Forest Path",
            "Abandoned Tower",
            "Supply Depot",
            "River Crossing",
            "Enemy Outpost",
            "Mountain Pass",
            "Final Base"
        };

        adjList.resize(locations.size());

        addEdge(0, 1, 8);
        addEdge(0, 2, 21);
        addEdge(1, 2, 6);
        addEdge(1, 3, 5);
        addEdge(1, 4, 4);
        addEdge(2, 7, 11);
        addEdge(2, 8, 8);
        addEdge(3, 4, 9);
        addEdge(5, 6, 10);
        addEdge(5, 7, 15);
        addEdge(5, 8, 5);
        addEdge(6, 7, 3);
        addEdge(6, 8, 7);
    }

    void addEdge(int from, int to, int danger) {
        adjList[from].push_back({to, danger});
        adjList[to].push_back({from, danger});
    }

    void displayMap() {
        cout << "\nGame Map Navigation Network:\n";
        cout << "Each node is a game location.\n";
        cout << "Each edge is a possible route.\n";
        cout << "Edge weight represents danger level.\n";
        cout << "Lower danger level means a safer route.\n";
        cout << "========================================\n";

        for (int i = 0; i < adjList.size(); ++i) {
            cout << i << " - " << locations[i] << " connects to:\n";
            for (const Edge& edge : adjList[i]) {
                cout << "  -> " << edge.to << " - " << locations[edge.to]
                     << " | danger level: " << edge.danger << endl;
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(adjList.size(), false);
        stack<int> s;

        s.push(start);

        cout << "\nDFS Exploration from " << locations[start] << ":\n";
        cout << "========================================\n";

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << "Exploring " << current << " - " << locations[current] << endl;

                for (const Edge& edge : adjList[current]) {
                    if (!visited[edge.to]) {
                        cout << "  -> Possible path to "
                             << edge.to << " - " << locations[edge.to]
                             << " | danger level: " << edge.danger << endl;
                        s.push(edge.to);
                    }
                }
            }
        }
    }

    void safestPaths(int start) {
        const int INF = numeric_limits<int>::max();
        int n = adjList.size();

        vector<int> dist(n, INF);
        vector<bool> visited(n, false);

        dist[start] = 0;

        for (int count = 0; count < n - 1; ++count) {
            int current = -1;

            for (int i = 0; i < n; ++i) {
                if (!visited[i] && (current == -1 || dist[i] < dist[current])) {
                    current = i;
                }
            }

            if (current == -1 || dist[current] == INF) {
                break;
            }

            visited[current] = true;

            for (const Edge& edge : adjList[current]) {
                int next = edge.to;

                if (!visited[next] && dist[current] + edge.danger < dist[next]) {
                    dist[next] = dist[current] + edge.danger;
                }
            }
        }

        cout << "\nSafest paths from " << locations[start] << ":\n";
        cout << "========================================\n";

        for (int i = 0; i < n; ++i) {
            cout << start << " -> " << i << " : ";

            if (dist[i] == INF) {
                cout << "unreachable\n";
            } else {
                cout << dist[i] << " total danger\n";
            }
        }
    }

    void minimumDangerTree() {
        const int INF = numeric_limits<int>::max();
        int n = adjList.size();

        vector<int> key(n, INF);
        vector<int> parent(n, -1);
        vector<bool> inMST(n, false);

        key[0] = 0;

        for (int count = 0; count < n - 1; ++count) {
            int current = -1;

            for (int i = 0; i < n; ++i) {
                if (!inMST[i] && (current == -1 || key[i] < key[current])) {
                    current = i;
                }
            }

            if (current == -1) {
                break;
            }

            inMST[current] = true;

            for (const Edge& edge : adjList[current]) {
                int next = edge.to;

                if (!inMST[next] && edge.danger < key[next]) {
                    key[next] = edge.danger;
                    parent[next] = current;
                }
            }
        }

        cout << "\nMinimum Danger Spanning Tree:\n";
        cout << "========================================\n";

        for (int i = 1; i < n; ++i) {
            if (parent[i] != -1) {
                cout << "Edge from " << parent[i] << " - " << locations[parent[i]]
                     << " to " << i << " - " << locations[i]
                     << " | danger level: " << key[i] << endl;
            }
        }
    }

    void BFS(int start) {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Scouting from " << locations[start] << ":\n";
        cout << "========================================\n";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << "Checking " << current << " - " << locations[current] << endl;

            for (const Edge& edge : adjList[current]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    cout << "  -> Next reachable area: "
                         << edge.to << " - " << locations[edge.to]
                         << " | danger level: " << edge.danger << endl;
                    q.push(edge.to);
                }
            }
        }
    }
};

int main() {
    GameMap gameMap;
    int choice;

    do {
        cout << "\nGame Map Navigation Menu:\n";
        cout << "[1] Display game map\n";
        cout << "[2] Scout nearby safe zones (BFS)\n";
        cout << "[3] Explore deep dangerous routes (DFS)\n";
        cout << "[4] Find safest paths\n";
        cout << "[5] Build minimum danger network\n";
        cout << "[0] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                gameMap.displayMap();
                break;
            case 2:
                gameMap.BFS(0);
                break;
            case 3:
                gameMap.DFS(0);
                break;
            case 4:
                gameMap.safestPaths(0);
                break;
            case 5:
                gameMap.minimumDangerTree();
                break;
            case 0:
                cout << "Program exited.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}