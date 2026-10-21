#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char c) : data(c), left(NULL), right(NULL) {}
};

// ---------- building the tree from string ----------
Node* build(const string& s, int& i) {
    if (i >= (int)s.length() || s[i] == ',' || s[i] == ')')
        return NULL;

    Node* root = new Node(s[i]);
    i++;

    if (i < (int)s.length() && s[i] == '(') {
        i++;                       // skip '('
        root->left = build(s, i);
        if (s[i] == ',') i++;      // skip ','
        root->right = build(s, i);
        i++;                       // skip ')'
    }
    return root;
}

// ---------- preorder (recursive) ----------
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// ---------- inorder using stack ----------
void inorderIter(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    while (cur != NULL || !st.empty()) {
        while (cur != NULL) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        cout << cur->data << " ";
        cur = cur->right;
    }
}

// ---------- postorder iterative (two stacks) ----------
void postorderIter(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* t = s1.top();
        s1.pop();
        s2.push(t);
        if (t->left)  s1.push(t->left);
        if (t->right) s1.push(t->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// ---------- validate string without building ----------
bool isValid(const string& s) {
    int open = 0;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(') {
            // '(' must come right after a node letter
            if (i == 0 || !isalpha(s[i - 1])) return false;
            open++;
        } else if (c == ')') {
            open--;
            if (open < 0) return false;
        } else if (c == ',') {
            if (open == 0) return false;     // comma outside brackets
        } else if (!isalpha(c)) {
            return false;
        } else {
            // a letter can't directly follow another letter or ')'
            if (i > 0 && (isalpha(s[i - 1]) || s[i - 1] == ')')) return false;
        }
    }
    return open == 0 && n > 0;
}

// ---------- height and depth ----------
int height(Node* root) {
    if (root == NULL) return -1;       // height counted in edges
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

void printDepths(Node* root, int d) {
    if (root == NULL) return;
    cout << "   Node " << root->data << " -> depth " << d << endl;
    printDepths(root->left, d + 1);
    printDepths(root->right, d + 1);
}

// ---------- BST from integers ----------
struct BNode {
    int val;
    BNode* left;
    BNode* right;
    BNode(int v) : val(v), left(NULL), right(NULL) {}
};

BNode* insertBST(BNode* root, int v) {
    if (root == NULL) return new BNode(v);
    if (v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);
    return root;
}

void inorderBST(BNode* root) {
    if (root == NULL) return;
    inorderBST(root->left);
    cout << root->val << " ";
    inorderBST(root->right);
}

int main() {
    string str = "a(b(d,e),c(,f(g,)))";
    cout << "Given string: " << str << endl << endl;

    cout << "1) Validating string...  ";
    if (isValid(str)) cout << "VALID" << endl;
    else cout << "INVALID" << endl;

    int i = 0;
    Node* root = build(str, i);

    cout << "2) Preorder (recursive):  ";
    preorder(root);
    cout << endl;

    cout << "3) Inorder (stack):       ";
    inorderIter(root);
    cout << endl;

    cout << "4) Postorder (iterative): ";
    postorderIter(root);
    cout << endl;

    cout << "5) Height of tree: " << height(root) << endl;
    cout << "   Depth of each node:" << endl;
    printDepths(root, 0);

    cout << endl << "6) Checking some bad strings:" << endl;
    string bad[] = { "a(b,c", "a(b,c))", "(b,c)", "a(b,,c)x" };
    for (int k = 0; k < 4; k++) {
        cout << "   " << bad[k] << "  ->  "
             << (isValid(bad[k]) ? "VALID" : "INVALID") << endl;
    }

    cout << endl << "7) BST from sequence" << endl;
    int arr[] = { 50, 30, 70, 20, 40, 60, 80 };
    BNode* bst = NULL;
    for (int k = 0; k < 7; k++) bst = insertBST(bst, arr[k]);
    cout << "   Inorder: ";
    inorderBST(bst);
    cout << endl;

    return 0;
}
