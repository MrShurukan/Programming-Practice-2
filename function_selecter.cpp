#include <iostream>
#include "function_selecter.h"
#include "tasks.h"

void def() {
    std::cout << "���� ���� ��� �� ��������.\n";
}

voidptr pickTask(int number) {
    switch (number) {
        case 31: return task31;

        default:
            return def;
    }
}