#pragma once
#include<random>

class RNG{
    private:
        std::mt19937 SpawnRNG;
    public:
        RNG();
        int uniformInt(int min,int max);
        bool chance(float prob);
        std::mt19937& engine();
};
