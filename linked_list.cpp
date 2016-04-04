#include <cstdio>
#include <iostream>
#include <string>
#include <stdint.h>
#include <memory>
#include <cstdint>

/// @brief simple LL class to implement the
/// "classic" reverse a linked list interview
/// question
///
/// @tparam _T type held at each node, must be
/// copy constructable and have a public destructor
template <class _T>
class linked_list {
public:
    linked_list() {};

    struct node {
        node() : _T() {};
        node(const _T& t) : data(t) {};

        _T data;
        std::unique_ptr<node> pnext;
    };

    void add(const _T& thing) {
        if (head) {
            node* current = head.get();
            node* last = nullptr;
            while (current) {
                last = current;
                current = current->pnext.get();
            }
            last->pnext.reset(new node(thing));
        }
        else {
            head.reset(new node(thing));
        }
    };

    void reverse() {
        node* last = nullptr;;
        if (head) {
            node* current = head.release();
            while (current) {
                node* temp = current->pnext.release();
                current->pnext.reset(last);
                last = current;
                current = temp;
            }
            head.reset(last);
        }
    }

    void print() {
        node* pcurr = head.get();
        while(pcurr) {
            std::cout << pcurr->data << std::endl;
            pcurr = pcurr->pnext.get();
        }
    }

private:
    std::unique_ptr<node> head;
};


int main(int argc, char * argv[]) {
    //LL with strings
    linked_list<std::string> my_list_str;
    my_list_str.add("one");
    my_list_str.add("two");
    my_list_str.add("three");
    my_list_str.add("four");
    my_list_str.add("five");
    std::cout << "+++++++++++++++++++++++" << std::endl;
    my_list_str.print();
    std::cout << "-----------------------" << std::endl;
    my_list_str.reverse();
    my_list_str.print();
    std::cout << "+++++++++++++++++++++++" << std::endl;

    linked_list<uint32_t> my_list_int;
    my_list_int.add(1);
    my_list_int.add(2);
    my_list_int.add(3);
    my_list_int.add(4);
    my_list_int.add(5);
    std::cout << "+++++++++++++++++++++++" << std::endl;
    my_list_int.print();
    std::cout << "-----------------------" << std::endl;
    my_list_int.reverse();
    my_list_int.print();
    std::cout << "+++++++++++++++++++++++" << std::endl;

    return 0;
}

