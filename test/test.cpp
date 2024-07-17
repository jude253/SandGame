#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <iostream>
#include <random>

void printfExamples() {
    int a = 120;
    int b = 65;
    float float_a_b = (float)a/b;
    double double_a_b = (double)a/b;
    float double_to_float_a_b = (float)double_a_b;
    
    printf("a/b=%lf\n", ((double)a/b));
    printf("Precision int: %.*d\n", 5, 10);
    printf("Precision int: %.5d\n", 10);
    printf("Precision int: %.5d\n", 1234567);


    // I can't remember exactly why the float isn't just truncated at a
    // shorter amount than the double, but I believe it has to do with
    // how floats and doubles are stored in memory as binary not decimal.
    printf("Precision double: %.60f\n", (double)1234567);
    printf("Precision float_a_b: %.60f\n", float_a_b);
    printf("Precision double_a_b: %.60f\n", double_a_b);
    printf("Precision double_to_float_a_b: %.60f\n", double_to_float_a_b);

    // Prints whatever happened to be in that location of memory before:
    float uninitialized_float;
    printf("Uninitialized float: %f\n", uninitialized_float);
}


/**
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


/*
Run with:
gcc test/test.cpp -o test.out && ./test.out
*/
int main() {
    for (int i = 0; i < 100; i++) {
        std::cout << randomIntInRange(1, 5) << '\n';
    }
    
    return 0;
}