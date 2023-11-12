#include <iostream>
#include <fstream> // for file handling
#include <vector> // insted of array
#include <cstring> // for string functions
#include <cctype> // for isdigit function

// Function to check if a string is a C++ keyword
bool isKeyword(const std::string &word) {
    const char *keywords[] = {
    "alignas", "alignof", "auto",
    "bool", "break",
    "case", "catch", "char", "class", "const", "constexpr", "const_cast", "continue",
    "decltype", "default", "delete", "do", "double", "dynamic_cast",
    "else", "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend",
    "goto",
    "if", "inline", "int","include","iostream",
    "long",
    "mutable",
    "namespace", "new", "noexcept", "nullptr",
    "operator",
    "private", "protected", "public",
    "register", "reinterpret_cast", "return",
    "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch",
    "template", "this", "throw", "true", "try", "typedef", "typeid", "typename",
    "union", "unsigned","using",
    "virtual", "void", "volatile",
    "wchar_t", "while"};
	for (const char *keyword : keywords) {
        if (strcmp(keyword, word.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a character is a C++ operator
bool isOperator(char ch) {
    const char operators[] = {'+', '-', '*', '/', '=', '<', '>', '&', '|', '!', '%'};
    for (char op : operators) {
        if (ch == op) {
            return true;
        }
    }
    return false;
}

// Function to check if a string is a legal C++ identifier (function or variable name)
bool isLegalIdentifier(const std::string &name) {
    if (name.empty() || !isalpha(name[0]) && name[0] != '_') {
        return false; // Identifier must start with a letter or underscore
    }
    for (char ch : name) {
        if (!isalnum(ch) && ch != '_') {
            return false; // Identifier can only contain letters, digits, and underscores
        }
    }
    return true;
}

int main() {
    std::ifstream inputFile("Test1.cpp");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!\n";
        return 1;
    }

    std::vector<std::string> keywordResults;
    std::vector<char> operatorResults;
    std::vector<std::string> identifiers; // Legal function and variable names

    std::string line;
    bool withinString = false;

    while (std::getline(inputFile, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            char ch = line[i];

            // Check if the character is within a string
            if (ch == '"') {
                withinString = !withinString;
                continue;
            }

            if (!withinString && (isalpha(ch) || ch == '_')) {
                std::string word;
                while (isalnum(ch) || ch == '_') {
                    word += ch;
                    ch = line[++i];
                }
                if (isKeyword(word)) {
                    keywordResults.push_back(word);
                } else {
                    // Check if it's a legal identifier (function or variable name)
                    if (isLegalIdentifier(word)) {
                        identifiers.push_back(word);
                    }
                }
                --i; // Adjust the index as we have moved forward while reading the word
            } else if (isOperator(ch)) {
                operatorResults.push_back(ch);
            }
        }
    }

    inputFile.close();

    // Display results
    std::cout << "Keywords: ";
    for (const auto &keyword : keywordResults) {
        std::cout << keyword << " ";
    }
    std::cout << "\nOperators: ";
    for (char op : operatorResults) {
        std::cout << op << " ";
    }

    // Display identifier results
    std::cout << "\nIdentifiers: ";
    for (const auto &identifier : identifiers) {
        std::cout << identifier << " ";
    }

    return 0;
}
