#include <iostream>
#include "function_selecter.h"

int main() {
    setlocale(LC_ALL, "Russian");

    int taskN = -1;
    while (true) {
        std::cout << "Номер задания: ";
        std::cin >> taskN;

        if (taskN <= 0) break;
        pickTask(taskN) ();
    }

    return 0;
}