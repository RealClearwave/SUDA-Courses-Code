#include <iostream>
#include <cstdlib>

using namespace std;

class Link {
public:
    virtual void initialize() = 0;
    virtual void destroy() = 0;
    virtual void create(int arr[], int n) = 0;
    virtual void insert(int i, int x) = 0;
    virtual void remove(int i) = 0;
    virtual int get(int i) = 0;
    virtual int search(int x) = 0;
    virtual void display() = 0;
    virtual ~Link() {}
};

// Single Linked List
class SingleLink : public Link {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;

public:
    SingleLink() { head = nullptr; }
    virtual ~SingleLink() { destroy(); }

    void initialize() override {
        destroy();
        head = new Node;
        head->next = nullptr;
    }

    void destroy() override {
        Node* p = head;
        while (p) {
            Node* q = p->next;
            delete p;
            p = q;
        }
        head = nullptr;
    }

    void create(int arr[], int n) override {
        initialize();
        Node* tail = head;
        for (int i = 0; i < n; ++i) {
            Node* node = new Node;
            node->data = arr[i];
            node->next = nullptr;
            tail->next = node;
            tail = node;
        }
    }

    void insert(int i, int x) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* p = head;
        int j = 0;
        while (p && j < i - 1) {
            p = p->next;
            j++;
        }
        if (!p) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* node = new Node;
        node->data = x;
        node->next = p->next;
        p->next = node;
    }

    void remove(int i) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* p = head;
        int j = 0;
        while (p->next && j < i - 1) {
            p = p->next;
            j++;
        }
        if (!p->next) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* q = p->next;
        p->next = q->next;
        delete q;
    }

    int get(int i) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            exit(EXIT_FAILURE);
        }
        Node* p = head->next;
        int j = 1;
        while (p && j < i) {
            p = p->next;
            j++;
        }
        if (!p) {
            cout << "Invalid position!" << endl;
            exit(EXIT_FAILURE);
        }
        return p->data;
    }

    int search(int x) override {
        Node* p = head->next;
        int j = 1;
        while (p) {
            if (p->data == x)
                return j;
            p = p->next;
            j++;
        }
        return -1; // Not found
    }

    void display() override {
        Node* p = head->next;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

// Circular Single Linked List
class IterSingleLink : public Link {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;

public:
    IterSingleLink() { head = nullptr; }
    virtual ~IterSingleLink() { destroy(); }

    void initialize() override {
        destroy();
        head = new Node;
        head->next = head;
    }

    void destroy() override {
        if (!head)
            return;
        Node* p = head->next;
        while (p != head) {
            Node* q = p->next;
            delete p;
            p = q;
        }
        delete head;
        head = nullptr;
    }

    void create(int arr[], int n) override {
        initialize();
        Node* tail = head;
        for (int i = 0; i < n; ++i) {
            Node* node = new Node;
            node->data = arr[i];
            node->next = head;
            tail->next = node;
            tail = node;
        }
    }

    void insert(int i, int x) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* p = head;
        int j = 0;
        while (p->next != head && j < i - 1) {
            p = p->next;
            j++;
        }
        if (j != i -1) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* node = new Node;
        node->data = x;
        node->next = p->next;
        p->next = node;
    }

    void remove(int i) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* p = head;
        int j = 0;
        while (p->next != head && j < i -1) {
            p = p->next;
            j++;
        }
        if (p->next == head || j != i -1) {
            cout << "Invalid position!" << endl;
            return;
        }
        Node* q = p->next;
        p->next = q->next;
        delete q;
    }

    int get(int i) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            exit(EXIT_FAILURE);
        }
        Node* p = head->next;
        int j = 1;
        while (p != head && j < i) {
            p = p->next;
            j++;
        }
        if (p == head) {
            cout << "Invalid position!" << endl;
            exit(EXIT_FAILURE);
        }
        return p->data;
    }

    int search(int x) override {
        Node* p = head->next;
        int j = 1;
        while (p != head) {
            if (p->data == x)
                return j;
            p = p->next;
            j++;
        }
        return -1;
    }

    void display() override {
        Node* p = head->next;
        while (p != head) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

// Doubly Linked List
class DoubleLink : public Link {
private:
    struct DNode {
        int data;
        DNode* prev;
        DNode* next;
    };
    DNode* head;

public:
    DoubleLink() { head = nullptr; }
    virtual ~DoubleLink() { destroy(); }

    void initialize() override {
        destroy();
        head = new DNode;
        head->prev = nullptr;
        head->next = nullptr;
    }

    void destroy() override {
        DNode* p = head;
        while (p) {
            DNode* q = p->next;
            delete p;
            p = q;
        }
        head = nullptr;
    }

    void create(int arr[], int n) override {
        initialize();
        DNode* tail = head;
        for (int i = 0; i < n; ++i) {
            DNode* node = new DNode;
            node->data = arr[i];
            node->next = nullptr;
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }

    void insert(int i, int x) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        DNode* p = head;
        int j = 0;
        while (p && j < i -1) {
            p = p->next;
            j++;
        }
        if (!p) {
            cout << "Invalid position!" << endl;
            return;
        }
        DNode* node = new DNode;
        node->data = x;
        node->next = p->next;
        node->prev = p;
        if (p->next)
            p->next->prev = node;
        p->next = node;
    }

    void remove(int i) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        DNode* p = head;
        int j = 0;
        while (p->next && j < i -1) {
            p = p->next;
            j++;
        }
        if (!p->next) {
            cout << "Invalid position!" << endl;
            return;
        }
        DNode* q = p->next;
        p->next = q->next;
        if (q->next)
            q->next->prev = p;
        delete q;
    }

    int get(int i) override {
        if (i < 1) {
            cout << "Invalid position!" << endl;
            exit(EXIT_FAILURE);
        }
        DNode* p = head->next;
        int j =1;
        while (p && j < i) {
            p = p->next;
            j++;
        }
        if (!p) {
            cout << "Invalid position!" << endl;
            exit(EXIT_FAILURE);
        }
        return p->data;
    }

    int search(int x) override {
        DNode* p = head->next;
        int j = 1;
        while (p) {
            if (p->data == x)
                return j;
            p = p->next;
            j++;
        }
        return -1;
    }

    void display() override {
        DNode* p = head->next;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

void menu() {
    cout << "Select list type:" << endl;
    cout << "1. Single Linked List" << endl;
    cout << "2. Circular Single Linked List" << endl;
    cout << "3. Double Linked List" << endl;
    cout << "Q. Quit" << endl;
    cout << "Enter your choice: ";
}

void operationsMenu() {
    cout << "\nSelect an operation:" << endl;
    cout << "1. Create list" << endl;
    cout << "2. Insert element" << endl;
    cout << "3. Delete element" << endl;
    cout << "4. Get element" << endl;
    cout << "5. Search element" << endl;
    cout << "6. Display list" << endl;
    cout << "Q. Quit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Link* list = nullptr;
    char choice;
    while (true) {
        menu();
        cin >> choice;
        if (choice == 'Q' || choice == 'q') {
            cout << "Program exited." << endl;
            break;
        }
        switch (choice) {
        case '1':
            list = new SingleLink();
            break;
        case '2':
            list = new IterSingleLink();
            break;
        case '3':
            list = new DoubleLink();
            break;
        default:
            cout << "Invalid choice, please try again!" << endl;
            continue;
        }
        break;
    }
    if (!list)
        return 0;

    char opChoice;
    while (true) {
        operationsMenu();
        cin >> opChoice;
        if (opChoice == 'Q' || opChoice == 'q') {
            cout << "Program exited." << endl;
            delete list;
            break;
        }
        int pos, x, n;
        switch (opChoice) {
        case '1':
            cout << "Enter number of elements: ";
            cin >> n;
            if (n <= 0) {
                cout << "Invalid number!" << endl;
                break;
            }
            int* arr;
            arr = new int[n];
            cout << "Enter the elements: ";
            for (int i = 0; i < n; ++i) {
                cin >> arr[i];
            }
            list->create(arr, n);
            delete[] arr;
            break;
        case '2':
            cout << "Enter position to insert: ";
            cin >> pos;
            cout << "Enter element to insert: ";
            cin >> x;
            list->insert(pos, x);
            break;
        case '3':
            cout << "Enter position to delete: ";
            cin >> pos;
            list->remove(pos);
            break;
        case '4':
            cout << "Enter position to get: ";
            cin >> pos;
            x = list->get(pos);
            cout << "Element at position " << pos << " is " << x << endl;
            break;
        case '5':
            cout << "Enter element to search: ";
            cin >> x;
            pos = list->search(x);
            if (pos != -1)
                cout << "Element found at position " << pos << endl;
            else
                cout << "Element not found." << endl;
            break;
        case '6':
            cout << "Current list elements: ";
            list->display();
            break;
        default:
            cout << "Invalid choice, please try again!" << endl;
            break;
        }
    }
    return 0;
}
