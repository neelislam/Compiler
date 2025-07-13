#include <iostream>     // For input and output (cin, cout)
#include <vector>       // For using vector (dynamic array) to store tokens
#include <string>       // For handling strings
#include <sstream>      // For string stream operations

using namespace std;    // To avoid using std:: prefix everywhere

// Function to break (tokenize) an expression like "a+b*c+d" into parts: ["a", "+", "b", "*", "c", "+", "d"]
vector<string> tokenize(string expr) {
    vector<string> tokens;
    string token = "";

    // Loop through each character in the expression
    for (char ch : expr) {
        if (ch == ' ') continue; // Skip spaces

        // If the character is an operator (+, -, *, /)
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // If we have built an operand before, add it to the token list
            if (!token.empty()) {
                tokens.push_back(token);
                token = "";
            }
            // Add the operator as a separate token (convert char to string)
            tokens.push_back(string(1, ch));
        } else {
            // It's part of an operand (e.g., 'a', 'b', 'x', '1')
            token += ch;
        }
    }

    // After the loop, add the last token if it's not empty
    if (!token.empty())
        tokens.push_back(token);

    return tokens;
}

// Function to simulate parsing with "only left precedence" (strict left-to-right)
// This function was missing from your provided code, so I've added a basic version.
string parseLeftPrecedence(const vector<string>& tokens) {
    if (tokens.empty()) {
        return "";
    }
    if (tokens.size() == 1) {
        return tokens[0];
    }

    string result = tokens[0];
    for (int i = 1; i < tokens.size(); i += 2) {
        string op = tokens[i];
        string next = tokens[i + 1];
        result = "(" + result + op + next + ")";
    }
    return result;
}

// Function to parse with standard operator precedence (*,/ before +,-)
string parseWithPrecedence( vector<string>& tokens) {
    if (tokens.empty()) return "";
    if (tokens.size() == 1) return tokens[0];
    vector<string> intermediateTokens;
    for (int i = 0; i < tokens.size(); ++i) {
        if(tokens[i] == "*" || tokens[i] == "/"){
            string left_operand = intermediateTokens.back();
            intermediateTokens.pop_back();
            string op = tokens[i];
            string right_operand = tokens[++i];

            intermediateTokens.push_back("(" + left_operand + op + right_operand + ")");
        } else{
            intermediateTokens.push_back(tokens[i]);
        }
    }
    if (intermediateTokens.empty()) return "";

    string finalResult = intermediateTokens[0];
    for (int i = 1; i < intermediateTokens.size(); i += 2) {
        string op = intermediateTokens[i];
        string next = intermediateTokens[i + 1];
        finalResult = "(" + finalResult + op + next + ")";
    }
    if (finalResult.length() > 2 && finalResult[0] == '(' && finalResult.back() == ')') {
        // Check if removing the outermost parentheses maintains a valid expression.
        // This is a heuristic. For simple "a+b", it should remain "(a+b)".
        // For "a+(b*c)", it would be "(a+(b*c))", should remain.
        // For "a+(b*c)+d", it results in "((a+(b*c))+d)". We strip the outer layer.

        // Count balanced parentheses to check if the outermost pair wraps the entire valid expression.
        int balance = 0;
        bool outer_parentheses_wrap_all = true;
        for (size_t k = 1; k < finalResult.length() - 1; ++k) {
            if (finalResult[k] == '(') balance++;
            else if (finalResult[k] == ')') balance--;

            // If balance drops to 0 before the end, it means the expression
            // is composed of multiple top-level parts, so the outer parentheses
            // are essential for grouping the *entire* expression.
            if(balance == 0 && k != finalResult.length() - 2) {
                outer_parentheses_wrap_all = false;
                break;
            }
        }

        if (outer_parentheses_wrap_all) {
             return finalResult.substr(1, finalResult.length() - 2);
        }
    }

    return finalResult;
}


// Main function: Entry point of the program
int main() {
    string expr = "a+b * c +d"; // Input expression
    vector<string> tokens = tokenize(expr); // Tokenize it

    cout << "Input: " << expr << endl;

    //cout << "Output (Left Precedence): " << parseLeftPrecedence(tokens) << endl;
    cout << "Output (Standard Precedence): " << parseWithPrecedence(tokens) << endl;

    return 0;
}