#include <iostream>
#include <vector>

using namespace std;

// Merges two sorted subarrays arr[left..mid] and arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary buffers
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        // <= ensures stability of sort
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free dynamically allocated temporary arrays
    delete[] L;
    delete[] R;
}

// Recursively divides and sorts the array using divide-and-conquer
void mergeSort(int arr[], int left, int right) {
    // Base case: 0 or 1 element
    if (left >= right || arr == nullptr) {
        return;
    }

    int mid = left + (right - left) / 2;

    // Recursively sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
}

// Displays the array elements
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
    cout << "   CS250 LAB 6: TASK 3 - MERGE SORT (STUDENT MARKS)         " << endl;
    cout << "============================================================" << endl << endl;

    struct TestCase {
        vector<int> arr;
        string description;
    };

    vector<TestCase> testCases = {
        {{45, 12, 78, 33, 20, 60}, "General unsorted student marks"},
        {{1, 2, 3, 4}, "Already sorted array (Best case behavior)"},
        {{9, 7, 5, 3, 1}, "Reverse sorted array (Worst case scenario)"},
        {{5, 2, 5, 1, 2}, "Array with duplicate elements (Stability test)"},
        {{8}, "Single element array base case"},
        {{}, "Empty array edge case"}
    };

    for (size_t t = 0; t < testCases.size(); t++) {
        cout << "--- TEST CASE " << (t + 1) << ": " << testCases[t].description << " ---" << endl;
        int n = static_cast<int>(testCases[t].arr.size());
        int* arr = nullptr;
        if (n > 0) {
            arr = new int[n];
            for (int i = 0; i < n; i++) arr[i] = testCases[t].arr[i];
        }

        cout << "Before Sorting : ";
        displayArray(arr, n);
        cout << endl;

        if (n > 1) {
            mergeSort(arr, 0, n - 1);
        }

        cout << "After Sorting  : ";
        displayArray(arr, n);
        cout << endl << endl;

        delete[] arr;
    }

    cout << "======================= END OF TESTS =======================" << endl;
    return 0;
}
