#pragma once

#include<vector>

class DisjointSet {
private:
	std::vector<size_t> parent;
	std::vector<size_t> sizes;
public:
	DisjointSet(size_t size);
	size_t getParent(size_t child);
	bool areInOneSet(size_t first, size_t second);
	bool Union(size_t first, size_t second);

};