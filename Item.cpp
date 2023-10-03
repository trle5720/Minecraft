// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Item.cpp

#include <iostream>
#include "Item.h"
using namespace std;

Item::Item() {

}
Item::Item (string item_name, int damage, int increaseHpBy, bool canChop,  bool canMine) {
    item_name_ = item_name;
    damage_ = damage;
    increaseHpBy_ = increaseHpBy;
    canChop_ = canChop;
    canMine_ = canMine;
} 

//NAME
void Item::setItemName(string name){
    item_name_ = name;
}

string Item::getItemName() const{
    return item_name_;
}

//DAMAGE
void Item::setDamage(int damage){
    damage_ = damage;
}
int Item::getDamage() const{
    return damage_;
}

//INCREASE HP BY
void Item::setIncreaseHpBy(int increase_amount){
    increaseHpBy_ = increase_amount;
}
int Item::getIncreaseHpBy() const{
    return increaseHpBy_;
}


bool Item::getCanChop(){
    return canChop_;
}

void Item::setCanChop(bool chop){
    canChop_ = chop;
}


bool Item::getCanMine(){
    return canMine_;
}

void Item::setCanMine(bool mine){
    canMine_ = mine;
}


