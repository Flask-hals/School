#include "Time.h"

int main() {

    Time t0 {"23:59:59"};
    Time t1 {};


    //std::cout << t0 << std::endl;
    //t0++;
    //std::cout << t1 << std::endl;
    //std::cout << t0 << std::endl;

    for ( int i {0}; i < 10; i++){
        std::cout << t0 << std::endl;
        t0++;
    }


    return 0;
}