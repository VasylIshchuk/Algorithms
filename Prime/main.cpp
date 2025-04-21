#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

void magic_lines();

double calculateSurvivalProbability(int node_count, const vector<vector<pair<double, int>>> &graph);

int main() {
    magic_lines();

    int node_count, edge_count;
    cin >> node_count >> edge_count;

    if (node_count == 0) {
        cout << fixed << setprecision(5) << 0.0;
        return 0;
    }

    vector<vector<pair<double, int>>> graph(node_count);

    for (int i = 0; i < edge_count; ++i) {
        int from_node, to_node;
        double weight;

        cin >> from_node >> to_node >> weight;

        graph[from_node].push_back({weight, to_node});
        graph[to_node].push_back({weight, from_node});
    }

    cout << fixed << setprecision(5) << calculateSurvivalProbability(node_count, graph);

    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

double calculateSurvivalProbability(int node_count, const vector<vector<pair<double, int>>> &graph) {
    if (node_count == 1) {
        return 1.0;
    }

    double probability_survival = 1;
    priority_queue<pair<double, int>> priorityQueue;
    vector<bool> visited(node_count, false);

    priorityQueue.push(graph[0][0]);
    visited[0] = true;

    for (int i = 0; i < graph[0].size(); ++i) {
        if (!visited[graph[0][i].second]) priorityQueue.push(graph[0][i]);
    }

    while (!priorityQueue.empty()) {
        double value = priorityQueue.top().first;
        int index_node = priorityQueue.top().second;
        priorityQueue.pop();

        if (visited[index_node]) {
            continue;
        }

        visited[index_node] = true;
        probability_survival *= value;

        for (int i = 0; i < graph[index_node].size(); ++i) {
            if (visited[graph[index_node][i].second]) continue;

            priorityQueue.push(graph[index_node][i]);
        }
    }
    return probability_survival;
}
