#include <tree_thing.h>
#include <iostream>

int main(int argc, const char * argv[]) 
{
    std::shared_ptr<TreeNode> root;

    if (argc >= 2) {
        std::ifstream datafile(argv[1]);
        root = read_tree(datafile);
    }
    else {
        root = read_tree(std::cin);
    }

    print_tree_breadth(root, std::cout);

    return 0;
}
