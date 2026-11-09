#include "Machine.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

Machine::Machine() : cpu(registers, memory), isHalted(false) {}

void Machine::printMenu() const {
    cout << "\n=========================================\n";
    cout << "         VOLE MACHINE SIMULATOR          \n";
    cout << "=========================================\n";
    cout << "1) Load Program\n";
    cout << "2) Run Program\n";
    cout << "3) Run Current Instruction\n";
    cout << "4) Print State\n";
    cout << "5) Exit\n";
    cout << "Choice: ";
}

int Machine::takeInput() {
    int choice;
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Input\n";
        printMenu();
        cin >> choice;
    }
    return choice;
}

void Machine::displayState() const {
    cout << "\n--- REGISTERS ---\n";
    for (int i = 0; i < 16; ++i) {
        cout << "R" << hex << uppercase << i << ": "
            << const_cast <Register&>(registers).getValue(i) << "   ";
        if ((i + 1) % 4 == 0) cout << "\n";
    }
    cout << "PC: " << hex << uppercase << setfill('0') << setw(2) << cpu.getPC() << "   ";
    cout << "IR: " << cpu.getIR() << "\n";

    cout << "\n--- MEMORY ---\n";
    cout << "   ";
    for (int i = 0; i < 16; ++i) {
        cout << hex << uppercase << i << "    ";
    }
    cout << "\n";

    for (int row = 0; row < 16; ++row) {
        cout << hex << uppercase << row << "  ";
        for (int col = 0; col < 16; ++col) {
            int addr = row * 16 + col;
            cout << const_cast<Memory&>(memory).getCell(addr) << "   ";
        }
        cout << "\n";
    }
}

void Machine::handleChoice(int choice) {
    if (choice == 1) {
        string fileName, address;
        cout << "Enter the file name: ";
        cin >> fileName;
        cout << "Enter the memory address to start loading the program at (Hex): ";
        cin >> address;

        
        if (loader.loadProgram(fileName, address, memory, cpu)) {
            cout << "Program loaded successfully\n\n";
            isHalted = false;
        }
        else {
            cout << "Error loading file\n\n";
        }
    }
    else if (choice == 2) {
        if (isHalted) {
            cout << "Program already finished executing\n\n";
            return;
        }
        cpu.run();
        isHalted = true;
        displayState();
    }
    else if (choice == 3) {
        if (isHalted || cpu.isHalted()) {
            cout << "Program already finished executing\n\n";
            return;
        }
        cpu.step();
        displayState();
        if (cpu.isHalted()) {
            isHalted = true;
        }
    }
    else if (choice == 4) {
        displayState();
    }
    else if (choice == 5) {
        cout << "Exiting...\n";
        exit(0);
    }
}

void Machine::run() {
    while (true) {
        printMenu();
        int choice = takeInput();
        handleChoice(choice);
    }
}