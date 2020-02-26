#include <iostream>
#include "function_selecter.h"
#include "tasks.h"

void def() {
    std::cout << "Этот таск ещё не определён.\n";   
}

voidptr pickTask(int number) {
    switch (number) {
        case 1: return task1;

        default:
            return def;
    }
}