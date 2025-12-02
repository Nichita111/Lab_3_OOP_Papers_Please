#include <iostream>
#include <cassert>
#include <string>
#include "Queue.hpp"

using namespace std;

// A simple helper to test any implementation of Queue
void testQueueImplementation(Queue<int>* q, const string& name) {
    cout << "Testing " << name << "..." << endl;

    // Test Empty
    assert(q->isEmpty() == true);
    assert(q->size() == 0);

    // Test Enqueue
    q->enqueue(10);
    q->enqueue(20);
    q->enqueue(30);

    assert(q->isEmpty() == false);
    assert(q->size() == 3);

    // Test Dequeue (FIFO order)
    int val1 = q->dequeue();
    assert(val1 == 10);
    assert(q->size() == 2);

    int val2 = q->dequeue();
    assert(val2 == 20);
    assert(q->size() == 1);

    int val3 = q->dequeue();
    assert(val3 == 30);
    assert(q->size() == 0);
    assert(q->isEmpty() == true);

    // Test Exception
    try {
        q->dequeue();
        cerr << "Failed: Should have thrown out_of_range exception" << endl;
        assert(false);
    } catch (const out_of_range& e) {
        // Expected
    }

    cout << "PASSED" << endl << endl;
}

int main() {
    cout << "Task 1: Queue Tests" << endl;

    // 1. Test DequeQueue
    DequeQueue<int> dq;
    testQueueImplementation(&dq, "DequeQueue");

    // 2. Test VectorQueue
    VectorQueue<int> vq;
    testQueueImplementation(&vq, "VectorQueue");

    // 3. Test ListQueue
    ListQueue<int> lq;
    testQueueImplementation(&lq, "ListQueue");

    cout << "All Queue tests passed!" << endl;
    return 0;
}
