#include "game.h"

int main(int argc, char * argv[]) {
    while(game::ask_start()) {
        game a_game;
        a_game.play();
    }
	return 0;
}

