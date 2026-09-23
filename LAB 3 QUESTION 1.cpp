#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& str) {
    int left = 0;
    int right = (int)str.length() - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false; // MISMATCH FOUND TRIGERREDODD!!
        }
        left++;
        right--;
    }
    return true; // ALL MATCHING PATTERNS PASSED
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    if (isPalindrome(input)) {
        cout << "\"" << input << "\" is a palindrome." << endl; // I WANTED TO PRINT DOUBLE QUOTATIONS. THATS WHY!
    } else {
        cout << "\"" << input << "\" is not a palindrome." << endl;
    }
    return 0;
}