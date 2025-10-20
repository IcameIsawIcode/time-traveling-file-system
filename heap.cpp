#include "heap.h"
#include <stdexcept> // I have included this to throw runtime errors


Heap::Heap(int s){
	arr = new std::pair<long long,std::string>[s];
	capacity = s;
	size = 0;
}
Heap::~Heap(){
	delete[] arr;
}
int Heap::get_parent(int index){
	return (index-1)/2;
}
int Heap::get_left(int index){
	return 2*index + 1;
}
int Heap::get_right(int index){
	return 2*index + 2;
}
void Heap::upheap(int index){
	int parent = get_parent(index);
	if(parent <0){
		return;
	}
	if(arr[parent].first < arr[index].first){
		swap(arr[parent], arr[index]);
		upheap(parent);
	}
}
void Heap::downheap(int index){
	int largest =index;
	int left = get_left(index);
	int right = get_right(index);
    if(left<size && arr[left].first > arr[index].first){
		largest =left;
	}
	if(right<size && arr[right].first > arr[index].first){
		largest =right;
	}
    if(largest !=index){
		swap(arr[index], arr[largest]);
		downheap(largest);
	}
}
void Heap::add(long long key,std::string value){
	if(size==capacity){
		throw std::runtime_error("Capacity full");
	}
	arr[size] = {key,value};
	upheap(size);
	size++;
}
std::pair<long long,std::string> Heap::remove(){
	if (size==0) throw std::runtime_error("No objects to remove");
	std::pair<long long,std::string> val =  arr[0];
	arr[0] = arr[--size];
	downheap(0);
	return val;
}
std::pair<long long,std::string> Heap::top(){
	if (size==0) return {0,""};
	return arr[0];
}
int Heap::get_size(){
	return size;
}
bool Heap::is_empty(){
	return size==0;
}
