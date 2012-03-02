#include <sum_bin.hpp>
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * test helper = creates a binary string representation 
 * for a given unsigned int
 *
 */
string _to_bin_string(const unsigned int & value)
{
    unsigned int _tmp_value = value;
    string result;
    const int shift_by = 8 * sizeof( unsigned int ) - 1;
    const unsigned mask = 1 << shift_by;
    for ( int i = 1; i <= shift_by + 1; i++ ) {
        result += ( _tmp_value & mask ? '1' : '0' );
        _tmp_value <<= 1;
    }
    trim_leading_zeros(result);
    return result;
}

/* 
 * test helper - runs test comparison for given strings
 *
 */
bool _do_test(const string & a, const string & b, const string & expect)
{
    string sum = sum_binary_strings(a, b);
    cout << "sum of " << a << " and " << b << " is " << sum << "." << endl;
    bool stat = (sum == expect);
    cout << "expected " << expect << " -- " << (stat ? "PASS" : "FAIL") << "." << endl;
    return stat;
}

/* 
 * test helper - runs test comparison for given unsigned ints
 *
 */
bool _do_test(const unsigned int & a , const unsigned int & b, const unsigned int & expect)
{
    return _do_test(
        _to_bin_string(a),
        _to_bin_string(b),
        _to_bin_string(expect));
}

int main(int /*argc*/, char** /*argv*/)
{
    cout << "basic tests for sum_binary_strings..." << endl;
    int pass = 0;
    int fail = 0;

    // TESTS
    _do_test("1", "1", "10") ? pass++ : fail++;
    _do_test("0", "0", "0") ? pass++ : fail++;
    _do_test("11", "0", "11") ? pass++ : fail++;
    _do_test("10001", "0", "10001") ? pass++ : fail++;
    _do_test(1, 1, 2) ? pass++ : fail++;
    _do_test(42, 43, 85) ? pass++ : fail++;
    // TODO - more test cases

    //SUMMARIZE
    cout << "------------------------------" << endl;
    cout << pass << " PASSED, " << fail << " FAILED." << endl;
}

