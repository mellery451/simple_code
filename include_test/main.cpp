#include <cstdio>
#include <iostream>

// BUILD: "g++ -I ./include main.cpp && a.out"

// this changes behavior:
//#include "b.h"
#include "new_api/a.h"

int main() {
    std::cout << "my_api returns " << my_api() << "\n";
    return 0;
}
