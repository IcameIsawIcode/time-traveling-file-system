

#ifndef FILE_H
#define FILE_H
#include <string>

#include "tree.h"
#include "hashmap.h"
#include "heap.h"
using namespace std;



class File{

	TreeNode* root;
	TreeNode* active_version;
    HashMap<int, TreeNode*> version_map;
    int total_versions;
	time_t last_modified;
public:
	File();
	void insert(const string &cont);
	time_t getLastModified() const;
	int getTotalVersions() const;
	string read();
	void update(string cont);
	bool snapshot(string messages);
	void rollback(int id = -1);
	void history();
};

class FileSystem{
	HashMap<string, File*> Allfiles;
	Heap recent_files;
	Heap biggest_trees;

public:
	FileSystem();

	void createFile(string file_name);
	void updateHeaps(string name);
	File* getFile(string file_name);
	void recentFiles(int num);
	void biggestTrees(int num);


};



#endif
