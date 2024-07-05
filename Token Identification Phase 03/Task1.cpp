#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

string getOperatorType(char ch) {
    const char operators[] = {'+', '-', '*', '/', '=', '%'};
    for (char op : operators) {
        if (ch == op) {
            switch (op) {
                case '+':
                    return "Addition";
                case '-':
                    return "Subtraction";
                case '*':
                    return "Multiplication";
                case '/':
                    return "Division";
                case '=':
                    return "Assignment";
                case '%':
                    return "Modulus";
            }
        }
    }
    return "false";
}



string extractFunctionName(string& line) {
    int openingParenthesisPos = line.find('(');
    bool foundClosingParenthesis = false;
    bool foundOpeningCurlyBrace = false;

    for (char ch : line) {
        if (ch == ')') {
            foundClosingParenthesis = true;
        } else if (ch == '{') {
            foundOpeningCurlyBrace = true;
        }
    }


    if (openingParenthesisPos != string::npos && foundClosingParenthesis && foundOpeningCurlyBrace) {
        int i = openingParenthesisPos;

        while (i > 0 && std::isalnum(line[i - 1])) {
            --i;
        }

        return line.substr(i, openingParenthesisPos - i);
    }

    return "";
}





int main(){
    ifstream inputFile("Program.cpp");
    string line;
    unordered_set<string> operatorTypes;
    int functionCount = 0;

    while(getline(inputFile, line)){

    string functionName = extractFunctionName(line);


    if (!functionName.empty() && functionName != "main") {
        cout << "User defined function Name: " << functionName << "\n";
        cout << "\n";
        functionCount++;
    }
        for (char ch : line) {
            string type = getOperatorType(ch);
            if (type != "false") {
                operatorTypes.insert(type);
            }
        }
    }

    inputFile.close();

    string functionName = extractFunctionName(line);



    if (!functionName.empty()) {
        std::cout << "Function Name: " << functionName << std::endl;
    }

    cout<<"Total number of the user defined function: "<<functionCount<<endl;

    cout << "Operator Types:" << endl;
    int count = 1;
    for (const auto &type : operatorTypes) {
        cout << "Operator-" << count << ": " << type << endl;
        count++;
    }

    std::cout << "Total number of operators: " << operatorTypes.size();
}
