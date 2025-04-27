#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Entry {
    string name;
    string definition;
};

static int getChildIndexForInsertion(const string &existingEntryName, const string &newEntryName) {
    int index = 0;
    if (existingEntryName < newEntryName)
        ++index;
    return index;
}


class BTreeNode {
private:
    Entry *entries;
    int minDegree;
    BTreeNode **children;
    int keyCount;
    bool leaf;

    int calculateMaxKeys() const;

    void copySecondHalfEntries(BTreeNode *&newRightChild, BTreeNode *&fullChild);

    void copySecondHalfChildren(BTreeNode *&newRightChild, BTreeNode *&fullChild);

    void shiftChildrenRightFrom(int start_index);

    void shiftEntriesRightFrom(int start_index);

    int findInsertPosition(const string &name) const;

    bool isDuplicateEntry(int i, const Entry &entry);

public:
    BTreeNode(int minDegree, bool leaf);

    void addEntry(int index, Entry &entry);

    bool isFull();

    string getEntryName(int index);

    string getEntryDefinition(int index);

    void addChild(int index, BTreeNode *child);

    BTreeNode *&getChild(int index);

    int getKeyCount() const;

    void increaseKeyCount();

    bool isLeaf() const;

    void splitChild(int index, BTreeNode *fullChild);

    void insertNonFull(Entry &entry);
};

BTreeNode::BTreeNode(int minDegree, bool leaf) : minDegree(minDegree), leaf(leaf), keyCount(0) {
    int max_keys = calculateMaxKeys();
    entries = new Entry[max_keys];
    children = new BTreeNode *[2 * minDegree];
}

int BTreeNode::calculateMaxKeys() const {
    return 2 * minDegree - 1;
}

void BTreeNode::addEntry(int index, Entry &entry) {
    entries[index] = entry;
}

bool BTreeNode::isFull() {
    return keyCount == calculateMaxKeys();
}

string BTreeNode::getEntryName(int index) {
    return entries[index].name;
}

string BTreeNode::getEntryDefinition(int index) {
    return entries[index].definition;
}

void BTreeNode::addChild(int index, BTreeNode *child) {
    children[index] = child;
}

BTreeNode *&BTreeNode::getChild(int index) {
    return children[index];
}

int BTreeNode::getKeyCount() const {
    return keyCount;
}

void BTreeNode::increaseKeyCount() {
    ++keyCount;
}

bool BTreeNode::isLeaf() const {
    return leaf;
}

void BTreeNode::splitChild(int child_index, BTreeNode *fullChild) {
    BTreeNode *newRightChild = new BTreeNode(fullChild->minDegree, fullChild->leaf);
    newRightChild->keyCount = minDegree - 1;

    copySecondHalfEntries(newRightChild, fullChild);
    copySecondHalfChildren(newRightChild, fullChild);
    fullChild->keyCount = minDegree - 1;

    shiftChildrenRightFrom(child_index);
    children[child_index + 1] = newRightChild;

    shiftEntriesRightFrom(child_index);
    entries[child_index] = fullChild->entries[minDegree - 1];

    increaseKeyCount();
}

void BTreeNode::copySecondHalfEntries(BTreeNode *&newRightChild, BTreeNode *&fullChild) {
    for (int i = 0; i < minDegree - 1; ++i)
        newRightChild->entries[i] = fullChild->entries[i + minDegree];
}

void BTreeNode::copySecondHalfChildren(BTreeNode *&newRightChild, BTreeNode *&fullChild) {
    if (!fullChild->isLeaf()) {
        for (int i = 0; i < minDegree; ++i)
            newRightChild->children[i] = fullChild->children[i + minDegree];
    }
}

void BTreeNode::shiftChildrenRightFrom(int start_index) {
    for (int i = keyCount; i >= start_index + 1; --i) {
        children[i + 1] = children[i];
    }
}

void BTreeNode::shiftEntriesRightFrom(int start_index) {
    for (int i = keyCount - 1; i >= start_index; --i) {
        entries[i + 1] = entries[i];
    }
}

void BTreeNode::insertNonFull(Entry &entry) {
    int index = findInsertPosition(entry.name);
    if (isDuplicateEntry(index, entry)) {
        entries[index].definition = entry.definition;
        return;
    }

    ++index;
    if (isLeaf()) {
        shiftEntriesRightFrom(index);
        entries[index] = entry;
        increaseKeyCount();
    } else {
        BTreeNode *targetChild = children[index];

        if (targetChild->isFull()) {
            splitChild(index, targetChild);
            index += getChildIndexForInsertion(entries[index].name, entry.name);
        }

        children[index]->insertNonFull(entry);
    }
}

int BTreeNode::findInsertPosition(const std::string &name) const {
    int i = keyCount - 1;
    while (i >= 0 && entries[i].name > name) {
        --i;
    }
    return i;
}

bool BTreeNode::isDuplicateEntry(int i, const Entry &entry) {
    return i >= 0 && entries[i].name == entry.name;
}


class BTree {
private:
    BTreeNode *root;
    int minDegree;

    string search(BTreeNode *node, const string &name);

public:
    BTree(int minDegree);

    void insert(Entry &entry);

    string search(const string &name) {
        if (root == nullptr) {
            return "BRAK";
        } else {
            return search(root, name);
        }
    };
};

BTree::BTree(int minDegree) : minDegree(minDegree) {
    root = nullptr;
}

void BTree::insert(Entry &entry) {
    if (root == nullptr) {
        root = new BTreeNode(minDegree, true);
        root->addEntry(0, entry);
        root->increaseKeyCount();
    } else {
        if (root->isFull()) {
            BTreeNode *newRoot = new BTreeNode(minDegree, false);
            newRoot->addChild(0, root);
            newRoot->splitChild(0, root);

            int child_index = getChildIndexForInsertion(newRoot->getEntryName(0), entry.name);
            newRoot->getChild(child_index)->insertNonFull(entry);

            root = newRoot;
        } else root->insertNonFull(entry);
    }
}

string BTree::search(BTreeNode *node, const string &name) {
    int i = 0;
    int key_count = node->getKeyCount();

    while (i < key_count && name > node->getEntryName(i)) ++i;

    if (i < key_count && name == node->getEntryName(i)) return node->getEntryDefinition(i);

    if (node->isLeaf()) return "BRAK";

    return search(node->getChild(i), name);
}


void magic_lines();

int main() {
    magic_lines();

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    BTree *tree = new BTree(20);

    string line;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);

        size_t colon_pos = line.find(':');

        if (colon_pos != string::npos) {
            Entry newEntry;
            newEntry.name = line.substr(0, colon_pos);

            size_t definition_start = colon_pos + 2;

            newEntry.definition = line.substr(definition_start);

            tree->insert(newEntry);
        } else {
            string result = tree->search(line);

            cout << result << endl;
        }
    }

    delete tree;

    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}
