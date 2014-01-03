#ifndef __TREE_THING_H__ 
#define __TREE_THING_H__ 

#include <fstream>
#include <sstream>
#include <ostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <queue>

struct TreeNode {
    TreeNode(unsigned int id, const std::string desc = "") :
        my_id(id), description(desc), left(nullptr), right(nullptr)
    {}

    unsigned int my_id;
    std::string description;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
}; 
 
enum ChildSide {
    TREE_LEFT = 0,
    TREE_RIGHT
};

typedef std::queue< std::shared_ptr<TreeNode> > TreeNodeQueue;
typedef std::unordered_map< unsigned int, std::shared_ptr<TreeNode> > TreeNodeOrphanMap;
typedef std::pair< ChildSide, std::weak_ptr<TreeNode> > ParentMapEntry;
typedef std::unordered_map< unsigned int, ParentMapEntry > TreeNodeParentMap;

struct TreeContext {
    int foo;
}; 

std::shared_ptr<TreeNode> read_tree(std::istream & input);
void print_tree_breadth(std::shared_ptr<TreeNode> root, std::ostream & output);

#endif /* end of include guard */
