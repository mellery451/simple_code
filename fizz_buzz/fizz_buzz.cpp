
#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char * argv[]) {
    int counter;
    for (counter = 1; counter <= 100; ++counter) {
        std::string msg;
        if (counter % 3 == 0) { msg += "Fizz"; }
        if (counter % 5 == 0) { msg += "Buzz"; }
        if (! msg.empty() ) {
           std::cout << counter << ": " << msg << std::endl;
        }
    }

}
