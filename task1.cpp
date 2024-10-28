#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Function to check if a string is a keyword
bool isKeyword(const string &str) {
    return (str == "int" || str == "float" || str == "double" || str == "char");
}

// Function to check if a string is an identifier
bool isIdentifier(const string &str) {
    if (!isalpha(str[0]) && str[0] != '_') return false; // Identifier must start with a letter or underscore
    for (char ch : str) {
        if (!isalnum(ch) && ch != '_') return false; // Identifiers can only contain letters, digits, or underscores
    }
    return true;
}

// Function to check if a string is a literal (integer in this case)
bool isLiteral(const string &str) {
    for (char ch : str) {
        if (!isdigit(ch)) return false; // Literals are composed of digits only
    }
    return true;
}

int main() {
    string statement = "int age = 25;";
    stack<string> elements; // Stack to store elements temporarily

    // Tokenize the statement by separating keywords, identifiers, operators, etc.
    string token = "";
    for (char ch : statement) {
        if (isspace(ch)) { // Space indicates end of a token
            if (!token.empty()) { // Push completed token to the stack
                elements.push(token);
                token.clear();
            }
        } else if (ch == '=' || ch == ';') { // Special characters: '=' and ';'
            if (!token.empty()) { // Push completed token before handling the operator
                elements.push(token);
                token.clear();
            }
            string op(1, ch);
            elements.push(op); // Push operator or semicolon as a separate token
        } else {
            token += ch; // Build up token character by character
        }
    }

    // Process the stack and classify each element
    cout << "Lexical Analysis of the Statement: \"" << statement << "\"\n";
    cout << "---------------------------------------\n";
    while (!elements.empty()) {
        string elem = elements.top(); // Get top element of the stack
        elements.pop();

        if (isKeyword(elem)) {
            cout << elem << " : Keyword\n";
        } else if (isIdentifier(elem)) {
            cout << elem << " : Identifier\n";
        } else if (isLiteral(elem)) {
            cout << elem << " : Literal\n";
        } else if (elem == "=") {
            cout << elem << " : Operator\n";
        } else if (elem == ";") {
            cout << elem << " : Semicolon\n";
        } else {
            cout << elem << " : Unknown\n";
        }
    }

    return 0;
}
