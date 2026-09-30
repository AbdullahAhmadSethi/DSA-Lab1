#include <iostream>
using namespace std;

struct Node {

    int id;
    Node* next;

};

class Josephus {

    Node* head;

public:

    Josephus() : head(nullptr) {}

    // CREATE CIRCULAR LIST OF N PEOPLE

    void createCircle(int n) {

        head = nullptr;

        for (int i = 1; i <= n; i++) {

            Node* newNode = new Node{i, nullptr};

            if (!head) {

                head = newNode;
                newNode->next = head;

            }
             else {

                Node* temp = head;
                while (temp->next != head) temp = temp->next;
                temp->next = newNode;
                newNode->next = head;

            }
        }
    }

    // ELIMINATE EVERY K-TH PERSON AND PRINT ORDER

    void eliminate(int k) {

        if (!head) { cout << "Circle is empty.\n"; return; }

        Node* curr = head;
        Node* prev = head;
        while (prev->next != head) prev = prev->next;   // prev = last node

        cout << "\nEliminated Order: ";
        
        while (curr->next != curr) {                    // stop when one remains

            for (int count = 1; count < k; count++) {   // move k-1 steps

                prev = curr;
                curr = curr->next;

            }

            cout << curr->id << " ";

            prev->next = curr->next;                    // unlink curr
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        head = curr;   // remaining single node
        cout << "\n";
    }

    // DISPLAY SURVIVOR

    void displaySurvivor() {

        if (!head) { cout << "No survivor.\n"; return; }
        cout << "Survivor: " << head->id << "\n";

    }

    // DISPLAY CIRCLE (for verification)

    void displayCircle() {

        if (!head) { cout << "Circle is empty.\n"; return; }
        cout << "Circle: ";
        Node* temp = head;

        do {
            cout << temp->id << " ";
            temp = temp->next;
        } while (temp != head);

        cout << "\n";
    }
};

int main() {

    Josephus j;
    int n, k;

    cout << "ENTER NUMBER OF PEOPLE (N): ";
    cin >> n;
    cout << "ENTER STEP COUNT (k): ";
    cin >> k;

    j.createCircle(n);
    j.displayCircle();
    j.eliminate(k);
    j.displaySurvivor();

    return 0;
}