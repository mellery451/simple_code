
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char * argv[]) {

    if (argc == 2) {
        long value = 0;
        bool neg = false;
        char * pchar = argv[1]; 

        std::stringstream u64(pchar);
        uint64_t     u64val;
        u64 >> std::hex >> u64val;
        
        std::cout << "--value as 32 bit signed: " << static_cast<int32_t>(u64val) << std::endl;
        std::cout << "--value as 32 bit unsigned: " << static_cast<uint32_t>(u64val) << std::endl;
        std::cout << "--value as 64 bit signed: " << static_cast<int64_t>(u64val) << std::endl;
        std::cout << "--value as 64 bit unsigned: " << u64val << std::endl;
    }
    else {
        std::cerr << "one argument required" << std::endl;
    }
}
