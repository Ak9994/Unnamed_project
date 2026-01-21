#include "include/RNG.h"

RNG::RNG():spawn(std::random_device rd){ }

int RNG::UniformDistribution(int l,int h){
    std::uniform_int_distribution<int> d(l,h);
    return dist(spawn);
}

bool RNG:chance(float prob){
    if(prob >= 1.0) return true;
    if(prob <= 0.0) return false;
    std::bernoulli_distribution d(prob);
    return d(spawn);
}

std::mt19937 RNG:engine(){
    return spawn;
}