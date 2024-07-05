#include <iostream>

using namespace std;

bool isNumeric(string input) {
    for (char c : input) {
        if (!(c >= '0' && c <= '9')) {
            return false;
        }
    }
    return true;
}

int main() {
    string input;

    cout << "Enter a string: ";
    cin >> input;

    if (isNumeric(input)) {
        cout << "Numeric constant" << endl;
    } else {
        cout << "Not numeric constant" << endl;
    }

    return 0;
}