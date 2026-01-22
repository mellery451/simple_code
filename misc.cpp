#include <optional>

int main()  {
    std::optional<double> foo;
    if (foo) {
        return 0;
    }
    return 1;
}

