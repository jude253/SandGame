#pragma once
#include <iostream>
#include <random>


/**
 * Not sure how to not have this in the header file right now.
 * 
 * This is inclusive of the endpoints.  Based on this stackoverflow post:
 * 
 * https://stackoverflow.com/a/20136256
 * 
 * Not sure if I need to reseed the random_device every time or just at
 * beginning of program.
 */
template<typename T>
T randomIntInRange(T range_from, T range_to) {
    std::random_device                 rand_dev;
    std::mt19937                       generator(rand_dev());
    std::uniform_int_distribution<int> distr(range_from, range_to);
    return distr(generator);
}