#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
};

Student* createStudent(int id, string name, float gpa) {
    Student* s = new Student;
    s->studentID = id;
    s->name = name;
    s->GPA = gpa;
    s->left = NULL;
    s->right = NULL;
    return s;
}

// Insert() - ordered by studentID
Student* Insert(Student* root, int id, string name, float gpa) {
    if (root == NULL) return createStudent(id, name, gpa);
    if (id < root->studentID)
        root->left = Insert(root->left, id, name, gpa);
    else if (id > root->studentID)
        root->right = Insert(root->right, id, name, gpa);
    else
        cout << "ID " << id << " already exists, skipped." << endl;
    return root;
}

// Search() - find by ID
Student* Search(Student* root, int id) {
    if (root == NULL || root->studentID == id) return root;
    if (id < root->studentID) return Search(root->left, id);
    return Search(root->right, id);
}

Student* findMin(Student* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Delete() - handles 0, 1 and 2 children
Student* Delete(Student* root, int id) {
    if (root == NULL) return NULL;
    if (id < root->studentID) root->left = Delete(root->left, id);
    else if (id > root->studentID) root->right = Delete(root->right, id);
    else {
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }
        // two children: copy inorder successor then delete it
        Student* succ = findMin(root->right);
        root->studentID = succ->studentID;
        root->name = succ->name;
        root->GPA = succ->GPA;
        root->right = Delete(root->right, succ->studentID);
    }
    return root;
}

void printStudent(Student* s) {
    cout << left << setw(8) << s->studentID
         << setw(16) << s->name
         << fixed << setprecision(2) << s->GPA << endl;
}

// Inorder traversal -> sorted by ID
void Inorder(Student* root) {
    if (root == NULL) return;
    Inorder(root->left);
    printStudent(root);
    Inorder(root->right);
}

int countStudents(Student* root) {
    if (root == NULL) return 0;
    return 1 + countStudents(root->left) + countStudents(root->right);
}

void findExtremes(Student* root, Student*& hi, Student*& lo) {
    if (root == NULL) return;
    if (hi == NULL || root->GPA > hi->GPA) hi = root;
    if (lo == NULL || root->GPA < lo->GPA) lo = root;
    findExtremes(root->left, hi, lo);
    findExtremes(root->right, hi, lo);
}

void aboveThreshold(Student* root, float t) {
    if (root == NULL) return;
    aboveThreshold(root->left, t);
    if (root->GPA > t) printStudent(root);
    aboveThreshold(root->right, t);
}

void header() {
    cout << left << setw(8) << "ID" << setw(16) << "Name" << "GPA" << endl;
    cout << "------------------------------" << endl;
}

int main() {
    Student* root = NULL;

    root = Insert(root, 541, "Ali Raza", 3.45);
    root = Insert(root, 322, "Sara Khan", 3.80);
    root = Insert(root, 760, "Hamza Tariq", 2.65);
    root = Insert(root, 210, "Ayesha Noor", 3.92);
    root = Insert(root, 430, "Bilal Ahmed", 2.10);
    root = Insert(root, 650, "Zainab Fatima", 3.15);
    root = Insert(root, 890, "Usman Ghani", 2.85);
    root = Insert(root, 430, "Duplicate Test", 1.00);

    cout << "=== All students (inorder, sorted by ID) ===" << endl;
    header();
    Inorder(root);

    cout << endl << "Total students: " << countStudents(root) << endl;

    cout << endl << "=== Search ===" << endl;
    int ids[] = { 650, 999 };
    for (int k = 0; k < 2; k++) {
        Student* f = Search(root, ids[k]);
        if (f != NULL) {
            cout << "Found: ";
            printStudent(f);
        } else {
            cout << "ID " << ids[k] << " not found." << endl;
        }
    }

    Student* hi = NULL;
    Student* lo = NULL;
    findExtremes(root, hi, lo);
    cout << endl << "=== GPA analysis ===" << endl;
    cout << "Highest GPA: " << hi->name << " (" << hi->GPA << ")" << endl;
    cout << "Lowest GPA : " << lo->name << " (" << lo->GPA << ")" << endl;

    float threshold = 3.0;
    cout << endl << "Students with GPA above " << threshold << ":" << endl;
    header();
    aboveThreshold(root, threshold);

    cout << endl << "=== Delete ===" << endl;
    cout << "Deleting 430 (leaf), 322 (one/two children), 541 (root)..." << endl;
    root = Delete(root, 430);
    root = Delete(root, 322);
    root = Delete(root, 541);
    header();
    Inorder(root);
    cout << endl << "Total students now: " << countStudents(root) << endl;

    return 0;
}
