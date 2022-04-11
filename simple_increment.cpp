#include <iostream>
#include <string>

void update(std::string & dest, std::string & src, bool preinc) {
    auto p = &(dest[0]);
    auto d = &(src[0]);
    for (auto i = 0; i < std::min(dest.size(), src.size()) - 2; ++i)
        if (preinc)
            *(++p) = *(++d);
        else
            *(p++) = *(d++);
}

int main () {
    static constexpr size_t count {30U};

    std::string one (count, 'x');
    std::string two (count, 'B');
    auto three = one;


    update(one, two, true);
    std::cout << "WITH PREINC:\n";
    std::cout << "  " << one << "\n";

    update(three, two, false);
    std::cout << "WITH POSTINC:\n";
    std::cout << "  " << three << "\n";

    return 0;
}
