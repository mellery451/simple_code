
#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char * argv[]) {

    if (argc == 2) {
        long value = 0;
        bool neg = false;
        char * pchar = argv[1];
        if (*pchar == '-') {
            neg = true;
            pchar += 1;
        }
        while (*pchar != '\0') {
            if (*pchar >= '0' && *pchar <= '9') {
                long lastval = value;
                value = value * 10 + (*pchar - '0');
                // check for overflow
                if (lastval > value) {
                    std::cerr << "looks like we overflowed..." << std::endl;
                    break;
                }
            }
            else {
                std::cerr << "invalid character: " << *pchar << std::endl;
            }
            pchar += 1;
        }

        if (neg) {
            value = value * -1;
        }

        std::cout << "value is " << value << std::endl;
    }
    else {
        std::cerr << "one argument required" << std::endl;
    }
}
