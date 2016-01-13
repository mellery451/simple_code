#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

unsigned long long fib(int n_val, std::vector<unsigned long long> & mem)
{
    if (n_val <= 1) {
        mem[n_val] = n_val;
    }
    else if (mem[n_val] == 0) {
        mem[n_val] = fib(n_val - 1, mem) + fib(n_val - 2, mem);
    }
    return mem[n_val];
}

int main(int argc, char * argv[]) {
    if (argc == 1) {
        std::cerr << "argument required" << std::endl;
        return -1;
    }
    std::string size_str(argv[1]);
    std::stringstream cnvt(size_str);
    unsigned long long size = 0;
    cnvt >> size;

    size_t mem_size = size + 1;
    std::vector<unsigned long long> memory(mem_size, 0);
    std::cout << "FIB of " << size << " is " << fib(size, memory) << std::endl;
    if (size > 1) {
        std::cout.precision(12);
        std::cout << "PHI of " << size << " is "
            << static_cast<double>(memory[mem_size - 1]) / static_cast<double>(memory[mem_size - 2])
            << std::endl;
    }
}


