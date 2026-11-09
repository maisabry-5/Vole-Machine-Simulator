#include "Memory.h"
#include "ALU.h"
#include <stdexcept>

Memory::Memory() {
    for (size_t i = 0; i < 256; ++i) {
        this->cells[i] = "00"; 
    }
}

std::string Memory::getCell(const int& address) {
    if (address < 0 || address > 255) {
        throw std::out_of_range("Memory address is out of range");
    }
    return this->cells[address];
}

std::string Memory::getCell(const std::string& address) {
    ALU* alu = new ALU();
    int dec = alu->HexToDec(address); 
    delete alu;
    return this->getCell(dec);
}

void Memory::setCell(const int& address, const std::string& value) {
    if (address < 0 || address > 255) {
        throw std::out_of_range("Memory address is out of range");
    }
    this->cells[address] = value;
}

void Memory::setCell(const std::string& address, const std::string& value) {
    ALU* alu = new ALU();
    int dec = alu->HexToDec(address);
    this->setCell(dec, value);
    delete alu;
}