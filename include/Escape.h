#pragma once
#include<vector>
#include<string>
#include"GameConfig.h"
#include"RNG.h"

struct GameState{
    int age;
    int time;
    int levels_cleared;
};

enum GameOutcome{
    Success,
    Fail,
    None
};

class Escape{
    private:
        GameConfig cfg;
        RNG rng;
        //Level Variables
        std::vector<int> Level_remaining;
        int Start_Level;
        bool levels_cleared = false;
        bool level_iteration = true;
    public:
        Escape(GameConfig& config);
        void GameLoop();
        int PickNextLevel();
        void RemoveLevel(int lvl);
        GameOutcome Select_exit(int Level,GameState& state);
        GameOutcome end_loop(int level,GameState& state);
};
