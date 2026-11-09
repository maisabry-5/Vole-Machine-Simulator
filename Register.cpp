
#include "Register.h"
#include "ALU.h"
#include <stdexcept>

Register::Register() {
    for (size_t i = 0; i < 16; ++i) {
        this->registers[i] = "00"; 
    }
}

void Register::setValue(const int& address, const std::string& value) {
    if (address < 0 || address > 15) {
        throw std::out_of_range("Register address is out of range");
    }
    this->registers[address] = value;
}

void Register::setValue(const std::string& address, const std::string& value) {
    ALU* alu = new ALU();
    int dec = alu->HexToDec(address); 
    this->setValue(dec, value);
    delete alu;
}

std::string Register::getValue(const int& address) {
    if (address < 0 || address > 15) {
        throw std::out_of_range("Register address is out of range");
    }
    return this->registers[address];
}

std::string Register::getValue(const std::string& address) {
    ALU* alu = new ALU();
    int dec = alu->HexToDec(address);
    delete alu;
    return this->getValue(dec);
}