#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

static std::vector<std::unique_ptr<char[]>> makeArgs(std::vector<std::string> const& args)
{
    std::vector<std::unique_ptr<char[]>> retval(args.size() + 1);
    size_t index = 0;
    for (auto& s : args)
    {
        retval[index] = std::make_unique<char[]>(s.size() + 1);
        s.copy(retval[index].get(), s.size() + 1);
        ++index;
    }
    return retval;
}

std::vector<char*> makePlain(std::vector<std::unique_ptr<char[]>>& src)
{
    std::vector<char*> plain (src.size());
    std::transform(src.begin(), src.end(), plain.begin(), [](std::unique_ptr<char[]>& up)->char*{return up.get();});
    return plain;
}

//BUILD/RUN with:  clang++ --std=c++14 -fsanitize=address -fno-omit-frame-pointer -g -O2 src.cpp && ASAN_OPTIONS=detect_leaks=1 ./a.out<CR>
int main()
{
    auto foo = makeArgs({"foo", "bar", "asdklfjlasdjfljsladjfsdljf"});
    for (auto const& s: foo)
    {
        std::cout << (s.get() ? s.get() : "<LAST ELEMENT>") << "\n";
    }

    std::cout << "----- PLAIN ------" << "\n";

    auto plain = makePlain(foo);
    for (auto const c: plain)
    {
        std::cout << (c ? c : "<LAST ELEMENT>") << "\n";
    }

    return 0;
}
