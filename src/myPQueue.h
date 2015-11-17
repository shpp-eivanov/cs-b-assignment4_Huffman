/*
 * File: myPqueue.h
 * -------------
 * This file implements priority queue structure
 * with my implelmentaion
 */

#ifndef _myPQueue_h
#define _myPQueue_h

#include "error.h"
#include <iostream>
#include <stdlib.h>

/*
 * Class: PQueue<ValueType>
 * -----------------------
 */
template <typename ValueType>
class MyPQueue {
public:
    /*
     * Constructor: PQueue
     * Usage: PQueue<ValueType> stack;
     * ------------------------------
     * Initializes a new empty queue.
     */
    MyPQueue();

    /*
     * Destructor: ~PQueue
     * ------------------
     * Frees any heap storage associated with this queue.
     */
    virtual ~MyPQueue();
    
    /* Returns the number of elements in the priority queue. */
    int size() const;
    
    /* Returns whether or not the priority queue is empty. */
    bool isEmpty() const;
    
    /* Enqueues a new string into the priority queue. */
    void enqueue(const ValueType& value, const int priority);

    /* Returns, but does not remove, the lexicographically first string in the
     * priority queue.
     */
    ValueType peek() const;

    /* Returns and removes the lexicographically first string in the
     * priority queue.
     */
    ValueType dequeueMin();

    /*
     * Deep copying support
     * --------------------
     * This copy constructor and operator= are defined to make a deep copy,
     * making it possible to pass or return queues by value and assign
     * from one queue to another.
     */
    MyPQueue(const MyPQueue<ValueType> &src);
    MyPQueue& operator =(const MyPQueue& src);

private:
    /*
     * Implementation notes: Queue data structure
     * -------------------------------------------
     * The elements of the Queue are stored in a dynamic array of
     * the specified element type.  If the space in the array is ever
     * exhausted, the implementation doubles the array capacity.
     */
    struct Cell{
        int priority;
        ValueType data;
        Cell * link;

        bool operator==(const Cell & n1){
                 return (priority == n1.priority) && (data == n1.data) && (link == n1.link);
        }
    };

    Cell * head;
    int count;

    /* Private functions */
    void clear();
    void deepCopy(const MyPQueue<ValueType>& src);

};

/* Implementation section */

/*
 * Implementation notes
 * -------------------------------------------------------
 */
template <typename ValueType>
MyPQueue<ValueType>::MyPQueue() {
    head= NULL;
    count = 0;
}

template <typename ValueType>
MyPQueue<ValueType>::~MyPQueue() {
    clear();
}

template <typename ValueType>
MyPQueue<ValueType>::MyPQueue(const MyPQueue<ValueType>& src) {
    deepCopy(src);
}

template <typename ValueType>
int MyPQueue<ValueType>::size() const {
    return count;
}

template <typename ValueType>
void MyPQueue<ValueType>::clear(){
    while(count > 0){
        dequeueMin();
    }
}

template <typename ValueType>
bool MyPQueue<ValueType>::isEmpty() const {
    return count == 0;
}

template <typename ValueType>
MyPQueue<ValueType> & MyPQueue<ValueType>::operator =(const MyPQueue& src) {
    std::cout << "Hey!" << std::endl;

    if (this != &src) {
        clear();
        deepCopy(src);
    }

    return *this;
}

template <typename ValueType>
void MyPQueue<ValueType>::deepCopy(const MyPQueue<ValueType>& src) {
    head = NULL;
    count = 0;
    for (Cell *cp = src.head; cp != NULL; cp = cp->link) {
        enqueue(cp->data, cp->priority);
    }
}

template <typename ValueType>
void MyPQueue<ValueType>::enqueue(const ValueType& value, const int priority) {
    if(priority < 0)error("enqueue: Attempting to enqueue negative priority");
    Cell * inputCell = new Cell;
    inputCell->data = value;
    inputCell->priority = priority;
    inputCell->link = NULL;
    if(head == NULL){//first input
        head = inputCell;
    }else if(priority < head->priority){
        inputCell->link = head;
        head = inputCell;
    }else{
        Cell * cp = head;
        Cell * previousCell = head;
        while(priority >= cp->priority){
            previousCell = cp;
            cp = cp->link;
            if(cp == NULL)break;
        }
        previousCell->link = inputCell;
        inputCell->link = cp;
    }
    count++;
}

template <typename ValueType>
ValueType MyPQueue<ValueType>::dequeueMin(){
    if(isEmpty())error("dequeueMin: Attempting to dequeue from empty queue");
    Cell *cp = head;
    ValueType result = cp->data;
    head = cp->link;
    delete cp;
    count--;
    return result;
}

template <typename ValueType>
ValueType MyPQueue<ValueType>::peek() const{
    if(isEmpty())error("peek: Attempting to peek empty queue");
    return head->data;
}

#endif
