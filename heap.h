#ifndef HEAP_H
#define HEAP_H
#include <utility>
#include <string>

class Heap{
	std::pair<long long,std::string>* arr;
	int size;
	int capacity;
    public:
	Heap(int size);
	~Heap();
	int get_parent(int index);
	int get_left(int index);
	int get_right(int index);
	void upheap(int index);
	void downheap(int index);
	std::pair<long long,std::string> remove();
	void add(long long key,std::string value);
	std::pair<long long,std::string> top();
	int get_size();
	bool is_empty();
};
#endif
