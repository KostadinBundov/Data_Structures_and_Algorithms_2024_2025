#include "DisjointSet.h"

size_t DisjointSet::getParent(size_t child) {
	if (child != parent[child]) {
		parent[child] = getParent(parent[child]);
	}
	
	return parent[child];
}

DisjointSet::DisjointSet(size_t size) {
	parent.resize(size);
	sizes.resize(size, 1);

	for (int i = 0; i < size; i++) {
		parent[i] = i;
	}
}

bool DisjointSet::areInOneSet(size_t first, size_t second) {
	return getParent(first) == getParent(second);
}

bool DisjointSet::Union(size_t first, size_t second) {
	size_t firstRoot = getParent(first);
	size_t secondRoot = getParent(second);

	if (firstRoot == secondRoot) {
		return false;
	}

	if (sizes[firstRoot] > sizes[secondRoot]) {
		parent[secondRoot] = firstRoot;
		sizes[firstRoot] += sizes[secondRoot];
	}
	else {
		parent[firstRoot] = secondRoot;
		sizes[secondRoot] += sizes[firstRoot];
	}

	return true;
}