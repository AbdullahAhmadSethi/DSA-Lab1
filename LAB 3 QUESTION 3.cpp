#include <iostream>
using namespace std;

// CREATING NODE

struct Node {
    int data;
    Node* next;

    // CONSTRUCTOR
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// LINKED LIST TO ENCAPSULATE ALL
class LinkedList {

private:
    Node* head;

public:
    // Constructor initializes the list to be empty
    LinkedList() {
        head = nullptr;
    }

    // Destructor to free memory when program ends
    ~LinkedList() {

        Node* current = head;

        while (current != nullptr) {

            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // 1. Insert a node at the beginning (head)
    void insertAtHead(int value) {

        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        cout << " [Success] Inserted " << value << " at the head.\n";
    }

    // 2. Insert a node at the 3rd location
    void insertAtThird(int value) {
        // Handle edge cases if list has fewer than 2 nodes
        if (head == nullptr) {
            cout << "[Notice] List is empty. Inserting at head instead.\n";
            insertAtHead(value);
            return;
        }
        if (head->next == nullptr) {
            cout << "[Notice] List has only 1 node. Inserting at the end instead.\n";
            Node* newNode = new Node(value);
            head->next = newNode;
            return;
        }
        // Traverse to the 2nd node (so we can insert after it)
        Node* current = head;
        int count = 1;

        while (current != nullptr && count < 2) {
            current = current->next;
            count++;
        }
        // Insert new node after the 2nd node
        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
        cout << "[Success] Inserted " << value << " at the 3rd position.\n";
    }

    // 3. Display the contents of the linked list
    void displayList() {
        if (head == nullptr) {
            cout << "[Empty] The list is currently empty.\n";
            return;
        }
        Node* current = head;
        cout << "List: ";

        while (current != nullptr) {
            cout << current->data;

            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << " -> NULL\n";
    }

    // 4. Delete the last node of the linked list

    void deleteLast() {
        if (head == nullptr) {
            cout << "[Error] cannot delete. The list is empty.\n"; // Exact typo from document
            return;
        }
        // Special case: Only one node
        if (head->next == nullptr) {
            cout << "[Success] Deleted last node (" << head->data << "). List is now empty.\n"; // Exact typo from document
            delete head;
            head = nullptr;
            return;
        }
        // Traverse to the second-to-last node
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        // Delete the last node
        Node* lastNode = current->next;
        cout << " [Success] Deleted last node (" << lastNode->data << ").\n";
        delete lastNode;

        current->next = nullptr;
    }

    // 5. Count the number of nodes
    int countNodes() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // 6. Reverse the linked list iteratively
    void reverseList() {

        if (head == nullptr || head->next == nullptr) {
            cout << "[Notice] List is empty or has only 1 node. Nothing to reverse.\n";
            return;
        }

        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {

            next = current->next; // Store next node
            current->next = prev; // Reverse current node pointer
            prev = current;       // Move prev forward
            current = next;       // Move current forward
        }

        head = prev; // update head to the new front
        cout << "[Success] List reversed iteratively.\n";
    }

    // 7. Search for a given value in the list
    void searchValue(int value) {

        Node* current = head;
        int position = 1;
        bool found = false;

        while (current != nullptr) {

            if (current->data == value) {
                cout << "[Found] Value " << value << " found at position " << position << ".\n";
                found = true;

                // Break if you only want the first occurrence.
                // Remove break if you want all occurrences.
                break;
            }
            current = current->next;
            position++;
        }
        if (!found) {
            cout << "[Not Found] Value " << value << " does not exist in the list.\n";
        }
    }
};

int main() {
    LinkedList list;
    int choice, value;

    do {

        cout << "       SINGLY LINKED LIST MENU          \n";

        cout << "1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Reverse List\n";
        cout << "7. Search Value\n";
        cout << "8. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice (1-8): ";
        
        while (!(cin >> choice)) {
            cout << "[Invalid Input] Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> value;
                list.insertAtHead(value);
                break;
            case 2:
                cout << "Enter value to insert at 3rd position: ";
                cin >> value;
                list.insertAtThird(value);
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                list.deleteLast();
                break;
            case 5:
                cout << "[Info] Total nodes in the list: " << list.countNodes() << "\n";
                break;
            case 6:
                list.reverseList();
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> value;
                list.searchValue(value);
                break;
            case 8:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "[Error] Invalid choice. Please select between 1 and 8.\n";
        }
    } while (choice != 8);

    return 0;
}