#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int LENGTH_DICTIONARY = 101;
const int HASH_MODULUS = INT_MAX;

void magic_lines();

vector<int> read_sequence();

vector<int> algorithm_Rabin_Karp(vector<int> &sequence, vector<int> &pattern_sequence);

long long calculate_highest_weight(int pattern_size);

int calculate_position_next_occurrence(int previous_occurrence_index, int current_occurrence_index, int sequence_size);

int main() {
    magic_lines();

    vector<int> sequence = read_sequence();
    vector<int> pattern_sequence = read_sequence();

    vector<int> occurrence_indexes = algorithm_Rabin_Karp(sequence, pattern_sequence);

    int position_next_occurrence = calculate_position_next_occurrence(occurrence_indexes[0], occurrence_indexes[1],
                                                                      sequence.size());
    cout << position_next_occurrence;

    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

vector<int> read_sequence() {
    int count;
    vector<int> sequence;

    cin >> count;
    for (int i = 0; i < count; ++i) {
        int value;
        cin >> value;
        sequence.push_back(value);
    }

    return sequence;
}

vector<int> algorithm_Rabin_Karp(vector<int> &sequence, vector<int> &pattern_sequence) {
    int sequence_size = sequence.size();
    int pattern_size = pattern_sequence.size();
    long long highest_weight = calculate_highest_weight(pattern_size);
    long long hash_current_window_sequence = 0;
    long long hash_pattern = 0;
    vector<int> occurrence_indexes;

    for (int i = 0; i < pattern_size; ++i) {
        hash_pattern = (LENGTH_DICTIONARY * hash_pattern + pattern_sequence[i]) % HASH_MODULUS;
        hash_current_window_sequence = (LENGTH_DICTIONARY * hash_current_window_sequence + sequence[i]) % HASH_MODULUS;
    }

    int last_possible_index = sequence_size - pattern_size;
    for (int i = 0; i <= last_possible_index; ++i) {

        if (hash_pattern == hash_current_window_sequence) {
            bool match = true;

            for (int j = 0; j < pattern_size; ++j) {
                if (sequence[i + j] != pattern_sequence[j]) {
                    match = false;
                    break;
                }
            }

            if (match) occurrence_indexes.push_back(i);
        }

        if (occurrence_indexes.size() == 2) break;

        if (i < last_possible_index) {
            hash_current_window_sequence =
                    (LENGTH_DICTIONARY * (hash_current_window_sequence - sequence[i] * highest_weight) +
                     sequence[i + pattern_size]) % HASH_MODULUS;

            if (hash_current_window_sequence < 0) hash_current_window_sequence += HASH_MODULUS;
        }
    }

    return occurrence_indexes;
}

long long calculate_highest_weight(int pattern_size) {
    long long highest_weight = 1;
    for (int i = 0; i < pattern_size - 1; ++i) highest_weight = (highest_weight * LENGTH_DICTIONARY) % HASH_MODULUS;
    return highest_weight;
}

int calculate_position_next_occurrence(int previous_occurrence_index, int current_occurrence_index, int sequence_size) {
    int next_occurrence_index = previous_occurrence_index + current_occurrence_index;

    if (next_occurrence_index >= sequence_size) {
        return next_occurrence_index - sequence_size;
    }

    return calculate_position_next_occurrence(current_occurrence_index, next_occurrence_index, sequence_size);
}


