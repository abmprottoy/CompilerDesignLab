#include <iostream>

using namespace std;

int main() {
    string equation;

    cout << "Enter an equation: ";
    getline(cin, equation);

    int operatorCount = 0;

    for (char c : equation) {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '%') {
            operatorCount++;
            cout << "Operator " << operatorCount << ": " << c << endl;
        }
    }

    if (operatorCount == 0) {
        cout << "No operator found." << endl;
    }

    return 0;
}