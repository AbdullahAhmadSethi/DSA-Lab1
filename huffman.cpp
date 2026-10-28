#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------- Huffman tree node ----------
struct Node {
    char ch;          // character (only meaningful for leaves)
    int freq;         // frequency of this node
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

// ---------- Min binary heap of Node* (ordered by freq) ----------
class MinHeap {
    vector<Node*> a;  // array representation: children of i are 2i+1 and 2i+2

    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[p]->freq <= a[i]->freq) break;
            swap(a[p], a[i]);
            i = p;
        }
    }
    void siftDown(int i) {
        int n = a.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, small = i;
            if (l < n && a[l]->freq < a[small]->freq) small = l;
            if (r < n && a[r]->freq < a[small]->freq) small = r;
            if (small == i) break;
            swap(a[i], a[small]);
            i = small;
        }
    }
public:
    int size() { return a.size(); }
    void push(Node* x) { a.push_back(x); siftUp(a.size() - 1); }
    Node* pop() {                       // remove and return the smallest node
        Node* top = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) siftDown(0);
        return top;
    }
};

// ---------- build the Huffman tree using the heap ----------
Node* buildHuffman(const string& S, const vector<int>& f) {
    MinHeap heap;
    for (int i = 0; i < (int)S.size(); i++)
        heap.push(new Node(S[i], f[i]));            // one leaf per character

    while (heap.size() > 1) {
        Node* x = heap.pop();                        // smallest  -> left
        Node* y = heap.pop();                        // 2nd smallest -> right
        Node* z = new Node('$', x->freq + y->freq);  // '$' marks an internal node
        z->left = x;
        z->right = y;
        heap.push(z);
    }
    return heap.pop();                               // the root
}

// ---------- print codes in preorder (root, left, right) ----------
void printCodes(Node* root, string code) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL)   // leaf -> print its code
        cout << "   " << root->ch << " : " << code << endl;
    printCodes(root->left, code + "0");              // left edge  = 0
    printCodes(root->right, code + "1");             // right edge = 1
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};

    cout << "Characters and frequencies:" << endl;
    for (int i = 0; i < (int)S.size(); i++)
        cout << "   " << S[i] << " -> " << f[i] << endl;

    Node* root = buildHuffman(S, f);
    cout << endl << "Root frequency = " << root->freq << endl;
    cout << endl << "Huffman codes (preorder traversal):" << endl;
    printCodes(root, "");

    // second test with a different input
    string S2 = "wxyz";
    vector<int> f2 = {7, 3, 10, 20};
    Node* root2 = buildHuffman(S2, f2);
    cout << endl << "Second input w:7 x:3 y:10 z:20" << endl;
    cout << "Huffman codes (preorder traversal):" << endl;
    printCodes(root2, "");
    return 0;
}
