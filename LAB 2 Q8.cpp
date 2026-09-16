#include <iostream>
using namespace std;

int main() {
    int n = 3;
    
    // ALLOCATE ARRAY
    int* values = new int[n];

    // READ 3 INTEGERS (I < N, NOT I <= N)
    cout << "Enter 3 integers: ";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    // DISPLAY ALL 3 INTEGERS BEFORE DELETING
    cout << "You entered: ";
    for (int i = 0; i < n; i++) {
        cout << values[i] << " ";
    }
    cout << endl;

    // RELEASE THE ALLOCATION CORRECTLY
    delete[] values;

    // RESET THE POINTER TO NULL
    values = nullptr;

    return 0;
}
