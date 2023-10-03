// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Resources.cpp

#include "Resources.h"
#include <iostream>
#include <fstream>
using namespace std;

Resources::Resources(){
    name_ = "";
    amount_ = 0;
}

Resources::Resources(string resource_name, int amount_input){
    name_ = resource_name;
    amount_ = amount_input;
}

void Resources::increaseAmount(int amount){
    amount_+= amount;

}

void Resources::setAmount(int amount){
    amount_ = amount;
}

int Resources::getAmount()const{
    return amount_;
}

void Resources::setName(string name_input){
    name_ = name_input;
}

string Resources::getName()const{
    return name_;
}
