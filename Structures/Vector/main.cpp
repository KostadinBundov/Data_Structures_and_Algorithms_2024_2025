#include "vector.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

struct Entity {
    int x;

    Entity(int _x) : x(_x) {}
    Entity() : x() {}

    ~Entity() {
        x = -1;
    }
};

void tests_default() {
    Vector<Entity> v;

    v.push_back(Entity(1));
    assert(v.back().x == 1);
    assert(v.getSize() == 1);
    assert(v.getCapacity() == 1);

    v.emplace_back(2);
    assert(v.back().x == 2);
    assert(v.getSize() == 2);
    assert(v.getCapacity() == 2);

    for (int i = 3; i <= 10; i++)
        v.emplace_back(i);

    for (int i = 1; i <= 10; i++)
        assert(v[i - 1].x == i);

    for (int i = 1; i <= 10; i++)
        assert((v.begin() + (i - 1))->x == i);

    assert(v.getSize() == 10);
    assert(v.getCapacity() == 16);

    int cnt = 1;
    for (auto e : v)
        assert(e.x == cnt++);
}

void test_resize_reserve() {
    std::vector<Entity> v;
    Vector<Entity> v1;

    assert(v1.getSize() == v.size() && v1.getCapacity() == v.capacity());
    assert(v.data() == nullptr && v1.getData() == nullptr);

    v.reserve(10);
    v1.reserve(10);
    assert(v1.getSize() == v.size() && v1.getCapacity() == v.capacity());

    v.reserve(20);
    v1.reserve(20);
    assert(v1.getSize() == v.size() && v1.getCapacity() == v.capacity());

    v.shrink_to_fit();
    v1.shrink_to_fit();
    assert(v1.getSize() == v.size() && v1.getCapacity() == v.capacity());
}

void push_pop_tests() {
    Vector<int> v;

    for (size_t i = 0; i < 100; i++)
        v.push_back(i);

    int j = 100;
    while (!v.isEmpty()) {
        assert(v.back() == --j);
        v.pop_back();
    }
}

void erase_tests() {
    Vector<int> v;
    for (size_t i = 1; i <= 100; i++) {
        v.push_back(i);
    }

    v.erase(v.begin(), v.begin() + 49);

    int j = 50;
    for (auto x : v) {
        assert(x == j++);
    }

    assert(v.getSize() == 51);
}

void push_back_tests() {
    Vector<int> v;
    for (size_t i = 0; i < 1000; i++)
        v.push_back(i);

    assert(v.getSize() == 1000);
    for (int i = 0; i < 1000; i++)
        assert(v[i] == i);
}

void iterator_tests() {
    Vector<int> v;
    for (size_t i = 0; i < 100; i++) {
        v.push_back(i);
    }

    for (size_t i = 0; i < 100; i++) {
        assert(*(v.begin() + i) == i);
        assert(*(v.end() - i - 1) == 100 - i - 1);
    }
}

void run_all() {
    Vector<std::thread> v;
    Vector<std::function<void()>> tests;

    tests.push_back(tests_default);
    tests.push_back(test_resize_reserve);
    tests.push_back(push_back_tests);
    tests.push_back(push_pop_tests);
    tests.push_back(erase_tests);
    tests.push_back(iterator_tests);

    for (const auto& func : tests) {
        v.emplace_back(func);
    }

    for (auto& c_thread : v) {
        c_thread.join();
    }
}

int main() {
    std::cout << "Start tests...\n";
    run_all();
    std::cout << "No assertions failed!";
}
