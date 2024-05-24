#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;
template <typename T> 
class Queue
{
private:
    size_t front, rear, size, capacity;
    T* arr;
public:
    Queue():capacity(3), arr(new T[capacity]),front(0),
            rear(0), size(0){}
    virtual ~Queue() {clear();}
    size_t getSize();
    void print();
    T find(size_t key);
    void set(size_t index, const T& item);
    T& get(size_t index);
    size_t indexOf(const T& item);
    void clear();
    void enqueue(const T& item);
    T& dequeue();
    void insertAt(size_t index,const T& item);
    void removeAt(size_t index);
    T& operator[](size_t index) const;
    T& top() const;
    T& back() const;
    bool isFull();
    bool isEmpty();

};
#endif
template <typename T>
size_t Queue<T>::getSize()
{
    return size;
}
template <typename T>
void Queue<T>::print()
{
    for(int i=0; i<size; i++)
        cout<< arr[(i+front)%capacity]
            <<"\n------------------\n";
}
template <typename T>
T Queue<T>::find(size_t key)
{
    for(int i=0; i<size ; i++)
    {
        if(arr[i]->find(key))
            return arr[i];
    }
}
template <typename T>
bool Queue<T>::isFull()
{
    return size == capacity;
}
template <typename T>
bool Queue<T>::isEmpty()
{
    return size == 0;
}
template <typename T>
T& Queue<T>::top() const
{
    return arr[front];
}
template <typename T>
T& Queue<T>::back() const
{
    return arr[(rear == 0)?capacity-1:(rear-1) % capacity];
}
template <typename T>
T &Queue<T>::operator[](size_t index) const
{
    return arr[(index+front)%capacity];
}
template <typename T>
void Queue<T>::clear()
{
    delete[]arr;
}
template <typename T>
void Queue<T>::set(size_t index,const T& item)
{
    arr[(index+front)%capacity] = item;
}
template <typename T>
T& Queue<T>::get(size_t index)
{
    return arr[(index+front)%capacity];
}
template <typename T>
size_t Queue<T>::indexOf(const T& item)
{
    for(int i=0; i<size ; i++)
    {
        if(arr[(i+front)%capacity] == item)
            return i;
    }
    return -1;
}
template <typename T>
void Queue<T>::enqueue(const T& item)
{
    arr[rear]= item;
    rear = (rear+1) % capacity;
    size++;
}
template <typename T>
T& Queue<T>::dequeue()
{
    T value = arr[front];
    front = (front+1) % capacity;
    size--;
    return value;
}
template <typename T>
void Queue<T>::insertAt(size_t index,const T& item)
{
    if(index < size/2)
    {
        front = (front == 0)? capacity-1 : front-1;
        for(int i=0 ; i<index ; ++i)
            arr[(front+i)%capacity] = arr[(front+i+1)%capacity];
    }
    else
    {
        for (int i = size ; i > index; i--)
        {
            arr[(front+i)%capacity] = arr[(front+i-1)%capacity];
        }
        rear = (rear+1) % capacity;
    }
    arr[(front+index)%capacity] = item;
    size++;
}
template <typename T>
void Queue<T>::removeAt(size_t index)
{
    if(index < size/2)
    {
        for(int i=index ; i>0 ; --i)
            arr[(front+i)%capacity] = arr[(front+i-1)%capacity];
        front = (front+1) % capacity;
    }
    else
    {
        for (int i = index ; i < size-1 ; i++)
        {
            arr[(front+i)%capacity] = arr[(front+i+1)%capacity];
        }
        rear = (rear == 0)? capacity-1 : rear-1;
    }
    size--;
}