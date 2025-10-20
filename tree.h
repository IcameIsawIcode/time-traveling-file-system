
#ifndef TREE_H
#define TREE_H
#include <string>
#include <ctime>
#include <vector>


class TreeNode{
public:
    int version_id;
    std::string content;
    std::string message;
    time_t created_timestamp;
    time_t snapshot_timestamp;
    TreeNode* parent;
    std::vector<TreeNode*> children;
	TreeNode(int id, std::string cont, TreeNode* parent);

};
#endif
