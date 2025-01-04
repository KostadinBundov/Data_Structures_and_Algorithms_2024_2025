#pragma once
#include "SortCriteria.h"
#include "Tab.h"

namespace Constants {
	const std::string defaultMessage = "about::blank";
}

class Browser {
private:
	struct Node {
		Tab data;
		Node* next = nullptr;
		Node* prev = nullptr;

		Node(const Tab& data);
	};

	Node* head;
	Node* tail;
	Node* current;

	void copyFrom(const Browser& other);
	void moveFrom(Browser&& other);
	void free();

	static bool sortByURLComparator(Node* first, Node* second);
	static bool sortByTimeStampComparator(Node* first, Node* second);

	void pushBack(Node*& resultBegin, Node*& resultEnd, Node* curr);
	Node* findMiddle(Node* list) const;
	Node* merge(Node* left, Node* right, bool(*pred)(Node*, Node*));
	Node* mergeSort(Node* list, bool(*pred)(Node*, Node*));

public:
	Browser();
	Browser(const Browser& other);
	Browser(Browser&& other) noexcept;

	Browser& operator=(const Browser& other);
	Browser& operator=(Browser&& other) noexcept;

	~Browser();

	void go(std::string url);

	void back();
	void forward();

	void insert(std::string url);
	void remove();

	void print() const;

	void sort(const SortCriteria& criteria);
};