#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

long long fib(int n_val, std::vector<long long> & mem) 
{
    if (n_val <= 1) {
        return n_val;
    }
    if (mem[n_val] == 0) {
        mem[n_val] = fib(n_val - 1, mem) + fib(n_val - 2, mem);
    }
    return mem[n_val];
}

int main(int argc, char * argv[]) {
    std::string size_str(argv[1]);
    std::stringstream cnvt(size_str);
    long long size = 0;
    cnvt >> size;

    std::vector<long long> memory(size, 0);
    std::cout << "FIB of " << size << " is " << fib(size, memory) << std::endl;
    std::cout << "PHI of " << size << " is " << static_cast<double>(memory[size-1]) / static_cast<double>(memory[size-2]) << std::endl;
}

