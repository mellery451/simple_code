#include <optional>
#include <any>

int main()  {
    std::any bar;
    std::optional<double> foo;
    if (foo) {
        return 0;
    }
    return 1;
}

