#ifndef ALU_H
#define ALU_H

#include <cmath>

class ALU {
public:
    static int HexToDec(const std::string& hexStr) {
        int decValue = 0;
        for (char c : hexStr) {
            decValue = decValue * 16 + (c >= '0' && c <= '9' ? c - '0' : (c | 32) - 'a' + 10);
        }
        return decValue;
    }

    static int Hextodec(const std::string& hexStr) {
        return HexToDec(hexStr);
    }
    static double getValue(int bits) {
        int sign = bits / 128;
        int exp = (bits / 16) % 8;
        int man = bits % 16;
        double value = man / 16.0;
        value = value * std::pow(2, exp - 4);
        if (sign == 1)
            value = -value;
        return value;
    }

    static int getBits(double value) {
        int best = 0;
        double diff = 1000;
        for (int i = 0; i < 256; i++) {
            double d = getValue(i) - value;
            if (d < 0)
                d = -d;
            if (d < diff) {
                diff = d;
                best = i;
            }
        }
        return best;
    }
};

#endif