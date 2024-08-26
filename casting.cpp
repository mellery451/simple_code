
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <limits>

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

    uint8_t  g_u8 = 127;
    int8_t   g_s8 = static_cast<int8_t>(g_u8);
    std::cout << "g_s8 is " << static_cast<int>(g_s8) << std::endl;

    uint8_t  h_u8 = 128;
    int8_t   h_s8 = static_cast<int8_t>(h_u8);
    std::cout << "h_s8 is " << static_cast<int>(h_s8) << std::endl;

    uint8_t  i_u8 = 255;
    int8_t   i_s8 = static_cast<int8_t>(i_u8);
    std::cout << "i_s8 is " << static_cast<int>(i_s8) << std::endl;

    MyB obj_b;
    //std::cout << "printing B as an A??" << *(MyA*(&obj_b)) << std::endl;
    //DANGEROUS C-style cast...
    //std::cout << "printing B as an A??: " << *(MyA*)&obj_b << std::endl;


    char c_low = std::numeric_limits<char>::min();
    char c_high = std::numeric_limits<char>::max();
    std::cout << "char min as int: " << static_cast<int>(c_low) << std::endl;
    std::cout << "char max as int: " << static_cast<int>(c_high) << std::endl;
    std::cout << "char min as unsigned char: " << static_cast<int>(static_cast<unsigned char>(static_cast<int>(c_low))) << std::endl;
    std::cout << "char max as unsigned char: " << static_cast<int>(static_cast<unsigned char>(static_cast<int>(c_high))) << std::endl;
}
