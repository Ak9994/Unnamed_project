#pragma once
#include<random>

class RNG{
    private:
        std::mt19937 spawn;
    public:
        RNG();
        int UniformDistribution(int min,int max);
        bool chance(float prob);
        std::mt19937 engine();
};