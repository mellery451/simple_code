#include <iostream>
#include <iomanip>
#include <type_traits>
#include <cstdint>

namespace fnv1a_64
{
    typedef std::uint64_t hash_t;

    constexpr hash_t prime = 0x100000001B3ull;
    constexpr hash_t basis = 0xCBF29CE484222325ull;

    constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
    {
        return *str ? hash_compile_time(str+1, (*str ^ last_value) * prime) : last_value;
    }

    hash_t hash(char const* str)
    {
        hash_t ret{basis};

        while (*str) {
            ret ^= *str;
            ret *= prime;
            str++;
        }

        return ret;
    }
}

constexpr unsigned long long operator "" _hash(char const* p, size_t)
{
    return fnv1a_64::hash_compile_time(p);
}

void simple_switch(char const* str)
{
    std::cout << "Considering string [" << str << "].....I get:  ";
    switch(fnv1a_64::hash(str)){
    case "String_ONE"_hash:
        std::cout << "first one" << std::endl;
        break;
    case "String_TWO"_hash:
        std::cout << "second one" << std::endl;
        break;
    case "String_THREE"_hash:
        std::cout << "third one" << std::endl;
        break;
    default:
        std::cout << "I don't know that one..." << std::endl;
    }
}

int main()
{
    constexpr auto const_test = std::integral_constant<fnv1a_64::hash_t, "dummy_string"_hash>::value ;

    simple_switch("String_ONE");
    simple_switch("unknown");
    simple_switch("String_TWO");
    simple_switch("String_THREE");
    simple_switch("something else");
}
