
#include <cstdio>
#include <iostream>
#include <locale>
#include <vector>
#include "game.h"

struct csv_reader: std::ctype<char> {
    csv_reader(): std::ctype<char>(get_table()) {}
    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

        rc[' ']  = std::ctype_base::space;
        rc[',']  = std::ctype_base::space;
        rc['/']  = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        return &rc[0];
    }
};

game::game() {
    std::array<box_entry,BOARD_SIZE> inner;
    inner.fill(box_entry::OPEN);
    m_board.fill(inner);
}

std::string game::player_string(player p) {
    switch (p) {
    case player::X_PLAYER:
        return "X";
    case player::O_PLAYER:
        return "O";
    default:
        throw std::runtime_error("invalid player type");
    }
}

std::string game::box_entry_string(box_entry e) {
    switch (e) {
    case box_entry::OPEN:
        return "-";
    case box_entry::X_MARK:
        return "X";
    case box_entry::O_MARK:
        return "O";
    default:
        throw std::runtime_error("invalid box_entry type");
    }
}

bool game::ask_start() {
    std::cout << "Shall we play a game?" << std::endl;
    char ans = 0;
    std::cin >> ans;
    while(std::isspace(ans)) {
        std::cin >> ans;
    }
    std::string toss;
    std::getline(std::cin, toss);
    bool stat;
    if (ans != 'n' && ans != 'N' && ans != 'y' && ans != 'Y') {
        std::cout << "I don't understand..." << std::endl;
        stat = ask_start();
    }
    else {
        if (ans == 'y' || ans == 'Y') {
            stat = true;
            std::cout << "Great! let's start...." << std::endl;
        }
        else {
            stat = false;
            std::cout << "Goodbye, cruel world..." << std::endl;
        }
    }
    return stat;
}

void game::print_board(const std::string& prepend) const {
    for (auto row : m_board) {
        std::cout << prepend << "|";
        for (auto col : row) {
            std::cout << " " << box_entry_string(col) << " |";
        }
        std::cout << std::endl;
    }
}

bool game::is_full_board() const {
    bool full = true;
    for (auto row : m_board) {
        for (auto item : row) {
            full &= (item != box_entry::OPEN);
        }
    }
    return full;
}

bool game::is_winning_board() const {
    box_entry match;
    bool winner;

    // top left to bottom right diag
    if (m_board[0][0] != box_entry::OPEN) {
        match = m_board[0][0];
        winner = true;
        for (int i = 1; i < BOARD_SIZE; i++) {
            winner &= (m_board[i][i] == match);
        }
        if (winner) {
            return true;
        }
    }

    // top right to bottom left diag
    if (m_board[0][BOARD_SIZE-1] != box_entry::OPEN) {
        match = m_board[0][BOARD_SIZE-1];
        winner = true;
        for (int i = 1; i < BOARD_SIZE; i++) {
            winner &= (m_board[i][BOARD_SIZE-1-i] == match);
        }
        if (winner) {
            return true;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        // check column win
        if (m_board[0][i] != box_entry::OPEN) {
            match = m_board[0][i];
            winner = true;
            for (int j = 1 ; j < BOARD_SIZE; j++) {
                winner &= (m_board[j][i] == match);
            }
            if (winner) {
                return true;
            }
        }

        //check row win
        if (m_board[i][0] != box_entry::OPEN) {
            match = m_board[i][0];
            winner = true;
            for (int j = 1 ; j < BOARD_SIZE; j++) {
                winner &= (m_board[i][j] == match);
            }
            if (winner) {
                return true;
            }
        }
    }
    return false;
}

void game::ask_move(player p) {
    int row = 0;
    int col = 0;
    bool done = false;
    while (! done) {
        print_board();
        std::cout << "Player " << player_string(p) << ", please enter move (row,col):" << std::endl;
        std::cin.imbue(std::locale(std::locale(), new csv_reader()));
        std::cin >> row >> col;
        if (row > 0 && row <= BOARD_SIZE && col > 0 && col <= BOARD_SIZE) {
            if (m_board[row-1][col-1] == box_entry::OPEN) {
                set_box(row, col, p);
                done = true;
            }
            else {
                std::cout << "POSITION ALREADY TAKEN - please try again..." << std::endl;
            }
        }
        else {
            std::cout << "INVALID coordindates - please try again..." << std::endl;
        }
    }
}

void game::set_box(int row, int col, player p) {
    m_board[row-1][col-1] = (p == player::X_PLAYER) ? box_entry::X_MARK : box_entry::O_MARK;
}

void game::play() {
    bool done = false;
    player current_player = player::X_PLAYER;
    std::string prefix;
    while (! done) {
        ask_move(current_player);
        if (is_winning_board()) {
            std::cout << "Player " << player_string(current_player) << " WINS!" << std::endl;
            prefix = "---Winner!, Winner!--- >> ";
            done = true;
        }
        if (is_full_board()) {
            std::cout << "Game is a draw." << std::endl;
            prefix = "---Draw--- >> ";
            done = true;
        }
        current_player = (current_player == player::X_PLAYER) ? player::O_PLAYER : player::X_PLAYER;
    }
    print_board(prefix);
}

