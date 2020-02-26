#pragma once

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

enum StepDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    START
};

bool atLeastOneExit = false;
void step(int x, int y, StepDirection dir) {
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

    // Двигаемся дальше, только если не пришли из этой клетки
    if (dir != LEFT) step(x+1, y, RIGHT);
    if (dir != RIGHT) step(x-1, y, LEFT);
    if (dir != DOWN) step(x, y+1, UP);
    if (dir != UP) step(x, y-1, DOWN);
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

    step(x, y, START);
    if (!atLeastOneExit) std::cout << "Выхода нет";

    std::cout << '\n';
}