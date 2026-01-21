#pragma once

struct GameConfig{
    //player stats
    int start_age = 20;
    int max_age = 100;
    //Time Constraints in hrs
    int GameEnd_TimeLimit = 5;
    int Level_TimeLimit = 1;
    //Exit Generation : generate an exit for every 12 min per level which has time limit of 1 hr
    int ExitSpawn_Count = 5;
    //initialize auto select exit for testing code
    bool Idleplay = false;
    float CorrectSelectionProb = 0.02;
};