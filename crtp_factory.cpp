
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>

template <class T>
struct MyBase {
    static std::unique_ptr<T> create(int p) { return T::create(p); }
};

struct SubT1 : public MyBase<SubT1> {
    static std::unique_ptr<SubT1> create(int p) { return std::make_unique<SubT1>(p); }
    SubT1(int p = 0) : val{p} {};
    friend std::ostream& operator<<(std::ostream& os, const SubT1& t);
private:
    int val;
};

std::ostream& operator<<(std::ostream& os, const SubT1& t) { os << "ST1: " << t.val; return os; }

struct SubT2 : public MyBase<SubT2> {
    static std::unique_ptr<SubT2> create(int p) { return std::make_unique<SubT2>(p); }
    SubT2(int p = 0) : val{p} {};
    friend std::ostream& operator<<(std::ostream& os, const SubT2& t);
private:
    int val;
};

std::ostream& operator<<(std::ostream& os, const SubT2& t) { os << "ST2: " << t.val; return os; }

int main(int argc, char * argv[]) {
    auto v1 = MyBase<SubT1>::create(4);
    auto v2 = MyBase<SubT2>::create(5);
    std::cout << *(v1.get()) << "\n";
    std::cout << *(v2.get()) << "\n";
}
