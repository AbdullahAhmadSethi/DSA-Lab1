#include <iostream>

using namespace std;

// HEAP THAT WORKS AS MAX OR MIN USING A FLAG
class Heap {
    int* a;
    int size, cap;
    bool isMax;

    // TRUE IF X SHOULD SIT ABOVE Y
    bool above(int x, int y) { return isMax ? x > y : x < y; }

public:
    Heap(int c, bool m) : size(0), cap(c), isMax(m) { a = new int[cap]; }
    ~Heap() { delete[] a; }

    // PUSH WITH SIFT UP, O(LOG N)
    void push(int v) {
        int i = size++;
        a[i] = v;

        while (i > 0 && above(a[i], a[(i - 1) / 2])) {
            swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // POP ROOT WITH SIFT DOWN, O(LOG N)
    int pop() {
        int top = a[0], i = 0;
        a[0] = a[--size];

        while (true) {
            int best = i, l = 2 * i + 1, r = 2 * i + 2;

            if (l < size && above(a[l], a[best])) best = l;
            if (r < size && above(a[r], a[best])) best = r;
            if (best == i) break;

            swap(a[i], a[best]);
            i = best;
        }
        return top;
    }

    int top() { return a[0]; }
    int getSize() { return size; }
};

class ERMonitor {
    Heap low, high;

public:
    ERMonitor(int n) : low(n, true), high(n, false) {}

    // ADD WAIT AND REBALANCE, O(LOG N)
    void addWait(int x) {
        if (low.getSize() == 0 || x <= low.top()) low.push(x);
        else high.push(x);

        // SIZES MAY DIFFER BY ONE, MAX HEAP KEEPS EXTRA
        if (low.getSize() > high.getSize() + 1) high.push(low.pop());
        else if (high.getSize() > low.getSize()) low.push(high.pop());
    }

    // MEDIAN LOOKUP, O(1)
    double getMedian() {
        if (low.getSize() > high.getSize()) return low.top();
        return (low.top() + high.top()) / 2.0;
    }

    void report(int no, int x) {
        double m = getMedian();

        cout << no << "\t" << x << "\t" << low.top() << "\t";
        if (high.getSize() == 0) cout << "none";
        else cout << high.top();

        cout << "\t" << m << "\t" << (m > 35 ? "ALERT: call extra staff" : "Normal") << endl;
    }
};

int main() {
    int waits[] = {45, 20, 60, 15, 30, 90, 10, 55};
    int n = 8;
    ERMonitor er(n);

    cout << "Arrival\tWait\tMaxRoot\tMinRoot\tMedian\tStatus" << endl;

    for (int i = 0; i < n; i++) {
        er.addWait(waits[i]);
        er.report(i + 1, waits[i]);
    }

    // Q1: ARRIVAL 6 AVERAGE = 45, MEDIAN = 37.5, 90 DRAGS AVERAGE UP
    // Q2: ROOTS STOP BEING THE MIDDLE SO MEDIAN GETS WRONG
    // Q3: SORTING = O(N^2 LOG N), HEAPS = O(N LOG N)
    return 0;
}
