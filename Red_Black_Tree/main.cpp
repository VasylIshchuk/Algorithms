#include <iostream>
#include <vector>

using namespace std;
const bool RED = false;
const bool BLACK = true;

struct ListNode {
    string value;
    ListNode *next;
    ListNode *previous;

    ListNode(string &value) : value(value), next(nullptr), previous(nullptr) {}
};

class List {
private:
    ListNode *tail;
    ListNode *head;

    void moveDown(ListNode *targetNode, int offset);

    void moveUp(ListNode *targetNode, int offset);

public:
    ListNode *add(string &value);

    void swap(ListNode *firstNode, ListNode *secondNode);

    void move(ListNode *targetNode, int offset);

    void print();

    void detachNode(ListNode *targetNode);
};

ListNode *List::add(string &value) {
    ListNode *newNode = new ListNode(value);

    if (tail == nullptr) {
        tail = head = newNode;
    } else {
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }

    return newNode;
}

void List::swap(ListNode *firstNode, ListNode *secondNode) {
    std::swap(firstNode->value, secondNode->value);
}

void List::move(ListNode *targetNode, int offset) {
    if (offset == 0) return;

    if (offset > 0) moveUp(targetNode, offset);
    else moveDown(targetNode, offset);
}

void List::moveUp(ListNode *targetNode, int offset) {
    ListNode *current = targetNode;

    while (offset > 0 && current != nullptr) {
        current = current->previous;
        --offset;
    }

    detachNode(targetNode);

    if (current == nullptr) {
        targetNode->next = head;
        head->previous = targetNode;
        targetNode->previous = nullptr;
        head = targetNode;
    } else {
        targetNode->next = current;
        targetNode->previous = current->previous;
        if (current->previous) current->previous->next = targetNode;
        else head = targetNode;
        current->previous = targetNode;
    }
}

void List::moveDown(ListNode *targetNode, int offset) {
    ListNode *current = targetNode;

    while (offset < 0 && current != nullptr) {
        current = current->next;
        ++offset;
    }

    detachNode(targetNode);

    if (current == nullptr) {
        targetNode->previous = tail;
        targetNode->next = nullptr;
        tail->next = targetNode;
        tail = targetNode;
    } else {
        targetNode->previous = current;
        targetNode->next = current->next;
        if (current->next) current->next->previous = targetNode;
        else tail = targetNode;
        current->next = targetNode;
    }
}

void List::detachNode(ListNode *targetNode) {
    if (targetNode->previous) targetNode->previous->next = targetNode->next;
    else head = targetNode->next;

    if (targetNode->next) targetNode->next->previous = targetNode->previous;
    else tail = targetNode->previous;
}

void List::print() {
    ListNode *current = head;
    while (current) {
        cout << current->value << '\n';
        current = current->next;
    }
}

struct TreeNode {
    string value;
    ListNode *listNode;
    bool color;
    TreeNode *left, *right, *parent;

    TreeNode(string &value, ListNode *listNode) : value(value), listNode(listNode), color(RED), left(nullptr),
                                                  right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    TreeNode *root;

    void fixInsert(TreeNode *newNode);

    void handleSpecialSituationRight(TreeNode *&newNode, TreeNode *grandparent);

    void handleSpecialSituationLeft(TreeNode *&newNode, TreeNode *grandparent);

    bool isFirstSituation(TreeNode *uncle);

    void handleFirstSituation(TreeNode *&newNode, TreeNode *grandparent, TreeNode *uncle);

    void handleSecondSituation(TreeNode *&newNode);

    void handleThirdSituation(TreeNode *&newNode, TreeNode *grandparent);

    void rotateLeft(TreeNode *&node);

    void rotateRight(TreeNode *&node);

    TreeNode *search(TreeNode *node, string &value);

public:
    RedBlackTree() : root(nullptr) {}

    void insert(string &value, ListNode *node);

    TreeNode *search(string &value) {
        return search(root, value);
    }
};

void RedBlackTree::insert(string &value, ListNode *node) {
    TreeNode *newNode = new TreeNode(value, node);
    TreeNode *parent = nullptr;
    TreeNode *current = root;

    while (current != nullptr) {
        parent = current;

        if (newNode->value < current->value) current = current->left;
        else current = current->right;
    }

    newNode->parent = parent;

    if (parent == nullptr) {
        root = newNode;
        newNode->color = BLACK;
        return;
    } else if (newNode->value < parent->value) parent->left = newNode;
    else parent->right = newNode;

    if (newNode->parent->parent == nullptr) return;

    fixInsert(newNode);
}

void RedBlackTree::fixInsert(TreeNode *newNode) {
    while (newNode->parent != nullptr && newNode->parent->color == RED) {
        TreeNode *grandparent = newNode->parent->parent;
        if (newNode->parent == grandparent->left) {
            handleSpecialSituationRight(newNode, grandparent);
        } else {
            handleSpecialSituationLeft(newNode, grandparent);
        }
    }

    root->color = BLACK;
}

void RedBlackTree::handleSpecialSituationRight(TreeNode *&newNode, TreeNode *grandparent) {
    TreeNode *uncle = grandparent->right;
    if (isFirstSituation(uncle)) handleFirstSituation(newNode, grandparent, uncle);
    else {
        if (newNode == newNode->parent->right) {
            handleSecondSituation(newNode);
            rotateLeft(newNode);
        }
        handleThirdSituation(newNode, grandparent);
        rotateRight(grandparent);
    }
}

void RedBlackTree::handleSpecialSituationLeft(TreeNode *&newNode, TreeNode *grandparent) {
    TreeNode *uncle = grandparent->left;
    if (isFirstSituation(uncle)) handleFirstSituation(newNode, grandparent, uncle);
    else {
        if (newNode == newNode->parent->left) {
            handleSecondSituation(newNode);
            rotateRight(newNode);
        }
        handleThirdSituation(newNode, grandparent);
        rotateLeft(grandparent);
    }
}

bool RedBlackTree::isFirstSituation(TreeNode *uncle) {
    return uncle != nullptr && uncle->color == RED;
}

void RedBlackTree::handleFirstSituation(TreeNode *&newNode, TreeNode *grandparent, TreeNode *uncle) {
    newNode->parent->color = BLACK;
    uncle->color = BLACK;
    grandparent->color = RED;
    newNode = grandparent;
}

void RedBlackTree::handleSecondSituation(TreeNode *&newNode) {
    newNode = newNode->parent;
}

void RedBlackTree::handleThirdSituation(TreeNode *&newNode, TreeNode *grandparent) {
    newNode->parent->color = BLACK;
    grandparent->color = RED;
}

void RedBlackTree::rotateLeft(TreeNode *&node) {
    TreeNode *rightNode = node->right;

    node->right = rightNode->left;
    if (rightNode->left != nullptr)rightNode->left->parent = node;

    rightNode->parent = node->parent;
    if (node->parent == nullptr) root = rightNode;
    else if (node == node->parent->left) node->parent->left = rightNode;
    else node->parent->right = rightNode;

    rightNode->left = node;
    node->parent = rightNode;
}

void RedBlackTree::rotateRight(TreeNode *&node) {
    TreeNode *rightNode = node->left;

    node->left = rightNode->right;
    if (rightNode->right != nullptr)rightNode->right->parent = node;

    rightNode->parent = node->parent;
    if (node->parent == nullptr) root = rightNode;
    else if (node == node->parent->right) node->parent->right = rightNode;
    else node->parent->left = rightNode;

    rightNode->right = node;
    node->parent = rightNode;
}

TreeNode *RedBlackTree::search(TreeNode *node, string &value) {
    if (node == nullptr || value == node->value) return node;
    if (value < node->value) return search(node->left, value);
    return search(node->right, value);
}


void magic_lines();

int main() {
    magic_lines();

    List *list = new List();
    RedBlackTree *redBlackTree = new RedBlackTree();
    int number_pseudonyms, number_operations;

    cin >> number_pseudonyms;
    for (int i = 0; i < number_pseudonyms; ++i) {
        string pseudonym;
        cin >> pseudonym;
        ListNode *node = list->add(pseudonym);
        redBlackTree->insert(pseudonym, node);
    }

    cin >> number_operations;
    for (int i = 0; i < number_operations; ++i) {
        string operation, firstPseudonym;
        cin >> operation >> firstPseudonym;

        if (operation == "r") {
            string secondPseudonym;
            cin >> secondPseudonym;

            TreeNode *firstTreeNode = redBlackTree->search(firstPseudonym);
            TreeNode *secondTreeNode = redBlackTree->search(secondPseudonym);

            list->swap(firstTreeNode->listNode, secondTreeNode->listNode);
            swap(firstTreeNode->listNode, secondTreeNode->listNode);
        } else if (operation == "a") {
            ListNode *node = list->add(firstPseudonym);
            redBlackTree->insert(firstPseudonym, node);
        } else if (operation == "m") {
            int offset;
            cin >> offset;
            ListNode *node = redBlackTree->search(firstPseudonym)->listNode;
            list->move(node, offset);
        }
    }

    list->print();
    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}