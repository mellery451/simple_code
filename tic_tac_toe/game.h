
#include <string>
#include <array>

/// @brief game instance represents a single use game from start through end of
/// game
class game
{
public:
    static bool ask_start();
    static constexpr int BOARD_SIZE = 3;

    enum class player {
        X_PLAYER,
        O_PLAYER
    };
    enum class box_entry {
        OPEN,
        X_MARK,
        O_MARK
    };

    game();

    void play();

private:
    void ask_move(player p);
    void print_board(const std::string& prepend = "") const;
    bool is_winning_board() const;
    bool is_full_board() const;

    static std::string player_string(player p);
    static std::string box_entry_string(box_entry e);

    typedef std::array< std::array<box_entry,BOARD_SIZE> , BOARD_SIZE> board;
    board  m_board;
};

