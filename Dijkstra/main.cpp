#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

void magic_lines();

void add_or_update_edge(vector<vector<pair<int, int>>> &graph, int graph_index, int stop_index, int weight);

void connect_adjacent_stops(vector<vector<pair<int, int>>> &graph, vector<pair<int, int>> &stops, int stop_index);

int dijkstras_algorithm(vector<vector<pair<int, int>>> &graph, int start_stop, int end_stop);

int main() {
    magic_lines();

    int stop_count;
    vector<pair<int, int>> stops_sorted_by_x;
    vector<pair<int, int>> stops_sorted_by_y;

    cin >> stop_count;

    for (int i = 0; i < stop_count; ++i) {
        int x, y;
        cin >> x >> y;
        stops_sorted_by_x.push_back({x, i});
        stops_sorted_by_y.push_back({y, i});
    }

    int start_stop, end_stop;
    cin >> start_stop >> end_stop;

    sort(stops_sorted_by_x.begin(), stops_sorted_by_x.end());
    sort(stops_sorted_by_y.begin(), stops_sorted_by_y.end());

    vector<vector<pair<int, int>>> graph(stop_count);
    for (int i = 0; i < stop_count - 1; ++i) {
        connect_adjacent_stops(graph, stops_sorted_by_x, i);
        connect_adjacent_stops(graph, stops_sorted_by_y, i);
    }

    cout << dijkstras_algorithm(graph, start_stop, end_stop);

    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

void connect_adjacent_stops(vector<vector<pair<int, int>>> &graph, vector<pair<int, int>> &stops, int stop_index) {
    int from_stop = stops[stop_index].second;
    int to_stop = stops[stop_index + 1].second;
    int weight = stops[stop_index + 1].first - stops[stop_index].first;

    add_or_update_edge(graph, from_stop, to_stop, weight);
    add_or_update_edge(graph, to_stop, from_stop, weight);
}

void add_or_update_edge(vector<vector<pair<int, int>>> &graph, int graph_index, int stop_index, int weight) {
    bool updated = false;
    for (int i = 0; i < graph[graph_index].size(); ++i) {
        if (graph[graph_index][i].second == stop_index) {
            if (weight < graph[graph_index][i].first) {
                graph[graph_index][i].first = weight;
            }
            updated = true;
            break;
        }
    }
    if (!updated) {
        graph[graph_index].push_back({weight, stop_index});
    }
}

int dijkstras_algorithm(vector<vector<pair<int, int>>> &graph, int start_stop, int end_stop) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> priorityQueue;
    vector<int> distances(graph.size(), INT_MAX);

    priorityQueue.push({0, start_stop});
    distances[start_stop] = 0;

    while (!priorityQueue.empty()) {
        int current_distance = priorityQueue.top().first;
        int current_stop = priorityQueue.top().second;
        priorityQueue.pop();

        if (current_stop == end_stop) return current_distance;

        for (int i = 0; i < graph[current_stop].size(); ++i) {
            int weight = graph[current_stop][i].first;
            int next_stop = graph[current_stop][i].second;

            if (current_distance + weight < distances[next_stop]) {
                distances[next_stop] = distances[current_stop] + weight;
                priorityQueue.push({distances[next_stop], next_stop});
            }
        }
    }
}

