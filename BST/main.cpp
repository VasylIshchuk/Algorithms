#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node *root;

    Node *insert(Node *node, int value);

    Node *trimBST(Node *node, int low, int high);

    void inorderToArray(Node *node, vector<int> &arr);

public:
    BST() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void trimBST(int low, int high) {
        root = trimBST(root, low, high);
    }

    void find_pair_by_sum(int sum) {
        vector<int> arr;
        inorderToArray(root, arr);

        int i = 0;
        int j = arr.size() - 1;
        int difference = INT_MAX;
        pair<int, int> pair;
        bool found_pair = false;

        while (i < j) {
            int current_sum = arr[i] + arr[j];
            if (current_sum == sum) {
                int current_different = arr[j] - arr[i];
                if (current_different < difference) {
                    pair = {arr[i], arr[j]};
                    found_pair = true;
                }
                ++i;
                --j;
            } else if (current_sum < sum) ++i;
            else --j;
        }

        if (found_pair) cout << pair.first << ' ' << pair.second;
        else cout << "NIE ZNALEZIONO";
    }
};

Node *BST::insert(Node *node, int value) {
    if (node == nullptr) return new Node(value);
    else if (value < node->value) node->left = insert(node->left, value);
    else node->right = insert(node->right, value);
    return node;
}

Node *BST::trimBST(Node *node, int low, int high) {
    if (node == nullptr) return nullptr;

    // Check if the node's value is outside the [low, high] range.
    // If it's too small, move to the right subtree; if too large, move to the left.
    if (node->value < low)
        return trimBST(node->right, low, high);

    if (node->value > high)
        return trimBST(node->left, low, high);

    node->left = trimBST(node->left, low, high);
    node->right = trimBST(node->right, low, high);

    return node;
}

void BST::inorderToArray(Node *node, vector<int> &arr) {
    if (node == nullptr) return;
    inorderToArray(node->left, arr);
    arr.push_back(node->value);
    inorderToArray(node->right, arr);
}

void magic_lines();

int main() {
    magic_lines();

    BST *tree_BST = new BST();
    int numberOfTrails, low, high, sum;

    cin >> numberOfTrails;
    for (int i = 0; i < numberOfTrails; ++i) {
        int politicalInfluence;
        cin >> politicalInfluence;
        tree_BST->insert(politicalInfluence);
    }
    cin >> low >> high >> sum;


    tree_BST->trimBST(low, high);
    tree_BST->find_pair_by_sum(sum);

    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}
