#include <cstdio>
#include <iostream>
#include <string>

namespace foo {
    class TheError {
    public:
        TheError() : m_message("from FOO") {}
        std::string m_message;
    };

    void some_function()
    {
        TheError e;
        std::cout << e.m_message << std::endl;
    }

}

using namespace foo;

namespace bar {
    class TheError {
    public:
        TheError() : m_message("from BAR") {}
        std::string m_message;
    };

    void some_function()
    {
        TheError e;
        std::cout << e.m_message << std::endl;
    }
}

void some_other_function()
{
    TheError e;
    std::cout << e.m_message << std::endl;
}


int main(int argc, char * argv[]) {
    foo::some_function();
    bar::some_function();
    some_other_function();
    return 0;
}
