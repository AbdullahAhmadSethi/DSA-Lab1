#include <iostream>
#include <string>
using namespace std;

struct Node {
    int bit;
    Node* next;
    Node* prev;
};

class Binary {

    Node* head;   // MSB SIDE
    Node* tail;   // LSB SIDE

public:

    Binary() : head(nullptr), tail(nullptr) {}

    // COPY SUPPORT (NEEDED FOR MULTIPLICATION)

    Binary(const Binary& o) : head(nullptr), tail(nullptr) { copyFrom(o); }

    Binary& operator=(const Binary& o) {

        if (this != &o) { clear(); copyFrom(o); }
        return *this;

    }

    ~Binary() { clear(); }

    void copyFrom(const Binary& o) {

        for (Node* t = o.head; t; t = t->next) {

            Node* n = new Node{t->bit, nullptr, nullptr};
            if (!head) head = tail = n;
            else { tail->next = n; n->prev = tail; tail = n; }

        }
    }

    void clear() {

        while (head) { Node* nx = head->next; delete head; head = nx; }
        tail = nullptr;

    }

    // STORE BITS FROM STRING (MSB AT HEAD, LSB AT TAIL)

    void fromString(const string& s) {

        clear();

        for (char c : s) {

            if (c != '0' && c != '1') continue;
            Node* n = new Node{c - '0', nullptr, nullptr};

            if (!head) head = tail = n;
            else { tail->next = n; n->prev = tail; tail = n; }
        }

        if (!head) { Node* n = new Node{0, nullptr, nullptr}; head = tail = n; }
    }

    // DISPLAY IN 8-BIT GROUPS WITH LEADING ZEROS

    void display() {

        int count = 0;
        for (Node* t = head; t; t = t->next) count++;
        int pad = (8 - count % 8) % 8;
        
        string out(pad, '0');

        for (Node* t = head; t; t = t->next) out += char('0' + t->bit);

        for (int i = 0; i < (int)out.size(); i++) {
            if (i > 0 && i % 8 == 0) cout << ' ';
            cout << out[i];
        }
    }

    // FLIP EVERY BIT

    void onesComplement() {
        for (Node* t = head; t; t = t->next) t->bit ^= 1;
    }

    // ADD 1 TO THE DLL (USED IN 2'S COMPLEMENT)

    void addOne() {

        Node* t = tail;
        int carry = 1;

        while (t && carry) {
            int s = t->bit + carry;
            t->bit = s % 2;
            carry = s / 2;
            t = t->prev;
        }

        if (carry) {  // PREPEND NEW MSB
            Node* n = new Node{1, head, nullptr};
            head->prev = n;
            head = n;
        }
    }

    void twosComplement() {
        onesComplement();
        addOne();
    }

    // SHIFT LEFT BY n (MULTIPLY BY 2^n): APPEND n ZEROS AT LSB SIDE

    void shiftLeft(int n) {

        for (int i = 0; i < n; i++) {
            Node* node = new Node{0, nullptr, tail};
            tail->next = node;
            tail = node;

        }
    }

    // BINARY ADDITION (RETURNS NEW DLL, CARRIES HANDLED)

    static Binary add(const Binary& a, const Binary& b) {

        Binary result;
        Node* pa = a.tail;
        Node* pb = b.tail;
        int carry = 0;

        while (pa || pb || carry) {
            
            int s = carry;
            if (pa) { s += pa->bit; pa = pa->prev; }
            if (pb) { s += pb->bit; pb = pb->prev; }
            Node* n = new Node{s % 2, nullptr, nullptr};

            if (!result.head) result.head = result.tail = n;
            else {                 // PREPEND AT MSB SIDE
                n->next = result.head;
                result.head->prev = n;
                result.head = n;
            }
            carry = s / 2;
        }
        return result;
    }

    // BINARY MULTIPLICATION: SHIFT-AND-ADD

    static Binary multiply(const Binary& a, const Binary& b) {

        Binary result;
        result.fromString("0");
        int pos = 0;

        for (Node* t = b.tail; t; t = t->prev, pos++) {
            if (t->bit == 1) {
                Binary temp = a;        // COPY A
                temp.shiftLeft(pos);    // A * 2^pos
                result = add(result, temp);
            }
        }
        return result;
    }

    // BINARY DLL TO DECIMAL

    long long toDecimal() {

        long long val = 0;
        for (Node* t = head; t; t = t->next) val = val * 2 + t->bit;
        return val;

    }
};

int main() {

    Binary a, b;
    string s;
    cout << "Enter first binary number:  "; cin >> s; a.fromString(s);
    cout << "Enter second binary number: "; cin >> s; b.fromString(s);

    int choice;
    while (true) {
        cout << "\n1.Display\n2.1's Comp(A)\n3.2's Comp(A)"
                "\n4.Add\n5.Multiply\n6.To Decimal\n7.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "A = "; a.display(); cout << "\n";
                cout << "B = "; b.display(); cout << "\n";
                break;
            case 2:
                a.onesComplement();
                cout << "1's Complement of A = "; a.display(); cout << "\n";
                break;
            case 3:
                a.twosComplement();
                cout << "2's Complement of A = "; a.display(); cout << "\n";
                break;
            case 4: {
                Binary r = Binary::add(a, b);
                cout << "Sum = "; r.display(); cout << "\n";
                break;
            }
            case 5: {
                Binary r = Binary::multiply(a, b);
                cout << "Product = "; r.display(); cout << "\n";
                break;
            }
            case 6:
                cout << "A in decimal = " << a.toDecimal() << "\n";
                cout << "B in decimal = " << b.toDecimal() << "\n";
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    
    cout << "\n____________________________________________________________";
    }
}