#include <memory>
#include <string>
#include <iostream>

using Foo = struct Foo
{
    double one;
    double three;
    std::array<int,10> items;
    std::string data;
};
using pFoo = Foo*;

void createFoo(pFoo* ppfoo) {
    *ppfoo = new Foo{1.0, 2.0, {0}, "some string data"};
    std::cout << "createFoo called!!\n";
}

void clearFoo(pFoo pfoo)
{
    delete pfoo;
    std::cout << "clearFoo called!!\n";
}

//BUILD/RUN with:  clang++ --std=c++14 -fsanitize=address -fno-omit-frame-pointer -g -O2 src.cpp && ASAN_OPTIONS=detect_leaks=1 ./a.out<CR>
int main()
{
#if 1
    // this does not leak
    using smartFoo = std::unique_ptr<Foo, void(*)(pFoo)>;
    smartFoo spFoo {nullptr, [](pFoo p){return clearFoo(p);}};

    pFoo ptr;
    createFoo(&ptr);
    spFoo.reset(ptr);
    std::cout << spFoo->data << "\n";
#else
    // this leaks a pointer because pFoo itself is never deleted
    using smartFoo = std::unique_ptr<Foo*, void(*)(pFoo*)>;
    smartFoo spFoo {new pFoo{}, [](pFoo* p){return clearFoo(*p);}};

    createFoo(spFoo.get());
    std::cout << (*spFoo)->data << "\n";
#endif

    return 0;
}
