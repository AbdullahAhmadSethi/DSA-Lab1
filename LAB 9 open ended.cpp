#include <iostream>
#include <string>
using namespace std;

/*

TASK 1: PLANNING

MY Data Structures Used:

1. Binary Search Tree (BST):
   Used to store student records.
   Each node contains roll number, name,
   and pointers to left and right child nodes.

2. Stack:
   Used to maintain student search history.
   It follows LIFO (Last In, First Out).

Time Complexity:
BST insertion: O(n) worst case. BEST CASE O(log n)
BST searching: O(n) worst case. BEST CASE O(log n)
Stack push: O(1).
Stack pop: O(1).

*/

// Structure for Student BST Node

struct Student
{
    int rollNo;
    string name;

    Student* left;
    Student* right;
};

// Structure for Stack Node

struct StackNode
{
    int rollNo;
    StackNode* next;
};

// BST ROOT POINTER

Student* root = NULL;

// STACK TOP POINTER

StackNode* top = NULL;

// FUNCTION TO ADD STUDENT IN BST

Student* addStudent(Student* node, int roll, string studentName)
{
    if (node == NULL)
    {
        Student* newNode = new Student;

        newNode->rollNo = roll;
        newNode->name = studentName;

        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if (roll < node->rollNo)
    {
        node->left = addStudent(node->left, roll, studentName);
    }

    else if (roll > node->rollNo)
    {
        node->right = addStudent(node->right, roll, studentName);
    }

    else
    {
        cout << "\nDuplicate Roll Number!!!" << endl;
    }

    return node;
}

// FUNCTION TO SEARCH STUDENT IN BST

Student* searchStudent(Student* node, int roll)
{
    if (node == NULL || node->rollNo == roll)
    {
        return node;
    }

    if (roll < node->rollNo)
    {
        return searchStudent(node->left, roll);
    }

    return searchStudent(node->right, roll);
}

// FUNCTION TO DISPLAY ALL STUDENTS

void displayStudents(Student* node)
{
    if (node == NULL)

    {
        return;
    }

    displayStudents(node->left);

    cout << "\nRoll Number: " << node->rollNo;
    cout << "\nStudent Name: " << node->name << endl;

    displayStudents(node->right);

}

// FUNCTION TO PUSH SEARCH HISTORY IN STACK

void pushHistory(int roll)

{
    StackNode* newNode = new StackNode;

    newNode->rollNo = roll;
    newNode->next = top;

    top = newNode;
}

// FUNCTION TO DISPLAY SEARCH HISTORY

void displayHistory()
{
    if (top == NULL)
    {
        cout << "\nSearch History is Empty!!!" << endl;
        return;
    }

    StackNode* temp = top;

    cout << "\nSEARCH HISTORY" << endl;

    while (temp != NULL)
    {
        cout << "Roll Number: " << temp->rollNo << endl;

        temp = temp->next;
    }
}

// FUNCTION TO REMOVE RECENT SEARCH FROM STACK

void popHistory()
{
    if (top == NULL)

    {
        cout << "\nSearch History is Empty!!!" << endl;
        return;
    }

    StackNode* temp = top;

    cout << "\nRemoved Search: " << temp->rollNo << endl;

    top = top->next;

    delete temp;
}

// FUNCTION TO DELETE BST MEMORY

void deleteBST(Student* node)
{
    if (node == NULL)

    {
        return;
    }

    deleteBST(node->left);
    deleteBST(node->right);

    delete node;
}

// FUNCTION TO DELETE STACK MEMORY

void deleteStack()
{
    while (top != NULL)

    {
        StackNode* temp = top;

        top = top->next;

        delete temp;
    }

}

// MAIN FUNCTION

int main()
{
    int choice;
    int roll;
    string studentName;

    do
    {
        cout << "\nSTUDENT HELP DESK SYSTEM";

        cout << "\n1. Add Student";
        cout << "\n2. Search Student";
        cout << "\n3. Display All Students";
        cout << "\n4. Display Search History";
        cout << "\n5. Remove Recent Search History";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {

            // ADD STUDENT

            case 1:
            {
                cout << "Enter Roll Number: ";
                cin >> roll;

                if (searchStudent(root, roll) != NULL)
                {
                    cout << "\nDuplicate Roll Number!!!" << endl;
                    break;
                }

                cout << "Enter Student Name: ";
                cin >> ws;
                getline(cin, studentName);

                root = addStudent(root, roll, studentName);

                cout << "\nStudent Added Successfully!!!" << endl;

                break;
            }

            // SEARCH STUDENT

            case 2:
            {
                cout << "Enter Roll Number to Search: ";
                cin >> roll;

                Student* result = searchStudent(root, roll);

                if (result != NULL)
                {
                    cout << "\nStudent Found!!!" << endl;

                    cout << "Roll Number: " << result->rollNo << endl;
                    cout << "Student Name: " << result->name << endl;

                    pushHistory(roll);
                }
                else
                {
                    cout << "\nStudent Not Found!!!" << endl;
                }

                break;
            }

            // DISPLAY ALL STUDENTS

            case 3:
            {
                if (root == NULL)
                {
                    cout << "\nNo Student Records Available!!!" << endl;
                }
                else
                {
                    cout << "ALL STUDENT RECORDS" << endl;

                    displayStudents(root);
                }

                break;
            }

            // DISPLAY SEARCH HISTORY

            case 4:
            {
                displayHistory();

                break;
            }

            // REMOVE RECENT SEARCH HISTORY

            case 5:
            {
                popHistory();

                break;
            }

            // EXIT PROGRAM

            case 6:
            {
                cout << "\nExiting Student Help Desk System..." << endl;

                break;
            }

            // INVALID CHOICE

            default:
            {
                cout << "\nInvalid Choice!!! Try Again." << endl;
            }

        }

    } while (choice != 6);

    // FREE DYNAMICALLY ALLOCATED MEMORY

    deleteBST(root);
    deleteStack();

    root = NULL;

    cout << "\nMemory Released Successfully!!!" << endl;

    return 0;
}

