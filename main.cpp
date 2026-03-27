#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    bool isOperator(const string& s);
    vector<Token> tokens;
    int i = 0;
    while (i < line.length()) {
        if (isOperator(line.substr(i, 1)) || isdigit(line[i]) || line[i] == ')' || line[i] == '(') {
            if (isdigit(line[i])) {
                string num = line.substr(i, 1);
                while (i + 1 < line.length() && isdigit(line[i + 1])) {
                    num += line.substr(++i, 1);
                }
                Token t;
                t.value = num;
                tokens.push_back(t);
                i++;
            }
            else {
                if (line[i] == '(' && !tokens.empty()) {
                    const Token* last = &tokens.back();
                    if (isdigit(last->value[0])) {
                        Token mult;
                        mult.value = "*";
                        tokens.push_back(mult);
                    }
                }
                Token t;
                t.value = line.substr(i, 1);
                tokens.push_back(t);
                i++;
            }
        }
        else if (!isspace(line[i])) {
            throw runtime_error("Input only digits (0-9), arithmetic operators (+, -, /, *), and parentheses only");
        } else i++;
    }
    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    if (op == "(") return 3;
    if (isOperator(op)) return (op == "*" || op == "/") ? 2 : 1;
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    if (tokens.empty()) return false;

    int numCount = 0;
    int opCount = 0;

    for (const Token& t : tokens) {
        if (t.value == "(" || t.value == ")") return false;
        if (isOperator(t.value)) {
            opCount++;
            if (opCount >= numCount) return false;
        }
        else {
            numCount++;
        }
    }

    return numCount - opCount == 1;
}

bool isValidInfix(const vector<Token>& tokens) {
    if (tokens.empty()) return false;

    int i = 0;
    ArrayStack<string> openParentheses;
    while (i < tokens.size()) {
        const Token *t = &tokens[i];
        if (t->value == "(") {
            openParentheses.push(t->value);
        }
        else if (t->value == ")") {
            try {
                openParentheses.pop();
            }
            catch (...) {
                return false;
            }
        }
        else {
            if (i == 0) {
                if (isOperator(t->value)) return false;
            }
            else {
                const Token *prev = &tokens[i - 1];
                if (isOperator(t->value)) {
                    if (i == tokens.size() - 1) return false;
                    if (isOperator(prev->value)) return false;
                }
                else {
                    if (prev->value == ")") return false;
                    if (prev->value != "(" && !isOperator(prev->value)) return false;
                }
            }
        }

        i++;
    }

    return true;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    if (!isValidInfix(tokens)) {
        throw runtime_error("Not a valid infix expression");
    }

    vector<Token> output;
    ArrayStack<Token> opStack;

    for (const Token& t : tokens) {
        if (precedence(t.value) > 0) {
            if (!opStack.empty()) {
                Token prev = opStack.top();
                if (isOperator(prev.value) && precedence(prev.value) > precedence(t.value)) {
                    opStack.pop();
                    output.push_back(prev);
                }
            }
            opStack.push(t);
        }
        else if (t.value == ")") {
            while (!opStack.empty() && isOperator(opStack.top().value)) {
                Token op = opStack.top();
                opStack.pop();
                output.push_back(op);
            }
            opStack.pop();
        }
        else {
            output.push_back(t);
        }
    }
    while (!opStack.empty()) {
        Token t = opStack.top();
        opStack.pop();
        output.push_back(t);
    }

    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    if (!isValidPostfix(tokens)) {
        throw runtime_error("Not a valid postfix expression");
    }
    for (const Token& t : tokens) {
        if (!isOperator(t.value)) {
            stack.push(stod(t.value));
        }
        else {
            const double num1 = stack.top();
            stack.pop();
            const double num2 = stack.top();
            stack.pop();
            if (t.value == "+") {
                const double num3 = num1 + num2;
                stack.push(num3);
            }
            else if (t.value == "-") {
                const double num3 = num2 - num1;
                stack.push(num3);
            }
            else if (t.value == "*") {
                const double num3 = num1 * num2;
                stack.push(num3);
            }
            else if (t.value == "/") {
                const double num3 = num2 / num1;
                stack.push(num3);
            }
            else {
                throw runtime_error("how did this get reached what the heck");
            }
        }
    }
    return stack.top();
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    // ArrayStack<double> stack;
    // cout << "Adding 2 values to the stack: 5, 6" << endl << endl;
    // stack.push(5);
    // stack.push(6);
    // cout << "Top of the stack: " << stack.top() << endl;
    // cout << "Current size: " << stack.size() << endl;
    // cout << "Is stack empty? " << stack.empty() << endl << endl;
    // cout << "Popping the stack until it is empty" << endl << endl;
    // stack.pop();
    // cout << "Top of the stack with size of " << stack.size() << ": " << stack.top() << endl;
    // stack.pop();
    // cout << "Current size: " << stack.size() << endl;
    // cout << "Is stack empty? " << stack.empty() << endl << endl;
    // cout << "Testing edge cases with empty stack" << endl << endl;
    // try {
    //     stack.pop();
    // }
    // catch (...) {
    //     cout << "pop method has successful safeguard" << endl;
    // }
    // try {
    //     cout << stack.top() << endl;
    // }
    // catch (...) {
    //     cout << "top method has successful safeguard" << endl << endl;
    // }

    return 0;
}
