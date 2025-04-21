#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <queue>

using namespace std;
const int NOT_PAIRED = 0;
const int INFINITY_DISTANCE = INT_MAX;

class BipartiteGraph {
private:
    int size_left_side;
    int size_right_size;

    vector<vector<int>> neighbors_of_left_side;

    vector<int> matched_right_for_left_side;
    vector<int> matched_left_for_right_side;

    vector<int> bfs_level;

    bool BFS();

    bool DFS(int u);

public:
    BipartiteGraph(int size_left_side, int size_right_size);

    void add_edge(int left_value, int right_value);

    int maximum_matching();

};

BipartiteGraph::BipartiteGraph(int size_left_side, int size_right_size) {
    this->size_left_side = size_left_side;
    this->size_right_size = size_right_size;

    neighbors_of_left_side.resize(size_left_side + 1);

    matched_right_for_left_side.assign(size_left_side + 1, NOT_PAIRED);
    matched_left_for_right_side.assign(size_right_size + 1, NOT_PAIRED);

    bfs_level.assign(size_left_side + 1, 0);
}

void BipartiteGraph::add_edge(int left_value, int right_value) {
    neighbors_of_left_side[left_value].push_back(right_value);
}

int BipartiteGraph::maximum_matching() {
    int matching = 0;

    while (BFS()) {
        for (int node_left_side = 1; node_left_side <= size_left_side; ++node_left_side) {
            if (matched_right_for_left_side[node_left_side] == NOT_PAIRED) {
                if (DFS(node_left_side)) {
                    ++matching;
                }
            }
        }
    }

    return matching;
}

bool BipartiteGraph::BFS() {
    queue<int> queue;

    for (int node_left_side = 1; node_left_side <= size_left_side; ++node_left_side) {
        if (matched_right_for_left_side[node_left_side] == NOT_PAIRED) {
            bfs_level[node_left_side] = 0;
            queue.push(node_left_side);
        } else {
            bfs_level[node_left_side] = INFINITY_DISTANCE;
        }
    }

    bfs_level[NOT_PAIRED] = INFINITY_DISTANCE;

    while (!queue.empty()) {
        int node_left_side = queue.front();
        queue.pop();

        if (bfs_level[node_left_side] < bfs_level[NOT_PAIRED]) {
            for (int node_right_side: neighbors_of_left_side[node_left_side]) {
                if (bfs_level[matched_left_for_right_side[node_right_side]] == INFINITY_DISTANCE) {
                    bfs_level[matched_left_for_right_side[node_right_side]] = bfs_level[node_left_side] + 1;
                    queue.push(matched_left_for_right_side[node_right_side]);
                }
            }
        }
    }

    return bfs_level[NOT_PAIRED] != INFINITY_DISTANCE;

}

bool BipartiteGraph::DFS(int node_left_side) {
    if (node_left_side != NOT_PAIRED) {
        for (int node_right_side: neighbors_of_left_side[node_left_side]) {
            if (bfs_level[matched_left_for_right_side[node_right_side]] == bfs_level[node_left_side] + 1) {
                if (DFS(matched_left_for_right_side[node_right_side])) {
                    matched_right_for_left_side[node_left_side] = node_right_side;
                    matched_left_for_right_side[node_right_side] = node_left_side;
                    return true;
                }
            }
        }
        bfs_level[node_left_side] = INFINITY_DISTANCE;
        return false;
    }
    return true;
}


struct BoardData {
    vector<vector<int>> board;
    int size;

    BoardData(int n) : size(n), board(n, vector<int>(n)) {}
};

struct PieceMapping {
    map<pair<int, int>, int> black_coords;
    map<pair<int, int>, int> white_coords;
    int black_count = 0;
    int white_count = 0;
};

void magic_lines();

void map_active_pawns(BoardData &board_data, PieceMapping &mapping);

bool is_black_tile(int x, int y);

BipartiteGraph *build_graph(BoardData &board_data, PieceMapping &mapping);

bool is_active_pawn(int x, int y, BoardData &board_data);

bool is_valid_target(int x, int y, BoardData &board_data);

bool in_bounds(int x, int y, int size);

vector<pair<int, int>> get_targets(int x, int y, int type);

int main() {
    magic_lines();

    int board_size;
    cin >> board_size;
    BoardData board_data(board_size);

    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            cin >> board_data.board[i][j];
        }
    }

    PieceMapping mapping;
    map_active_pawns(board_data, mapping);

    BipartiteGraph *bipartite_graph = build_graph(board_data, mapping);

    cout << (board_size * board_size) - bipartite_graph->maximum_matching();

    delete bipartite_graph;
    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

void map_active_pawns(BoardData &board_data, PieceMapping &mapping) {
    for (int i = 0; i < board_data.size; ++i) {
        for (int j = 0; j < board_data.size; ++j) {
            if (!is_active_pawn(i, j, board_data)) continue;

            pair<int, int> coordinate = {i, j};
            if (is_black_tile(i, j)) {
                mapping.black_coords[coordinate] = ++mapping.black_count;
            } else {
                mapping.white_coords[coordinate] = ++mapping.white_count;
            }
        }
    }
}

bool is_black_tile(int x, int y) {
    return (x + y) % 2 == 0;
}


BipartiteGraph *build_graph(BoardData &board_data, PieceMapping &mapping) {
    BipartiteGraph *graph = new BipartiteGraph(mapping.black_count, mapping.white_count);

    for (int x = 0; x < board_data.size; ++x) {
        for (int y = 0; y < board_data.size; ++y) {
            if (!is_black_tile(x, y) || !is_active_pawn(x, y, board_data)) continue;

            int attacker_id = mapping.black_coords.at({x, y});
            vector<pair<int, int>> targets = get_targets(x, y, board_data.board[x][y]);

            for (int i = 0; i < targets.size(); ++i) {
                int target_x = targets[i].first;
                int target_y = targets[i].second;

                if (is_valid_target(target_x, target_y, board_data)) {
                    int target_id = mapping.white_coords.at({target_x, target_y});
                    graph->add_edge(attacker_id, target_id);
                }
            }
        }
    }

    return graph;
}

bool is_active_pawn(int x, int y, BoardData &board_data) {
    return board_data.board[x][y] != 0;
}

bool is_valid_target(int x, int y, BoardData &board_data) {
    return in_bounds(x, y, board_data.size) && is_active_pawn(x, y, board_data) && !is_black_tile(x, y);
}

bool in_bounds(int x, int y, int size) {
    return (x >= 0 && x < size) && (y >= 0 && y < size);
}

vector<pair<int, int>> get_targets(int x, int y, int type) {
    vector<pair<int, int>> targets;

    if (type == 1) {
        targets.push_back({x, y + 3});
        targets.push_back({x - 1, y + 2});
        targets.push_back({x + 1, y + 2});
    } else if (type == 2) {
        targets.push_back({x, y + 1});
        targets.push_back({x - 1, y});
        targets.push_back({x + 1, y});
    } else if (type == 3) {
        targets.push_back({x, y + 1});
        targets.push_back({x - 1, y + 2});
        targets.push_back({x + 1, y + 2});
    }

    return targets;
}

