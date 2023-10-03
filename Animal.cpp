// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Animal.cpp

#include <iostream>
#include "Resources.h"
#include "Animal.h"
#include <string>


Animal::Animal() {
    animal_name_ = "";
}
Animal::Animal(string animal_name, int hp, Resources animal_drop) {
    animal_name_ = animal_name;
    hp_ = hp;
    animal_drop_ = animal_drop;
}

//NAME
void Animal::setAnimalName(string animal_name) {
    animal_name_ = animal_name;
}
string Animal::getAnimalName() const {
    return animal_name_;
}

//HEALTH
void Animal::setAnimalHealth(int hp) {
    hp_ = hp;
}
int Animal::getAnimalHealth() const {
    return hp_;
}

//STUFF WE DONT NEED SET FUNCTIONS FOR
int Animal::getAnimalXp() const {
    return xp_drop_;
}
Resources Animal::getAnimalDrop() const {
    return animal_drop_;
}

