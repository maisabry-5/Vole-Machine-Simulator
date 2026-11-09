#ifndef MACHINE_H
#define MACHINE_H

#include "Memory.h"
#include "Register.h"
#include "CPU.h"
#include "Loader.h"
#include <string>

class Machine {
private:
    Memory memory;
    Register registers;
    CPU cpu;
    Loader loader;
    bool isHalted;

    void printMenu() const;
    int takeInput();
    void handleChoice(int choice);
    void displayState() const;

public:
    Machine();
    void run();
};

#endif
