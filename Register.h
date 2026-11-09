
#ifndef _REGISTER_H
#define _REGISTER_H

#include <string>

class Register {
private:
    std::string registers[16]; 
public:
    Register(); 
    void setValue(const int& address, const std::string& value);
    void setValue(const std::string& address, const std::string& value);

    std::string getValue(const int& address);
    std::string getValue(const std::string& address);
};

#endif