#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------- AVL node ----------
struct Node {
    int key;
    int height;               // height of the subtree rooted here (leaf = 1)
    Node* left;
    Node* right;
    Node(int k) : key(k), height(1), left(NULL), right(NULL) {}
};

int height(Node* n) { return n ? n->height : 0; }
int balanceFactor(Node* n) { return n ? height(n->left) - height(n->right) : 0; }
void update(Node* n) { n->height = 1 + max(height(n->left), height(n->right)); }

// ---------- rotations ----------
Node* rotateRight(Node* y) {          // y's left child x becomes the new root
    Node* x = y->left;
    y->left = x->right;               // x's right subtree moves under y
    x->right = y;                     // y becomes the right child of x
    update(y); update(x);             // fix heights bottom-up
    return x;
}
Node* rotateLeft(Node* x) {           // x's right child y becomes the new root
    Node* y = x->right;
    x->right = y->left;               // y's left subtree moves under x
    y->left = x;                      // x becomes the left child of y
    update(x); update(y);
    return y;
}

// ---------- rebalance one node (the self-healing step) ----------
Node* rebalance(Node* n) {
    update(n);
    int bf = balanceFactor(n);
    if (bf > 1) {                                       // left heavy
        if (balanceFactor(n->left) < 0) {               // Left-Right case
            cout << "   [rotation] Left-Right case at " << n->key << endl;
            n->left = rotateLeft(n->left);
        } else {
            cout << "   [rotation] Left-Left case at " << n->key << endl;
        }
        return rotateRight(n);
    }
    if (bf < -1) {                                      // right heavy
        if (balanceFactor(n->right) > 0) {              // Right-Left case
            cout << "   [rotation] Right-Left case at " << n->key << endl;
            n->right = rotateRight(n->right);
        } else {
            cout << "   [rotation] Right-Right case at " << n->key << endl;
        }
        return rotateLeft(n);
    }
    return n;                                           // already balanced
}

// ---------- insert / delete ----------
Node* insert(Node* n, int key) {
    if (n == NULL) return new Node(key);
    if (key < n->key) n->left = insert(n->left, key);
    else if (key > n->key) n->right = insert(n->right, key);
    else return n;                                      // duplicates are ignored
    return rebalance(n);
}

Node* minNode(Node* n) { while (n->left) n = n->left; return n; }

Node* remove(Node* n, int key) {
    if (n == NULL) return NULL;
    if (key < n->key) n->left = remove(n->left, key);
    else if (key > n->key) n->right = remove(n->right, key);
    else {
        if (n->left == NULL || n->right == NULL) {      // 0 or 1 child
            Node* child = n->left ? n->left : n->right;
            delete n;
            return child;
        }
        Node* succ = minNode(n->right);                 // 2 children: inorder successor
        n->key = succ->key;
        n->right = remove(n->right, succ->key);
    }
    return rebalance(n);
}

// ---------- print the tree sideways (right subtree on top) ----------
void printTree(Node* n, int depth = 0) {
    if (n == NULL) return;
    printTree(n->right, depth + 1);
    cout << string(depth * 6, ' ') << n->key << " (h=" << n->height
         << ",bf=" << balanceFactor(n) << ")" << endl;
    printTree(n->left, depth + 1);
}

// ---------- top-k queries ----------
// collects the k LARGEST keys (reverse inorder) or the k SMALLEST keys (inorder)
void collect(Node* n, int k, bool largest, vector<int>& out) {
    if (n == NULL || (int)out.size() >= k) return;
    collect(largest ? n->right : n->left, k, largest, out);
    if ((int)out.size() < k) out.push_back(n->key);
    collect(largest ? n->left : n->right, k, largest, out);
}

// criterion: "max" -> k largest, "min" -> k smallest, "sum" -> sum of the k largest
vector<int> topK(Node* root, int k, const string& criterion) {
    vector<int> result;
    collect(root, k, criterion != "min", result);
    return result;
}

void printTopK(Node* root, int k, const string& criterion) {
    vector<int> r = topK(root, k, criterion);
    cout << "Top " << k << " by " << criterion << ": ";
    int sum = 0;
    for (int i = 0; i < (int)r.size(); i++) { cout << r[i] << " "; sum += r[i]; }
    if (criterion == "sum") cout << "(sum = " << sum << ")";
    cout << endl;
}

// delete the top k elements of the given criterion, one by one
Node* deleteTopK(Node* root, int k, const string& criterion) {
    vector<int> r = topK(root, k, criterion);          // decide the keys first
    for (int i = 0; i < (int)r.size(); i++) {
        cout << endl << "Delete " << r[i] << ":" << endl;
        root = remove(root, r[i]);
        printTree(root);
    }
    return root;
}

int main() {
    Node* root = NULL;
    int values[] = {10, 20, 30, 40, 50, 25};
    cout << "=== Insertions (tree printed after each one) ===" << endl;
    for (int i = 0; i < 6; i++) {
        cout << endl << "Insert " << values[i] << ":" << endl;
        root = insert(root, values[i]);
        printTree(root);
    }

    cout << endl << "=== Top-k queries (k = 3) ===" << endl;
    printTopK(root, 3, "max");
    printTopK(root, 3, "min");
    printTopK(root, 3, "sum");

    cout << endl << "=== Delete top 3 elements (criterion: max) ===" << endl;
    root = deleteTopK(root, 3, "max");

    cout << endl << "=== Remaining top-2 by min ===" << endl;
    printTopK(root, 2, "min");
    return 0;
}
