#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <cmath>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"

class Register { 
    public:
    int getvalue(int index) {return 0;}
    void setvalue(int index, int value) {}
};
class Memory {
    public:
    int getcell(int index) {return 0;}
    void setcell(int index, int value) {}
};

class CPU {
private:
	int pc;
	int ir;
	int op, r, s, t, xy;
	bool halted;
	Register& regs;
	Memory& mem;

	double getValue(int bits) {
		int sign = bits / 128;
		int exp = (bits / 16) % 8;
		int man = bits % 16;
		double value = man / 16.0;
		value = value * pow(2, exp - 4);
		if (sign == 1)
			value = -value;
		return value;
	}

	int getBits(double value) {
		int best = 0;
		double diff = 1000;
		for (int i = 0; i < 256; i++) {
			double d = getValue(i) - value;
			if (d < 0) d = -d;
			if (d < diff) {
				diff = d;
				best = i;
			}
		}
		return best;
	}

	void fetch() {
		ir = (mem.getcell(pc) << 8) | mem.getcell(pc + 1);
		pc += 2;
	}

	void decode() {
		op = ir >> 12;
		r = (ir >> 8) & 15;
		s = (ir >> 4) & 15;
		t = ir & 15;
		xy = ir & 255;
	}

	bool validate() {
		if (op == 0x1 || op == 0x2 || op == 0x3) return true;
		if (op == 0x4) return r == 0;
		if (op >= 0x5 && op <= 0x9) return true;
		if (op == 0xA) return s == 0;
		if (op == 0xB) return xy <= 254;
		if (op == 0xC) return ir == 0xC000;
		return false;
	}

	void execute() {
		if (op == 0x1) {
			regs.setvalue(r, mem.getcell(xy));
		}
		else if (op == 0x2) {
			regs.setvalue(r, xy);
		}
		else if (op == 0x3) {
			mem.setcell(xy, regs.getvalue(r));
			if (xy == 0xFF)
				std::cout << std::hex << std::uppercase << regs.getvalue(r) << std::dec << std::endl;
		}
		else if (op == 0x4) {
			regs.setvalue(t, regs.getvalue(s));
		}
		else if (op == 0x5) {
			regs.setvalue(r, (regs.getvalue(s) + regs.getvalue(t)) & 255);
		}
		else if (op == 0x6) {
			double sum = getValue(regs.getvalue(s)) + getValue(regs.getvalue(t));
			regs.setvalue(r, getBits(sum));
		}
		else if (op == 0x7) {
			regs.setvalue(r, regs.getvalue(s) | regs.getvalue(t));
		}
		else if (op == 0x8) {
			regs.setvalue(r, regs.getvalue(s) & regs.getvalue(t));
		}
		else if (op == 0x9) {
			regs.setvalue(r, regs.getvalue(s) ^ regs.getvalue(t));
		}
		else if (op == 0xA) {
			int value = regs.getvalue(r);
			int steps = t % 8;
			int result = ((value >> steps) | (value << (8 - steps))) & 255;
			regs.setvalue(r, result);
		}
		else if (op == 0xB) {
			if (regs.getvalue(r) == regs.getvalue(0))
				pc = xy;
		}
		else if (op == 0xC) {
			halted = true;
		}
	}

public:
	CPU(Register& registers, Memory& memory) : regs(registers), mem(memory) {
		pc = 0;
		ir = 0;
		halted = false;
	}

	void setPC(int address) {
		pc = address;
		halted = false;
	}

	int getPC() { return pc; }
	int getIR() { return ir; }
	bool isHalted() { return halted; }

	void step() {
		if (halted) return;
		if (pc < 0 || pc > 254) {
			std::cout << "PC out of memory" << std::endl;
			halted = true;
			return;
		}
		fetch();
		decode();
		if (!validate()) {
			std::cout << "Invalid instruction" << std::endl;
			halted = true;
			return;
		}
		execute();
	}

	void run() {
		while (!halted)
			step();
	}
};

#endif
