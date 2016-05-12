#include "bi_map.hpp"

// hmmm...not happy about this copy-pasta here...
template <class T, class U>
void try_search(bi_map<T,U> m, T const& t) {
    std::cout << "searching for " << t << ", result is: " << (m.find(t) == m.end() ? "NOT FOUND" : "FOUND") << std::endl;
}

template <class T, class U>
void try_search(bi_map<T,U> m, U const& u) {
    std::cout << "searching for " << u << ", result is: " << (m.find(u) == m.end() ? "NOT FOUND" : "FOUND") << std::endl;
}
int main(int argc, char** argv)
{
    /*
    1.  Implement “Hello, world!”

        a. Write a main function that prints “Hello, world!”
        b. Compile and run the program

        Feel free to use any reference materials necessary.
        This site offers an API reference for C++11:
            http://en.cppreference.com/w/
    */

    std::cout << "Hello, world!" << std::endl;

    //------------------------------------------------------------------
    /*
    2.  Consider *carefully* the following declaration, which
        is intended to allow the client to store a pair<T, U>, and
        look up the pair by either T or U.  We will start with a simple
        O(N) lookup:

        a. Finish the insert member function definition below the class.
        b. Add a definition for the size member function.
        c. Default construct a bi_map<std::string, int> in main()
        d. Print the size of the bi_map constructed in main()
        e. Insert an element to the bi_map constructed in main()

        Throughout this exercise, please feel free to add any API to the
        problem which aids you in completing the task.  However please
        work with the given data structure (the data members of bi_map).
    */

    //  c. Default construct a bi_map<std::string, int> in main()
    bi_map<std::string, int> my_bi_map;

    // d. Print the size of the bi_map constructed in main()
    std::cout << "Size of default constructed bi_map: " << my_bi_map.size() << std::endl;

    // e. Insert an element to the bi_map constructed in main()
    my_bi_map.insert(std::make_pair(std::string("my_string_key"), 42));

    // verify size is sane!
    std::cout << "Size of bi_map after single insertion: " << my_bi_map.size() << std::endl;

    my_bi_map.insert(std::make_pair(std::string("my_other_key"), 24));
    std::cout << "Size of bi_map after second insertion: " << my_bi_map.size() << std::endl;

    my_bi_map.insert(std::make_pair(std::string("my_string_key"), 24));
    std::cout << "Size of bi_map after no-op insertion: " << my_bi_map.size() << std::endl;

    //------------------------------------------------------------------
    /*

    3.  Add the ability to print the contents of the bi_map to a
        std::ostream. One possible signature for the stream function is
        this non-member function:

        // Print each pair in the bi_map to the ostream
        template <class T, class U>
        std::ostream&
        operator<<(std::ostream& os, bi_map<T, U> const& m);

        The format of the output is up to you.

        Change main() to print the bi_map to std::cout.
    */
    std::cout << "---- STREAMING bi_map: ----" << std::endl;
    std::cout << my_bi_map << std::endl;

    //------------------------------------------------------------------
    /*

    4.  Add the following class member functions to bi_map, and provide
        an implementation for each.

        const_iterator find(T const& t) const;
        const_iterator find(U const& u) const;

        Return an "end iterator" when the element does not exist

        Modify main() to exercise both of these functions and print the
        result.

    */
    //------------------------------------------------------------------


    try_search(my_bi_map, std::string("my_string_key"));
    try_search(my_bi_map, std::string("my_other_key"));
    try_search(my_bi_map, std::string("some random key"));
    try_search(my_bi_map, 42);
    try_search(my_bi_map, 24);
    try_search(my_bi_map, 99);

    return 0;
}

