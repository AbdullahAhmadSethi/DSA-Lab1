#include <iostream>
using namespace std;

int main() {
    int n;
    // READ AND VALIDATE N (1 TO 10)
    do {
        cout << "Enter number of students (1 to 10): ";
        cin >> n;
    } while (n < 1 || n > 10);

    // ALLOCATE THE ORIGINAL BLOCK OF N INTEGERS
    int *marks = new int[n];
    
    cout << "Enter " << n << " marks: ";

    for (int i = 0; i < n; i++) {
        cin >> *(marks + i); // POINTER NOTATION
    }

    // 1. ALLOCATE A SECOND BLOCK OF N + 1 INTEGERS
    int *new_marks = new int[n + 1];

    // COPY ORIGINAL N VALUES USING POINTER NOTATION
    for (int i = 0; i < n; i++) {
        *(new_marks + i) = *(marks + i);
    }

    // READ THE NEW MARK INTO THE FINAL POSITION
    cout << "Enter the new mark: ";
    cin >> *(new_marks + n);
    // 2. RELEASE THE OLD BLOCK
    delete[] marks;

    // MAKE THE ORIGINAL POINTER REFER TO THE NEW BLOCK
    marks = new_marks;

    // UPDATE THE STORED SIZE
    n = n + 1;

    cout << "All marks: ";
    
    for (int i = 0; i < n; i++) {
        cout << *(marks + i) << " ";
    }
    cout << endl;

    // 3. RELEASE THE FINAL BLOCK EXACTLY ONCE
    delete[] marks;
    marks = nullptr; // PREVENT DANGLING POINTER
    return 0;
}
