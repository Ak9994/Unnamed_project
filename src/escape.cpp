#pragma once
#include "include/Escape.h"
#include <iostream>
#include <algorithm>
#include <optional>
#include <vector>

Escape::Escape(GameConfig& config):cfg(config){
    //Levels
    for(int i=0;i<6;i++){
        Level_remaining.push_back(i);
    }
    Start_Level = rng.UniformDistribution(1,6);
    //Start at level Generated
    auto Current_level = std::find(Level_remaining.begin(),Level_remaining.end(),Start_Level);
    //Swap the start
    if(Current_level != Level_remaining.end()){
        std::iter_swap(Current_level,Level_remaining.begin());
    }
};

void Escape::GameLoop(){
    GameOutcome outcome = GameOutcome::None;
    GameState loopstate;
    //Set age
    loopstate.age = cfg.start_age;
    //Starting information
    std::cout << " Dimensional Escape , plan your escape before time limit \n";
    std::cout << "Starting Hub: \n"
              << "Age->" << loopstate.age << "\n"
              << "Hour->" << loopstate.time << "\n"
              << "Time Left to escape->" << cfg.GameEnd_TimeLimit << "\n";
    //Level Display
    std::cout << "Levels to clear: 6 | Exit spawn per level: "
              << cfg.ExitSpawn_Count << "\n";

    while((outcome == GameOutcome::None) && (!Level_remaining.empty())){
        int currlevel = PickNextLevel();
        std::cout << "Entering Level: " << currlevel << "\n";

        //Select exit
        outcome = Escape::Select_exit(currlevel,loopstate);

        //Level Clear
        if(levels_cleared){
            RemoveLevel(currlevel);
            loopstate.levels_cleared++;
            
            std::cout << "Level " << currlevel << " cleared. Levels cleared so far: "
                      << loopstate.levels_cleared << "\n";
        }

        //Result of Selecting exit
        // On Success
        if((outcome == GameOutcome::None) && (loopstate.age <= cfg.max_age) 
           && (loopstate.time <= cfg.Level_TimeLimit) && loopstate.levels_cleared == 6){
            std::cout << " Success: Cleared all 6 levels within limits.\n";
            outcome = GameOutcome::Success;
           }
        //On fail
        if((outcome == GameOutcome::None) && (loopstate.age == cfg.max_age) 
           && (loopstate.time == cfg.GameEnd_TimeLimit)){
            std::cout << " Age == Max_Age AND Hour == GameEndlimit.\n";
            outcome = GameOutcome::Fail;
           }

        //Display Outcome
        std::cout << "\n Game Over \n";
        std::cout << "Final Age: " << loopstate.age 
                  << ", Final Hour: " << loopstate.time
                  << ", Levels Cleared: " << loopstate.levels_cleared << "\n";
        if(outcome == GameOutcome::Success){ std::cout << " Escaped the dimension!\n"; }
        else if(outcome == GameOutcome::Fail){ std::cout << " Failed to escape the dimension!\n"; }
        else { std::cout << "Ongoing Loop!\n";}
    }
};

int Escape::PickNextLevel(){
    if(level_iter){
        level_iter = false;
        //Display Current Level
        std::cout << "the current level is" << Start_Level << "\n";
    }
    //Check remaining levels to see if final stage or not
    if(Level_remaining.size() == 1){ return Level_remaining.front(); }
    //Shuffle the levels
    std::Shuffle(
                Level_remaining.begin()+1,
                Level_remaining.end(),
                rng.rand(),
                );
    return Level_remaining.front();
};

void Escape::RemoveLevel(int lvl){
    auto level = std::find(Level_remaining.begin(),Level_remaining.end(),lvl);
        if (level != Level_remaining.end()) Level_remaining.erase(level);
        levels_cleared = false; // reset flag
};

GameOutcome Escape::Select_exit(int LID,GameState& SID){
    levels_cleared = false;
    GameOutcome exit_outcome = GameOutcome::None;
    //Exit variable
    int CorrectExit = rng.UniformDistribution(1,cfg.ExitSpawn_Count);
    std::cout << "Level:" << LID
              << "has spawned:" << cfg.ExitSpawn_Count
              << "exits , Only one correct exit exists \n";
    //Selection_Loop
    for( int sel_exit = 0; sel_exit <= cfg.ExitSpawn_Count; sel_exit++){
        //Take player Input
        std::string choice;
        bool select = false;
        //Temp storage for selection
        std::optional<int> Temp_exit;
        int input = std::stoi(choice);

        if(cfg.Idleplay){
            
            std::cout << " Attempt no: " << sel_exit
                        << " Choose exit: 1-" << cfg.ExitSpawn_Count
                        << ") or 'N' for no choice: ";
        
            std::getline(std::cin,choice);

            if(choice.empty()){ select = true; }
            else if((choice == "N") || (choice == "n")){ select = true; }
            else{
                try {
                        if((input >= 1) && (input <= cfg.ExitSpawn_Count)){
                        Temp_exit = input;
                    } else {
                    //invalidate Choice
                        std::cout << "Invalid input & counting as wrong choice.\n";
                        Temp_exit = -1; }
                } catch (...){
                //invalidate Choice
                    std::cout << "Invalid input & counting as wrong choice.\n";
                    Temp_exit = -1; }
            } 
        }
        else {
            //Testing Auto Input
            select = rng.chance(cfg.CorrectSelectionProb);
            if(!input) { Temp_exit = rng.UniformDistribution(1,cfg.ExitSpawn_Count); }
            std::cout << " Attempt no: " << sel_exit << "\n";
            if(select){ std::cout << "No Choice Made \n";}
            else if(Temp_exit.has_value()){ std::cout << "Picked exit " << sel_exit << "\n";}
            else { std::cout << "Picked exit <none>\n"; }
        }
    } };

