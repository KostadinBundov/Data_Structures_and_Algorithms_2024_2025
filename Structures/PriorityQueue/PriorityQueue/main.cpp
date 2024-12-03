#include "PriorityQueue.hpp"

int main() {
    PriorityQueue<int> pq;

    pq.push(3);
    pq.push(10);
    pq.push(0);

    std::cout << pq.peek() << std::endl;

    pq.pop();
    std::cout << pq.peek() << std::endl;

    pq.push(2);
    std::cout << pq.peek() << std::endl;

    pq.pop();
    std::cout << pq.peek();

}