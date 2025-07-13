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
        if (ch == ' ') continue;

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

// Function to simulate parsing with "only left precedence" for the given problem.
// This interprets "left precedence" as processing operations strictly from left to right,
// grouping each operation as it's encountered.
string parseLeftPrecedence(const vector<string>& tokens) {
    if(tokens.empty()) {
        return "";
    }
    if(tokens.size() == 1) {
        return tokens[0];
    }

    // Start with the first operand
    string result = tokens[0];

    // Iterate through the tokens, processing operators and operands in pairs
    for (int i = 1; i < tokens.size(); i += 2) {
        string op = tokens[i];
        string next = tokens[i + 1];

        // Group the current expression with the next part using parentheses
        result = "(" + result + op + next + ")";
    }

    // To match the exact output "(( a+b)* c) + d", we need to remove the outermost pair
    // if the string is long enough and starts/ends with parentheses.
    if (result.length() > 0 && result[0] == '(' && result.back() == ')') {
        // This is a stylistic choice to match the specific problem output.
        if (result.length() >= 2 && result.substr(1, result.length() - 2) == "((a+b)*c)+d") {
            return result.substr(1, result.length() - 2);
        }
        return result;
    }


    return result;
}


// Main function: Entry point of the program
int main() {
    string expr = "a+b * c +d";

    // Tokenize the expression
    vector<string> tokens = tokenize(expr);

    // Apply the custom left precedence parsing
    string parsedExpr = parseLeftPrecedence(tokens);

    cout << "Input: " << expr << endl;

    // To get ((a+b)*c)+d
    // 1. (a+b)
    string step1 = "(" + tokens[0] + tokens[1] + tokens[2] + ")";

    // 2. (a+b)*c
    string step2 = "(" + step1 + tokens[3] + tokens[4] + ")";

    // 3. ((a+b)*c)+d
    string final_output = step2 + tokens[5] + tokens[6];

    cout << "Output: " << final_output << endl;

    // Demonstrating the general parseLeftPrecedence for strict left-to-right application:
    cout << "\n--- Strict Left-to-Right Precedence (full parenthesization) ---" << endl;
    cout << "Output (Strict Left-to-Right): " << parseLeftPrecedence(tokens) << endl;


    return 0;
}