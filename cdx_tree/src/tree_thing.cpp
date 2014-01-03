#include <tree_thing.h>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cctype>

static void skip_spaces(
    std::istringstream & strm) 
{
    while (std::isspace(strm.peek())) { 
        strm.get(); 
    }
}

static void record_node(
    std::shared_ptr<TreeNode> & node, 
    TreeNodeOrphanMap & orphans, 
    TreeNodeParentMap & parents)
{
    if (parents.find(node->my_id) == parents.end()) { 
        orphans[node->my_id] = node;
    }
    else { 
        if (parents[node->my_id].first == TREE_LEFT) {
            parents[node->my_id].second.lock()->left = node;
        }
        else {
            parents[node->my_id].second.lock()->right = node;
        }
        parents.erase(node->my_id);
    }
}

void print_tree_breadth(
    std::shared_ptr<TreeNode> root, 
    std::ostream & output)
{
    if (root.get() == nullptr) {
        return;
    }
    
   TreeNodeQueue working_set;
    working_set.push(root);
    std::shared_ptr<TreeNode> current_node;

    while (! working_set.empty()) {
        current_node = working_set.front();
        working_set.pop();
        output << current_node->description << std::endl;
        if (current_node->left != nullptr) {
            working_set.push(current_node->left);
        }
        
        if (current_node->right != nullptr) {
            working_set.push(current_node->right);
        }

    }
}

std::shared_ptr<TreeNode> read_tree(
    std::istream & input) 
{
    unsigned int center, left, right;
    std::string line;
    std::string description;
    TreeNodeOrphanMap orphans;
    TreeNodeParentMap parents;

    while (std::getline(input, line)) {
        std::istringstream iss_three(line);
        try {
            if (iss_three >> center >> left >> right) { 
                skip_spaces(iss_three);
                if (! std::getline(iss_three, description) || description.size() == 0) {
                    throw std::invalid_argument("no description field");
                }
                #ifdef DEBUG
                std::cout << "READ THIS --> " <<
                    "center: [" << center << "], " <<
                    "left: [" << left << "], " <<
                    "right: [" << right << "], " <<
                    "desc: [" << description << "]" << std::endl;
                #endif

                std::shared_ptr<TreeNode> new_node(new TreeNode(center, description));

                // link up any orphan children ...
                if (orphans.find(left) != orphans.end()) {
                    new_node->left = orphans[left];
                    orphans.erase(left);
                }
                else {
                    parents[left] = ParentMapEntry(TREE_LEFT, new_node);
                }

                if (orphans.find(right) != orphans.end()) {
                    new_node->right = orphans[right];
                    orphans.erase(right);
                }
                else {
                    parents[right] = ParentMapEntry(TREE_RIGHT, new_node);
                }

                record_node(new_node, orphans, parents);
            }
            else {
                std::istringstream iss_one(line);
                if (iss_one >> center) { 
                    skip_spaces(iss_one);
                    if (! std::getline(iss_one, description) || description.size() == 0) {
                        throw std::invalid_argument("no description field");
                    }
                    #ifdef DEBUG
                    std::cout << "READ THIS --> " <<
                        "center: [" << center << "], " <<
                        "desc: [" << description << "]" << std::endl;
                    #endif
                    
                    std::shared_ptr<TreeNode> new_node(new TreeNode(center, description));

                    record_node(new_node, orphans, parents);
                }
                else {
                    throw std::invalid_argument("unknown line format");
                }
            }
        }
        catch (const std::exception & ex) {
            std::cerr << ex.what() << ": [" << line << "]" << std::endl;
            /* invalid line - continue or abort? aborting for now... */
            throw;
        }
    }

    if (orphans.size() == 1) {
        return orphans.begin()->second;
    }
    else {
        throw std::runtime_error("unable to determine unique root");
    }
}


