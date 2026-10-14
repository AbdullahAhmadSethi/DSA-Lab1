#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to populate array with IDs (simulated or console input)
void inputIDs(int arr[], int n, const vector<int>& source) {
    for (int i = 0; i < n; i++) {
        arr[i] = source[i];
    }
}

// Linear search implementation checking elements one by one from index 0
// Returns index on first match, or -1 if target is not registered
int linearSearch(const int arr[], int n, int target) {
    // Handle empty array edge case
    if (n <= 0 || arr == nullptr) {
        return -1;
    }

    // Iterate through array sequentially
    for (int i = 0; i < n; i++) {
        // Return immediately when target is found (first occurrence)
        if (arr[i] == target) {
            return i;
        }
    }

    // Finished loop without finding match
    return -1;
}

// Helper to display formatted array contents
void displayArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

// Display search result message
void displayResult(int target, int index) {
    if (index != -1) {
        cout << "Target ID " << target << " -> Found at Index " << index << endl;
    } else {
        cout << "Target ID " << target << " -> Not registered in laboratory session (-1)" << endl;
    }
}

int main() {
    cout << "============================================================" << endl;
    cout << "   CS250 LAB 6: TASK 1 - LINEAR SEARCH (STUDENT IDS)        " << endl;
    cout << "============================================================" << endl << endl;

    struct TestCase {
        vector<int> arr;
        int target;
        string description;
    };

    vector<TestCase> testCases = {
        {{10, 20, 30, 40}, 10, "Target at start (Best Case)"},
        {{10, 20, 30, 40}, 30, "Target in middle (Average Case)"},
        {{10, 20, 30, 40}, 50, "Target absent (Worst Case)"},
        {{7}, 7, "Single element match"},
        {{}, 5, "Empty array edge case"},
        {{10, 20, 10, 40}, 10, "Duplicate IDs - First occurrence returned"}
    };

    for (size_t t = 0; t < testCases.size(); t++) {
        cout << "--- TEST CASE " << (t + 1) << ": " << testCases[t].description << " ---" << endl;
        int n = static_cast<int>(testCases[t].arr.size());
        int* arr = nullptr;
        if (n > 0) {
            arr = new int[n];
            inputIDs(arr, n, testCases[t].arr);
        }

        cout << "Input Array : ";
        displayArray(arr, n);
        cout << endl;
        cout << "Target ID   : " << testCases[t].target << endl;

        int resultIndex = linearSearch(arr, n, testCases[t].target);
        cout << "Result      : ";
        displayResult(testCases[t].target, resultIndex);
        cout << endl;

        delete[] arr;
    }

    cout << "======================= END OF TESTS =======================" << endl;
    return 0;
}
