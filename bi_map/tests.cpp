#include "bi_map.hpp"
#include <random>
#include <iostream>
#include <sstream>
#include <check.h> /* WARNING - include order weirdness..include this one after others */

std::random_device generator;

START_TEST(basic_insert)
{
    bi_map<std::string, int> my_bi_map;
    ck_assert(my_bi_map.size() == 0);
    my_bi_map.insert(std::make_pair(std::string("my_string_key"), 42));
    ck_assert(my_bi_map.size() == 1);
    my_bi_map.insert(std::make_pair(std::string("my_other_key"), 24));
    ck_assert(my_bi_map.size() == 2);
    my_bi_map.insert(std::make_pair(std::string("my_string_key"), 24));
    //still two since the last insert was no-op
    ck_assert(my_bi_map.size() == 2);
}
END_TEST

START_TEST(basic_search)
{
    bi_map<std::string, int> my_bi_map;
    my_bi_map.insert(std::make_pair(std::string("key_01"), 1));
    my_bi_map.insert(std::make_pair(std::string("key_02"), 2));
    my_bi_map.insert(std::make_pair(std::string("key_03"), 3));
    my_bi_map.insert(std::make_pair(std::string("key_04"), 4));

    ck_assert(my_bi_map.find(std::string("key_01")) != my_bi_map.end());
    ck_assert(my_bi_map.find(std::string("key_02")) != my_bi_map.end());
    ck_assert(my_bi_map.find(std::string("DOES NOT EXIST")) == my_bi_map.end());
    ck_assert(my_bi_map.find(1) != my_bi_map.end());
    ck_assert(my_bi_map.find(2) != my_bi_map.end());
    ck_assert(my_bi_map.find(333) == my_bi_map.end());
}
END_TEST

int main(int argc, const char *argv[])
{
    int number_failed;
    Suite *s = suite_create("bi_map");
    TCase *tc1 = tcase_create("insert");
    tcase_add_test(tc1, basic_insert);
    TCase *tc2 = tcase_create("stats");
    tcase_add_test(tc2, basic_search);
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
