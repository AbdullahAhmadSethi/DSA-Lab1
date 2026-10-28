#include <iostream>
#include <vector>
using namespace std;

// ---------- singly linked list node ----------
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(NULL) {}
};

// ---------- Min binary heap of ListNode* (ordered by val) ----------
class MinHeap {
    vector<ListNode*> a;

    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[p]->val <= a[i]->val) break;
            swap(a[p], a[i]);
            i = p;
        }
    }
    void siftDown(int i) {
        int n = a.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, small = i;
            if (l < n && a[l]->val < a[small]->val) small = l;
            if (r < n && a[r]->val < a[small]->val) small = r;
            if (small == i) break;
            swap(a[i], a[small]);
            i = small;
        }
    }
public:
    bool empty() { return a.empty(); }
    void push(ListNode* x) { a.push_back(x); siftUp(a.size() - 1); }
    ListNode* pop() {
        ListNode* top = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) siftDown(0);
        return top;
    }
};

// ---------- merge k sorted lists: O(N log k) ----------
ListNode* mergeKLists(vector<ListNode*>& lists) {
    MinHeap heap;
    for (int i = 0; i < (int)lists.size(); i++)
        if (lists[i] != NULL) heap.push(lists[i]);   // only the head of each list

    ListNode dummy(0);                               // dummy head makes appending easy
    ListNode* tail = &dummy;
    while (!heap.empty()) {
        ListNode* smallest = heap.pop();             // smallest of all current heads
        tail->next = smallest;
        tail = smallest;
        if (smallest->next != NULL)
            heap.push(smallest->next);               // next node of that same list
    }
    return dummy.next;
}

// ---------- helpers ----------
ListNode* makeList(const vector<int>& v) {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    for (int i = 0; i < (int)v.size(); i++) {
        ListNode* n = new ListNode(v[i]);
        if (head == NULL) head = tail = n;
        else { tail->next = n; tail = n; }
    }
    return head;
}

void printList(ListNode* head) {
    if (head == NULL) { cout << "(empty)" << endl; return; }
    while (head != NULL) {
        cout << head->val;
        if (head->next != NULL) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<vector<int>> input = { {1, 4, 5}, {1, 3, 4}, {2, 6} };
    vector<ListNode*> lists;
    cout << "Input lists:" << endl;
    for (int i = 0; i < (int)input.size(); i++) {
        lists.push_back(makeList(input[i]));
        cout << "   list " << i + 1 << ": ";
        printList(lists[i]);
    }
    ListNode* merged = mergeKLists(lists);
    cout << endl << "Merged sorted list:" << endl << "   ";
    printList(merged);

    // edge cases: empty list inside the array, and no lists at all
    vector<ListNode*> withEmpty = { NULL, makeList({7, 9}), NULL, makeList({8}) };
    cout << endl << "With empty lists {}, {7,9}, {}, {8}:" << endl << "   ";
    printList(mergeKLists(withEmpty));

    vector<ListNode*> none;
    cout << "With no lists at all:" << endl << "   ";
    printList(mergeKLists(none));
    return 0;
}
