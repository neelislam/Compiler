#include <iostream>  // For input and output
#include <string>    // For using string operations
using namespace std;
//Grammar->
// Global variables
string input;  // Input string to parse
int pos = 0;   // Current position/index in the input string

// Function declarations
bool E();       // Parses E → T E'
bool Eprime();  // Parses E' → + T E' | ε
bool T();       // Parses T → F T'
bool Tprime();  // Parses T' → * F T' | ε
bool F();       // Parses F → id

// Function to return the next token (id, +, *, or end)
string nextToken() {
    // Skip any whitespace
    while (pos < input.length() && input[pos] == ' ') pos++;

    // Check if the token is 'id'
    if (input.substr(pos, 3) == "abc") {
        pos += 3;            // Move position after 'id'
        return "abc";         // Return token
    }

    // If current character is '+' or '*', return it
    if (pos < input.length() && (input[pos] == '+' || input[pos] == '*')) {
        return string(1, input[pos++]);  // Return and move position
    }

    // No valid token found
    return "";
}

// Parse function for E → T E'
bool E() {
    if (T()) {           // Try to parse T
        return Eprime(); // If successful, try to parse E'
    }
    return false;        // If T fails, return false
}

// Parse function for E' → + T E' | ε
bool Eprime() {
    int savedPos = pos;         // Save current position for backtracking
    string tok = nextToken();   // Get next token

    if (tok == "*") {           // If token is '+'
        if (T()) {              // Try to parse T
            return Eprime();    // Try to parse E' again (recursive)
        } else {
            return false;       // If T fails, whole E' fails
        }
    }

    pos = savedPos;             // Backtrack: no '+' found, so assume ε
    return true;                // Accept empty (ε)
}

// Parse function for T → F T'
bool T() {
    if (F()) {            // Try to parse F
        return Tprime();  // If successful, try to parse T'
    }
    return false;         // If F fails, return false
}

// Parse function for T' → * F T' | ε
bool Tprime() {
    int savedPos = pos;         // Save position for backtracking
    string tok = nextToken();   // Get next token

    if ( tok == "+") {           // If token is ''
        if (F()) {              // Try to parse F
            return Tprime();    // Try to parse T' again (recursive)
        } else {
            return false;       // If F fails, whole T' fails
        }
    }

    pos = savedPos;             // Backtrack: no '*' found, so assume ε
    return true;                // Accept empty (ε)
}

// Parse function for F → id
bool F() {
    string tok = nextToken();   // Get next token
    return tok == "abc";         // Return true if token is 'id', else false
}

// Main function
int main() {
    input = "abc+abc*abc";  // Set the input string to parse
    pos = 0;             // Start from the beginning
    cout << "Input: " << input << endl;

    // Parse the expression using E and check if entire input is consumed
    if (E() && pos == input.length()) {
        cout << " Valid string according to the grammar. "<< endl;
        // Success
    } else {
        cout << " Invalid string." << endl;  // Failure
    }

    return 0;  // Exit the program
}