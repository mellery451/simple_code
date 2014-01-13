
#include <cstdio>
#include <iostream>
#include <string>

uint32_t do_hash(const char * message) {
    uint32_t hash = 5381;
    char c;
    while ((c = *message++)) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c); /* hash * 33 + c */
    }
    return hash;
}

int main(int argc, char * argv[]) {
    if (argc == 2) {
        uint32_t val = do_hash(argv[1]);
        printf("hash as signed: %d, as unsigned: %u\n", val, val);
    }
    else {
        std::cerr << "one argument required" << std::endl;
    }
}
