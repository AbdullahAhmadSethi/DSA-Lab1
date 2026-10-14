#include <iostream>
#include <vector>

using namespace std;

// Checks whether the input array is sorted in non-decreasing order
bool isSorted(const int arr[], int n) {
    if (n <= 1 || arr == nullptr) return true;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Populates registration numbers into array
void inputSortedIDs(int arr[], int n, const vector<int>& source) {
    for (int i = 0; i < n; i++) {
        arr[i] = source[i];
    }
}

// Recursive Binary Search
// Searches for target within index range [low, high]
int binarySearch(const int arr[], int low, int high, int target) {
    // Base case: search space exhausted
    if (low > high || arr == nullptr) {
        return -1;
    }

    // Overflow-safe midpoint calculation
    int mid = low + (high - low) / 2;

    // Check if middle element matches target (Best Case on initial call)
    if (arr[mid] == target) {
        return mid;
    }

    // If target is smaller than mid, search left subarray
    if (target < arr[mid]) {
        return binarySearch(arr, low, mid - 1, target);
    }

    // Otherwise, search right subarray
    return binarySearch(arr, mid + 1, high, target);
}

// Iterative Binary Search implementation for comparison
int binarySearchIterative(const int arr[], int n, int target) {
    if (n <= 0 || arr == nullptr) return -1;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (target < arr[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

void displayArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    cout << "============================================================" << endl;
    cout << "   CS250 LAB 6: TASK 2 - BINARY SEARCH (STUDENT MARKS/IDS)  " << endl;
    cout << "============================================================" << endl << endl;

    struct TestCase {
        vector<int> arr;
        int target;
        string description;
    };

    vector<TestCase> testCases = {
        {{10, 20, 30, 40, 50}, 30, "Middle element - Best Case O(1)"},
        {{10, 20, 30, 40, 50}, 10, "Left boundary element"},
        {{10, 20, 30, 40, 50}, 50, "Right boundary element"},
        {{10, 20, 30, 40, 50}, 25, "Element absent - Worst Case O(log n)"},
        {{7}, 7, "Single element match"},
        {{}, 5, "Empty array edge case"},
        {{50, 10, 40, 20, 30}, 20, "Unsorted array validation failure"}
    };

    for (size_t t = 0; t < testCases.size(); t++) {
        cout << "--- TEST CASE " << (t + 1) << ": " << testCases[t].description << " ---" << endl;
        int n = static_cast<int>(testCases[t].arr.size());
        int* arr = nullptr;
        if (n > 0) {
            arr = new int[n];
            inputSortedIDs(arr, n, testCases[t].arr);
        }

        cout << "Input Array     : ";
        displayArray(arr, n);
        cout << endl;
        cout << "Target Value    : " << testCases[t].target << endl;

        // Validation step
        bool sorted = isSorted(arr, n);
        cout << "Array is Sorted : " << (sorted ? "YES (Valid for Binary Search)" : "NO (Invalid!)") << endl;

        if (sorted) {
            int recResult = binarySearch(arr, 0, n - 1, testCases[t].target);
            int iterResult = binarySearchIterative(arr, n, testCases[t].target);

            if (recResult != -1) {
                cout << "Search Result   : Found at index " << recResult << endl;
            } else {
                cout << "Search Result   : Not found (-1)" << endl;
            }
            cout << "Iterative Check : " << (iterResult == recResult ? "Match" : "Mismatch") << " (Index: " << iterResult << ")" << endl;
        } else {
            cout << "Search Result   : Search rejected! Binary search requires non-decreasing order." << endl;
        }
        cout << endl;

        delete[] arr;
    }

    cout << "======================= END OF TESTS =======================" << endl;
    return 0;
}
