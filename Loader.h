#ifndef LOADER_H
#define LOADER_H

#include <string>
#include "Memory.h"
using namespace std;

class Loader {
public:
    bool load(string path, int start, Memory& memory);
};

#endif