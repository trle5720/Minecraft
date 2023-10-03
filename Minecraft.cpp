// CSCI1300 Fall 2022 Project 3
// Author: Trish Le and Benson Zou
// Recitation: 303 – Xuefei Sun
// Project 3 - Minecraft.cpp 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Minecraft.h"
#include "Mob.h"
#include "Resources.h"
#include "Map.h"
#include "Item.h"

using namespace std;

Minecraft::Minecraft() {
    username_ = "";
}

//constructor
Minecraft::Minecraft(string username) {
    //users stats
    username_ = username;
    health_points_ = 10;
    max_hp_ = 10;
    xp_ = 0;
    mobs_killed_ = 0;

    //game assets/tangibles
        //mobs, we'll pull these out of the mobs_ array everytime the player needs to fight one
    Resources creeper_drop = Resources("GUNPOWDER", 1);
    Mob creeper = Mob("Creeper", 10, 5, creeper_drop);
    mobs_.push_back(creeper);

    Resources zombie_drop = Resources("ROTTEN FLESH", 1);
    Mob zombie = Mob("Zombie", 10, 2, zombie_drop);
    mobs_.push_back(zombie);

    Resources skeleton_drop = Resources("BONE", 1);
    Mob skeleton = Mob("Skeleton", 10, 3, skeleton_drop);
    mobs_.push_back(skeleton);

    Resources spider_drop = Resources("SPIDER EYE", 1);
    Mob spider = Mob("Spider", 10, 2, spider_drop);
    mobs_.push_back(spider);

    //starting item
    //player needs to be able to chop wood in the beginning, we'll give them an axe
    Item wooden_axe = Item("WOODEN AXE", 4, 0, true, false);
    items_.push_back(wooden_axe);

    //starting resources

    Resources food = Resources("FOOD", 1);
    inventory_.push_back(food);
    // Map("overworld"); //need to figure out how to generate multiple map TYPES, like end, lower level...
    // Map("end_dimension");
    // Map("lower_level");
    //time permitting, nether

    Resources dragon_drop = Resources("DRAGON DROP", 1);
    ender_dragon_ = Mob("Dragon", 40, 10, dragon_drop);
}

/*
 1. Displays user information such as username, HP, Xp, mobs killed
 2. Loops through every vector and displays elements such as inventory and items
*/
void Minecraft::stats() { //displays stats for player at any given moment, username, gear, hp, xp, resources
    cout << "---------------------------USER STATISTICS---------------------------" << endl;
    cout << "USER TAG: " << username_ << " | " << "HP: " << health_points_ << " | XP: " << xp_ << " | TOTAL MOBS KILLED: " << mobs_killed_ << endl; 
    cout << "GEAR/ITEMS: [ ";
    if(items_.size() > 0){
        cout << items_[0].getItemName();
    
        for(int i = 1; i < items_.size(); i++){
            cout << " , "<<items_[i].getItemName();
        }
    }
    cout << " ] " << endl;
    cout << "INVENTORY: [ ";
    if(inventory_.size() > 0){
        cout << inventory_[0].getName() << ": " << inventory_[0].getAmount();
    
        for(int i = 1; i < inventory_.size(); i++){
            cout << " , "<<inventory_[i].getName() << ": " << inventory_[i].getAmount();
        }
    }
    cout << " ]" << endl;
    cout << "---------------------------------------------------------------------" << endl; 
    return;
}   

/*
 1. presents a menu for the user to select which action they would like to do:
    move, craft, trade, mine, eat, quit
 2. pulls up another menu if craft or trade is chosen
 3. calls on appropriate minecraft function for whatever choice the user picks
 4. quit game if user picks so
*/
int Minecraft::action_menu(int mapIndex) { //displays actions for player in any given moment   
    //dynamic action menu, only prints certain action if player is in position to do them
    string options[128]; //temporary string array
    //index indicates choice number
    //string indications action
    //displays available actions


    cout << "------------------------------ACTION MENU:--------------------------------" << endl;
    cout << " USE 'W' 'A' 'S' 'D' KEYS TO MOVE ON MAP " << endl;
    //cout << " 1. MOVE (Use 'W' 'A' 'S' 'D' as arrow keys)" << endl; //call on map function to move
    cout << " 1. CRAFT " << endl; //crafting function not yet made: pull up a crafting menu
    cout << " 2. EAT FOOD " << endl; //eat function: increase health, decrement food resource
    int n = 2;
    if (map_.isNextToVillage() && mapIndex == 0) {
        n++;
        options[n] = "TRADE";
        cout << " " << n << ". TRADE " <<endl;
    }
    if (map_.isNextToIron() || map_.isNextToGold() || map_.isNextToDiamond()) {
        if (mapIndex == 1) {
            n++;
            options[n] = "MINE";
            cout << " " << n << ". MINE ORE " << endl;
        }
    }
    if (map_.isNextToTree() && mapIndex == 0) {
        n++;
        options[n] = "CHOP";
        cout << " " << n << ". CHOP" << endl;
    }
    if (map_.isNextToMob() && mapIndex == 0) {
        n++;
        options[n] = "FIGHT";
        cout << " " << n << ". FIGHT" << endl;
    }
    if (map_.isNextToAnimal() && mapIndex == 0) {
        n++;
        options[n] = "GENTLY AND PAINLESSLY HARM AN INNOCENT ANIMAL AND TAKE ITS RESOURCE";
        cout << " " << n << ". GENTLY AND PAINLESSLY HARM AN INNOCENT ANIMAL AND TAKE ITS RESOURCE" << endl;
    }
    if (map_.isNextToCave() && mapIndex == 0 ) {
        n++;
        options[n] = "ENTER CAVE";
        cout << " " << n << ". ENTER CAVE" << endl;
    }
    if (map_.isNextToCave() && mapIndex == 1) {
        n++;
        options[n] = "LEAVE CAVE";
        cout << " " << n << ". LEAVE CAVE" << endl;
    }
    if (map_.isNextToStronghold() && mapIndex == 0) {
        n++;
        options[n] = "GO TO END";
        cout << " " << n << ". GO TO END" << endl;
    }
    if (map_.isNextToStronghold() & mapIndex == 2) {
        n++;
        options[n] = "LEAVE END";
        cout << " " << n << ". LEAVE END" << endl;
    }
    if (map_.isNextToDragon() && mapIndex == 2) {
        n++;
        options[n] = "ATTACK DRAGON"; 
        cout << " " << n << ". ATTACK DRAGON" << endl;
    }
    n++;
    cout << " " << n << ". QUIT GAME " << endl; //ends program    //in mcDriver, if world.action_menu() returns 0, return 0 in int main ()
    cout << "--------------------------------------------------------------------------" << endl;
    //take string input
    string sInput;
    char choice;

    //do{ 
        //checks for valid choice input
        cin >> sInput;
        
        //take char input from string
        choice = sInput[0];
        //ascii values, ADSW, adsw, 
        if(choice != 65 && choice != 68 && choice != 83 && choice != 87 && choice != 97 && choice != 100 && choice != 115 && choice != 119 && !(choice < (n + 48)) && !(choice > 48) ){
            cout << "That is not a valid option. Please enter a choice between 1-" << n << " or 'w', 'a', 's', and 'd'. " << endl;
        }
        int intChoice = choice - '0';
        if (intChoice == 1) {
            crafting();
        }
        if (intChoice == 2) { //EAT FOOD 
            YOMPNOMPNOMNOM();
        }
        if (options[intChoice] == "MINE") {
            bonkbonkbonk();
        }
        if (options[intChoice] == "TRADE") {
            trading();
        }
        if (options[intChoice] == "CHOP") {
            wackwackwack();
        }
        if (options[intChoice] == "FIGHT") {
            fighting(); //function, should display hp and such 
            if(health_points_ <= 0){
                cout << "YOU DIED!" << endl;
                return playerIsDead();
            }
        }
        if (options[intChoice] == "GENTLY AND PAINLESSLY HARM AN INNOCENT ANIMAL AND TAKE ITS RESOURCE") {
            harmAnimal(); //prints hp and such of animal, + display info about animal drop!
        }
        if (options[intChoice] == "ENTER CAVE") {
            map_.travelToFrom(1,0);
            mapIndex = 1;
        }
        if (options[intChoice] == "LEAVE CAVE") {
            map_.travelToFrom(0,1);
            mapIndex = 0;
        }
        if (options[intChoice] == "GO TO END") {
            map_.travelToFrom(2,0);
            mapIndex = 2;
        }
        if (options[intChoice] == "LEAVE END") {
            map_.travelToFrom(0,2);
            mapIndex = 0;
        }
        if (options[intChoice] == "ATTACK DRAGON")  {
            dragon();
            if(health_points_ <= 0){
                cout << "YOU DIED!" << endl;
                return playerIsDead();
            }

            if(ender_dragon_.getMobHealth() <= 0){
                return playerIsDead();
            }
            
        }

        if(!map_.move(choice, mapIndex)) { //check if move function returns false
            //move function returns false sometimes when the player 
            //bumps into a map element or is out of map bounds
            cout << "player did not move" << endl;
            cout << " " << endl;
        }
            //display map every time input is detected regardless of input validity
        if (intChoice == n) {
            return 3;
        }
    return mapIndex;
} 
    

/*
 1. Presents menu of crafting options for the user to choose from
 2. Takes user input and asks for amount of resources they would like to input
 3. Checks if user has enough resources to craft desired amount:
    if so: calculate total number of items they successfully crafted
 4. Decreases amount of inputted resource in inventory: if 0 then delete item from inventory
 5. Adds the newly crafted resource to inventory
*/
int Minecraft::crafting(){
    int num_crafted = 0; // amount that can actually be crafted
    int craft_choice;
    string input_string;

    do{
        cout << " " << endl;
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "What would you like to Craft? (Enter a number between 1-6)" << endl;
        cout << "1) 4 WOODEN PLANKS | NEED: 1 Wood" << endl;
        cout << "2) 4 STICKS        | NEED: 2 Wooden Planks" << endl;
        cout << "3) 1 PICKAXE       | NEED: 3 Ores(Wooden Plank,Iron,Gold,or Diamond), 2 Sticks" << endl;
        cout << "4) 1 SWORD         | NEED: 2 Ores(Wooden Plank,Iron,Gold,or Diamond), 1 Stick" << endl;
        cout << "5) 1 AXE           | NEED: 3 Ores(Wooden Plank,Iron,Gold,or Diamond), 2 Stick" << endl;
        cout << "6) QUIT CRAFTING MENU" << endl;
        cout << "--------------------------------------------------------------------------------------------------" << endl;

        int num_wood, num_planks, num_sticks, num_ores,  ore_index, stick_index, amountOres,amountSticks, maxToolOres, maxToolSticks;
        bool enoughOres = false;
        bool enoughSticks = false;
        bool have_enough = false;
        bool found = false;
        bool found_sticks = false;
        string mineral;
        int maxTool = 0;
        Resources temp;

        do{ //checks for valid choice input
            //cin >> craft_choice;
            cin >> input_string;
            craft_choice = input_string[0]-'0';

            if(craft_choice < 1 || craft_choice > 6){
                cout << "That is not a valid option. Please enter a choice between 1-6." << endl;
            }
        } while(craft_choice < 1 || craft_choice > 6);
            

        switch(craft_choice){
            case 1: //wooden planks
                do{
                    do{
                        cout << "How many Wood blocks would you like to input?" << endl; 
                        cin >> input_string;
                        num_wood = input_string[0]-'0';

                        if(num_wood < 1){
                            cout << "Invalid input. Number of wood blocks must be at least 1." << endl;
                        }
                    }while(num_wood <1);

                    for(int i = 0; i < inventory_.size(); i++){ //loops through inventory
                        int current_amount = inventory_[i].getAmount();
                        if(inventory_[i].getName() == "WOOD"){ //checks if user has wood
                            found =true;
                            if(num_wood <= current_amount){ //if they have enough wood for the amount desired
                                have_enough = true;
                                num_crafted = num_wood*4;
                                inventory_[i].setAmount(current_amount - num_wood); //*****decide if should get rid of resource from inventory if amount = 0
                                if(inventory_[i].getAmount()==0){
                                    inventory_.erase(inventory_.begin() + i);
                                }
                                addResource("WOODEN PLANK", num_crafted); //adds to inventory: calls on addResource()
                                cout << "You've successfully crafted " << num_crafted << " Wooden Planks!" << endl;
                            }
                            else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                    }
                    if(found == false){
                        have_enough = true;
                        cout <<"You don't have any Wood blocks! Go chop down some trees before crafting Wooden Planks!" << endl;
                    }
                }while(have_enough == false);

                break;

            case 2: //sticks
                do{
                    do{

                        cout << "How many Wooden Planks would you like to input?" << endl; 
                        cin >> input_string;
                        num_planks = input_string[0]-'0';
                     
                        if(num_planks < 2){
                            cout << "You need at least 2 wooden planks to craft sticks!" << endl;
                        }
                    }while(num_planks<2);
                    
                    for(int i = 0; i < inventory_.size(); i++){ //loops through inventory
                        int current_amount = inventory_[i].getAmount();
                        if(inventory_[i].getName() == "WOODEN PLANK"){ //checks if user has planks
                            found = true;
                            if(num_planks <= current_amount){ //if they have enough planks to craft
                                have_enough = true;
                                num_crafted = num_planks*2;
                                inventory_[i].setAmount(current_amount - num_planks); 
                                if(inventory_[i].getAmount()==0){
                                    inventory_.erase(inventory_.begin() + i);
                                }
                                addResource("STICK", num_crafted); //adds to inventory: calls on addResource()
                                cout << "You've succesfully crafted " << num_crafted << " Sticks!" << endl;

                            }
                            else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                    }
                    if(found == false){
                        have_enough = true;
                        cout << "You don't have any Wooden Planks! Make sure you craft some using wood before making sticks!" << endl;
                    }
                }while(have_enough == false);
                break;

            case 3: //pickaxe
                do{
                    cout << "What kind of ore is being used? (Type in 'Wood', 'Iron', 'Gold', or 'Diamond')" << endl;
                    cin >> mineral;

                    for(int i = 0; i < mineral.length(); i++){
                    mineral[i] = toupper(mineral[i]);
                    }

                    if(mineral!= "WOOD" && mineral!= "IRON"&& mineral != "GOLD" && mineral != "DIAMOND"){
                        cout << "That's not a valid ore input! Please type in one of the listed ores." << endl;
                    }
                
                }while(mineral!= "WOOD" && mineral!= "IRON"&& mineral != "GOLD" && mineral != "DIAMOND");

                
                if(mineral == "WOOD"){
                    mineral = "WOODEN PLANK";
                }
                do{
                    do{
                        cout << "How many " << mineral << " blocks would you like to input?" << endl; 
                        cin >> input_string;
                        num_ores = input_string[0]-'0';
                        if(num_ores < 3){
                            cout << "Invalid input. Number of ore blocks must be at least 3." << endl;
                        }
                    }while(num_ores <3);
                    
                    do{
                        cout << "How many STICKS would you like to input?" << endl;
                        cin >> input_string;
                        num_sticks = input_string[0]-'0';
                        if(num_sticks < 2){
                            cout << "Invalid input. Number of sticks must be 2." << endl;
                        }
                    }while(num_sticks < 2);

                    for(int i = 0; i < inventory_.size(); i++){ //loops through inventory
                        int num_resources = inventory_[i].getAmount();
                        if(inventory_[i].getName()== mineral){ //checks if user has ores in their inventory
                            found = true;
                            amountOres = num_resources;
                            if(num_ores <= num_resources){ //if they have enough ores:
                                have_enough = true;
                                enoughOres = true;
                                ore_index = i;
                                //number of pix they can make from ores
                                maxToolOres = num_ores/3;
                            }else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                        if(inventory_[i].getName()== "STICK"){
                            found_sticks = true;
                            amountSticks = num_resources;
                            if(num_sticks <= num_resources){
                                have_enough = true;
                                enoughSticks = true;
                                stick_index = i;
                                maxToolSticks = num_sticks/2;
                            }else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                    }
                    if(found == false || found_sticks == false){
                        have_enough = true;
                        cout << " You either don't have Wooden Planks or Sticks! You can't craft a pickaxe quite yet." << endl;
                    }
                }while(have_enough == false);

                    if(enoughOres && enoughSticks){
                        if(maxToolOres < maxToolSticks){
                            num_crafted = maxToolOres;
                        } 
                        else{
                            num_crafted = maxToolSticks;
                        }
                        inventory_[ore_index].setAmount(amountOres - num_crafted*3); 
                        inventory_[stick_index].setAmount(amountSticks - num_crafted*2);
                        removeResource();
                        if(num_crafted > 0){
                            if(mineral == "WOODEN PLANK"){
                                mineral = "WOODEN";
                            }
                            if(mineral == "DIAMOND"){
                                addItem(Item(mineral+ " PICKAXE", 5, 0, false, true));
                                cout << "You've succesfully crafted a " << mineral << " PICKAXE! It does 5 damage to mobs, and can mine ores!" << endl;
                                cout << " " << endl;
                            }else if(mineral == "GOLD"){
                                addItem(Item(mineral+" PICKAXE", 3, 0, false, true)); //adds to inventory: calls on addResource()
                                cout << "You've succesfully crafted a " << mineral << " PICKAXE! It does 3 damage to mobs, and can mine ores!" << endl;
                                cout << " " << endl;
                            }else if(mineral == "IRON"){
                                addItem(Item(mineral+" PICKAXE", 2, 0, false, true)); //adds to inventory: calls on addResource()
                                cout << "You've succesfully crafted a " << mineral << " PICKAXE! It does 2 damage to mobs, and can mine ores!" << endl;
                                cout << " " << endl;
                            }else{
                                addItem(Item(mineral+" PICKAXE", 1, 0, false, true)); //adds to inventory: calls on addResource()
                                cout << "You've succesfully crafted a " << mineral << " PICKAXE! It does 1 damage to mobs, and can mine ores!" << endl;
                                cout << " " << endl;
                            } 
                        }
                    }
                break;

            case 4: //sword
                do{
                    cout << "What kind of ore is being used? (Type in 'Wood', 'Iron', 'Gold', or 'Diamond')" << endl;
                    cin >> mineral;

                    for(int i = 0; i < mineral.length(); i++){
                    mineral[i] = toupper(mineral[i]);
                    }
                    if(mineral!= "WOOD" && mineral!= "IRON"&& mineral != "GOLD" && mineral != "DIAMOND"){
                        cout << "That's not a valid ore input! Please type in one of the listed ores." << endl;
                    }
                    
                }while(mineral!= "WOOD" && mineral!= "IRON"&& mineral != "GOLD" && mineral != "DIAMOND");

                
                if(mineral == "WOOD"){
                    mineral = "WOODEN PLANK";
                }
                
                do{
                    do{
                        cout << "How many " << mineral << " blocks would you like to input?" << endl; 
                        cin >> input_string;
                        num_ores = input_string[0]-'0';

                        if(num_ores < 2){
                            cout << "Invalid input. Number of ore blocks must be at least 2." << endl;
                        }
                    }while(num_ores <2);
                    
                    do{
                        cout << "How many STICKS would you like to input?" << endl;
                        cin >> input_string;
                        num_sticks = input_string[0]-'0';

                        if(num_sticks < 1){
                            cout << "Invalid input. Number of sticks must be 1." << endl;
                        }
                    }while(num_sticks < 1);

                    for(int i = 0; i < inventory_.size(); i++){ //loops through inventory
                        int num_resources = inventory_[i].getAmount();
                        if(inventory_[i].getName()== mineral){ //checks if user has ores in their inventory
                            found = true;
                            amountOres = num_resources;
                            if(num_ores <= num_resources){ //if they have enough ores:
                                have_enough = true;
                                enoughOres = true;
                                ore_index = i;
                                //number of pix they can make from ores
                                maxToolOres = num_ores/2;
                            }else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                        if(inventory_[i].getName()== "STICK"){
                            found_sticks = true;
                            amountSticks = num_resources;
                            if(num_sticks <= num_resources){
                                have_enough = true;
                                enoughSticks = true;
                                stick_index = i;
                                maxToolSticks = num_sticks;
                            }else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                    }
                if(found == false || found_sticks == false){
                        have_enough = true;
                        cout << " You either don't have Wooden Planks or Sticks! You can't craft a sword quite yet." << endl;

                    }
            }while(have_enough == false);

                if(enoughOres && enoughSticks){
                    if(maxToolOres < maxToolSticks){
                        num_crafted = maxToolOres;
                    } 
                    else{
                        num_crafted = maxToolSticks;
                    }
                    inventory_[ore_index].setAmount(amountOres - num_crafted*2); 
                    inventory_[stick_index].setAmount(amountSticks - num_crafted);
                    removeResource();
                    if(num_crafted > 0){
                        if(mineral == "WOODEN PLANK"){
                            mineral = "WOODEN";
                        }
                        if(mineral == "DIAMOND"){
                            addItem(Item(mineral+ " SWORD", 15, 0, false, false));
                            cout << "You've succesfully crafted a " << mineral << " SWORD! It does 15 damage to mobs, and can harm an animal!" << endl;
                            cout << " " << endl;
                        }else if(mineral == "GOLD"){
                            addItem(Item(mineral+" SWORD", 10, 0, false, false)); //adds to inventory: calls on addResource()
                            cout << "You've succesfully crafted a " << mineral << " SWORD! It does 10 damage to mobs, and can harm animals!" << endl;
                            cout << " " << endl;
                        }else if(mineral == "IRON"){
                            addItem(Item(mineral+" SWORD", 5, 0, false, false)); //adds to inventory: calls on addResource()
                            cout << "You've succesfully crafted a " << mineral << " SWORD! It does 5 damage to mobs, and can harm animals!" << endl;
                            cout << " " << endl;
                        }else{
                            addItem(Item(mineral+" SWORD", 2, 0, false, false)); //adds to inventory: calls on addResource()
                            cout << "You've succesfully crafted a " << mineral << " SWORD! It does 2 damage to mobs, and can harm animals!" << endl;
                            cout << " " << endl;
                        } 
                    }
                }
                break;

            case 5: //axe
                do{
                    cout << "What kind of ore is being used? (Type in 'Wood', 'Iron', 'Gold', or 'Diamond')" << endl;
                    cin >> mineral;

                    for(int i = 0; i < mineral.length(); i++){
                    mineral[i] = toupper(mineral[i]);
                    }
                    if(mineral!= "WOOD" && mineral!= "IRON"&& mineral != "GOLD" && mineral != "DIAMOND"){
                        cout << "That's not a valid ore input! Please type in one of the listed ores." << endl;
                    }
                
                }while(mineral!= "WOOD" && mineral!= "IRON"&& mineral != "GOLD" && mineral != "DIAMOND");

                if(mineral == "WOOD"){
                    mineral = "WOODEN PLANK";
                }
                do{
                    do{
                        cout << "How many " << mineral << " blocks would you like to input?" << endl; 
                        cin >> input_string;
                        num_ores = input_string[0]-'0';

                        if(num_ores < 3){
                            cout << "Invalid input. Number of ore blocks must be at least 3." << endl;
                        }
                    }while(num_ores <3);
                    
                    do{
                        cout << "How many STICKS would you like to input?" << endl;
                        cin >> input_string;
                        num_sticks = input_string[0]-'0';
                        if(num_sticks < 2){
                            cout << "Invalid input. Number of sticks must be 2." << endl;
                        }
                    }while(num_sticks < 2);

                    for(int i = 0; i < inventory_.size(); i++){ //loops through inventory
                        int num_resources = inventory_[i].getAmount();
                        if(inventory_[i].getName()== mineral){ //checks if user has ores in their inventory
                            found = true;
                            amountOres = num_resources;
                            if(num_ores <= num_resources){ //if they have enough ores:
                                have_enough = true;
                                enoughOres = true;
                                ore_index = i;
                                //number of pix they can make from ores
                                maxToolOres = num_ores/3;
                            }else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                        if(inventory_[i].getName()== "STICK"){
                            found_sticks = true;
                            amountSticks = num_resources;
                            if(num_sticks <= num_resources){
                                have_enough = true;
                                enoughSticks = true;
                                stick_index = i;
                                maxToolSticks = num_sticks/2;
                            }else{
                                cout << "That's not a valid input." << endl;
                            }
                        }
                    }
                    if(found == false || found_sticks == false){
                        have_enough = true;
                        cout << " You either don't have Wooden Planks or Sticks! You can't craft an axe quite yet." << endl;
                    }
                }while(have_enough == false);

                if(enoughOres && enoughSticks){
                    if(maxToolOres < maxToolSticks){
                        num_crafted = maxToolOres;
                    } 
                    else{
                        num_crafted = maxToolSticks;
                    }
                    inventory_[ore_index].setAmount(amountOres - num_crafted*3); 
                    inventory_[stick_index].setAmount(amountSticks - num_crafted*2);
                    removeResource();
                    if(num_crafted > 0){
                        if(mineral == "WOODEN PLANK"){
                            mineral = "WOODEN";
                        }
                        if(mineral == "DIAMOND"){
                            addItem(Item(mineral+ " AXE", 5, 0, true, false));
                            cout << "You've succesfully crafted a " << mineral << " AXE! It does 5 damage to mobs, and can chop wood!" << endl;
                            cout << " " << endl;
                        }else if(mineral == "GOLD"){
                            addItem(Item(mineral+" AXE", 3, 0, true, false)); //adds to inventory: calls on addResource()
                            cout << "You've succesfully crafted a " << mineral << " AXE! It does 3 damage to mobs, and can chop wood!" << endl;
                            cout << " " << endl;
                        }else if(mineral == "IRON"){
                            addItem(Item(mineral+" AXE", 2, 0, true, false)); //adds to inventory: calls on addResource()
                            cout << "You've succesfully crafted a " << mineral << " AXE! It does 2 damage to mobs, and can chop wood!" << endl;
                            cout << " " << endl;
                        }else{
                            addItem(Item(mineral+" AXE", 2, 0, true, false)); //adds to inventory: calls on addResource()
                            cout << "You've succesfully crafted a " << mineral << " AXE! It does 1 damage to mobs, and can chop wood!" << endl;
                            cout << " " << endl;
                        } 
                    }
                }
                break;

            case 6:
                cout << "EXITING CRAFTING TABLE!" << endl;
                cout << " " << endl;
                return 0;
        }
    }while(craft_choice != 6);
    return num_crafted;
}    


/*
 1. Pulls up trading menu that shows user the choices that they can trade for
 2. Asks for the item they would like to trade for
 3. Determines if they have enough materials to trade for certain item
 4. If so, decrease the inputted item from inventory and add the newly traded item to inventory or item vector
*/    
void Minecraft::trading(){
    string input_string;
    int trade_choice;
    do{
        cout << " " << endl;
        cout << "----------------------------------------------------------------" << endl;
        cout << "What would you like to trade?" << endl;
        cout << "1. Bone -----> Diamond Chestplate" << endl;
        cout << "2. Rotten Flesh ---> Diamond Leggings" << endl;
        cout << "3. Gunpowder ------> Diamond Boots" << endl;
        cout << "4. Spider Eye -----> Diamond Helmet" << endl;
        cout << "5. Quit Trading Menu" << endl;
        cout << "----------------------------------------------------------------" << endl;

        do{
            cin >> input_string;
            trade_choice = input_string[0]- '0';
            
            if(trade_choice < 1 || trade_choice > 5){
                cout << "That's not a valid choice. Please enter a number between 1-4." << endl;
            }
        }while(trade_choice < 1 || trade_choice > 5);

        int num_items;
        bool item_found = false;
        switch(trade_choice){
            case 1:
                num_items = getResourceAmount("BONE");
                if(num_items < 1){
                    cout << "You do not have enough bone to make this trade." << endl;
                    break;
                }
                else{
                    for(int i = 0; i < items_.size(); i++){
                        if(items_[i].getItemName() == "DIAMOND CHESTPLATE"){
                            cout << "You already have a Diamond Chestplate!" << endl;
                            item_found = true;
                            break;
                        }
                    }
                    if(item_found == false){
                        for(int i = 0; i < inventory_.size(); i++){
                            item_found = true;
                            if(inventory_[i].getName() == "BONE"){
                                inventory_[i].increaseAmount(-1);

                                if(inventory_[i].getAmount() == 0){
                                    inventory_.erase(inventory_.begin()+i);
                                }

                                cout << "Succesfully traded 2 Bones for a Diamond Chestplate! Your max HP went up by 10." << endl;
                                addItem(Item("DIAMOND CHESTPLATE", 0, 10, false, false));
                            }
                        }
                        if(item_found == false){
                            cout << "You don't have any bones!" << endl;
                            break;
                        }
                        changeMaxHp(10);
                        changeXp(5);
                        break;
                    }
                }
            case 2:
                num_items = getResourceAmount("ROTTEN FLESH");
                    if(num_items < 1){
                        cout << "Unable to make trade. You do not have rotten flesh. Your max HP went up by 10." << endl;
                        break;
                    }
                    else{
                        for(int i = 0; i < items_.size(); i++){
                            if(items_[i].getItemName() == "DIAMOND LEGGINGS"){
                                cout << "You already have Diamond leggings!" << endl;
                                item_found = true;
                                break;
                            }
                        }
                        if(item_found == false){
                            
                            for(int i = 0; i < inventory_.size(); i++){
                                if(inventory_[i].getName() == "ROTTEN FLESH"){
                                    item_found = true;
                                    inventory_[i].increaseAmount(-1);

                                    if(inventory_[i].getAmount() == 0){
                                    inventory_.erase(inventory_.begin()+i);
                                    }

                                    cout << "Succesfully traded Rotten Flesh for Diamond Legging!" << endl;
                                    addItem(Item("DIAMOND LEGGINGS", 0, 10, false, false));
                                }
                            }
                            if(item_found == false){
                            cout << "You don't have any Rotten Flesh!" << endl;
                            break;
                            }
                            changeHp(5);
                            changeMaxHp(10);
                            changeXp(5);

                            break;
                        }
                    }

            case 3:
                num_items = getResourceAmount("GUNPOWDER");
                    if(num_items < 1){
                        cout << "Unable to make trade. You do not have gunpowder." << endl;
                        break;
                    }
                    else{
                        for(int i = 0; i < items_.size(); i++){
                            if(items_[i].getItemName() == "DIAMOND BOOTS"){
                                cout << "You already have Diamond boots!" << endl;
                                item_found = true;
                                break;
                            }
                        }
                        if(item_found == false){
                            cout << "Succesfully traded Gunpowder for a Diamond Boots! Your max HP went up by 10." << endl;
                            addItem(Item("DIAMOND BOOTS", 0, 10, false, false));
                            for(int i = 0; i < inventory_.size(); i++){
                                if(inventory_[i].getName() == "GUNPOWDER"){
                                    item_found = true;
                                    inventory_[i].increaseAmount(-1);
                                    if(inventory_[i].getAmount() == 0){
                                    inventory_.erase(inventory_.begin()+i);
                                    }
                                    
                                }
                            }
                            if(item_found == false){
                            cout << "You don't have any gunpowder!" << endl;
                            break;
                            }
                            changeHp(5);
                            changeMaxHp(10);
                            changeXp(5);

                            break;
                        }
                    }

            case 4:
                num_items = getResourceAmount("SPIDER EYE");
                    if(num_items < 1){
                        cout << "Unable to make trade. You do not have a Spider eye." << endl;
                        break;
                    }
                    else{
                        for(int i = 0; i < items_.size(); i++){
                            if(items_[i].getItemName() == "DIAMOND HELMET"){
                                cout << "You already have Diamond helmet!" << endl;
                                item_found = true;
                                break;
                            }
                        }
                        if(item_found == false){
                            cout << "Succesfully traded Spider Eye for a Diamond Helmet!" << endl;
                            addItem(Item("DIAMOND HELMET", 0, 10, false, false));
                            for(int i = 0; i < inventory_.size(); i++){
                                if(inventory_[i].getName() == "SPIDER EYE"){
                                    item_found = true;
                                    inventory_[i].increaseAmount(-1);
                                    if(inventory_[i].getAmount() == 0){
                                    inventory_.erase(inventory_.begin()+i);
                                    }
                                }
                            }
                            if(item_found == false){
                            cout << "You don't have any Spider eyes!" << endl;
                            break;
                            }
                            changeHp(5);
                            changeMaxHp(10);
                            changeXp(5);

                            break;
                        }
                    }

            case 5:
                cout << "EXITING TRADING MENU!" << endl;
                return;
        }
    }while(trade_choice!=5);
    return;
}

/*
 1. Decreases food resource in inventory by 1
 2. Increases HP by 2
*/
void Minecraft::YOMPNOMPNOMNOM() {
    string input_string;
    int count = 1;
    int food_choice;
    string food_name;
    vector<string> names;
    cout << "Select which food you would like to consume: " << endl;
    for(int i = 0; i < inventory_.size(); i++){
        if(inventory_[i].getName()=="FOOD" || inventory_[i].getName()=="LAMBCHOP" || inventory_[i].getName()=="STEAK"|| inventory_[i].getName()=="CHICKEN"){
            cout << count << ". " << inventory_[i].getName() << endl;
            names.push_back(inventory_[i].getName());
            count++;
        }
    }

    if(count == 1){
        cout << "You don't have any food." << endl;
        cout << " " << endl;
    }else{

        cin >> input_string;
        food_choice = input_string[0]- '0';
       
        if(food_choice < 1 || food_choice > count){
            cout <<"Invalid Choice!" << endl;
            }else{
            food_name = names[food_choice-1];
         }

        if(getHp() >= getMaxHp()){
            cout << "Your health is already full!" << endl;
            cout << " " << endl;
            return;
        }
        else if(getHp()+2 <= getMaxHp()){
            changeHp(2);
            changeXp(2);
            cout << "You're HP and XP both went up by 2!" << endl;
            for(int i = 0; i < inventory_.size(); i++){
                if(inventory_[i].getName()== food_name){
                    inventory_[i].increaseAmount(-1);
                    if(inventory_[i].getAmount() == 0){
                        inventory_.erase(inventory_.begin()+ i);
                    }
                }
            }
            return;
        }
        else{
            changeHp(getMaxHp()-getHp());
            changeXp(2);
            cout << "You're HP and XP both went up by 2!" << endl;
            for(int i = 0; i < inventory_.size(); i++){
                if(inventory_[i].getName()== food_name){
                    inventory_[i].increaseAmount(-1);
                    if(inventory_[i].getAmount() == 0){
                        inventory_.erase(inventory_.begin()+ i);
                    }
                }
            }
            return;
        }
    }
    return;
} 

/*
 1. only applicable if user has axe and is next to a wood block
 2. if requirements met: add wood resource to inventory or increment it, and decrease durability on axe
 3. if axe durability is 0, remove it from items list
*/
void Minecraft::wackwackwack() {
    string input_string;
    int item_choice;
    int coords[2];
    int count = 1;
    cout << "Which Item would you like to use to chop?" << endl;

    for(int i = 0; i < items_.size(); i++){
        if(items_[i].getCanChop()){
        cout << count << ". " << items_[i].getItemName()<< endl;
        count++;
        }
    }

    if(count == 1){
        cout << "You don't have an AXE! Can't chop." << endl;
        cout << " " << endl;
        return;
    }


    do{
        cin >> input_string;
        item_choice = input_string[0]- '0';

        if(item_choice < 1 || item_choice >= count){
            cout << "Invalid option!" << endl;
        }
    }while(item_choice < 1|| item_choice >=count);
    
    if(map_.isNextToTree()){
        if(items_[item_choice-1].getCanChop()){
            cout << "You got 2 wood!" << endl;
            addResource("WOOD", 2);
            changeXp(2);
        } 

        if (map_.isTreeLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
            coords[0] = map_.getPlayerRow()+1;
            coords[1] = map_.getPlayerCol();
        }
        if(map_.isTreeLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
            coords[0] = map_.getPlayerRow()-1;
            coords[1] = map_.getPlayerCol();
        }
        if (map_.isTreeLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
            coords[0] = map_.getPlayerRow();
            coords[1] = map_.getPlayerCol()+1;
        }
        if(map_.isTreeLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
            coords[0] = map_.getPlayerRow();
            coords[1] = map_.getPlayerCol()-1;
        }
        map_.removeTree(coords[0],coords[1]);
    }
    return;
} 

/*
 1. only applicable if user has a pickaxe 
 2. add the mined object to inventory
 3. if pickaxe health is 0, remove it from items list
*/
void Minecraft::bonkbonkbonk(){
    string input_string;
    int item_choice;
    int coords[2];
    int count = 1;
    cout << "Which Item would you like to use to mine?" << endl;

    for(int i = 0; i < items_.size(); i++){
        if(items_[i].getCanMine()){
        cout << count << ". " << items_[i].getItemName()<< endl;
        count++;
        }
    }

    if(count == 1){
        cout << "You don't have a PICKAXE! Can't mine." << endl;
        cout << " " << endl;
        return;
    }

    do{
        cin >> input_string;
        item_choice = input_string[0]- '0';

        if(item_choice < 1 || item_choice >= count){
            cout << "Invalid option!" << endl;
        }
    }while(item_choice < 1|| item_choice >=count);

    
    if(map_.isNextToIron()){
            cout <<"You got 1 IRON ORE!" << endl;
            addResource("IRON", 1);
            changeXp(2);

            if (map_.isIronLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
                coords[0] = map_.getPlayerRow()+1;
                coords[1] = map_.getPlayerCol();
            }
            if(map_.isIronLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
                coords[0] = map_.getPlayerRow()-1;
                coords[1] = map_.getPlayerCol();
            }
            if (map_.isIronLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
                coords[0] = map_.getPlayerRow();
                coords[1] = map_.getPlayerCol()+1;
            }
            if(map_.isIronLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
                coords[0] = map_.getPlayerRow();
                coords[1] = map_.getPlayerCol()-1;
            }
            map_.removeIron(coords[0],coords[1]);
            return;
    }
    else if(map_.isNextToGold()){
            cout << "You got 1 GOLD ORE!" << endl;
            addResource("GOLD", 1);
            changeXp(5);
            if (map_.isGoldLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
            coords[0] = map_.getPlayerRow()+1;
            coords[1] = map_.getPlayerCol();
            }
            if(map_.isGoldLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
                coords[0] = map_.getPlayerRow()-1;
                coords[1] = map_.getPlayerCol();
            }
            if (map_.isGoldLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
                coords[0] = map_.getPlayerRow();
                coords[1] = map_.getPlayerCol()+1;
            }
            if(map_.isGoldLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
                coords[0] = map_.getPlayerRow();
                coords[1] = map_.getPlayerCol()-1;
            }
            map_.removeGold(coords[0],coords[1]);
            return;

    }
    else if(map_.isNextToDiamond()){
            cout << "You got 1 DIAMOND ORE!" << endl;
            addResource("DIAMOND", 1);
            changeXp(10);
            if (map_.isDiamondLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
            coords[0] = map_.getPlayerRow()+1;
            coords[1] = map_.getPlayerCol();
            }
            if(map_.isDiamondLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
                coords[0] = map_.getPlayerRow()-1;
                coords[1] = map_.getPlayerCol();
            }
            if (map_.isDiamondLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
                coords[0] = map_.getPlayerRow();
                coords[1] = map_.getPlayerCol()+1;
            }
            if(map_.isDiamondLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
                coords[0] = map_.getPlayerRow();
                coords[1] = map_.getPlayerCol()-1;
            }
            map_.removeDiamond(coords[0],coords[1]);
            return;
    }
}

/*
1. If user is next to an animal, allows option to harm animal
2. Searches through and see if they have sword
3. Randomly generates what kind of mob type it is
4. If they harm animal, they get food added to their inventory
*/
void Minecraft::harmAnimal(){
    Resources animal_drop;

    srand(time(0));
    int random_animal = randomNum(1,3); //randomly selects an animal mob
    if(random_animal == 1){
        cout << "INFORMATION ABOUT ANIMAL:" << endl << "NAME: SHEEP" << endl <<"ANIMAL DROP: LAMBCHOP (heals 2 HP)" <<endl;
        animal_drop = Resources("LAMBCHOP", 2);
    } else if(random_animal == 2){
        cout << "INFORMATION ABOUT ANIMAL:" << endl << "NAME: COW" << endl <<"ANIMAL DROP: STEAK (heals 2 HP)" <<endl;
        animal_drop = Resources("STEAK", 2);
    } else if(random_animal ==3){
        cout << "INFORMATION ABOUT ANIMAL:" << endl << "NAME: CHICKEN" << endl <<"ANIMAL DROP: CHICKEN (heals 1 HP)" <<endl;
        animal_drop = Resources("CHICKEN", 2);
    }
    string input_string;
    int item_choice;
    int coords[2];
    int count = 1;
    bool have_sword = true;
    string name;
    cout << "Which Item would you like to use to gently harm the animal?" << endl;
    //check for sword in inventory
    for(int i = 0; i < items_.size(); i++){
        for(int j = 0; j<items_[i].getItemName().length(); j++){
            name = items_[i].getItemName().substr(j,5);
            if( name == "SWORD"){
                cout << count << ". " << items_[i].getItemName()<< endl;
                count++;
            }
        }
    }

    if (count == 1) {
        have_sword = false;
    }
    if(!have_sword) {
        cout << "You don't have a sword. Cannot harm animal!" << endl;
        cout << " " << endl;
        return;
    }

    do{
        cin >> input_string;
        item_choice = input_string[0]- '0';

        if(item_choice < 1 || item_choice >= count){
            cout << "Invalid option!" << endl;
        }
    }while(item_choice < 1|| item_choice >=count);
    
    if(map_.isNextToAnimal()){
        cout << "You got 2 " << animal_drop.getName()<< endl;
        addResource(animal_drop.getName(), animal_drop.getAmount());

        if (map_.isAnimalLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
            coords[0] = map_.getPlayerRow()+1;
            coords[1] = map_.getPlayerCol();
        }
        if(map_.isAnimalLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
            coords[0] = map_.getPlayerRow()-1;
            coords[1] = map_.getPlayerCol();
        }
        if (map_.isAnimalLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
            coords[0] = map_.getPlayerRow();
            coords[1] = map_.getPlayerCol()+1;
        }
        if(map_.isAnimalLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
            coords[0] = map_.getPlayerRow();
            coords[1] = map_.getPlayerCol()-1;
        }
        map_.removeAnimal(coords[0],coords[1]);
    }
    return;
}

/*
 1. pulls up a menu for choice to respawn or quit the game
 2. if respawn, then creates another minecraft object and restarts the game
 3. if quit, then end the program
 4. shows their game stats
*/
int Minecraft::playerIsDead() {
    if(health_points_ <= 0 && ender_dragon_.getMobHealth()>=0){
        cout << "1. Respawn" << endl;
        cout << "2. Exit Game" << endl;
        int dead_choice;
        do{
            cin >> dead_choice;
            if(dead_choice != 1 && dead_choice != 2){
                cout <<"That is not a valid option. Please select 1 or 2." << endl;
            }
        }while(dead_choice != 1 && dead_choice != 2);
        string username;
        switch(dead_choice){
            case 1:
                return 4;
                break; //all i changed was trading, bonkbonkbonk, wackwackwack, and playerIsDead
            case 2: 
                cout <<"Thanks for playing Minecraft!" << endl;
                return 3;
                break;
        } 
        return 3;
    }else if(health_points_ >=0 && ender_dragon_.getMobHealth()<=0){
        cout << "1. Respawn" << endl;
        cout << "2. Exit Game: See player rankings!" << endl;
        int alive_choice;
        do{
            cin >> alive_choice;
            if(alive_choice != 1 && alive_choice != 2){
                cout <<"That is not a valid option. Please select 1 or 2." << endl;
            }
        }while(alive_choice != 1 && alive_choice != 2);
        switch(alive_choice){
            case 1:
                return 4;
                break; //all i changed was trading, bonkbonkbonk, wackwackwack, and playerIsDead
            case 2: 
                cout <<"Thanks for playing Minecraft!" << endl;
                return 5;
                break;
        } 
        return 3;
    }
return 3;
    

}


void Minecraft::playerRankings(){
    cout << "CONGRATS! YOU BEAT THE GAME! " << endl;

    ifstream file;
    file.open("player_ranks");
    if(file.fail()){
        cout <<"Sorry, ranking file failed to open." << endl;
        return;
    }else{
        string line = "";
        //array for split function
        vector<string> usernames{}; //to hold all usernames
        vector<int> xp_scores{}; //to hold all xp's
        vector<string> sorted_usernames{}; 
        vector<int> sorted_xp_scores{};
        while(getline(file, line)){ //read in each line, goal is put all usernames and xp's into seperate vectors
            string temp[2];
            int count = 0;
            if(line != ""){ 
                for(int i = 0; i < line.length(); i++){ //small split function 
                    if(line[i] == '|'){
                        count++;
                    }else{
                        temp[count] += line[i];
                    }
                }
            }
            //add the usernames and xp_scores to correpsonding vectors
            usernames.push_back(temp[0]);
            xp_scores.push_back(stoi(temp[1]));
        }
        file.close();
        string name = getUsername();
        int player_xp = getXp();
        usernames.push_back(name); //adds the current player's stats
        xp_scores.push_back(player_xp);
                
        //sorting the xp
        int min_index = 0;
        for(int i = 0; i < xp_scores.size(); i++){
            int min = xp_scores[i];
            min_index = i;
            for(int k = 0; k < xp_scores.size(); k++){
                if(xp_scores[k] < min){
                    min = xp_scores[k];
                    min_index = k;
                }
            }
            sorted_xp_scores.push_back(xp_scores[min_index]);
            sorted_usernames.push_back(usernames[min_index]);
            xp_scores[min_index] = 100000;
        }
        //deletes all content from file, then rewrites with newly sorted players
        ofstream write_to_file;
        write_to_file.open("player_ranks", std::ofstream::out | std::ios::trunc);
        for(int i = 0; i < xp_scores.size(); i++){
            cout << sorted_usernames[i] << "|" << sorted_xp_scores[i] << endl;
            write_to_file << sorted_usernames[i] << "|" << sorted_xp_scores[i] << "\n";
        }
        return;
    }
    return;
}


/*
1. check for items //if no items are detected, end function // if true, generate random number between 0-3, 
//index of mobs<vector>, this chooses which mob to fight
//while loop that depends on hp of mob and hp of player or if player chooses to quit
2. pull up a menu of items that can be used to fight, or to quit
3. cout what mob player is fighting
4. mob hits first, check for if player is dead
5. display hp stats
6. check for bool playerQuit
//loop ends
//**rng for mob drop
//cout "you got" << mob.getDropName
*/

void Minecraft::fighting() {
    vector <Item> weapons;
    int coords[2];
    int choice;
    bool weaponsFound;
    bool valid = true;
    bool playerHasNotQuit = true;
    //generate random number 0-3 for mob type
    int randomMob = randomNum(0, 3);
    Mob fight = mobs_[randomMob];
    
    cout << "You are fighting a " << fight.getMobName() << endl;
    //find weapons
    for (int i = 0; i < items_.size(); i++) {
        if (items_[i].getDamage() > 0) {
            weapons.push_back(items_[i]);
        }
    }
        
        do {
            cout << fight.getMobName() << " just hit you for " << fight.getMobDamage() << " damage!" << endl;
            health_points_ -= fight.getMobDamage();
            cout << "PLAYER HP: " << health_points_ << endl;
            cout << "MOB HP: " << fight.getMobHealth() << endl;
            if (health_points_ <= 0) {
                return;
            }


            //printing menu
            cout << "Choose an item to fight with: " << endl;
            do {
                for (int i = 0; i < weapons.size(); i++)  {
                cout << i + 1 << ". " << weapons[i].getItemName() << " [" << weapons[i].getDamage() << " damage]" << endl;
                //choose item menu, show damage stats
                }

                cout << weapons.size() + 1 << ". Quit fighting" << endl;
                cin >> choice;
                if (choice < 1 || choice > weapons.size() + 1) {
                    cout << "Invalid input, choose a number between 1 and " << weapons.size() + 1 << endl;
                    valid = false;
                }
                else {
                    valid = true;
                }
            }
            while (!valid);
            //check for quit
            if (choice == weapons.size() + 1) {

                return;
            }
            //fighting 
            fight.setMobHealth(fight.getMobHealth() - weapons[choice - 1].getDamage());
            cout << "You just hit "  << fight.getMobName() << " for " << weapons[choice - 1].getDamage() << " damage!" << endl;
            cout << "PLAYER HP: " << health_points_ << endl;
            cout << "MOB HP: " << fight.getMobHealth() << endl;
            if (fight.getMobHealth() <= 0) {
                
                if (map_.isMobLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
                    coords[0] = map_.getPlayerRow()+1;
                    coords[1] = map_.getPlayerCol();
                }
                if(map_.isMobLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
                    coords[0] = map_.getPlayerRow()-1;
                    coords[1] = map_.getPlayerCol();
                }
                if (map_.isMobLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
                    coords[0] = map_.getPlayerRow();
                    coords[1] = map_.getPlayerCol()+1;
                }
                if(map_.isMobLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
                    coords[0] = map_.getPlayerRow();
                    coords[1] = map_.getPlayerCol()-1;
                }
                //cout << coords[0] << " " << coords[1]<< endl;
                map_.removeMob(coords[0],coords[1]);
                cout << "You got 10 XP." << endl;
                xp_ += 10;
                mobs_killed_++;
                //rng
                double randPerc = randomPercent();

                if (randPerc <= 0.70) {
                    cout << "You got " << fight.getMobDrop().getName() << "." << endl;
                    addResource(fight.getMobDrop().getName(), 1);
                }
                else {
                    cout << "You killed " << fight.getMobName() << "." << endl;
                }
                return;
            }

            //remember to include percentage of mob drop rng
            //remember to increase mobs_killed_ and xp_
            //player quit option
    
        }
        while(fight.getMobHealth() > 0 && playerHasNotQuit);
    return;
}


void Minecraft::dragon() {
    vector <Item> weapons;
    int coords[2];
    int choice;
    bool weaponsFound;
    bool valid = true;
    bool playerHasNotQuit = true;
        
    cout << "You are fighting THE ENDER DRAGON!!!!" << endl;
    //find weapons
    for (int i = 0; i < items_.size(); i++) {
        if (items_[i].getDamage() > 0) {
            weapons.push_back(items_[i]);
        }
    }
        
        do {
            cout << "The ENDER DRAGON just hit you for " << ender_dragon_.getMobDamage() << " damage!" << endl;
            health_points_ -= ender_dragon_.getMobDamage();
            cout << "PLAYER HP: " << health_points_ << endl;
            cout << "MOB HP: " << ender_dragon_.getMobHealth() << endl;
            if (health_points_ <= 0) {
                cout << "You died!" << endl;
                return;
            }


            //printing menu
            cout << "Choose an item to fight with: " << endl;
            do {
                for (int i = 0; i < weapons.size(); i++)  {
                cout << i + 1 << ". " << weapons[i].getItemName() << " [" << weapons[i].getDamage() << " damage]" << endl;
                //choose item menu, show damage stats
                }

                cout << weapons.size() + 1 << ". Quit fighting" << endl;
                cin >> choice;
                if (choice < 1 || choice > weapons.size() + 1) {
                    cout << "Invalid input, choose a number between 1 and " << weapons.size() + 1<< endl;
                    valid = false;
                }
                else {
                    valid = true;
                }
            }
            while (!valid);
            //check for quit
            if (choice == weapons.size() + 1) {

                return;
            }
            //fighting 
            ender_dragon_.setMobHealth(ender_dragon_.getMobHealth() - weapons[choice - 1].getDamage());
            cout << "You just hit the ENDER DRAGON for " << weapons[choice - 1].getDamage() << " damage!" << endl;
            cout << "PLAYER HP: " << health_points_ << endl;
            cout << "MOB HP: " << ender_dragon_.getMobHealth() << endl;
            if (ender_dragon_.getMobHealth() <= 0) {
                
                if (map_.isMobLocation(map_.getPlayerRow() + 1, map_.getPlayerCol())) {
                    coords[0] = map_.getPlayerRow()+1;
                    coords[1] = map_.getPlayerCol();
                }
                if(map_.isMobLocation(map_.getPlayerRow() - 1, map_.getPlayerCol())){
                    coords[0] = map_.getPlayerRow()-1;
                    coords[1] = map_.getPlayerCol();
                }
                if (map_.isMobLocation(map_.getPlayerRow(), map_.getPlayerCol() + 1)) {
                    coords[0] = map_.getPlayerRow();
                    coords[1] = map_.getPlayerCol()+1;
                }
                if(map_.isMobLocation(map_.getPlayerRow(), map_.getPlayerCol() - 1)){
                    coords[0] = map_.getPlayerRow();
                    coords[1] = map_.getPlayerCol()-1;
                }
                map_.removeMob(coords[0],coords[1]);
                cout << "YOU HAVE DEFEATED THE ENDER DRAGON!" << endl;
                mobs_killed_++;
            }

            //remember to include percentage of mob drop rng
            //remember to increase mobs_killed_ and xp_
            //player quit option
    
        }
        while(ender_dragon_.getMobHealth() > 0 && playerHasNotQuit);
    return;
}



    

//getters and setters
    void Minecraft::setUsername(string username) {
        username_ = username;
    } 

    string Minecraft::getUsername() const {
        return username_;
    }

    void Minecraft::changeHp(int changeHpBy) {
        health_points_ += changeHpBy;
    }

    int Minecraft::getHp() const {
        return health_points_;
    }

    void Minecraft::changeMaxHp(int changeHpBy){
        max_hp_ += changeHpBy;
    }

    int Minecraft::getMaxHp() const{
        return max_hp_;
    }

    void Minecraft::changeXp(int changeXpBy) {
        xp_ += changeXpBy;
    }

    int Minecraft::getXp() const {
        return xp_;
    }

    void Minecraft::changeMobsKills(int changeMKby) {
        mobs_killed_ += changeMKby;
    }

    int Minecraft::getMobsKilled() const {
        return mobs_killed_;
    }

    //array getters/setters
    Mob Minecraft::getMob(string mob_name) {
        for(int i = 0; i < mobs_.size(); i++){
            if(mobs_[i].getMobName() == mob_name){
                return mobs_[i];
            }
        }
        return Mob();
    }

    int Minecraft::getResourceAmount(string resource_name) const {
        for(int i = 0; i < inventory_.size(); i++){
            if(inventory_[i].getName() == resource_name){
                return inventory_[i].getAmount();
            }
        }
        return 0;
    }

    void Minecraft::addResource(string resource_name, int resource_amount){
        bool resource_found = false; 
        for(int i = 0; i < inventory_.size(); i++){ //checks if resource is already in the inventory: if it is, just increment the amount
            if(inventory_[i].getName() == resource_name){
                resource_found == true;
                inventory_[i].increaseAmount(resource_amount);
                return;
            }
        }

        if(resource_found == false){ //if resource is not in inventory, add a new resource to it
            Resources new_resource = Resources(resource_name, resource_amount);
            inventory_.push_back(new_resource);
            return;
        }   
    }

    void Minecraft::removeResource(){
        for(int i = 0; i < inventory_.size(); i++){
            if(inventory_[i].getAmount() == 0){
                inventory_.erase(inventory_.begin() + i);
                i--;
            }
        }
        return;
    }

    bool Minecraft::isInInventory(string resource_name){
        bool is_in_inventory = false;
        for(int i = 0; i < inventory_.size(); i++){
            if(inventory_[i].getName()== resource_name){
                is_in_inventory = true;
            }
        }
        return is_in_inventory;
    }


    
    Item Minecraft::getItem(string item_name) const {
       for(int i = 0; i < items_.size(); i++){
            if(items_[i].getItemName()==item_name){
                return items_[i];
            }
       }
       return Item();
    }

    void Minecraft::addItem(Item item) {
        items_.push_back(item);
        return;
    }

    int Minecraft::randomNum (int min, int max) {
        return (rand() % (max - min + 1)) + min;
    }

    Map Minecraft::getMap() const {
            return map_;
    }

    double Minecraft::randomPercent() {
        return (double)rand() / RAND_MAX;
    }


