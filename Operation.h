#pragma once
#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>
#include <string>
using namespace std;

class Operation
{
private:
     string name;
public:
    Operation() {}
    ~Operation() {}
    string getName();
    void setName( string n);
    bool find(string key);
    virtual void display();
};
#endif
string Operation::getName()
{
    return name;
}
inline void Operation::setName(string n)
{
    name = n;
}
bool Operation::find(string key)
{
    if(name == key)
        return true;
    else
        return false;
}

void Operation::display()
{
    cout << "Operation Name : " << name;
}

