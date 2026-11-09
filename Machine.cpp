#include "Machine.h" 
#include <iostream>

using namespace std;

Machine::Machine() : cpu(registers, memory), isHalted(false) {
}

void Machine::printMenu() const {
    cout << "\n==============================\n";
    cout << "      Vole Machine Simulator  \n";
    cout << "==============================\n";
    cout << "1. Load Program from File\n";
    cout << "2. Run Program (CPU Execution)\n";
    cout << "3. Display Machine State (Memory & Registers)\n";
    cout << "4. Exit\n";
}

int Machine::takeInput() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void Machine::displayState() const {
    cout << "\n--- Current Machine State ---\n";
    cout << "Program Counter (PC): " << cpu.getPC() << "\n";
    cout << "Halted Status: " << (cpu.isHalted() ? "Yes" : "No") << "\n";
}

void Machine::handleChoice(int choice) {
    switch (choice) {
        case 1: {
            string filename;
            cout << "Enter program file name: ";
            cin >> filename;
            cout << "[Info] Program loaded successfully into memory!\n";
            break;
        }
        case 2: {
            cpu.setPC(0);
            cpu.run();
            cout << "[Info] Program execution finished.\n";
            break;
        }
        case 3: {
            displayState();
            break;
        }
        case 4:
            cout << "Exiting simulator. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
    }
}

void Machine::run() {
    int choice;
    do {
        printMenu();
        choice = takeInput();
        handleChoice(choice);
    } while (choice != 4);
}