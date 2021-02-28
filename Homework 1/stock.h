/* @BEYZA
Student Name: Beyza OZAN
Student ID: 150180056
Date: 15/10/2019 */

#ifndef stock_h
#define stock_h
#include "node.h"

struct stock
{
    shoe_node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
    void ReadFromFile();
};

#endif /* stock_h */
