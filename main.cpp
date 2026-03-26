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
    vector<Token> output;
    // TODO
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
                const double num3 = num1 - num2;
                stack.push(num3);
            }
            else if (t.value == "*") {
                const double num3 = num1 * num2;
                stack.push(num3);
            }
            else if (t.value == "/") {
                const double num3 = num1 / num2;
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

    const string validPostfixStr = "13 4 2 * +";
    const vector<Token> validPostfix = tokenize(validPostfixStr);

    cout << "\"13 4 2 * +\" into isValidPostfix should return true: " << isValidPostfix(validPostfix) << endl;
    cout << "\"13 4 2 * +\" into evalPostfix should return 21: " << evalPostfix(validPostfix) << endl;

    const string tooManyOpsStr = "3 - 4 2 * + ";
    const string tooLittleOpsStr = "3 4 2 *";

    const vector<Token> tooManyOps = tokenize(tooManyOpsStr);
    const vector<Token> tooLittleOps = tokenize(tooLittleOpsStr);

    cout << "\"3 - 4 2 * + \" into isValidPostfix should return false: " << isValidPostfix(tooManyOps) << endl;

    try {
        cout << "\"3 - 4 2 * + \" into evalPostfix should throw an error: " << evalPostfix(tooManyOps) << endl;
    }
    catch (exception& e) {
        cout << "ERROR! " << e.what() << endl;
    }

    cout << "\"3 4 2 *\" into isValidPostfix should return false: " << isValidPostfix(tooLittleOps) << endl;

    try {
        cout << "\"3 - 4 2 * + \" into evalPostfix should throw an error: " << evalPostfix(tooLittleOps) << endl;
    }
    catch (exception& e) {
        cout << "ERROR! " << e.what() << endl;
    }

    const vector<Token> onlyOneNumber = tokenize("1");

    cout << "\"1\" into isValidPostfix should return true: " << isValidPostfix(onlyOneNumber) << endl;

    const vector<Token> onlyOneOperator = tokenize("+");

    cout << "\"+\" into isValidPostfix should return false: " << isValidPostfix(onlyOneOperator) << endl;

    cout << endl;

    const string strWithTrash = "(54 +trendy2 )/ 4  sussy baka (3 qwerty0uiop[]\\asdfg=h-1j7)kl;'\"zxcvbnm,./98|`~";
    const vector<Token> strWithTrashVector = tokenize(strWithTrash);

    cout << "strWithTrash into isValidInfix should return false: " << isValidPostfix(strWithTrashVector) << endl;

    const vector<Token> validInfix = tokenize("(30 + 42) * 10 + (15/20) - (201 + 400) * 1");

    cout << "\"(30 + 42) * 10 + (15/20) - (201 + 400) * 1\" into isValidInfix should return true: " << isValidInfix(validInfix) << endl;

    cout << "Tokens in strWithTrashVector: " << endl;
    for (const Token& t : strWithTrashVector) {
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
