
#include <cstdio>
#include <iostream>
#include <string>

void rev_chars(char * pstart, char * pend)
{
    char tmp;
    while (pstart < pend) {
        tmp = *pstart;
        *pstart = *pend;
        *pend = tmp;
        pstart += 1;
        pend -= 1;
    }
}

int main(int argc, char * argv[]) {
    std::string sentence(argv[1]);
    char * buffer = new char[sentence.size() + 1];
    strncpy(buffer, sentence.c_str(), sentence.size());
    // first, rev the whole string
    rev_chars(buffer, buffer + sentence.size() - 1);

    // now rev each word
    char * pstart = buffer;
    char * pend = buffer;
    char * string_end = pstart + sentence.size();
    while (pend < string_end) {
        if (*pend == ' ') {
            rev_chars(pstart, pend-1);
            pstart = pend + 1;
        }
        pend += 1;
    }
    rev_chars(pstart, pend-1);

    std::cout << buffer << std::endl;
}
