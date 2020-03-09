#include <iostream>

/**** Task 31 ****/
#define HSIZE 27

std::string maze[25] = {
"####B######################",
"# #       #   #      #    #",
"# # # ###### #### ####### #",
"# # # #       #   #       #",
"#   # # ######### # ##### #",
"# # # #   #       #     # #",
"### ### ### ############# #",
"# #   #     # #           #",
"# # #   ####### ###########",
"# # # #       # #         C",
"# # ##### ### # # ####### #",
"# # #     ### # #       # #",
"#   ##### ### # ######### #",
"######### ### #           #",
"# ####### ### #############",
"A           #   ###   #   #",
"# ############# ### # # # #",
"# ###       # # ### # # # #",
"# ######### # # ### # # # F",
"#       ### # #     # # # #",
"# ######### # ##### # # # #",
"# #######   #       #   # #",
"# ####### ######### #######",
"#         #########       #",
"#######E############D######"
};

void printMaze(int X, int Y) {
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < HSIZE; x++) {
            if (x == X && y == Y) std::cout << "@";
            else std::cout << maze[y][x];
        }
        std::cout << '\n';
    }

    std::cout << "\n\n";
}

/*enum StepDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    START
};*/

bool atLeastOneExit = false;
void step(int x, int y) {
    if (x < 0 || y < 0 ||
        x >= HSIZE || y >= 25 ||
        maze[y][x] == '#')
    {
        return;
    }

    /*printMaze(x, y);
    std::cin.get();*/

    char c = maze[y][x];

    // Наступили на выход
    if (c != ' ') {
        std::cout << c << ' ';
        atLeastOneExit = true;
    }

    maze[y][x] = '#';

    // Двигаемся дальше, только если не пришли из этой клетки
    step(x+1, y);
    step(x-1, y);
    step(x, y+1);
    step(x, y-1);
}

void task31() {
    int x, y;
    std::cin >> x >> y;

    if (x < 0 || y < 0 ||
        x >= HSIZE || y >= 25 ||
        maze[y][x] == '#')
    {
        std::cout << "Неверные координаты\n";
        return;
    }

    step(x, y);
    if (!atLeastOneExit) std::cout << "Выхода нет";

    std::cout << '\n';
}








/**** Task 32 ****/
#include <stack>
#include <map>
#include <sstream>
#include <vector>

enum Priority {
    LOWEST,
    LOW,
    MEDIUM,
    HIGH,
};

std::map<char, Priority> priority {
    {'^', HIGH},
    {'*', MEDIUM},
    {'/', MEDIUM},
    {'+', LOW},
    {'-', LOW},
    {'(', LOWEST},
    {')', LOWEST},
};

bool isNumber(char c) {
    return (c >= '0' && c <= '9') || (c == '.');
}

void task32() {
    std::stack<char> stack;
    std::string input, output;

    std::getline(std::cin, input);
    input += " ";

    bool isReadingNumber = false;
    std::string number;
    for (std::size_t i = 0; i < input.length(); i++) {
        char c = input[i];

        if (isNumber(c)) {
            output += c;
        }
        else if (c == '(') stack.push(c);
        else if (c == ')') {
            while (stack.top() != '(') {
                output += stack.top();
                stack.pop();
            }
        }
        else if (c == ' ')
            continue;
        // Операция
        else {

        }
    }
}
