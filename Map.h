// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Map.h

#ifndef MAP_H
#define MAP_H

#include <iostream>
using namespace std;

class Map {

private:

                //CHARACTERS AND MAP INDICATORS

    const string GRASSBLOCK = "🟩"; // marker for GRASSBLOCK spaces
    const string CAVEBLOCK = "⬛"; //marker for caveblock 
    const string ENDBLOCK = "🟫";   // marker for endblock
    string freeBlock_[3] = {GRASSBLOCK, CAVEBLOCK, ENDBLOCK};
    //overworld
    const string MOB = "💀";        // marker for HOSTILE mob locations
    const string VILLAGE = "🏠";       // marker for village
    const string TREE = "🌳";       // marker for tree locations
    const string ANIMAL = "🐂";        //marker for animal, PASSIVE mob
    const string STRONGHOLD = "🏰";      // marker for stronghold location
    const string CAVE = "🔳";
    //cave ore stringacters
    const string IRON = "🔲";
    const string GOLD = "🟨";
    const string DIAMOND = "💎";
    //end dimension/map
    const string DRAGON = "🐉";
    //player
    const string PLAYER = "😛";

    




                //MAP GENERATION LIMITS

    //variables that can easily change map generation, these variables are used everywhere

    static const int num_rows_ = 15; // number of rows in map
    static const int num_cols_ = 15; // number of columns in map

    //element numbers can be changed as desired, (1 for faster rng map generation)
    static const int max_mobs_ = 10;  // max non-player characters
    static const int max_villages_ = 1;
    static const int max_trees_ = 5;
    static const int max_animals_ = 15;
    static const int max_strongholds_ = 1;
    static const int max_caves_ = 1;
    //cave 
    static const int max_iron_ = 12;
    static const int max_gold_ = 9;
    static const int max_diamond_ = 3;
    //end dimension/map
    static const int max_dragons_ = 1;





                //PLAYER POSITION 

    int player_position_[2];// player position (row,col), position[0] = row, position[1] = col



                //MAP DATA

    string map_data_[3][num_rows_][num_cols_];
    //3D array, dont be intimidated by it
    //think of it like a file cabinet?
    //each file has a 2d sheet of paper, one map
    //the first file is the over world, the second is the cave map, etc
    //the 3d array stores 3 , 2d arrays (like 3 files) that in concept, would resemble these 3 lines:

    // char over_map_data_[num_rows_][num_cols_];
    // char cave_map_data_[num_rows_][num_cols_];
    // char end_map_data_[num_rows_][num_cols_];

    //index 0 is over world, 1 is cave, 2 is end map



                //2d arrays of element POSITIONS

    int mob_positions_[max_mobs_][2];     // stores the (row,col) positions of mobs present on map
    int animal_positions_[max_animals_][2];
    int village_positions_[max_villages_][2];  
    int tree_positions_[max_trees_][2];    
    int stronghold_position_[max_strongholds_][2];
    int cave_position_[max_caves_][2];
    //cave 
    int iron_positions_[max_iron_][2];
    int gold_positions_[max_gold_][2];
    int diamond_positions_[max_diamond_][2];
    //end dimension/map
    int dragon_position_[max_dragons_][2];



    //database COUNT_ of map elements
    int mob_count_ = 0;  // stores number of hostile mobs misfortunes currently on map
    int village_count_= 0; 
    int tree_count_ = 0;
    int animal_count_ = 0;
    int stronghold_count_ = 0;
    int cave_count_ = 0;
    //cave
    int iron_count_ = 0;
    int gold_count_ = 0;
    int diamond_count_ = 0;
    //end
    int dragon_count_ = 0;

public:
    Map();




    // RETURN/GETTER FUNCTIONS

    int getPlayerRow();
    int getPlayerCol();

    int getMobCount();
    int getVillageCount();
    int getTreeCount();
    int getAnimalCount();
        //cave
    int getIronCount();
    int getGoldCount();
    int getDiamondCount();

    int getNumRows();
    int getNumCols();





    //CHECK FUNCTIONS

    bool isOnMap(int row, int col);
    bool isFreeBlock(int row, int col, int mapIndex);


    bool isMobLocation(int row, int col);
    bool isVillageLocation(int row, int col);
    bool isTreeLocation (int row, int col);
    bool isAnimalLocation (int row, int col);
    bool isStrongholdLocation(int row, int col);
    bool isCaveLocation (int row, int col);
        //cave
    bool isIronLocation (int row, int col);
    bool isGoldLocation (int row, int col);
    bool isDiamondLocation (int row, int col);
            //end
    bool isDragonLocation (int row, int col);

    bool isNextToMob();
    bool isNextToVillage();
    bool isNextToTree();
    bool isNextToAnimal();
    bool isNextToStronghold();
    bool isNextToCave();
        //cave
    bool isNextToIron();
    bool isNextToGold();
    bool isNextToDiamond();
            //end
    bool isNextToDragon();




    // SETTER FUNCTIONS
    bool setPlayerData(int row, int col, int mapIndex);


    bool addMob (int row, int col);
    bool addVillage (int row, int col);
    bool addTree (int row, int col);
    bool addAnimal (int row, int col);
    bool addStronghold (int row, int col);
    bool addCave (int row, int col); //addCave adds a cave Char to both maps
        //cave
    bool addIron (int row, int col);
    bool addGold (int row, int col);
    bool addDiamond (int row, int col);
            //end
    bool addDragon (int row, int col);


    bool removeMob(int row, int col);
    bool removeTree(int row, int col);
    bool removeAnimal(int row, int col);
        //cave
    bool removeIron (int row, int col);
    bool removeGold (int row, int col);
    bool removeDiamond (int row, int col);
            //end
    //bool removeDragon (int row, int col); 




    // OTHER FUNCTIONS
    void displayMap(int mapIndex);

    bool move(char direction, int mapIndex);            

    int randomNumber(int min, int max);

    bool travelToFrom(int indexDestination, int indexFrom);

    bool resetMap();
};
#endif
