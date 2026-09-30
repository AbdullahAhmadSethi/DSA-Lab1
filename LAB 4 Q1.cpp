#include <iostream>
#include <string>
using namespace std;

struct Node {

    int id;
    string name;
    string duration;   // STORED AS min:sec
    Node* prev;
    Node* next;

};

class Playlist {

    Node* head;
    Node* tail;
    Node* current;   // POINTER TO CURRENTLY PLAYING THE SONG

public:

    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    // ADD SONG AT END

    void addSong(int id, string name, string duration) {

        Node* newNode = new Node{id, name, duration, nullptr, nullptr};

        if (!head) {                 // empty playlist
            head = tail = current = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // DELETE SONG BY ID

    void deleteSong(int id) {

        Node* temp = head;
        while (temp && temp->id != id) temp = temp->next;
        if (!temp) { cout << "Song not found.\n"; return; }

        // FIX CURRENT POINTER IF WE DELETE THE PLAYING SONG
        if (current == temp) current = temp->next ? temp->next : temp->prev;

        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next;         // deleting head

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev;         // deleting tail

        delete temp;
        cout << "Song deleted.\n";
    }

    // DISPLAY FORWARD

    void displayForward() {

        if (!head) { cout << "Playlist is empty.\n"; return; }
        cout << "\n--- Playlist (Forward) ---\n";

        for (Node* t = head; t; t = t->next)
            cout << "ID: " << t->id << " | " << t->name
                 << " | " << t->duration << "\n";
    }

    // DISPLAY BACKWARD

    void displayBackward() {

        if (!tail) { cout << "Playlist is empty.\n"; return; }

        cout << "\n--- Playlist (Backward) ---\n";

        for (Node* t = tail; t; t = t->prev)
            cout << "ID: " << t->id << " | " << t->name
                 << " | " << t->duration << "\n";
    }

    // SEARCH SONG BY ID

    void searchSong(int id) {

        for (Node* t = head; t; t = t->next) {

            if (t->id == id) {
                cout << "Found -> ID: " << t->id << " | " << t->name
                     << " | " << t->duration << "\n";
                return;

            }
        }
        cout << "Song not found.\n";
    }

    // PLAY NEXT SONG

    void playNext() {

        if (!current) { cout << "No song loaded.\n"; return; }

        if (current->next) current = current->next;
        else cout << "(End of playlist) ";

        cout << "Now playing: " << current->name << "\n";
    }

    // PLAY PREVIOUS SONG

    void playPrevious() {

        if (!current) { cout << "No song loaded.\n"; return; }

        if (current->prev) current = current->prev;
        else cout << "(Start of playlist) ";
        cout << "Now playing: " << current->name << "\n";
    }

    // REVERSE PLAYLIST IN PLACE (SWAP NEXT AND PREV OF EACH NODE)

    void reversePlaylist() {

        Node* temp = nullptr;
        Node* curr = head;
        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;   // move to next (which is old prev)
        }

        swap(head, tail);        // swap head and tail
        cout << "Playlist reversed.\n";
    }
};

int main() {

    Playlist p;
    int choice, id;
    string name, dur;

    while (true) {

        cout << "1.ADD\n2.DELETE\n3.FORWARD\n4.BACKWARD\n5.SEARCH"
                "\n6.NEXT\n7.PREV\n8.REVERSE\n9.EXIT\nCHOICE: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "ID: "; cin >> id;
                cout << "Name: "; cin.ignore(); getline(cin, name);
                cout << "Duration (m:ss): "; cin >> dur;
                p.addSong(id, name, dur);
                break;
            case 2:
                cout << "ID to delete: "; cin >> id;
                p.deleteSong(id); break;
            case 3: p.displayForward();  break;
            case 4: p.displayBackward(); break;
            case 5:
                cout << "ID to search: "; cin >> id;
                p.searchSong(id); break;
            case 6: p.playNext();     break;
            case 7: p.playPrevious(); break;
            case 8: p.reversePlaylist(); break;
            case 9: return 0;
            default: cout << "Invalid choice.\n";

        }

        
        cout<<"______________________________________________";
        cout << "\n";
    }
}