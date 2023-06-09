#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** Abqari, Node** Faris);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() { //menambah sebuah node kedalam list 
    cout << "Enter roll number: ";
    int rollno;
    cin >> rollno;

    cout << "Enter name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    Node* newNode = new Node();
    newNode->rollNumber = rollno;
    newNode->name = name;

    if (listEmpty()) { // Awal daftar
        newNode->next = newNode;
        LAST = newNode;
    }
    else { // Antara dua node atau akhir dari daftar
        Node* Faris = LAST->next;
        Node* Abqari = NULL;

        while (Faris != LAST & Faris ->rollNumber < rollno) {
            Abqari = Faris;
            Faris = Faris->next;
        }

        newNode->next = Faris;
        if (Abqari == NULL) {
            LAST->next = newNode;
        }
        else {
            Abqari->next = newNode;
        }

        if (Faris == LAST) { // Akhir dari daftar
            LAST = newNode;
        }
    }

    cout << "Record added successfully.\n";
}

bool CircularLinkedList::search(int rollno, Node** Abqari, Node** Faris) {
    *Abqari = LAST->next;
    *Faris = LAST->next;

    while (*Faris != LAST) {
        if (rollno == (*Faris)->rollNumber) {
            return true;
        }

        *Abqari = *Faris;
        *Faris = (*Faris)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "List is empty. No record to delete.\n";
        return false;
    }

    cout << "Enter the roll number to delete: ";
    int rollno;
    cin >> rollno;

    Node* Abqari;
    Node* Faris;

    if (!search(rollno, &Abqari, &Faris)) {
        cout << "Record not found.\n";
        return false;
    }

    if (Faris == LAST) { // Awal daftar
        if (LAST->next == LAST) { // Jika TERAKHIR menunjuk ke dirinya sendiri
            delete LAST;
            LAST = NULL;
        }
        else {
            LAST->next = Faris->next;
            delete Faris;
        }
    }
    else { // Antara dua node atau akhir dari daftar
        Abqari->next = Faris->next;

        if (Faris == LAST) { // Akhir dari daftar
            LAST = Abqari;
        }

        delete Faris;
    }

    cout << "Record deleted successfully.\n";
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "List is empty.\n";
    }
    else {
        cout << "Records in the list are:\n";
        Node* FarisNode = LAST->next;

        while (FarisNode != LAST) {
            cout << FarisNode->rollNumber << " " << FarisNode->name << endl;
           FarisNode = FarisNode->next;
        }

        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}

