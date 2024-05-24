#pragma once
#ifndef QUEUESUBLLIST_H
#define QUEUESUBLLIST_H
#include "Node.h"
#include <iostream>
template <typename T>
class queueSubLList
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t size;
    size_t count;
public:
    queueSubLList() : head(nullptr), tail(nullptr), size(0), count(0) {}
    virtual ~queueSubLList() { clear(); }
    size_t getSize();
    size_t getCount();
    void print();
    void set(size_t index, const T &item);
    T& get(size_t index) const;
    void clear();
    size_t indexOf(const T &item);
    void resize();
    void pushBack(const T & item);
    void pushFront(const T &item);
    void pushAt(size_t index,  T &item);
    T& popFront();
    T& popBack();
    T& popAt(size_t index);
    T& topFront() const;
    T& topBack() const;
    T& operator[](size_t index) const;
};
#endif
template <typename T>
void queueSubLList<T>::resize()
{
    if (head == nullptr) // create a head
    {
        Node<T> *newNode = new Node<T>;
        newNode->next = newNode->prev = nullptr;
        head = tail = newNode;
        size++;
        return;
    }
    else if (head->sublist.isEmpty())
    {
        delete head;
        head = tail = nullptr;
        size--;
        return;
    }
    else if (tail->sublist.isEmpty()) // delete it
    {
        Node<T>* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        size--;
        return;
    }
    else if (tail->sublist.isFull()) // make a new node
    {
        Node<T> *newNode = new Node<T>();
        newNode->next = nullptr;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        size++;
        return;
    }   
}
template <typename T>
void queueSubLList<T>::pushBack(const T &item)
{
    resize();
    tail->sublist.enqueue(item);
    count++;
}
template <typename T>
void queueSubLList<T>::pushFront(const T &item)
{
    resize();
    if (head->sublist.isFull())
    {
        Node<T> *newNode = new Node<T>();
        newNode->sublist.enqueue(item);
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
        size++;
        Node<T> *curr = head;
        while (curr->next)
        {
            while (!curr->sublist.isFull() && !curr->next->sublist.isEmpty())
            {
                curr->sublist.enqueue(curr->next->sublist.top());
                curr->next->sublist.dequeue();
            }
            curr = curr->next;
        }
        resize();
    }
    else
        head->sublist.insertAt(0, item);
    count++;
}
template <typename T>
void queueSubLList<T>::pushAt(size_t index,  T &item)
{
    if (!head)
    {
        pushBack(item);
    }
    else
    {
        Node<T> *curr = head;
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < curr->sublist.getSize(); j++)
            {
                if ((k + j) == index)
                {
                    if (curr->sublist.isFull())
                    {
                        resize();
                        Node<T> *temp = tail;
                        while (temp != curr)
                        {
                            temp->sublist.insertAt(0, temp->prev->sublist.back());
                            temp->prev->sublist.removeAt(temp->prev->sublist.getSize() - 1);
                            temp = temp->prev;
                        }
                    }
                    curr->sublist.insertAt(j, item);
                    return;
                }
            }
            k += curr->sublist.getSize();
            curr = curr->next;
        }
        resize();
        if (k == index)
            tail->sublist.insertAt(tail->sublist.getSize(), item);
    }
    count++;
}
template <typename T>
T& queueSubLList<T>::popFront()
{
    T value = head->sublist.top();
    head->sublist.dequeue();
    Node<T> *curr = head;
    while (curr->next)
    {
        curr->sublist.enqueue(curr->next->sublist.top());
        curr->next->sublist.dequeue();
        curr = curr->next;
    }
    resize();
    count--;
    return value;
}
template <typename T>
T& queueSubLList<T>::popBack()
{
    T value = tail->sublist.back();
    tail->sublist.removeAt(tail->sublist.getSize() - 1);
    resize();
    count--;
    return value;
}
template <typename T>
T& queueSubLList<T>::popAt(size_t index)
{
    T value{};
    Node<T> *curr = head;
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < curr->sublist.getSize(); j++)
        {
            if ((k + j) == index)
            {
                value = curr->sublist.get(j);
                curr->sublist.removeAt(j);
                if (curr->next)
                {
                    Node<T>* temp = curr;
                    while (temp->next)
                    {
                        temp->sublist.enqueue(temp->next->sublist.top());
                        temp->next->sublist.dequeue();
                        temp = temp->next;
                    }
                }
            }
        }
        resize();
        k += curr->sublist.getSize();
        curr = curr->next;
    }
    count--;
    return value;
}
template <typename T>
T& queueSubLList<T>::topFront() const
{
    return head->sublist.top();
}
template <typename T>
T& queueSubLList<T>::topBack() const
{
    return tail->sublist.back();
}
template <typename T>
T &queueSubLList<T>::operator[](size_t index) const
{
    Node<T> *curr = head;
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < curr->sublist.getSize(); j++)
        {
            if ((k + j) == index)
                return curr[j];
        }
        k += curr->sublist.getSize();
        curr = curr->next;
    }
}
template <typename T>
void queueSubLList<T>::set(size_t index, const T &item)
{
    Node<T> *curr = head;
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < curr->sublist.getSize(); j++)
        {
            if ((k + j) == index)
                curr->sublist.set(j, item);
        }
        k += curr->sublist.getSize();
        curr = curr->next;
    }
}
template <typename T>
T& queueSubLList<T>::get(size_t index) const
{
    Node<T> *curr = head;
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < curr->sublist.getSize(); j++)
        {
            if ((k + j) == index)
            {
                return curr->sublist.get(j);
            }
        }
        k += curr->sublist.getSize();
        curr = curr->next;
    }
}
template <typename T>
size_t queueSubLList<T>::indexOf(const T &item)
{
    Node<T> *curr = head;
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < curr->sublist.getSize(); j++)
        {
            if (curr->sublist.indexOf(item) == j)
            {
                return k + j;
            }
        }
        k += curr->sublist.getSize();
        curr = curr->next;
    }
    return -1;
}

template <typename T>
size_t queueSubLList<T>::getSize()
{
    return size;
}
template <typename T>
size_t queueSubLList<T>::getCount()
{
    return count;
}
template <typename T>
void queueSubLList<T>::clear()
{
    Node<T> *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        temp->sublist.clear();
        delete temp;
    }
    tail = nullptr;
    size = 0;
}
template <typename T>
void queueSubLList<T>::print()
{
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        curr->sublist.print();
        if (i != size - 1)
            std::cout << "\n==================\n";
        curr = curr->next;
    }
}