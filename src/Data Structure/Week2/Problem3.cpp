#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <climits>

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

    // Count total number of each unique card (suit and rank)
    int cardCounts[4][13] = {0};
    for (int i = 0; i < n; ++i) {
        for (int s = 0; s < 4; ++s) {
            SingleLink::Node* p = decks[i][s]->head->next;
            while (p) {
                cardCounts[s][p->data - 1]++;
                p = p->next;
            }
        }
    }

    // Calculate the number of complete decks that can be formed
    int completeSets = INT_MAX;
    for (int s = 0; s < 4; ++s) {
        for (int r = 0; r < 13; ++r) {
            if (cardCounts[s][r] < completeSets)
                completeSets = cardCounts[s][r];
        }
    }
    if (completeSets == INT_MAX)
        completeSets = 0;

    cout << completeSets << endl;

    // Remove cards used to form complete decks from the original decks
    for (int c = 0; c < completeSets; ++c) {
        for (int s = 0; s < 4; ++s) {
            for (int r = 1; r <=13; ++r) {
                bool removed = false;
                for (int i = 0; i < n && !removed; ++i) {
                    if (decks[i][s]->search(r)) {
                        decks[i][s]->remove(r);
                        removed = true;
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
        for (int s = 0; s < 4; ++s) {
            delete decks[i][s];
        }
        delete[] decks[i];
    }
    delete[] decks;

    return 0;
}

