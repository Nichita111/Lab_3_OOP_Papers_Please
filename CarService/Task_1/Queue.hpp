#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
#include <list>
#include <deque>
#include <stdexcept>
#include <iostream>
using namespace std;

// Task 1: Queue Interface

template <typename T>
class Queue {
public:
    virtual ~Queue() = default;

    // Adds an element to the back of the queue
    virtual void enqueue(const T& element) = 0;

    // Removes and returns the element from the front of the queue
    virtual T dequeue() = 0;

    // Checks if the queue is empty
    virtual bool isEmpty() const = 0;
    
    // Returns the size of the queue
    virtual size_t size() const = 0;
};


// Implementation 1: DequeQueue (using deque)

// T is a placeholder for the type inserted later in the form Queue<type>
template <typename T>
class DequeQueue : public Queue<T> {
private:
    deque<T> container;

public:
    void enqueue(const T& element) override {
        container.push_back(element);
    }

    T dequeue() override {
        if (container.empty()) {
            throw out_of_range("Queue is empty");
        }
        T front = container.front();
        container.pop_front();
        return front;
    }

    bool isEmpty() const override {
        return container.empty();
    }

    size_t size() const override {
        return container.size();
    }
};


// Implementation 2: VectorQueue (using vector)

template <typename T>
class VectorQueue : public Queue<T> {
private:
    vector<T> container;

public:
    void enqueue(const T& element) override {
        container.push_back(element);
    }

    T dequeue() override {
        if (container.empty()) {
            throw out_of_range("Queue is empty");
        }
        // Note dlia menia: front() returns the first element; begin() returns an iterator to the first element
        T front = container.front();
        container.erase(container.begin());
        return front;
    }

    bool isEmpty() const override {
        return container.empty();
    }

    size_t size() const override {
        return container.size();
    }
};


// Implementation 3: ListQueue (using list)

template <typename T>
class ListQueue : public Queue<T> {
private:
    list<T> container;

public:
    void enqueue(const T& element) override {
        container.push_back(element);
    }

    T dequeue() override {
        if (container.empty()) {
            throw out_of_range("Queue is empty");
        }
        T front = container.front();
        container.pop_front();
        return front;
    }

    bool isEmpty() const override {
        return container.empty();
    }

    size_t size() const override {
        return container.size();
    }
};

#endif // QUEUE_HPP
