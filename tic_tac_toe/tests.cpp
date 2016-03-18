#include <exception>
#include "game.h"
#include <check.h> /* WARNING - include order weirdness..include this one after others */

START_TEST(basic_wins)
{
    game instance;
    instance.set_box(1,1, game::player::O_PLAYER);
    instance.set_box(2,2, game::player::O_PLAYER);
    instance.set_box(3,3, game::player::O_PLAYER);

    ck_assert(instance.is_winning_board() == true);
}
END_TEST

int main(int argc, const char *argv[])
{
    int number_failed;
    Suite *s = suite_create("tic_tac_toe");
    TCase *tc1 = tcase_create("basic_wins ordered");
    tcase_add_test(tc1, basic_wins);
    //..

    //..
    suite_add_tcase(s, tc1);
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : -1;
}
