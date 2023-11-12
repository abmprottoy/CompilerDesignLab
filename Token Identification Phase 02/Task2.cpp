#include <iostream>
#include <fstream>
#include <vector>

// Function to check if a character is a digit
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Function to check if a character is a dot
bool isDot(char ch) {
    return ch == '.';
}

// Function to check if a character is a valid part of an integer or real number
bool isValidNumberCharacter(char ch) {
    return isDigit(ch) || isDot(ch);
}

// Function to check if a string is a valid integer
bool isInteger(const std::string &str) {
    if (str.empty() || (str.size() == 1 && !isDigit(str[0]))) {
        return false;
    }

    for (char ch : str) {
        if (!isDigit(ch)) {
            return false;
        }
    }

    return true;
}

// Function to check if a string is a valid real number
bool isRealNumber(const std::string &str) {
    if (str.empty()) {
        return false;
    }

    bool hasDot = false;

    for (char ch : str) {
        if (isDigit(ch)) {
            // Continue in the INTEGER state
        } else if (isDot(ch) && !hasDot) {
            hasDot = true;
        } else {
            return false;
        }
    }

    // The number is valid if it has at least one digit and, at most, one dot
    return hasDot;
}

int main() {
    std::ifstream inputFile("Test2.cpp");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!\n";
        return 1;
    }

    std::vector<std::string> integers;
    std::vector<std::string> realNumbers;

    std::string line;
    std::string currentToken;

    while (std::getline(inputFile, line)) {
        for (char ch : line) {
            if (isValidNumberCharacter(ch)) {
                currentToken += ch;
            } else {
                // Check if the current token is a valid integer or real number
                if (!currentToken.empty()) {
                    if (isInteger(currentToken)) {
                        integers.push_back(currentToken);
                    } else if (isRealNumber(currentToken)) {
                        realNumbers.push_back(currentToken);
                    }
                    currentToken.clear();
                }
            }
        }

        // Check the last token on the line
        if (!currentToken.empty()) {
            if (isInteger(currentToken)) {
                integers.push_back(currentToken);
            } else if (isRealNumber(currentToken)) {
                realNumbers.push_back(currentToken);
            }
            currentToken.clear();
        }
    }

    inputFile.close();

    // Display results
    std::cout << "Integers: ";
    for (const auto &integer : integers) {
        std::cout << integer << " ";
    }
    std::cout << "\nReal Numbers: ";
    for (const auto &realNumber : realNumbers) {
        std::cout << realNumber << " ";
    }
    std::cout << "\n";

    return 0;
}
