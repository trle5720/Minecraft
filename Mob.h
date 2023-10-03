// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Mob.h

#ifndef MOB_H
#define MOB_H
#include "Resources.h"
#include <iostream>


using namespace std;

class Mob {
    
private:
//mob characteristics
    string mob_name_; 
    int damage_;
    int hp_ = 10;
    Resources mob_drop_;
    int xp_drop_ = 5;
public:
//depending on mob type, mob characteristics will vary
    Mob();
    Mob(string mob_name, int hp, int damage, Resources drop);
    
    //NAMES
    void setMobName(string mob_name);
    string getMobName() const;

    //HEALTH
    void setMobHealth(int hp);
    int getMobHealth() const;

    //STUFF WE DONT NEED SET FUNCTIONS FOR
    int getMobDamage() const;
    int getMobXp() const;
    Resources getMobDrop() const;

};
#endif
