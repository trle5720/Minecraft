// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Mob.cpp

#include <iostream>
#include "Mob.h"
using namespace std;

Mob::Mob() {
    mob_name_ = "";
}

Mob::Mob(string mob_name, int hp, int damage, Resources mob_drop) {
    mob_name_ = mob_name;
    hp_ = hp;
    damage_ = damage;
    mob_drop_ = mob_drop;
}

//NAME
void Mob::setMobName(string mob_name){
    mob_name_ = mob_name;
}
string Mob::getMobName() const{
    return mob_name_;
}

//HEALTH
void Mob::setMobHealth(int hp){
    hp_ = hp;
}
int Mob::getMobHealth() const{
    return hp_;
}

//STUFF WE DONT NEED SET FUNCTIONS FOR
int Mob::getMobDamage() const{
    return damage_;
}
int Mob::getMobXp() const{
    return xp_drop_;
}
Resources Mob::getMobDrop() const{
    return mob_drop_;
}

