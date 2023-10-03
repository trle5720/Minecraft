// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Minecraft.h

#ifndef MINECRAFT_H
#define MINECRAFT_H
#include "Resources.h"
#include "Mob.h"
#include "Map.h"
#include "Item.h"

#include <iostream>
#include <vector>
using namespace std;
class Minecraft {

private:
    //player stats
    string username_;
    int health_points_;
    int max_hp_;
    int xp_;
    int mobs_killed_;
    Mob ender_dragon_;
    //fat meter (how much food eaten)

    //game tangibles/assets
    vector<Mob> mobs_;
    vector<Resources> inventory_;
    vector<Item> items_;

    Map map_;
    Map end_map_;

public:
    Minecraft();    //minecraft default function creates and sets variables related to the player, 
    //creates mob types, (animals, creepers etc), generates maps
    Minecraft(string username);

    void stats();   //dispalys stats for player at any given moment, username, gear, hp, xp, resources
    int action_menu(int mapIndex); //displays actions for player in any given moment
    //possible action functions
    bool player_move();  //uses map function move() to move player on map, moving is a map function unfortunately
    int crafting(); //crafting menu
    void trading(); //trading (only if near a trading village on map)
    void YOMPNOMPNOMNOM(); //eat food, health goes up if it isn't full
    void wackwackwack(); //axe chops tree down
    void bonkbonkbonk(); //pickaxes mines stone or mineral
    void harmAnimal(); //gently harms animal and takes their resource
    void dragon();

    int playerIsDead(); //menu asks player if they want to respawn or quit, maybe show stats like mobs killed
    void playerRankings(); //sorts and ranks players when they win the game

    //getters and setters
    void setUsername(string username); 
    string getUsername() const;

    void changeHp(int changeHpBy);
    int getHp() const;

    void changeMaxHp(int changeHpBy);
    int getMaxHp() const;

    void changeXp(int changeXpBy);
    int getXp() const;

    void changeMobsKills(int changeMKby);
    int getMobsKilled() const;

    //array getters/setters
    Mob getMob(string mob_name);
    //ooo i do nott
    int getResourceAmount(string resource_name) const; 
    void addResource(string resource_name, int resource_amount); 
    void removeResource();
    bool isInInventory(string resource_name);

    Item getItem(string item_name) const;
    void addItem(Item item);

    Map getMap() const;
    void fighting();
    int randomNum(int min, int max);
    double randomPercent();


};
#endif
