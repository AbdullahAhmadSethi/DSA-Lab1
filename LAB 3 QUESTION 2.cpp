#include <iostream>
#include <string>
using namespace std;

class StringPool {

private:
    string* stringPool; // DYNAMIC ARRAY OF STRINGS
    int currentSize; // Current number of strings in the pool
    int maxSize;

public:
    // Constructor: Initializes fields
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string[maxSize]; // Dynamic allocation
        cout << "[System] StringPool created with max size " << maxSize << ".\n";
    }

    // Destructor: Fixes the memory leak by deleting the dynamically allocated array
    ~StringPool() {
        delete[] stringPool;
        cout << "[System] Memory of string pool freed (Memory leak fixed).\n";
    }

    // addString: Adds a string to the pool
    void addString(const string& str) {
        if (currentSize < maxSize) {
            stringPool[currentSize] = str;
            currentSize++;
            cout << "[System] Added: \"" << str << "\"\n";
        }
        else {
            cout << "[System] Error: Pool is full! Cannot add \"" << str << "\"\n";
        }
    }

    // removeString: Removes a string from the pool without freeing memory
    void removeString(int index) {
        if (index < 0 || index >= currentSize) {
            cout << "[System] Error: Invalid index " << index << "\n";
            return;
        }
        cout << "[System] Removing string at index " << index
             << " (\"" << stringPool[index] << "\") without freeing memory...\n";

        // Shifting my elements to the left to fill the gap
        for (int i = index; i < currentSize - 1; ++i) {
            stringPool[i] = stringPool[i + 1];
        }
        currentSize--;
    }

    void displayPool() const {
        std::cout << "\n POOL STATUS (Current Size: " << currentSize << "/" << maxSize << ")\n";
        if (currentSize == 0) {
            cout << "[Empty]\n";
        }
        else {
            for (int i = 0; i < currentSize; ++i) {
                cout << "[" << i << "]: " << stringPool[i] << "\n";
            }
        }
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";
    }
};

int main() {
    std::cout << "STRING PROCESSING APPLICATION\n\n";

    // STRINGPOOL OBJECT
    StringPool pool;

    // a. MULTIPLE STRINGS
    cout << "\n[Action] Adding strings to the pool...\n";
    pool.addString("Apple");
    pool.addString("Banana");
    pool.addString("Nashpaati");
    pool.addString("Date");
    pool.addString("Chokandar");

    // This will trigger the "Pool is full" message
    pool.addString("Fig");

    pool.displayPool();

    // b. REMOVE STRINGS WITHOUT FREEING MEMORY
    cout << "[Action] Removing strings without freeing memory...\n";
    pool.removeString(1); // Remove "Banana"
    pool.removeString(2); // Remove "Date"

    pool.displayPool();

    // c. DETECT AND FIX MEMORY LEAK
    cout << "[Action] Exiting main function. Checking for memory leaks...\n";

    return 0; // DESTRUCTOR IS CALLED EXACTLY HERE SO FIXING THE LEAK!!
}