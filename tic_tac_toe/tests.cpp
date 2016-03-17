#include <game.h>
#include <exception>
#include <check.h> /* WARNING - include order weirdness..include this one after others */

START_TEST(reverse_order)
{
    std::stringstream ssin, ssout, ssexpect;

    ssin << "25 twenty-five" << std::endl
         << "3 three" << std::endl
         << "1 one" << std::endl
         << "2 1 3 another" << std::endl
         << "15 2 25 first description" << std::endl;

    ssexpect << "first description" << std::endl
             << "another" << std::endl
             << "twenty-five" << std::endl
             << "one" << std::endl
             << "three" << std::endl;

    print_tree_breadth(
        read_tree(ssin),
        ssout);

    ck_assert_str_eq(ssout.str().c_str(), ssexpect.str().c_str());
}
END_TEST

START_TEST(bad_input_no_description)
{
    std::stringstream ssin, ssout, ssexpect;
    bool caught = false;

    ssin << "15 2 25" << std::endl;

    try{
        read_tree(ssin);
    }
    catch (const std::exception & ex) {
        ck_assert_str_eq(ex.what(), "no description field");
        caught = true;
    }

    ck_assert(caught);
}
END_TEST

int main(int argc, const char *argv[])
{
    int number_failed;
    Suite *s = suite_create("tic_tac_toe");
    TCase *tc1 = tcase_create("simple ordered");
    tcase_add_test(tc1, simple_ordered);
    TCase *tc2 = tcase_create("child first");
    tcase_add_test(tc2, reverse_order);

    suite_add_tcase(s, tc3);
    suite_add_tcase(s, tc2);
    suite_add_tcase(s, tc1);
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : -1;
}
