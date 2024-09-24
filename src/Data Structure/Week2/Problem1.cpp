#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

class SeqList {
protected:
    int *data;
    int maxSize;
    int length;

    void resize();

public:
    SeqList(int size = 10);
    virtual ~SeqList();

    bool isEmpty();
    int getLength();
    virtual void insert(int pos, int elem);
    virtual void remove(int pos);
    int get(int pos);
    void set(int pos, int elem);
    void clear();
    void display();
};

SeqList::SeqList(int size) {
    maxSize = size;
    data = new int[maxSize];
    length = 0;
}

SeqList::~SeqList() {
    delete[] data;
}

void SeqList::resize() {
    maxSize *= 2;
    int *newData = new int[maxSize];
    for (int i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

bool SeqList::isEmpty() {
    return length == 0;
}

int SeqList::getLength() {
    return length;
}

void SeqList::insert(int pos, int elem) {
    if (pos < 1 || pos > length + 1) {
        cout << "Invalid insert position!" << endl;
        return;
    }
    if (length >= maxSize) {
        resize();
    }
    for (int i = length; i >= pos; --i) {
        data[i] = data[i - 1];
    }
    data[pos - 1] = elem;
    length++;
}

void SeqList::remove(int pos) {
    if (pos < 1 || pos > length) {
        cout << "Invalid remove position!" << endl;
        return;
    }
    for (int i = pos; i < length; ++i) {
        data[i - 1] = data[i];
    }
    length--;
}

int SeqList::get(int pos) {
    if (pos < 1 || pos > length) {
        cout << "Invalid position!" << endl;
        exit(EXIT_FAILURE);
    }
    return data[pos - 1];
}

void SeqList::set(int pos, int elem) {
    if (pos < 1 || pos > length) {
        cout << "Invalid position!" << endl;
        return;
    }
    data[pos - 1] = elem;
}

void SeqList::clear() {
    length = 0;
}

void SeqList::display() {
    if (isEmpty()) {
        cout << "The list is empty!" << endl;
        return;
    }
    for (int i = 0; i < length; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

class OrderedSeqList : public SeqList {
public:
    OrderedSeqList(int size = 10);
    ~OrderedSeqList();

    void insert(int elem);
    void insertAt(int pos, int elem);
    void replace(int pos, int elem);
    void insert(int pos, int elem) override;
    void remove(int pos) override;
};

OrderedSeqList::OrderedSeqList(int size) : SeqList(size) {}

OrderedSeqList::~OrderedSeqList() {}

void OrderedSeqList::insert(int elem) {
    if (length >= maxSize) {
        resize();
    }
    int pos = 0;
    while (pos < length && data[pos] < elem) {
        pos++;
    }
    for (int i = length; i > pos; --i) {
        data[i] = data[i - 1];
    }
    data[pos] = elem;
    length++;
}

void OrderedSeqList::insertAt(int pos, int elem) {
    if (pos < 1 || pos > length + 1 || !(data[pos-2] <= elem && data[pos-1] >= elem)) {
        cout << "Invalid insert position!" << endl;
        return;
    }
    
    insert(elem);
}

void OrderedSeqList::replace(int pos, int elem) {
    if (pos < 1 || pos > length || !(data[pos-2] <= elem && data[pos] >= elem)) {
        cout << "Invalid position!" << endl;
        return;
    }
    remove(pos);
    insert(elem);
}

void OrderedSeqList::insert(int pos, int elem) {
    insert(elem);
}

void OrderedSeqList::remove(int pos) {
    SeqList::remove(pos);
}

int main() {
    SeqList seqList;
    OrderedSeqList orderedList;
    char choice;

    while (true) {
        cout << "\nSelect an operation:" << endl;
        cout << "1. Insert element in unordered list" << endl;
        cout << "2. Insert element by value in ordered list" << endl;
        cout << "3. Insert element by position in ordered list" << endl;
        cout << "4. Replace element in ordered list" << endl;
        cout << "5. Display unordered list" << endl;
        cout << "6. Display ordered list" << endl;
        cout << "Q. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 'Q' || choice == 'q') {
            cout << "Program exited." << endl;
            break;
        }

        int elem, pos;

        switch (choice) {
        case '1':
            cout << "Enter the element to insert: ";
            cin >> elem;
            cout << "Enter the position to insert: ";
            cin >> pos;
            seqList.insert(pos, elem);
            break;
        case '2':
            cout << "Enter the element to insert: ";
            cin >> elem;
            orderedList.insert(elem);
            break;
        case '3':
            cout << "Enter the element to insert: ";
            cin >> elem;
            cout << "Enter the position to insert: ";
            cin >> pos;
            orderedList.insertAt(pos, elem);
            break;
        case '4':
            cout << "Enter the position to replace: ";
            cin >> pos;
            cout << "Enter the new element value: ";
            cin >> elem;
            orderedList.replace(pos, elem);
            break;
        case '5':
            cout << "Elements in unordered list:" << endl;
            seqList.display();
            break;
        case '6':
            cout << "Elements in ordered list:" << endl;
            orderedList.display();
            break;
        default:
            cout << "Invalid choice, please try again!" << endl;
            break;
        }
    }

    return 0;
}

