#include <string>
#include <iostream>
#include <memory>
#include <random>
#include <exception>

static const size_t dimension = 10;
//std::default_random_engine generator;
std::random_device generator;

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

int main() {

    std::uniform_int_distribution<int> distribution(1,100);

    // create two vectors, fill with random data
    std::vector<int> vec_1(dimension);
    std::vector<int> vec_2(dimension);
    for (auto i = 0; i < dimension; ++i) {
        vec_1[i] = distribution(generator);
        vec_2[i] = distribution(generator);
    }

    //dump(vec_1, "vector 1, unsorted:");
    //dump(vec_2, "vector 2, unsorted:");

    // sort the vectors
    std::sort(vec_1.begin(), vec_1.end());
    std::sort(vec_2.begin(), vec_2.end());

    std::cout << "vector 1, sorted:" << std::endl << "\t" << vec_1 << std::endl;
    std::cout << "vector 2, sorted:" << std::endl << "\t" << vec_2 << std::endl;

    //fold together
    std::vector<std::string> merged_str(dimension * 2);
    std::vector<int> merged(dimension * 2);

    for (auto i=0,j=0,k=0; i < dimension || j < dimension; ++k) {
        if (j == dimension || vec_1[i] <= vec_2[j]) {
            merged_str[k] = std::to_string(vec_1[i]) + " (from 1)";
            merged[k] = vec_1[i];
            i++;
            continue;
        }
        if (i == dimension || vec_2[j] <= vec_1[i]) {
            merged_str[k] = std::to_string(vec_2[j]) + " (from 2)";
            merged[k] = vec_2[j];
            j++;
            continue;
        }
        throw std::runtime_error("unexpected!");
    }

    std::cout << "the merged mess:" << std::endl << "\t" << merged << std::endl;
}

