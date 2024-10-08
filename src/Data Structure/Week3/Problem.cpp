#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

class Stack {
private:
    double *data;
    int top;
    int capacity;

public:
    Stack(int size) : top(-1), capacity(size) {
        data = new double[size];
    }

    ~Stack() {
        delete[] data;
    }

    void push(double value) {
        if (top == capacity - 1) {
            cout << "Stack overflow" << endl;
            exit(1);
        }
        data[++top] = value;
    }

    double pop() {
        if (top == -1) {
            cout << "Stack underflow" << endl;
            exit(1);
        }
        return data[top--];
    }

    double peek() const {
        if (top == -1) {
            cout << "Stack is empty" << endl;
            exit(1);
        }
        return data[top];
    }

    bool isEmpty() const {
        return top == -1;
    }
};

class ExpressionProcessor {
public:
    double evaluateInfix(const char *expression);
    double evaluatePostfix(const char *expression);
private:
    int precedence(char op);
    double applyOperation(double a, double b, char op);
    double readNumber(const char *&expr, bool isNegative);
};

int ExpressionProcessor::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double ExpressionProcessor::applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

double ExpressionProcessor::readNumber(const char *&expr, bool isNegative) {
    double result = 0;
    double fraction = 1;
    bool isFraction = false;

    while (isdigit(*expr) || *expr == '.') {
        if (*expr == '.') {
            isFraction = true;
            expr++;
            continue;
        }
        if (isFraction) {
            fraction *= 0.1;
            result += (*expr - '0') * fraction;
        } else {
            result = result * 10 + (*expr - '0');
        }
        expr++;
    }
    return isNegative ? -result : result;
}

double ExpressionProcessor::evaluateInfix(const char *expression) {
    Stack values(100);
    Stack ops(100);
    bool expectNegative = true;

    while (*expression != '#') {
        if (*expression == ' ') {
            expression++;
            continue;
        }
        if (isdigit(*expression) || (*expression == '-' && expectNegative)) {
            bool isNegative = (*expression == '-');
            if (isNegative) expression++;
            values.push(readNumber(expression, isNegative));
            expectNegative = false;
        } else if (*expression == '(') {
            ops.push(*expression++);
            expectNegative = true;
        } else if (*expression == ')') {
            while (!ops.isEmpty() && ops.peek() != '(') {
                double val2 = values.pop();
                double val1 = values.pop();
                char op = (char)ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.pop();
            expression++;
            expectNegative = false;
        } else {
            while (!ops.isEmpty() && precedence(ops.peek()) >= precedence(*expression)) {
                double val2 = values.pop();
                double val1 = values.pop();
                char op = (char)ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(*expression++);
            expectNegative = true;
        }
    }

    while (!ops.isEmpty()) {
        double val2 = values.pop();
        double val1 = values.pop();
        char op = (char)ops.pop();
        values.push(applyOperation(val1, val2, op));
    }

    return values.pop();
}

double ExpressionProcessor::evaluatePostfix(const char *expression) {
    Stack stack(100);

    while (*expression != '#') {
        if (*expression == ' ') {
            expression++;
            continue;
        }
        if (isdigit(*expression) || (*expression == '-' && isdigit(*(expression + 1)))) {
            stack.push(readNumber(expression, *expression == '-'));
            if (*expression == '-') expression++;
        } else {
            double val2 = stack.pop();
            double val1 = stack.pop();
            stack.push(applyOperation(val1, val2, *expression++));
        }
    }
    return stack.pop();
}

void runShell() {
    ExpressionProcessor processor;
    char expression[100];

    while (true) {
        cout << "Enter expression (end with '#') or 'exit' to quit: ";
        cin.getline(expression, 100);

        if (strcmp(expression, "exit") == 0) break;
        if (!strchr(expression, '#')) {
            cout << "Missing '#'.\n";
            continue;
        }

        if (strchr(expression, ' ')) {
            cout << "Postfix evaluation result: " << processor.evaluatePostfix(expression) << endl;
        } else {
            cout << "Infix evaluation result: " << processor.evaluateInfix(expression) << endl;
        }
    }
}

int main() {
    runShell();
    return 0;
}

