// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Animal.h

#ifndef ANIMAL_H
#define ANIMAL_H
#include "Resources.h"
#include <iostream>


using namespace std;

class Animal {
    
private:
//animal characteristics
    string animal_name_;
    int hp_ = 10;
    Resources animal_drop_;
    int xp_drop_ = 5;

public:
    Animal();
    Animal(string animal_name, int hp, Resources animal_drop);
     
    //NAME
    void setAnimalName(string animal_name);
    string getAnimalName() const;

    //HEALTH
    void setAnimalHealth(int hp);
    int getAnimalHealth() const;
    
    //STUFF WE DONT NEED SET FUNCTIONS FOR
    int getAnimalXp() const;
    Resources getAnimalDrop() const;

};
#endif
