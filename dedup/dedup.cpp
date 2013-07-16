
#include <cstdio>
#include <iostream>
#include <string>

/*
 * Function: dedup
 *
 * Description: Given a c-string, eliminates any consequetive 
 * (repeating) characters. The string is modified in place, so 
 * must be non-const. The function returns the count of duplicates removed
 *
 * Implementation: Iterate over the string with two pointers - a "read" pointer
 * and a "write" pointer. The reader is always incremented, the writer is only 
 * incremented when we encounter a non-consequetive (unique) character.
 *
 * TODO: This implementation only works for single byte character sets. 
 * Might want to consider adding utf-8 support (MBCS).
 *
 */
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
