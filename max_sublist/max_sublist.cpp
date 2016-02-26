
#include <cstdio>
#include <iostream>
#include <string>
#include <tuple>
#include <exception>
#include <algorithm>
#include <vector>

typedef std::vector<int> number_array;
typedef std::tuple<size_t, size_t, int> vector_slice;

/// @brief find_max_slice
///
///Kadane's algorithm
///
/// Kadane's algorithm consists of a scan through the array values, computing
/// at each position the maximum (positive sum) subarray ending at that
/// position. This subarray is either empty (in which case its sum is zero) or
/// consists of one more element than the maximum subarray ending at the
/// previous position.
///
/// @see https://en.wikipedia.org/wiki/Maximum_subarray_problem
/// @param nums vector of ints for which we want ot find the max slice (subarray)
///
/// @return tuple of start_index, end_index, sum for the max_slice found
vector_slice find_max_slice(number_array nums) {
    if (nums.empty()) {
        throw std::runtime_error("empty number list");
    }

    size_t start_index = 0, end_index = 0;
    int max_so_far, current_max, next_sum;

    max_so_far = current_max = nums.front();

    size_t idx = 0;
    for (auto item : nums) {
        next_sum = current_max + item;
        if (next_sum < item) {
            start_index = idx;
        }

        current_max = std::max(item,next_sum);
        if (max_so_far < current_max) {
            end_index = idx;
        }

        max_so_far = std::max(max_so_far,current_max);

        idx += 1;
    }

    return std::make_tuple(start_index, end_index, max_so_far);
}

int main(int argc, char * argv[]) {
    number_array t_1 = {-2, 5, -1, 7, -3};
    std::cout << "result for list [";
    for (auto i: t_1) {
        std::cout << i << " ";
    }
    auto res = find_max_slice(t_1);
    std::cout << "]" << " is  " << std::get<0>(res) << " <--> " << std::get<1>(res) << " : " << std::get<2>(res) << std::endl;
    //TODO: move the call and print to a function and invoke for a variety of test inputs
}
