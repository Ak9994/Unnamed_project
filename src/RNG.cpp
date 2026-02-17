#include "include/RNG.h"

RNG::RNG():SpawnRNG(std::random_device{}()){ }

int RNG::uniformInt(int l,int h){
    std::uniform_int_distribution<int> dist(l,h);
    return dist(SpawnRNG);
}

bool RNG::chance(float prob){
    if(prob >= 1.0) return true;
    if(prob <= 0.0) return false;
    std::bernoulli_distribution dist(prob);
    return dist(SpawnRNG);
}

std::mt19937& RNG::engine(){
    return SpawnRNG;
}
