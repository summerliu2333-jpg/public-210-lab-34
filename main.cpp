//COMSC-210-5068, lab 34, Yang Liu
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
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

    gameMap.displayMap();
    gameMap.DFS(0);
    gameMap.BFS(0);

    return 0;
}