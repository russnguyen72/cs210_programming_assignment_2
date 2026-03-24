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
    for (int i = 0; i < line.length(); i++) {
        if (isOperator(line.substr(i, 1)) || isdigit(line[i]) || line[i] == ')' || line[i] == '(') {
            if (line[i] == '(' && !tokens.empty()) {
                const Token* last = &tokens.back();
                if (isdigit(last->value[0])) {
                    Token mult;
                    mult.value = "*";
                    tokens.push_back(mult);
                }
            }
            Token t;
            t.value = line[i];
            tokens.push_back(t);
        }
    }
    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    if (op == "(" || op == ")") return 3;
    if (isOperator(op)) return (op == "*" || op == "/") ? 2 : 1;
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    int numCount = 0;
    int opCount = 0;

    for (const Token& t : tokens) {
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
    // TODO
    return false;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    return 0.0;
}

// Main

int main() {
    // string line;
    // getline(cin, line);
    //
    // vector<Token> tokens = tokenize(line);
    //
    // if (isValidPostfix(tokens)) {
    //     cout << "FORMAT: POSTFIX\n";
    //     cout << "RESULT: " << evalPostfix(tokens) << "\n";
    // }
    // else if (isValidInfix(tokens)) {
    //     vector<Token> postfix = infixToPostfix(tokens);
    //     cout << "FORMAT: INFIX\n";
    //     cout << "POSTFIX: ";
    //     for (const auto& t : postfix) {
    //         cout << t.value << " ";
    //     }
    //     cout << "\n";
    //     cout << "RESULT: " << evalPostfix(postfix) << "\n";
    // }
    // else {
    //     cout << "FORMAT: NEITHER\n";
    //     cout << "ERROR: invalid expression\n";
    // }

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

    const string validPostfixStr = "3 4 2 * +";
    const vector<Token> validPostfix = tokenize(validPostfixStr);

    cout << "\"3 4 2 * +\" into isValidPostfix should return true: " << isValidPostfix(validPostfix) << endl;

    const string tooManyOpsStr = "3 - 4 2 * + ";
    const string tooLittleOpsStr = "3 4 2 *";

    const vector<Token> tooManyOps = tokenize(tooManyOpsStr);
    const vector<Token> tooLittleOps = tokenize(tooLittleOpsStr);

    cout << "\"3 - 4 2 * + \" into isValidPostfix should return false: " << isValidPostfix(tooManyOps) << endl;
    cout << "\"3 4 2 *\" into isValidPostfix should return false: " << isValidPostfix(tooLittleOps) << endl;

    const vector<Token> onlyOneNumber = tokenize("1");

    cout << "\"1\" into isValidPostfix should return true: " << isValidPostfix(onlyOneNumber) << endl;

    const vector<Token> onlyOneOperator = tokenize("+");

    cout << "\"+\" into isValidPostfix should return false: " << isValidPostfix(onlyOneOperator) << endl;

    cout << endl;

    const string strWithTrash = "(5 +trendy2 )/ 4  sussy baka (3 qwerty0uiop[]\\asdfg=h-1j7)kl;'\"zxcvbnm,./98|`~";
    const vector<Token> validInfix = tokenize(strWithTrash);

    cout << "Tokens in validInfix vector: " << endl;
    for (const Token& t : validInfix) {
        cout << t.value << " ";
    }
    cout << endl;
    //
    // cout << "Precedence for the individual Token objects in validInfix vector: " << endl;
    // for (const Token& t : validInfix) {
    //     cout << precedence(t.value) << " ";
    // }

    return 0;
}
