//#ifndef QUEUE_HPP
//#define QUEUE_HPP
//
//#include <iostream>
//#include <queue>
//
//class c_Packet;
//
//class c_Queue {
//public:
//    // Adds an element to the back of the queue
//    void push(c_Packet* value) {
//        m_queue.push(value);
//    }
//
//    // Removes the element at the front of the queue
//    void pop() {
//        if (!m_queue.empty()) {
//            m_queue.pop();
//        }
//    }
//
//    // Prints the contents of the queue
//    void PrintQueue() {
//        std::queue<c_Packet*> temp_queue = m_queue;
//        std::cout << "c_Queue Contents: ";
//
//        while (!temp_queue.empty()) {
////         TODO   std::cout << temp_queue.front() << " ";
//            temp_queue.pop();
//        }
//
//        std::cout << std::endl;
//    }
//
//    // Returns the number of elements in the queue
//    int size() {
//        return m_queue.size();
//    }
//
//    // Returns whether the queue is empty or not
//    bool empty() {
//        return m_queue.empty();
//    }
//
//    c_Packet* top() {
//        return m_queue.front();
//    }
//private:
//    std::queue<c_Packet*> m_queue;
//};
//
//#endif  // QUEUE_HPP
//
////#include <iostream>
////#include <Packet.hpp>
////using namespace std;
////
////template <class T>
////class c_Queue {
////private:
////    T* arr;
////    int frontIdx;
////    int rearIdx;
////    int capacity;
////public:
////    c_Queue(int size = 100) {
////        arr = new T[size];
////        capacity = size;
////        frontIdx = -1;
////        rearIdx = -1;
////    }
////
////    ~c_Queue() {
////        delete[] arr;
////    }
////
////    bool isEmpty() {
////        return (frontIdx == -1 && rearIdx == -1);
////    }
////
////    bool isFull() {
////        return ((rearIdx + 1) % capacity == frontIdx);
////    }
////
////    void enqueue(T data) {
////        if (isFull()) {
////            cout << "c_Queue is full\n";
////            return;
////        }
////        if (isEmpty()) {
////            frontIdx = rearIdx = 0;
////        }
////        else {
////            rearIdx = (rearIdx + 1) % capacity;
////        }
////        arr[rearIdx] = data;
////    }
////
////    void dequeue() {
////        if (isEmpty()) {
////            cout << "c_Queue is empty\n";
////            return;
////        }
////        else if (frontIdx == rearIdx) {
////            frontIdx = rearIdx = -1;
////        }
////        else {
////            frontIdx = (frontIdx + 1) % capacity;
////        }
////    }
////
////    T front() {
////        if (isEmpty()) {
////            cout << "c_Queue is empty\n";
////            exit(1);
////        }
////        return arr[frontIdx];
////    }
////
////    T rear() {
////        if (isEmpty()) {
////            cout << "c_Queue is empty\n";
////            exit(1);
////        }
////        return arr[rearIdx];
////    }
////};
