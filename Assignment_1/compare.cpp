#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream programOutput("output.txt");
    std::ifstream expectedOutput("output_stress.txt");

    if (!programOutput.is_open() || !expectedOutput.is_open()) {
        std::cerr << "Failed to open one or both of the files." << std::endl;
        return 1;
    }

    std::string programLine, expectedLine;
    int lineNum = 1;
    bool match = true;

    while (std::getline(programOutput, programLine) && std::getline(expectedOutput, expectedLine)) {
        if (programLine != expectedLine) {
            std::cout << "Mismatch at line " << lineNum << ": " << programLine << " != " << expectedLine << std::endl;
            match = false;
        }
        lineNum++;
    }

    if (match) {
    } else {
        std::cout << "Output does not match expected output." << std::endl;
    }

    programOutput.close();
    expectedOutput.close();

    return 0;
}
