#pragma once
#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;
template <typename T>
struct stackNode
{
    T data;
    stackNode<T> *next;
    stackNode(T x): data(x){}
    ~stackNode(){}
};
template <typename T>
class Stack
{
private:
    stackNode<T> *head;
    stackNode<T> *tail;
    size_t size;

public:
    Stack() : head(nullptr), tail(nullptr), size(0) {}
    ~Stack() { clear(); }
    void clear();
    void set(size_t index, const T &new_value);
    T get(size_t index) const;
    T find(std::string key);
    void pushFront(const T &item);
    void pushBack(const T item);
    void pushAt(size_t index, const T &item);
    T popFront();
    T popBack();
    T popAt(size_t index);
    T Front();
    T Back();
    void reverse();
    size_t getSize() { return size;}
};
#endif
template <typename T>
void Stack<T>::clear()
{
    while (head != nullptr)
    {
        stackNode<T> *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}
template <typename T>
T Stack<T>::Front()
{
    return head->data;
}
template <typename T>
T Stack<T>::Back()
{
    return tail->data;
}
template <typename T>
void Stack<T>::pushBack( T item)
{
    stackNode<T> *newNode = new stackNode<T>(item);
    if (size == 0)
    {
        head = tail = newNode;
        newNode->next = nullptr;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}
template <typename T>
void Stack<T>::pushFront(const T &item)
{
    stackNode<T> *newNode = new stackNode<T>(item);
    if (size == 0)
    {
        head = tail = newNode;
        newNode->next = nullptr;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    size++;
}
template <typename T>
void Stack<T>::pushAt(size_t index, const T &item)
{
    if (index == 0)
    {
        pushFront(item);
    }
    else if (index == size)
    {
        pushBack(item);
    }
    else
    {
        stackNode<T> *newNode = new stackNode<T>(item);
        stackNode<T> *curr = head;
        for (int i = 1; i < index; i++)
        {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        size++;
    }
}
template <typename T>
T Stack<T>::popBack()
{
    T value;
    if (size == 1)
    {
        value = head->data;
        delete head;
        head = tail = nullptr;
    }
    else
    {
        stackNode<T> *curr;
        while (curr->next->next)
            curr = curr->next;
        value = curr->next->data;
        delete curr->next;
        tail = curr;
        curr->next = nullptr;
    }
    size--;
    return value;
}
template <typename T>
T Stack<T>::popFront()
{   
    T value;
    if (size == 1)
    {
        value = head->data;
        delete head;
        head = tail = nullptr;
    }
    else
    {
        value = head->data;
        stackNode<T> *temp = head;
        head = head->next;
        delete temp;
    }
    size--;
    return value;
}
template <typename T>
T Stack<T>::popAt(size_t index)
{
    if (index == 0)
        popFront();
    else if (index == size - 1)
    {
        popBack();
    }
    else
    {
        stackNode<T> *curr = head;
        for (int i = 1; i < index; i++)
            curr = curr->next;
        T value = curr->next->data;
        Node<T> *temp = curr->next;
        curr->next = temp->next;
        delete temp;
        size--;
        return value;
    }
}
template <typename T>
T Stack<T>::get(size_t index) const
{
    if (index == 0)
        return head->data;
    else if (index == size - 1)
        return tail->data;
    else
    {
        stackNode<T> *curr = head;
        for (int i = 0; i < index; ++i)
            curr = curr->next;
        return curr->data;
    }
}
template <typename T>
void Stack<T>::set(size_t index, const T &new_value)
{
    stackNode<T> *curr = head;
    for (int i = 0; i < index; ++i)
        curr = curr->next;
    curr->data = new_value;
}
template <typename T>
T Stack<T>::find(std::string key)
{
    stackNode<T> *curr = head;
    for (int i = 0; i < size; ++i)
    {
        if (curr->data.find(key))
            return curr->data;
        curr = curr->next;
    }
}
template <typename T>
void Stack<T>::reverse()
{
    if (head == nullptr)
        return;
    stackNode<T> *prev = nullptr;
    stackNode<T> *next = nullptr;
    stackNode<T> *curr = head;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    tail = head;
    head = prev;
}