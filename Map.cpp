// CSCI1300 Fall 2022 Project 2
// Author: Trish Le
// Recitation: 303 – Xuefei Sun
// Project 3 - Map.cpp

#include <iostream>
#include <locale>
#include "Map.h"
using namespace std;

Map::Map() {
    //populate map data with grassblock, end, caveblock characters (these are the "freeblocks")
    //map index indicates which world you are in, 0 is overworld, 1 is cave, 2 is end dimension
    for (int i = 0; i < num_rows_; i++) {
        for (int j = 0; j < num_cols_; j++) {
            map_data_[0][i][j] = GRASSBLOCK;
        }
    }
    for (int i = 0; i < num_rows_; i++) {
        for (int j = 0; j < num_cols_; j++) {
            map_data_[1][i][j] = CAVEBLOCK;
        }
    }
    for (int i = 0; i < num_rows_; i++) {
        for (int j = 0; j < num_cols_; j++) {
            map_data_[2][i][j] = ENDBLOCK;
        }
    }

    //initiate player position
    player_position_[0] = 0;
    player_position_[1] = 0;

    //put player indicator in map data //only for overworld map, map index 1
    map_data_[0][player_position_[0]][player_position_[1]] = PLAYER;

        //rest of map function randomly places all villages, mobs, animals, trees, and the stronghold
        
        //RANDOM MAP GENERATION
        int randRow;
        int randCol;
        //I used i-- for mobs, villages, animals, and trees
        //mob generation
        for (int i = 0; i < max_mobs_; i++) {
            //these lines generation two random numbers
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            //check for successful mob allocation on the map
            if (!addMob(randRow, randCol)) { //adds to positions array and map data array
                //^^^ also updates mob_count_
                i--; 
            }
        }
        //village generation
        for (int i = 0; i < max_villages_; i++) {
            //rng
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            //check for successful village allocation on map
            if (!addVillage(randRow, randCol)) { //adds to positions array and map data array
                i--; 
            }
        }
        //trees
        for (int i = 0; i < max_trees_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addTree(randRow, randCol)) {
                i--;
            }
        }
        //animals
        for (int i = 0; i < max_animals_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addAnimal(randRow, randCol)) {
                i--;
            }
        }
        //iron
        for (int i = 0; i < max_iron_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addIron(randRow, randCol)) {
                i--;
            }
        }
        //gold
        for (int i = 0; i < max_gold_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addGold(randRow, randCol)) {
                i--;
            }
        }
        //diamond
        for (int i = 0; i < max_diamond_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addDiamond(randRow, randCol)) {
                i--;
            }
        }
        
        //i used a count variable for caves and strongholds 
        //these are special because we will be only adding one of each these elements to the map array
        //...for the foreseeable future?
        //stronghold
        int count = 0;
        while (count < max_strongholds_) {
            //generate two random numbers
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            //check if add function is successful
            if (addStronghold(randRow, randCol)) { //adds to positions array and map data array
                count++;
            }
            else {
                count = 0;
            }
        }
        //cave
        count = 0;
        while (count < max_caves_) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (addCave(randRow, randCol)) { //adds to positions array and map data array)                 
                count++;
            }
            else {
                count = 0;
            }
        }

        //dragon
        count = 0;
        while (count < max_dragons_) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (addDragon(randRow, randCol)) { //adds to positions array and map data array)                 
                count++;
            }
            else {
                count = 0;
            }
        }




}






// RETURN/GETTER FUNCTIONS

int Map::getPlayerRow() {
    return player_position_[0];
}

int Map::getPlayerCol() {
    return player_position_[1];
}

int Map::getMobCount() {
    return mob_count_;
}

int Map::getVillageCount() {
    return village_count_;
}

int Map::getTreeCount() {
    return tree_count_;
}

int Map::getAnimalCount() {
    return animal_count_;
}

int Map::getIronCount() {
    return iron_count_;
}

int Map::getGoldCount() {
    return gold_count_;
}

int Map::getDiamondCount() {
    return diamond_count_;
}

int Map::getNumRows() {
    return num_rows_;
}

int Map::getNumCols() {
    return num_cols_;
}






//CHECK FUNCTIONS 

bool Map::isOnMap(int row, int col) {
    if (col >= 0 && col < num_cols_ && row >= 0 && row < num_rows_) {
        return true;
    }
    return false;
}

bool Map::isFreeBlock(int row, int col, int mapIndex) {
    if (!isOnMap(row, col)) {
        return false;
    }
    if (map_data_[mapIndex][row][col] == freeBlock_[mapIndex]) {
        return true;
    }
    return false;
}

bool Map::isMobLocation(int row, int col) {  //check for mob location in mob position array
    //does not check for a MOB character in the map_data_ array
    if (!isOnMap(row, col)) {
        return false;
    }
    for (int i = 0; i < mob_count_; i++) {
        if (row == mob_positions_[i][0] && col == mob_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isVillageLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }
    for (int i = 0; i < village_count_; i++) {
        if (row == village_positions_[i][0] && col == village_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isTreeLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    for (int i = 0; i < tree_count_; i++) {
        if (row == tree_positions_[i][0] && col == tree_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isAnimalLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    for (int i = 0; i < animal_count_; i++) {
        if (row == animal_positions_[i][0] && col == animal_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isIronLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    for (int i = 0; i < iron_count_; i++) {
        if (row == iron_positions_[i][0] && col == iron_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isGoldLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    for (int i = 0; i < gold_count_; i++) {
        if (row == gold_positions_[i][0] && col == gold_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isDiamondLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    for (int i = 0; i < diamond_count_; i++) {
        if (row == diamond_positions_[i][0] && col == diamond_positions_[i][1]) {
            return true;
        }
    }
    return false;
}

bool Map::isStrongholdLocation(int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    if (row == stronghold_position_[0][0] && col == stronghold_position_[0][1]) {
        return true;
    }
    return false;
}

bool Map::isCaveLocation (int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    if (row == cave_position_[0][0] && col == cave_position_[0][1]) {
        return true;
    }
    return false;
}


bool Map::isDragonLocation (int row, int col) {
    if (!isOnMap(row, col)) {
        return false;
    }

    if (row == dragon_position_[0][0] && col == dragon_position_[0][1]) {
        return true;
    }
    return false;
}

bool Map::isNextToMob() { //uses mobLocation functions (which uses mob_positions_) to determine if 
    //player is adjacent to mob character
    if (isMobLocation(player_position_[0] + 1, player_position_[1]) || isMobLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isMobLocation(player_position_[0], player_position_[1] + 1) || isMobLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToVillage() {
    if (isVillageLocation(player_position_[0] + 1, player_position_[1]) || isVillageLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isVillageLocation(player_position_[0], player_position_[1] + 1) || isVillageLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToTree() {
    if (isTreeLocation(player_position_[0] + 1, player_position_[1]) || isTreeLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isTreeLocation(player_position_[0], player_position_[1] + 1) || isTreeLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToAnimal() {
    if (isAnimalLocation(player_position_[0] + 1, player_position_[1]) || isAnimalLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isAnimalLocation(player_position_[0], player_position_[1] + 1) || isAnimalLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToStronghold() {
    if (isStrongholdLocation(player_position_[0] + 1, player_position_[1]) || isStrongholdLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isStrongholdLocation(player_position_[0], player_position_[1] + 1) || isStrongholdLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToCave() {
    if (isCaveLocation(player_position_[0] + 1, player_position_[1]) || isCaveLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isCaveLocation(player_position_[0], player_position_[1] + 1) || isCaveLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToIron() {
    if (isIronLocation(player_position_[0] + 1, player_position_[1]) || isIronLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isIronLocation(player_position_[0], player_position_[1] + 1) || isIronLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToGold() {
    if (isGoldLocation(player_position_[0] + 1, player_position_[1]) || isGoldLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isGoldLocation(player_position_[0], player_position_[1] + 1) || isGoldLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToDiamond() {
    if (isDiamondLocation(player_position_[0] + 1, player_position_[1]) || isDiamondLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isDiamondLocation(player_position_[0], player_position_[1] + 1) || isDiamondLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}

bool Map::isNextToDragon() {
    if (isDragonLocation(player_position_[0] + 1, player_position_[1]) || isDragonLocation(player_position_[0] - 1, player_position_[1])) {
        return true;
    }
    if (isDragonLocation(player_position_[0], player_position_[1] + 1) || isDragonLocation(player_position_[0], player_position_[1] - 1)) {
        return true;
    }
    return false;
}




    //SETTER FUNCTIONS

bool Map::setPlayerData(int row, int col, int mapIndex) {
    if (isOnMap(row, col) && isFreeBlock(row, col, mapIndex)) {
        map_data_[mapIndex][row][col]= PLAYER;
        player_position_[0] = row;
        player_position_[1] = col;
        return true;
    }
    return false;
}

bool Map::addMob (int row, int col) {
    if (mob_count_ >= max_mobs_) {
        return false;
    }
    if (!isFreeBlock(row, col, 0)) {
        return false;
    }
    mob_positions_[mob_count_][0] = row;
    mob_positions_[mob_count_][1] = col;
    map_data_[0][row][col] = MOB;
    mob_count_++;
    return true;
}

bool Map::addVillage (int row, int col) {
    if (village_count_ >= max_villages_) {
        return false;
    }
    if (!isFreeBlock(row, col, 0)) {
        return false;
    }
    village_positions_[village_count_][0] = row;
    village_positions_[village_count_][1] = col;
    map_data_[0][row][col] = VILLAGE;
    village_count_++;
    return true;
}
    
bool Map::addTree (int row, int col) {
    if (tree_count_ >= max_trees_) {
        return false;
    }
    if (!isFreeBlock(row, col, 0)) {
        return false;
    }
    tree_positions_[tree_count_][0] = row;
    tree_positions_[tree_count_][1] = col;
    map_data_[0][row][col] = TREE;
    tree_count_++;
    return true;
}

bool Map::addAnimal (int row, int col) {
    if (animal_count_ >= max_animals_) {
        return false;
    }
    if (!isFreeBlock(row, col, 0)) {
        return false;
    }
    animal_positions_[animal_count_][0] = row;
    animal_positions_[animal_count_][1] = col;
    map_data_[0][row][col] = ANIMAL;
    animal_count_++;
    return true;
}

bool Map::addStronghold (int row, int col) {
    if (stronghold_count_ >= max_strongholds_) {
        return false;
    }
    if (!isFreeBlock(row, col, 0) || !isFreeBlock(row, col, 2)) {
        return false;
    }
    if (isFreeBlock(row+1, col, 0) && isFreeBlock(row-1, col, 0) && isFreeBlock(row, col+1, 0) && isFreeBlock(row, col-1, 0)) {
        stronghold_position_[stronghold_count_][0] = row;
        stronghold_position_[stronghold_count_][1] = col;
        map_data_[0][row][col] = STRONGHOLD;
        map_data_[2][row][col] = STRONGHOLD;
        stronghold_count_++;
        return true;
    }
    return false;
}

bool Map::addCave (int row, int col) {
    if (cave_count_ >= max_caves_) {
        return false;
    }
    if (!isFreeBlock(row, col, 0) || !isFreeBlock(row, col, 1)) {
        return false;
    }
    if (isFreeBlock(row+1, col, 0) && isFreeBlock(row-1, col, 0) && isFreeBlock(row, col+1, 0) && isFreeBlock(row, col-1, 0)) {
        cave_position_[cave_count_][0] = row;
        cave_position_[cave_count_][1] = col;
        map_data_[0][row][col] = CAVE;
        map_data_[1][row][col] = CAVE;
        cave_count_++;
        return true;
    }
    return false;
}

bool Map::addIron (int row, int col) {
    if (iron_count_ >= max_iron_) {
        return false;
    }
    if (!isFreeBlock(row, col, 1)) {
        return false;
    }
    iron_positions_[iron_count_][0] = row;
    iron_positions_[iron_count_][1] = col;
    map_data_[1][row][col] = IRON;
    iron_count_++;
    return true;
}

bool Map::addGold (int row, int col) {
    if (gold_count_ >= max_gold_) {
        return false;
    }
    if (!isFreeBlock(row, col, 1)) {
        return false;
    }
    gold_positions_[gold_count_][0] = row;
    gold_positions_[gold_count_][1] = col;
    map_data_[1][row][col] = GOLD;
    gold_count_++;
    return true;
}

bool Map::addDiamond (int row, int col) {
    if (diamond_count_ >= max_diamond_) {
        return false;
    }
    if (!isFreeBlock(row, col, 1)) {
        return false;
    }
    diamond_positions_[diamond_count_][0] = row;
    diamond_positions_[diamond_count_][1] = col;
    map_data_[1][row][col] = DIAMOND;
    diamond_count_++;
    return true;
}

    //end
bool Map::addDragon (int row, int col) {
    if (dragon_count_ >= max_dragons_) {
        return false;
    }
    if (!isFreeBlock(row, col, 2)) {
        return false;
    }
    dragon_position_[dragon_count_][0] = row;
    dragon_position_[dragon_count_][1] = col;
    map_data_[2][row][col] = DRAGON;
    return true;
}

bool Map::removeMob(int row, int col) {
    for (int i = 0; i < mob_count_; i++)
    {
        if (mob_positions_[i][0] == row && mob_positions_[i][1] == col)
        {
            // swap i'th mob with last mob
            mob_positions_[i][0] = mob_positions_[mob_count_ - 1][0];
            mob_positions_[i][1] = mob_positions_[mob_count_ - 1][1];
            // reset last mob
            mob_positions_[mob_count_ - 1][0] = -1;
            mob_positions_[mob_count_ - 1][1] = -1;
            // decrement mob_count_
            mob_count_--;
            // set map data to freeblock
            map_data_[0][row][col] = GRASSBLOCK;
            return true;
        }
    }
    return false;
}

bool Map::removeTree(int row, int col) {
    for (int i = 0; i < tree_count_; i++)
    {
        if (tree_positions_[i][0] == row && tree_positions_[i][1] == col)
        {
            // swap i'th tree with last tree
            tree_positions_[i][0] = tree_positions_[tree_count_ - 1][0];
            tree_positions_[i][1] = tree_positions_[tree_count_ - 1][1];
            // reset last tree
            tree_positions_[tree_count_ - 1][0] = -1;
            tree_positions_[tree_count_ - 1][1] = -1;
            // decrement tree_count_
            tree_count_--;
            // set map data to grassblock
            map_data_[0][row][col] = GRASSBLOCK;
            return true;
        }
    }
    return false;
}
    
bool Map::removeAnimal(int row, int col) {
    for (int i = 0; i < animal_count_; i++)
    {
        if (animal_positions_[i][0] == row && animal_positions_[i][1] == col)
        {
            // swap i'th animal with last animal
            animal_positions_[i][0] = animal_positions_[animal_count_ - 1][0];
            animal_positions_[i][1] = animal_positions_[animal_count_ - 1][1];
            // reset last animal
            animal_positions_[animal_count_ - 1][0] = -1;
            animal_positions_[animal_count_ - 1][1] = -1;
            // decrement animal
            animal_count_--;
            // set map data to grassblock
            map_data_[0][row][col] = GRASSBLOCK;
            return true;
        }
    }
    return false;
}

bool Map::removeIron(int row, int col) {
    for (int i = 0; i < iron_count_; i++)
    {
        if (iron_positions_[i][0] == row && iron_positions_[i][1] == col)
        {
            // swap i'th iron with last iron
            iron_positions_[i][0] = iron_positions_[iron_count_ - 1][0];
            iron_positions_[i][1] = iron_positions_[iron_count_ - 1][1];
            // reset last iron
            iron_positions_[iron_count_ - 1][0] = -1;
            iron_positions_[iron_count_ - 1][1] = -1;
            // decrement iron
            iron_count_--;
            // set map data to caveblock
            map_data_[1][row][col] = CAVEBLOCK;
            return true;
        }
    }
    return false;
}

bool Map::removeGold(int row, int col) {
    for (int i = 0; i < gold_count_; i++)
    {
        if (gold_positions_[i][0] == row && gold_positions_[i][1] == col)
        {
            // swap i'th gold with last gold
            gold_positions_[i][0] = gold_positions_[gold_count_ - 1][0];
            gold_positions_[i][1] = gold_positions_[gold_count_ - 1][1];
            // reset last gold
            gold_positions_[gold_count_ - 1][0] = -1;
            gold_positions_[gold_count_ - 1][1] = -1;
            // decrement gold
            gold_count_--;
            // set map data to caveblock
            map_data_[1][row][col] = CAVEBLOCK;
            return true;
        }
    }
    return false;
}

bool Map::removeDiamond(int row, int col) {
    for (int i = 0; i < diamond_count_; i++)
    {
        if (diamond_positions_[i][0] == row && diamond_positions_[i][1] == col)
        {
            // swap i'th diamond with last diamond
            diamond_positions_[i][0] = diamond_positions_[diamond_count_ - 1][0];
            diamond_positions_[i][1] = diamond_positions_[diamond_count_ - 1][1];
            // reset last diamond
            diamond_positions_[diamond_count_ - 1][0] = -1;
            diamond_positions_[diamond_count_ - 1][1] = -1;
            // decrement diamond
            diamond_count_--;
            // set map data to caveblock
            map_data_[1][row][col] = CAVEBLOCK;
            return true;
        }
    }
    return false;
}




    //OTHER FUNCTIONS

void Map::displayMap(int mapIndex) {
    for (int i = 0; i < num_rows_; i++) {
        cout << "                                        ";
        for (int j = 0; j < num_cols_; j ++) {
            cout << map_data_[mapIndex][i][j];
        }
        if (mapIndex == 0) {
            switch(i) {
                case 0: 
                    cout << "    PLAYER = " << PLAYER;
                    break;
                case 1: 
                    cout << "    GRASSBLOCK = " << GRASSBLOCK;
                    break;
                case 2:
                    cout << "    STRONGHOLD = " << STRONGHOLD;
                    break;
                case 3:
                    cout << "    VILLAGE = " << VILLAGE;
                    break;
                case 4: 
                    cout << "    TREE = " << TREE;
                    break;
                case 5:
                    cout << "    ANIMAL = " << ANIMAL;
                    break;
                case 6: 
                    cout << "    CAVE = " << CAVE;
                    break;
                case 7:
                    cout << "    MOB = " << MOB;
                    break;
            }
        }
        if (mapIndex == 1) {
            switch(i) {
                case 0: 
                    cout << "    PLAYER = " << PLAYER;
                    break;
                case 1: 
                    cout << "    CAVEBLOCK = " << CAVEBLOCK;
                    break;
                case 2:
                    cout << "    IRON = " << IRON;
                    break;
                case 3:
                    cout << "    GOLD = " << GOLD;
                    break;
                case 4:
                    cout << "    DIAMOND = " << DIAMOND;
                    break;
                case 5: 
                    cout << "    CAVE = " << CAVE;
                    break;
            }
        }
        if (mapIndex == 2) {
            switch(i) {
                case 0:
                    cout << "    PLAYER = " << PLAYER;
                    break;
                case 1:
                    cout << "    ENDBLOCK = " << ENDBLOCK;
                    break;
                case 2: 
                    cout << "    DRAGON = " << DRAGON;
                    break;
            }
        }
        cout << endl;
    }
}

bool Map::move(char direction, int mapIndex) {
     // check input char and move accordingly
    switch (tolower(direction)) {
        case 'w': // if user inputs w, move up if it is in bounds and is a free block
            if (setPlayerData(player_position_[0]-1,player_position_[1], mapIndex)) {
                map_data_[mapIndex][player_position_[0]+1][player_position_[1]] = freeBlock_[mapIndex];
                return true;
            }
            return false;
            break;
        case 's': // if user inputs s, move down if it is an allowed move
            if (setPlayerData(player_position_[0]+1,player_position_[1], mapIndex)) {
                map_data_[mapIndex][player_position_[0]-1][player_position_[1]] = freeBlock_[mapIndex];
                return true;
            }
            return false;
            break;
        case 'a': // if user inputs a, move left if it is an allowed move
            if (setPlayerData(player_position_[0],player_position_[1]-1, mapIndex)) {
                map_data_[mapIndex][player_position_[0]][player_position_[1]+1] = freeBlock_[mapIndex];
                return true;
            }
            return false;
            break;
        case 'd': // if user inputs d, move right if it is an allowed move
            if (setPlayerData(player_position_[0],player_position_[1]+1, mapIndex)) {
                map_data_[mapIndex][player_position_[0]][player_position_[1]-1] = freeBlock_[mapIndex];
                return true;
            }
            return false;
            break;
        default:
            return false;
    }
    return false;
}

int Map::randomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

bool Map::travelToFrom(int indexDestination,  int indexFrom) {
    if (setPlayerData(player_position_[0], player_position_[1], indexDestination)) {    
        map_data_[indexFrom][player_position_[0]][player_position_[1]] = freeBlock_[indexFrom];
        return true;
    }
    return false;
}

bool Map::resetMap() {
    mob_count_ = 0;  // stores number of hostile mobs misfortunes currently on map
    village_count_= 0; 
    tree_count_ = 0;
    animal_count_ = 0;
    stronghold_count_ = 0;
    cave_count_ = 0;
        //cave
    iron_count_ = 0;
    gold_count_ = 0;
    diamond_count_ = 0;
        //end
    dragon_count_ = 0;
    //populate map data with grassblock, end, caveblock characters (these are the "freeblocks")
    //map index indicates which world you are in, 0 is overworld, 1 is cave, 2 is end dimension
    for (int i = 0; i < num_rows_; i++) {
        for (int j = 0; j < num_cols_; j++) {
            map_data_[0][i][j] = GRASSBLOCK;
        }
    }
    for (int i = 0; i < num_rows_; i++) {
        for (int j = 0; j < num_cols_; j++) {
            map_data_[1][i][j] = CAVEBLOCK;
        }
    }
    for (int i = 0; i < num_rows_; i++) {
        for (int j = 0; j < num_cols_; j++) {
            map_data_[2][i][j] = ENDBLOCK;
        }
    }

    //initiate player position
    player_position_[0] = 0;
    player_position_[1] = 0;

    //put player indicator in map data //only for overworld map, map index 1
    map_data_[0][player_position_[0]][player_position_[1]] = PLAYER;

        //rest of map function randomly places all villages, mobs, animals, trees, and the stronghold
        
        //RANDOM MAP GENERATION
        int randRow;
        int randCol;
        //I used i-- for mobs, villages, animals, and trees
        //mob generation
        for (int i = 0; i < max_mobs_; i++) {
            //these lines generation two random numbers
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            //check for successful mob allocation on the map
            if (!addMob(randRow, randCol)) { //adds to positions array and map data array
                //^^^ also updates mob_count_
                i--; 
            }
        }
        //village generation
        for (int i = 0; i < max_villages_; i++) {
            //rng
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            //check for successful village allocation on map
            if (!addVillage(randRow, randCol)) { //adds to positions array and map data array
                i--; 
            }
        }
        //trees
        for (int i = 0; i < max_trees_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addTree(randRow, randCol)) {
                i--;
            }
        }
        //animals
        for (int i = 0; i < max_animals_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addAnimal(randRow, randCol)) {
                i--;
            }
        }
        //iron
        for (int i = 0; i < max_iron_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addIron(randRow, randCol)) {
                i--;
            }
        }
        //gold
        for (int i = 0; i < max_gold_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addGold(randRow, randCol)) {
                i--;
            }
        }
        //diamond
        for (int i = 0; i < max_diamond_; i++) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (!addDiamond(randRow, randCol)) {
                i--;
            }
        }
        
        //i used a count variable for caves and strongholds 
        //these are special because we will be only adding one of each these elements to the map array
        //...for the foreseeable future?
        //stronghold
        int count = 0;
        while (count < max_strongholds_) {
            //generate two random numbers
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            //check if add function is successful
            if (addStronghold(randRow, randCol)) { //adds to positions array and map data array
                count++;
            }
            else {
                count = 0;
            }
        }
        //cave
        count = 0;
        while (count < max_caves_) {
            srand(time(0));
            randRow = randomNumber(0, num_rows_);
            srand(time(0));
            randCol = randomNumber(0, num_cols_);
            if (addCave(randRow, randCol)) { //adds to positions array and map data array)                 
                count++;
            }
            else {
                count = 0;
            }
        }
    return true;
}
