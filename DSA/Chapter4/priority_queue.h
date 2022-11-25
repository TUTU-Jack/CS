#pragma once
#include <iostream>

template <typename Elem>
class PriorityQueue {
public:
    PriorityQueue(int capacity):capacity(capacity),data(new Elem[capacity]),size(0) { };
    ~PriorityQueue() { delete[] data;};
public:
    bool isEmpty() const;
    bool isFull() const;
    PriorityQueue &percolateUp(int index);
    PriorityQueue &percloateDown(int index);
    PriorityQueue &insert(const Elem &data);
    PriorityQueue &remove();
private:
    Elem *data;
    int capacity;
    int size;
};