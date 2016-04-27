#include "hash_table.hpp"
#include <random>
#include <iostream>
#include <sstream>
#include <check.h> /* WARNING - include order weirdness..include this one after others */

std::random_device generator;

START_TEST(basic_insert)
{
    hash_table<std::string, int> my_table;
    my_table.insert("foo", 33);
    my_table.insert("bar", 44);

    ck_assert(my_table.has_key("bar"));
    ck_assert(my_table.get("bar") == 44);
    ck_assert(my_table.has_key("foo"));
    ck_assert(my_table.get("foo") == 33);
    ck_assert(my_table.has_key("baz") == false);
    my_table.remove("bar");
    ck_assert(my_table.has_key("bar") == false);
    ck_assert(my_table.get_stats().table_size == 128);
}
END_TEST

START_TEST(check_stats)
{
    std::uniform_int_distribution<int> distribution(1,100);
    hash_table<std::string, int> my_table;
    int count = 0;
    while (count < 1500) {
        std::stringstream strm;
        strm << "key_" << count;
        my_table.insert(strm.str(), distribution(generator));
        count += 1;
    }
    std::cout << "TABLE SIZE: " << my_table.get_stats().table_size << std::endl;
    std::cout << "LOAD FACTOR: " << my_table.get_stats().load_factor << std::endl;
    std::cout << "MAX CHAIN: " << my_table.get_stats().max_chain << std::endl;

    ck_assert(my_table.get_stats().table_size > 128);
    ck_assert(my_table.get_stats().load_factor < 0.8);
}
END_TEST

int main(int argc, const char *argv[])
{
    int number_failed;
    Suite *s = suite_create("hash_table");
    TCase *tc1 = tcase_create("insert");
    tcase_add_test(tc1, basic_insert);
    TCase *tc2 = tcase_create("stats");
    tcase_add_test(tc2, check_stats);
    //..

    //..
    suite_add_tcase(s, tc1);
    suite_add_tcase(s, tc2);
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : -1;
}
