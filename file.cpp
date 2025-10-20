

#include "file.h"

#include <iostream>
#include <unordered_set>
#include <vector>




using namespace std;


File::File() : version_map(10000){ //constructor

	root = new TreeNode(0, "",nullptr);
	root->message = "Initial message";
	root->created_timestamp = time(nullptr);
	version_map.insert(0,root);
	active_version = root;
	total_versions = 1;
	last_modified = time(nullptr);
	root->snapshot_timestamp = last_modified;

}

void File::insert(const string &cont){
	if(this->active_version->snapshot_timestamp!=0){ //checking if its a snapshot
		TreeNode* newver = new TreeNode((total_versions), (active_version->content) + cont, active_version);
		version_map.insert(newver->version_id, newver);

		active_version = newver;
		total_versions++;
		last_modified = time(nullptr);
		return;
	}
	active_version->content += cont;

	last_modified = time(nullptr);
}
time_t File::getLastModified() const{
	return last_modified;
}
int File::getTotalVersions() const{
	return total_versions;
}

string File::read(){
	return active_version->content;
}
void File::update(const string cont){ //same as insert
	if(this->active_version->snapshot_timestamp!=0){
		TreeNode* newver = new TreeNode((total_versions), cont, active_version);
		version_map.insert(newver->version_id, newver);

		active_version = newver;
		total_versions++;
		last_modified = time(nullptr);
		return;
	}
	active_version->content = cont;

	last_modified = time(nullptr);
}
bool File::snapshot(string message){
	if(active_version->snapshot_timestamp!=0) {
		return false;
	}
	active_version->snapshot_timestamp = time(nullptr);
	active_version->message = message;
	return true;
}

void File::rollback(int id) {
	if (id==-1) {
		if (active_version->parent) {
			active_version = version_map.get(active_version->parent->version_id);
			return;
		}
		else {
			cout<<"No such version"<<endl;//if no parent exists
			return;
		}

	}
	active_version = version_map.get(id);
}

void File::history(){
	std::cout << "History of snapshots for file: "<<endl;


	for (int v = 0; v < total_versions; v++) {
		TreeNode* node = version_map.get(v);
		if (version_map.get(v)) {
			if (node->snapshot_timestamp != 0) {
				std::cout << "Version " << node->version_id
					 << " | Time: " << ctime(&(node->snapshot_timestamp))
					 << " | Message: " << node->message << "\n";
			}
		}
	}
}










FileSystem::FileSystem() : recent_files(10000), biggest_trees(10000), Allfiles(10000){}
void FileSystem::createFile(string name){
	File* f = new File();
	Allfiles.insert(name, f);

}


void FileSystem::updateHeaps(string name) {
    File* f = getFile(name);
    if(!f) {
	    return;
    }
    recent_files.add(f->getLastModified(), name);
    biggest_trees.add(f->getTotalVersions(), name);
}
File* FileSystem::getFile(string name) {
    File* f;
    if (Allfiles.get(name)) {
    	f = Allfiles.get(name);
    	return f;
    }
    return nullptr;
}
void FileSystem::biggestTrees(int num) {
	std::vector<std::pair<long long, std::string>> temp;//has to use vector here instead of array for dynamic size, arrays are making my life tough
	unordered_set <string> check;
	int count = 0;
	while (count < num && !biggest_trees.is_empty()) {
		std::pair<long long, std::string> k = biggest_trees.top();
		biggest_trees.remove();
		File* f = getFile(k.second);
		if (f && f->getTotalVersions() == k.first && check.find(k.second)==check.end()) {//if it's an old version then I ignore it
			std::cout << k.second << " | Versions: " << k.first << "\n";
			check.insert(k.second);
			temp.push_back(k);
			count++;

		}

	}
	for (auto &p : temp){ // Here pass by ref to not make copies
		biggest_trees.add(p.first, p.second);
	}
	if (count<num) {
		std::cout << "END OF LIST\n";
	}
}
void FileSystem::recentFiles(int num) {
	std::vector<std::pair<long long, std::string>> temp;
	int count = 0; //same logic as above
	while (count < num && !recent_files.is_empty()) {
		std::pair<long long, std::string> k = recent_files.top();
		recent_files.remove();
		File* f = getFile(k.second);
		if (f && f->getLastModified() == k.first) {
			std::cout << k.second << " | Last modified: " << ctime(&k.first);
			count++;
			temp.push_back(k);
		}

	}
	for (auto &p : temp) {
		recent_files.add(p.first, p.second);
	}
	if (count<num) {
		std::cout << "END OF LIST\n";
	}
}

