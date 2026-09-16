#include <iostream>
using namespace std;

int main() {

    int rows, cols;

    do {

        cout << "Enter number of students (ROWS): ";
        cin >> rows;
        cout << "Enter number of subjects (COLS): ";
        cin >> cols;

        if (rows <= 0 || cols <= 0) {
            cout << "Invalid input. Please enter positive numbers." << endl;
        }

    } while (rows <= 0 || cols <= 0);

    int **marks = new int*[rows];

    for (int i = 0; i < rows; i++) {
        marks[i] = new int[cols];
    }

  
    cout << "Enter marks (0 to 100):" << endl;

    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            // Using required pointer math for input
            cin >> *(*(marks + r) + c); 

        }
    }
    cout << "\nThe Matrix:" << endl;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << marks[r][c] << " ";
        }
        cout << endl;
    }

    int bestTotal = -1; // Start low so first student always beats it
    int topStudent = 1; // Default to first student

    for (int r = 0; r < rows; r++) {
        int currentTotal = 0;

        for (int c = 0; c < cols; c++) {
            currentTotal += marks[r][c];
        }
        cout << "Student " << (r + 1) << " Total: " << currentTotal << endl;

        // If totals tie, we keep the first student because we only update on strictly greater

        if (currentTotal > bestTotal) {

            bestTotal = currentTotal;
            topStudent = r + 1;

        }
    }
    cout << "Top student: " << topStudent << " with total: " << bestTotal << endl;

    for (int i = 0; i < rows; i++) {
        delete[] marks[i]; // Delete the inner integer arrays first
    }
    
    delete[] marks; // Delete the outer array of pointers
    marks = nullptr; // Set to null to avoid dangling pointer
    return 0;
}
