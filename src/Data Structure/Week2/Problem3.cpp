#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class SingleLink {
public:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;
    SingleLink() {
        head = new Node;
        head->next = nullptr;
    }
    ~SingleLink() {
        destroy();
        delete head;
    }

    void insert(int x) {
        Node* node = new Node;
        node->data = x;
        node->next = head->next;
        head->next = node;
    }

    void remove(int x) {
        Node* p = head;
        while (p->next) {
            if (p->next->data == x) {
                Node* q = p->next;
                p->next = q->next;
                delete q;
                return;
            }
            p = p->next;
        }
    }

    bool search(int x) {
        Node* p = head->next;
        while (p) {
            if (p->data == x)
                return true;
            p = p->next;
        }
        return false;
    }

    void sort() {
        if (!head->next || !head->next->next)
            return;
        Node* p = head->next;
        Node* q;
        int temp;
        while (p) {
            q = p->next;
            while (q) {
                if (p->data > q->data) {
                    temp = p->data;
                    p->data = q->data;
                    q->data = temp;
                }
                q = q->next;
            }
            p = p->next;
        }
    }

    void display() {
        Node* p = head->next;
        if (!p) {
            cout << endl;
            return;
        }
        while (p) {
            cout << " " << p->data;
            p = p->next;
        }
        cout << endl;
    }

    int count() {
        int cnt = 0;
        Node* p = head->next;
        while (p) {
            cnt++;
            p = p->next;
        }
        return cnt;
    }

    void destroy() {
        Node* p = head->next;
        while (p) {
            Node* q = p->next;
            delete p;
            p = q;
        }
        head->next = nullptr;
    }

    int removeFirst() {
        if (!head->next)
            return -1;
        Node* p = head->next;
        int x = p->data;
        head->next = p->next;
        delete p;
        return x;
    }
};

int main() {
    ifstream infile("input.txt");
    if (!infile.is_open()) {
        cout << "Failed to open input file." << endl;
        return 0;
    }
    int n;
    infile >> n;
    if (n < 1 || n > 20) {
        cout << "Invalid number of decks." << endl;
        return 0;
    }

    SingleLink*** decks = new SingleLink**[n];
    for (int i = 0; i < n; ++i) {
        decks[i] = new SingleLink*[4];
        for (int j = 0; j < 4; ++j) {
            decks[i][j] = new SingleLink();
            int k;
            infile >> k;
            for (int l = 0; l < k; ++l) {
                int card;
                infile >> card;
                if (card < 1 || card > 13) {
                    cout << "Invalid card number." << endl;
                    return 0;
                }
                decks[i][j]->insert(card);
            }
        }
    }
    infile.close();

    int cardCounts[4][13] = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            SingleLink::Node* p = decks[i][j]->head->next;
            while (p) {
                cardCounts[j][p->data - 1]++;
                p = p->next;
            }
        }
    }

    int completeSets = INT_MAX;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            if (cardCounts[i][j] < completeSets)
                completeSets = cardCounts[i][j];
        }
    }
    if (completeSets == INT_MAX)
        completeSets = 0;

    cout << completeSets << endl;

    for (int i = 0; i < n; ++i) {
        for (int s = 0; s < 4; ++s) {
            for (int c = 1; c <= 13; ++c) {
                for (int k = 0; k < completeSets; ++k) {
                    if (decks[i][s]->search(c)) {
                        decks[i][s]->remove(c);
                        break;
                    }
                }
            }
        }
    }

    string suits[4] = {"Spades:", "Hearts:", "Clubs:", "Diamonds:"};

    for (int i = 0; i < n; ++i) {
        for (int s = 0; s < 4; ++s) {
            cout << suits[s];
            decks[i][s]->sort();
            decks[i][s]->display();
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            delete decks[i][j];
        }
        delete[] decks[i];
    }
    delete[] decks;

    return 0;
}
