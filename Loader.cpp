#include "Loader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>

bool isValidInstruction(string code) {
    char op = code[0];

    if (op >= '1' && op <= '3') return true;
    if (op == '4') return code[1] == '0';
    if (op >= '5' && op <= '9') return true;
    if (op == 'A') return code[2] == '0';
    if (op == 'B') return true;
    if (op == 'C') return code == "C000";
    return false;
}

bool Loader::load(string path, int start, Memory& memory) {
    if (start % 2 != 0 || start >= 255) {
        cout << "Start address must be even and less than FF\n";
        return false;
    }

    ifstream file(path);
    if (!file) {
        cout << "Cannot open file\n";
        return false;
    }

    vector<string> program;
    string line;
    int lineNo = 0;

    while (getline(file, line)) {
        lineNo++;

        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == ';') continue;

        if (line.size() < 4) {
            cout << "Line " << lineNo << ": expected 4 hex digits\n";
            return false;
        }

        string code = line.substr(0, 4);
        for (int i = 0; i < 4; i++) {
            if (!isxdigit(code[i])) {
                cout << "Line " << lineNo << ": invalid hex digit\n";
                return false;
            }
            code[i] = toupper(code[i]);
        }

        if (!isValidInstruction(code)) {
            cout << "Line " << lineNo << ": invalid instruction\n";
            return false;
        }

        program.push_back(code);
    }

    if (program.empty()) {
        cout << "Program is empty\n";
        return false;
    }
    if (start + 2 * program.size() > 256) {
        cout << "Program does not fit in memory\n";
        return false;
    }

    int address = start;
    for (int i = 0; i < program.size(); i++) {
        memory.setCell(address, program[i].substr(0, 2));
        memory.setCell(address + 1, program[i].substr(2, 2));
        address += 2;
    }
    return true;
}