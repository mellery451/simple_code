
#include <cstdio>
#include <iostream>
#include <string>
#include <stdint.h>

class MyA {
public:
    MyA() : three("I AM CLASS A") {};

    friend std::ostream& operator<< (std::ostream&, const MyA&);
private:
    int one;
    double two;
    std::string three;
};

std::ostream& operator <<(std::ostream& stream, const MyA& obj_a) {
    stream << obj_a.three;
    return stream;
}

class MyB {
public:
    MyB() : one("I AM CLASS B") {};
private:
    std::string one;
    int two;
    double three;
};

int main(int argc, char * argv[]) {

    int32_t a_32 = 0;
    int16_t a_16 = static_cast<int16_t>(a_32);
    std::cout << "a_16 is " << a_16 << std::endl;

    int32_t b_32 = 1;
    int16_t b_16 = static_cast<int16_t>(b_32);
    std::cout << "b_16 is " << b_16 << std::endl;

    int32_t c_32 = 1 << 15;
    int16_t c_16 = static_cast<int16_t>(c_32);
    std::cout << "c_16 is " << c_16 << std::endl;

    int32_t d_32 = 1 << 16;
    int16_t d_16 = static_cast<int16_t>(d_32);
    std::cout << "d_16 is " << d_16 << std::endl;

    int32_t e_32 = 1 << 30;
    int16_t e_16 = static_cast<int16_t>(e_32);
    std::cout << "e_16 is " << e_16 << std::endl;

    int32_t f_32 = 1 << 31;
    int16_t f_16 = static_cast<int16_t>(f_32);
    std::cout << "f_16 is " << f_16 << std::endl;

    MyB obj_b;
    //std::cout << "printing B as an A??" << *(MyA*(&obj_b)) << std::endl;
    //DANGEROUS C-style cast...
    std::cout << "printing B as an A??: " << *(MyA*)&obj_b << std::endl;
}
