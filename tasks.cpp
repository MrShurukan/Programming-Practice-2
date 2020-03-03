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

    // ��������� �� �����
    if (c != ' ') {
        std::cout << c << ' ';
        atLeastOneExit = true;
    }

    // ��������� ������, ������ ���� �� ������ �� ���� ������
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
        std::cout << "�������� ����������\n";
        return;
    }

    step(x, y, START);
    if (!atLeastOneExit) std::cout << "������ ���";

    std::cout << '\n';
}

/**** Task 32 ****/
#include <stack>
#include <map>
#include <sstream>

enum Priority {
    LOW,
    MEDIUM,
    HIGH,
    HIGHEST,
};

std::map<char, Priority> priority {
    {'(', HIGHEST},
    {')', HIGHEST},
    {'^', HIGH},
    {'*', MEDIUM},
    {'/', MEDIUM},
    {'+', LOW},
    {'-', LOW},
};

bool isNumber(char c) {
    return (c >= '0' && c <= '9');
}

void task32() {
    std::stack<char> stack;

    std::string s;
    while (std::cin >> s) {
        if (s == ";") {
            while (!stack.empty()) {
                std::cout << stack.top() << " ";
                stack.pop();
            }

            break;
        }

        // �����-�� �����
        if (s.length() > 1 || isNumber(s[0])) {
            std::cout << s << " ";
        }
        // ��������
        else {
            char c = s[0];

            // ���� ���� ����
            if (stack.empty()) stack.push(c);
            else if (priority[c] > priority[stack.top()]) {
                // ���� ��������� ���� ����������� ���������
                if (c != ')') stack.push(c);
                else {
                    // ���������� � ��������� ��� ������
                    while (!stack.empty() && stack.top() != '(') {
                        std::cout << stack.top() << " ";
                        stack.pop();
                    }

                    // ������� ����������� ������
                    stack.pop();
                }
            }
            else {
                // ���� ��������� ����� ��� ����
                std::cout << stack.top() << " ";
                stack.pop();

                stack.push(c);
            }
        }
    }
    std::cout << '\n';
}
