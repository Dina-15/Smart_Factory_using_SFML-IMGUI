#pragma once
#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_INCLUDED
#include <iostream>
#include <string>
#include "Stack.h"
#include "Operation.h"
using namespace std;
class Product : public Stack<Operation *>
{
private:
    string name;
    size_t id;
    
public:
    Product() : Stack<Operation *>() {}
    ~Product();
    void setName(string n);
    void setID(size_t i);
    size_t getID();
    string getName();
    bool find(size_t id);
};
#endif
inline Product::~Product()
{
}
inline void Product::setName(string n)
{
    name = n;
}
void Product::setID(size_t i)
{
    id = i;
}
inline size_t Product::getID()
{
    return id;
}
bool Product::find(size_t id)
{
    if (id == this->id)
        return true;
    else
        return false;
}
string Product::getName()
{
    return name;
}
