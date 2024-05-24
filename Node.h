#pragma once
#ifndef QUEUENODE_H
#define QUEUENODE_H
#include "Queue.h"
template<typename T>
class Node
{
    public:
    Node<T> *next ;
    Node<T> *prev ;
    Queue<T> sublist ;
    Node(): next(nullptr), prev(nullptr){}
    virtual ~Node(){}
};

#endif