#pragma once 

#include <iostream>
#include <deque>

template<class T, class Container = std::deque<T>>
class ContainerStack {
public:
	T& top() const {
		return c.back();
	}

	bool empty() const {
		return c.empty();
	}
	size_t size() const {
		return c.size();
	}

	void push(const T& el) {
		c.push_back(el);
	}
	void pop() {
		c.pop_back();
	}

private:
	Container c;
};