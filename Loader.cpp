#include "Loader.h"
#include <fstream>
#include <iostream>

void Loader::loadInstructions(const std::string& filename, Memory& memory) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string instruction;
    int address = 0;
    while (file >> instruction && address < 256) {
        if (instruction.length() == 4) {
            memory.setCell(address, instruction.substr(0, 2));
            memory.setCell(address + 1, instruction.substr(2, 2));
            address += 2;
        }
    }
    file.close();
}
