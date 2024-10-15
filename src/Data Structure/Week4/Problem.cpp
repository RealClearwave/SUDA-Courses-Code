#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class Queue {
    int data[MAX_SIZE];
    int front, rear, size;
public:
    Queue() : front(0), rear(0), size(0) {}

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == MAX_SIZE;
    }

    void enqueue(int value) {
        if (!isFull()) {
            data[rear] = value;
            rear = (rear + 1) % MAX_SIZE;
            size++;
        }
    }

    int dequeue() {
        if (!isEmpty()) {
            int value = data[front];
            front = (front + 1) % MAX_SIZE;
            size--;
            return value;
        }
        return -1;
    }
};

class Stack {
    int data[MAX_SIZE];
    int top;
public:
    Stack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    void push(int value) {
        if (!isFull()) {
            data[++top] = value;
        }
    }

    int pop() {
        if (!isEmpty()) {
            return data[top--];
        }
        return -1;
    }

    int peek() const {
        if (!isEmpty()) {
            return data[top];
        }
        return -1;
    }

    int find(int value) const {
        for (int i = 0; i <= top; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    void removeFrom(int index) {
        if (index <= top && index >= 0) {
            top = index - 1;
        }
    }

    void reset() {
        top = -1;
    }
};

void playGame(Queue& playerA, Queue& playerB) {
    Stack table;
    bool turnA = true;

    while (!playerA.isEmpty() && !playerB.isEmpty()) {
        Queue& currentPlayer = turnA ? playerA : playerB;
        int card = currentPlayer.dequeue();
        cout << "Player " << (turnA?'A':'B') << " plays " << card << endl; 
        int foundIndex = table.find(card);

        table.push(card);

        if (foundIndex != -1) {
            while (table.peek() != card) {
            	cout << "Player " << (turnA?'A':'B') << " takes " << table.peek() << endl; 
                currentPlayer.enqueue(table.pop());
            }
            
            cout << "Player " << (turnA?'A':'B') << " takes " << table.peek() << endl; 
            currentPlayer.enqueue(table.pop());
            table.reset(); 
        }

        turnA = !turnA;
    }

    cout << (playerA.isEmpty() ? "B wins!" : "A wins!") << endl;
}

int main() {
    int n;
    cout << "Enter the number of cards for each player: ";
    cin >> n;

    Queue playerA, playerB;
    int card;

    cout << "Enter cards for player A: ";
    for (int i = 0; i < n; i++) {
        cin >> card;
        playerA.enqueue(card);
    }

    cout << "Enter cards for player B: ";
    for (int i = 0; i < n; i++) {
        cin >> card;
        playerB.enqueue(card);
    }

    playGame(playerA, playerB);

    return 0;
}

