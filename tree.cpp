

#include "tree.h"

TreeNode::TreeNode(int id, std::string cont, TreeNode* parent){ // constructor needs parent
	version_id = id;
	content = cont;
	message = "";
	created_timestamp = time(nullptr);
	snapshot_timestamp = 0;
	this->parent = parent;
	if (this->parent != nullptr){ //pushing children as well while creating new node
		this->parent->children.push_back(this);
	}

}
