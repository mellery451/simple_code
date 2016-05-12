
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>

class my_a;

class my_b {
public:
    my_b();
    my_a* get_my_a() const;
private:
    class my_a* m_a_ptr;
};

int main(int argc, char * argv[]) {
    my_b  foo;
    class my_a* a_ptr = foo.get_my_a();
    return 0;
}

class my_a {
public:
    my_a() : three("I AM CLASS A") {};

    friend std::ostream& operator<< (std::ostream&, const my_a&);
private:
    int one;
    double two;
    std::string three;
};

std::ostream& operator <<(std::ostream& stream, const my_a& obj_a) {
    stream << obj_a.three;
    return stream;
}

my_b::my_b() : m_a_ptr( new class my_a() )
{
}

my_a* my_b::get_my_a() const
{
    return m_a_ptr;
}
