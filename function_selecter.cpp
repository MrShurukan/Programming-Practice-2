#include <iostream>
#include "function_selecter.h"
#include "tasks.h"

void def() {
    std::cout << "Этот таск ещё не определён.\n";
}

voidptr pickTask(int number) {
    switch (number) {
    case 31: return task31;
    case 32: return task32;
    case 33: return task33;

    default:
        return def;
    }
}
