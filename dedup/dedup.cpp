
#include <cstdio>
#include <iostream>
#include <string>

static int dedup(char * str)
{
    int removed = 0;

    if (str != NULL) {
        char *piter = str;
        char *pset = str;
        char chlast = '\0';
        while (*piter != '\0') {
            if (*piter == chlast) {
                removed += 1;
            }
            else {
                *pset = *piter;
                pset += 1;
            }
            chlast = *piter;
            piter += 1;
        }
        *pset = '\0';
    }
    return removed;
}

int main(int argc, char * argv[]) 
{
    char testdata[] = "AAABBCABBBCCC";
    char * pinput = (argc >= 2) ? argv[1] : testdata; 
    std::cout << "original string is " << "[" <<  pinput << "]" << std::endl;
    int trimmed = dedup(pinput);
    std::cout << "trimmed " << trimmed << " characters, string is now [" << pinput << "]" << std::endl;
    return 0;
}
