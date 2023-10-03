// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Item.h

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;

class Item {

private:
    string item_name_;
    int damage_;
    int increaseHpBy_;
    //int efficiency? cuz different types of tools, diamond, wooden
    bool canChop_;
    bool canMine_;

public:
    Item ();
    Item (string item_name, int damage, int increaseHpBy, bool canChop, bool canMine);
    
    //get/setter functions for all variables
    void setItemName(string name);
    string getItemName() const;

    void setDamage(int damage);
    int getDamage() const;

    void setIncreaseHpBy(int increase_amount);
    int getIncreaseHpBy() const;

    bool getCanChop();
    void setCanChop(bool chop);

    bool getCanMine();
    void setCanMine(bool mine);

};

#endif

