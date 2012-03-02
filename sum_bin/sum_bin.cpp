#include <sum_bin.hpp>
#include <iostream>

using namespace std;

/* 
 * trim_leading_zeros
 *
 * Removes leading zeros from a given string (passed by reference)
 * Returns the count of leading zeros removed.
 *
 */
int trim_leading_zeros(string & str)
{
    int count = 0;
    // stop if our string has become just one character
    while (str[0] == '0' && str.size() > 1) {
        str = str.substr(1, str.size()-1); 
        count++;
    }
    return count;
}

/* 
 * sum_binary_strings
 *
 * Accepts two strings containing binary digits (characters
 * '0' or '1' and produces a string representing the sum. 
 *
 * WARNING: no validation currently is currently done
 * on the input...passing strings containing characters 
 * other than '0' or '1' is ill-advised.
 * 
 * Returns the sum string.
 *
 */
string sum_binary_strings(const string & a, const string & b) 
{
    const string * top    = &a;
    const string * bottom = &b;
    if (a.size() < b.size()) {
        top = &b;
        bottom = &a;
    }
    // this holds the carry digits for each 
    // position (actually offset by one since 
    // the first least significant bit never needs
    // a carry value.
    string carry_digits(top->size(), '0');
    string result;

    for (size_t i = 0; i < top->size(); ++i) {
        // we are going to work from the 
        // end (least significant digit) of each 
        // string to the beginning
        int top_index = top->size() - i - 1;
        int bottom_index = bottom->size() - i - 1;
        unsigned char top_val = top->at(top_index);
        unsigned char bottom_val = bottom_index < 0 ? '0' :  bottom->at(bottom_index);
        unsigned char carry_val = (i == 0) ? '0' : carry_digits[i-1];
        // assuming ascii characters...
        // where '0' is dec value 48 and '1' is dec value 49
        // then 
        // three ones sums to 147
        // two ones and a zero sums to 146
        // one one and two zeros sums to 145
        // three zeros sums to 144
        unsigned char sum = top_val + bottom_val + carry_val;
        char result_char = (sum == 145 || sum == 147) ? '1' : '0';
        result = result_char + result;
        if (sum > 145) {
            carry_digits[i] = '1';
        }
    }

    if (carry_digits[top->size()-1] == '1') {
        result = '1' + result;
    }

    trim_leading_zeros(result);

    return result;
}


