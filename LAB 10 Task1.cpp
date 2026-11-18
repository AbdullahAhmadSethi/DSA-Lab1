#include <iostream>

using namespace std;

// MAX HEAP WITH DYNAMIC ARRAY
class MaxHeap {
    int* a;
    int size, cap;

public:
    MaxHeap(int c) : size(0), cap(c) { a = new int[cap]; }
    ~MaxHeap() { delete[] a; }

    // INSERT AND SIFT UP, O(LOG N), RETURNS SWAP COUNT
    int insert(int v) {
        if (size == cap) return -1;

        int i = size++, swaps = 0;
        a[i] = v;

        // KEEP SWAPPING WHILE BIGGER THAN PARENT
        while (i > 0 && a[i] > a[(i - 1) / 2]) {
            swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
            swaps++;
        }
        return swaps;
    }

    // SIFT DOWN WITHIN FIRST N ELEMENTS OF ARR
    static void siftDown(int* arr, int n, int i) {
        while (true) {
            int big = i, l = 2 * i + 1, r = 2 * i + 2;

            if (l < n && arr[l] > arr[big]) big = l;
            if (r < n && arr[r] > arr[big]) big = r;
            if (big == i) return;

            swap(arr[i], arr[big]);
            i = big;
        }
    }

    // HEAP SORT ON A COPY SO HEAP STAYS INTACT, O(N LOG N)
    void heapSort(int* out) {
        for (int i = 0; i < size; i++) out[i] = a[i];

        // MAX ROOT GOES TO THE BACK EACH ROUND
        for (int end = size - 1; end > 0; end--) {
            swap(out[0], out[end]);
            siftDown(out, end, 0);
        }
    }

    void print() {
        for (int i = 0; i < size; i++) cout << a[i] << " ";
        cout << endl;
    }

    int getSize() { return size; }
};

int main() {
    int data[] = {25, 40, 15, 60, 35, 10, 70, 50};
    int n = 8;
    MaxHeap h(n);

    cout << "Insert\tSwaps\tHeap after insertion" << endl;

    for (int i = 0; i < n; i++) {
        int s = h.insert(data[i]);
        cout << data[i] << "\t" << s << "\t";
        h.print();
    }

    cout << "\nFinal max heap: ";
    h.print();

    int* sorted = new int[n];
    h.heapSort(sorted);

    cout << "Sorted output: ";
    for (int i = 0; i < n; i++) cout << sorted[i] << " ";
    cout << endl;

    delete[] sorted;

    // Q1: WORST CASE SWAPS = HEIGHT OF HEAP = FLOOR(LOG2 N)
    // Q2: BUILD BY N INSERTS = O(N LOG N), HEAP SORT = O(N LOG N)
    return 0;
}
