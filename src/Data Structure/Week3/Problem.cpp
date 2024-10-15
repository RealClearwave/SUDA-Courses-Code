#include <iostream> 
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

template <typename T>
class Stack {
private:
    T *data;
    int topIndex;
    int capacity;

public:
    Stack(int size) : topIndex(-1), capacity(size) {
        data = new T[size];
    }

    ~Stack() {
        delete[] data;
    }

    void push(T value) {
        if (topIndex == capacity - 1) {
            cout << "Stack overflow" << endl;
            exit(1);
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (topIndex == -1) {
            cout << "Stack underflow" << endl;
            exit(1);
        }
        return data[topIndex--];
    }

    T top() const {
        if (topIndex == -1) {
            cout << "Stack is empty" << endl;
            exit(1);
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }
};

class exprProcessor{
public:
    double parseExpr(string expr);
private:
    vector<string> tokenize(string expr);

    int priority(char op);
    double operate(double opr1, double opr2, char op);

    double evalPrefix(vector<string> tokens);
    double evalInfix(vector<string> tokens);
    double evalPostfix(vector<string> tokens);

    bool isOperator(const string& token);
};

vector<string> exprProcessor::tokenize(string expr) {
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        if (isspace(ch)) {
            continue;
        }
        if (isdigit(ch) || ch == '.') {
            token += ch;
            while (i + 1 < expr.length() && (isdigit(expr[i + 1]) || expr[i + 1] == '.')) {
                token += expr[++i];
            }
            tokens.push_back(token);
            token.clear();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            if (ch == '-' && (tokens.empty() || isOperator(tokens.back()) || tokens.back() == "(")) {
                token += ch;
                while (i + 1 < expr.length() && (isdigit(expr[i + 1]) || expr[i + 1] == '.')) {
                    token += expr[++i];
                }
                tokens.push_back(token);
                token.clear();
            } else {
                tokens.push_back(string(1, ch));
            }
        } else if (ch == '(' || ch == ')' || ch == '#') {
            tokens.push_back(string(1, ch));
        } else {
            cout << "Invalid character: " << ch << endl;
            exit(1);
        }
    }
    return tokens;
}

bool exprProcessor::isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

int exprProcessor::priority(char op) {
    switch (op) {
        case '^': return 3;
        case '*': 
        case '/': return 2;
        case '+': 
        case '-': return 1;
        default: return 0;
    }
}

double exprProcessor::operate(double opr1, double opr2, char op) {
    switch (op) {
        case '+': return opr1 + opr2;
        case '-': return opr1 - opr2;
        case '*': return opr1 * opr2;
        case '/':
            if (opr2 == 0) {
                cout << "Division by zero error" << endl;
                exit(1);
            }
            return opr1 / opr2;
        case '^':
            return pow(opr1, opr2);
        default:
            cout << "Unknown operator: " << op << endl;
            exit(1);
    }
}

double exprProcessor::evalPostfix(vector<string> tokens) {
    Stack<double> stack(tokens.size());
    for (const string& token : tokens) {
        if (token == "#") {
            break;
        } else if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            stack.push(atof(token.c_str()));
        } else if (isOperator(token)) {
            if (stack.isEmpty()) {
                cout << "Invalid expression" << endl;
                exit(1);
            }
            double opr2 = stack.pop();
            if (stack.isEmpty()) {
                cout << "Invalid expression" << endl;
                exit(1);
            }
            double opr1 = stack.pop();
            double result = operate(opr1, opr2, token[0]);
            stack.push(result);
        } else {
            cout << "Invalid token: " << token << endl;
            exit(1);
        }
    }
    if (!stack.isEmpty()) {
        double result = stack.pop();
        if (!stack.isEmpty()) {
            cout << "Invalid expression" << endl;
            exit(1);
        }
        return result;
    } else {
        cout << "Invalid expression" << endl;
        exit(1);
    }
}

double exprProcessor::evalPrefix(vector<string> tokens) {
    Stack<double> stack(tokens.size());
    for (int i = tokens.size() - 1; i >= 0; i--) {
        const string& token = tokens[i];
        if (token == "#") {
            continue;
        } else if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            stack.push(atof(token.c_str()));
        } else if (isOperator(token)) {
            if (stack.isEmpty()) {
                cout << "Invalid expression" << endl;
                exit(1);
            }
            double opr1 = stack.pop();
            if (stack.isEmpty()) {
                cout << "Invalid expression" << endl;
                exit(1);
            }
            double opr2 = stack.pop();
            double result = operate(opr1, opr2, token[0]);
            stack.push(result);
        } else {
            cout << "Invalid token: " << token << endl;
            exit(1);
        }
    }
    if (!stack.isEmpty()) {
        double result = stack.pop();
        if (!stack.isEmpty()) {
            cout << "Invalid expression" << endl;
            exit(1);
        }
        return result;
    } else {
        cout << "Invalid expression" << endl;
        exit(1);
    }
}

double exprProcessor::evalInfix(vector<string> tokens) {
    Stack<double> values(tokens.size());
    Stack<char> operators(tokens.size());

    for (size_t i = 0; i < tokens.size(); ++i) {
        const string& token = tokens[i];
        if (token == "#") {
            break;
        } else if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            values.push(atof(token.c_str()));
        } else if (token == "(") {
            operators.push('(');
        } else if (token == ")") {
            while (!operators.isEmpty() && operators.top() != '(') {
                char op = operators.pop();
                double val2 = values.pop();
                double val1 = values.pop();
                double result = operate(val1, val2, op);
                values.push(result);
            }
            if (!operators.isEmpty() && operators.top() == '(') {
                operators.pop();
            } else {
                cout << "Invalid expression" << endl;
                exit(1);
            }
        } else if (isOperator(token)) {
            char currOp = token[0];
            while (!operators.isEmpty() && priority(operators.top()) >= priority(currOp)) {
                char op = operators.pop();
                double val2 = values.pop();
                double val1 = values.pop();
                double result = operate(val1, val2, op);
                values.push(result);
            }
            operators.push(currOp);
        } else {
            cout << "Invalid token: " << token << endl;
            exit(1);
        }
    }

    while (!operators.isEmpty()) {
        char op = operators.pop();
        double val2 = values.pop();
        double val1 = values.pop();
        double result = operate(val1, val2, op);
        values.push(result);
    }

    if (!values.isEmpty()) {
        double result = values.pop();
        if (!values.isEmpty()) {
            cout << "Invalid expression" << endl;
            exit(1);
        }
        return result;
    } else {
        cout << "Invalid expression" << endl;
        exit(1);
    }
}

double exprProcessor::parseExpr(string expr) {
    vector<string> tokens = tokenize(expr);
    if (tokens.empty()) {
        cout << "Empty expression" << endl;
        exit(1);
    }

    if (!tokens.empty() && tokens.back() == "#") {
        tokens.pop_back();
    }

    if (tokens.empty()) {
        cout << "Empty expression after removing '#'" << endl;
        exit(1);
    }

    bool isOperatorFirst = isOperator(tokens[0]);
    bool isOperatorLast = isOperator(tokens.back());

    if (isOperatorFirst && !isOperatorLast) {
        return evalPrefix(tokens);
    } else if (!isOperatorFirst && isOperatorLast) {
        return evalPostfix(tokens);
    } else {
        return evalInfix(tokens);
    }
}

int main() {
    exprProcessor processor;
    char expression[100];

    while (true) {
        cout << "Enter expression (end with '#' or 'exit' to quit): ";
        cin.getline(expression, 100);

        if (strcmp(expression, "exit") == 0) break;
        if (!strchr(expression, '#')) {
            cout << "Missing '#'.\n";
            continue;
        }

        cout << "Evaluation result: " << processor.parseExpr(string(expression)) << endl;
    }
    return 0;
}

