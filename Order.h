#pragma once
#ifndef ORDER_H
#define ORDER_H
#include "Operation.h"
#include <iostream>
using namespace std;
class Order :public Operation
{
private:
    string customerInfo, orderDate;
    size_t orderNum, quantity;
public:
    Order():Operation(){}
    ~Order(){}
    size_t getOrderNum();

    virtual void setCustomerInfo(string value);
    virtual void setDate(string value);
    virtual void setQuantity(size_t value);
    virtual void setNum(size_t num);
    virtual void display();
};

size_t Order::getOrderNum()
{
    return orderNum;
}
inline void Order::setCustomerInfo(string value)
{
    customerInfo = value;
}
inline void Order::setDate(string value)
{
    orderDate = value;
}
inline void Order::setQuantity(size_t value)
{
    quantity = value;
}
inline void Order::setNum(size_t num)
{
    orderNum = num;
}
void Order::display()
{
    cout << "\nOrder Number : "<<orderNum;
    cout << "\nOrdered Quantity : "<<quantity;
}
#endif
