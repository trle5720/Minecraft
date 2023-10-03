// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - mcDriver.cpp


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>

#include "Mob.h"
#include "Resources.h"
#include "Map.h"
#include "Item.h"
#include "Minecraft.h"

using namespace std;

int main () {
    int returned;
    int mapIndex = 0;

    //assert(NewWorld.getUsername().compare("Steve") == 0);
    //Minecraft NewWorld;
    do {
        string username;
        cout << "Type in a username!" << endl;
        cin >> username;
        cout << "Minecraft is generating..." << endl;
        Minecraft NewWorld = Minecraft(username);
        do {
            if (returned == 4) {
                mapIndex = 0;
            }
            NewWorld.getMap().displayMap(mapIndex);
            NewWorld.stats();
            returned = NewWorld.action_menu(mapIndex);
            if (returned != mapIndex) {
                mapIndex = returned;
            }
            if (returned == 5) {
                NewWorld.playerRankings();
                return 0;
            }
            
        }
        while (returned != 3 && returned != 4);
        //4 means respawn
        //3 means quit
        //2,1,0 are map indexes
        if (returned == 4) {
            cout << "resetting Minecraft..." << endl;
            NewWorld.getMap().resetMap();
        }

        
    }
    while (returned == 4);

    return 0;
}
