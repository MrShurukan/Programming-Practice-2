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
    step(x, y+1);
    step(x, y-1);
    step(x+1, y);
    step(x-1, y);
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
#include <cstring>
#include <math.h>

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

std::string convertToRPN(std::string input) {
    std::stack<char> stack;
    std::string output;

    // Преобразуем в Си строку, чтобы можно было воспользоваться strtok
    char* inputCStr = new char[input.length()];
    strcpy(inputCStr, input.c_str());

    // Используем strtok, чтобы разделить строку на лексемы
    char* lexem = strtok(inputCStr, " ");
    while (lexem != nullptr) {
        char c = lexem[0];

        // Если первый символ - это цифра, то вся лексема - число
        if (isNumber(c)) {
            output += lexem;
            output += " ";
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                output += stack.top();
                output += " ";
                stack.pop();
            }

            // Выталкиваем саму скобку из стека
            stack.pop();
        }
        // Операция
        else if (c != ' ') {

            if (!stack.empty()) {
                // Пока операция на стеке приоритетнее ИЛИ
                // операция на вершине левоассоциативная и с приотитетом как у "с"
                while (!stack.empty() &&
                       (priority[stack.top()] > priority[c] || (stack.top() != '^' && priority[stack.top()] == priority[c]))) {
                    output += stack.top();
                    output += " ";
                    stack.pop();
                }
            }

            stack.push(c);
        }

        // Ищем следующую лексему
        lexem = strtok(nullptr, " ");
    }

    while (!stack.empty()) {
        output += stack.top();
        output += " ";
        stack.pop();
    }

    delete[] inputCStr;
    return output;
}

double calculateRPN(std::string input) {
    std::stack<double> stack;

    // Временно переводим локаль на дефолтную, чтобы разделителем была точка, а не запятая
    setlocale(LC_ALL, "C");

    // Преобразуем в Си строку, чтобы можно было воспользоваться strtok
    char* inputCStr = new char[input.length()];
    strcpy(inputCStr, input.c_str());

    // Используем strtok, чтобы разделить строку на лексемы
    char* lexem = strtok(inputCStr, " ");
    while (lexem != nullptr) {
        char c = lexem[0];

        // Если первый символ - это цифра, то вся лексема - число
        if (isNumber(c)) {
            stack.push(atof(lexem));
        }
        // Оператор
        else {
            double firstOp, secondOp, result = 0;
            secondOp = stack.top(); stack.pop();
            firstOp = stack.top(); stack.pop();

            switch (c) {
            case '+':
                result = firstOp + secondOp;
                break;
            case '-':
                result = firstOp - secondOp;
                break;
            case '*':
                result = firstOp * secondOp;
                break;
            case '/':
                result = firstOp / secondOp;
                break;
            case '^':
                result = pow(firstOp, secondOp);
                break;
            }

            stack.push(result);
        }

        lexem = strtok(nullptr, " ");
    }

    delete[] inputCStr;
    // Возвращаем локаль обратно
    setlocale(LC_ALL, "Russian");

    return stack.top();
}

void task32() {
    // Сбрасываем прошлый ввод, чтобы getline сработал корректно
    std::cin.ignore();

    std::string input;
    std::getline(std::cin, input);

    std::string converted = convertToRPN(input);
    std::cout << converted << '\n';

    std::cout << calculateRPN(converted) << '\n' << '\n';
}


/**** Task 33 ****/
#include <time.h>

class Fighter {
private:
    int health_points;
    int health;
    int force_points;
    int critical_points;
    int defence_points;
    int agility_points;
    int points;

    // Add p points to arbitrary value (points_value)
    bool add_points_to(int* points_value, int p) {
        if (p <= points) {
            *points_value += p;
            points -= p;

            return true;
        }
        return false;
    }

    double force() {
        return 1 + force_points;
    }

    bool critical() {
        double critical_threshold = 1/(1+pow(critical_points/4.0, 4));
        double normalized_random = rand() / static_cast<double>(RAND_MAX);

        return (normalized_random > critical_threshold);
    }

    double defence() {
        return 1/(1+pow(defence_points/4.0, 4));
    }

    bool agility() {
        double critical_threshold = 1/(1+pow(agility_points/4.0, 4));
        double normalized_random = rand() / static_cast<double>(RAND_MAX);

        return (normalized_random > critical_threshold);
    }

public:
    Fighter() {
        health = 100;
        health_points = force_points = critical_points =
                defence_points = agility_points = 0;
        points = 10;
    }

    Fighter(int health_points, int force_points, int critical_points, int defence_points, int agility_points):
        health_points(health_points), force_points(force_points), critical_points(critical_points),
        defence_points(defence_points), agility_points(agility_points)
    {
        points = 0;
        health = 100+health_points*100;
    }

    double attack() {
        return force() * (1 + critical());
    }

    double damage(double dmg) {
        double real_damage = (1-agility()) * defence() * dmg;
        health -= real_damage;

        return real_damage;
    }

    bool is_dead() {
        return health <= 0;
    }

    bool add_health_points(int points) { return add_points_to(&health_points, points); }
    bool add_force_points(int points) { return add_points_to(&force_points, points); }
    bool add_defence_points(int points) { return add_points_to(&defence_points, points); }
    bool add_agility_points(int points) { return add_points_to(&agility_points, points); }
    bool add_critical_points(int points) { return add_points_to(&critical_points, points); }
};

int range_rnd(int from, int to) {
    return (rand() % (to - from + 1)) + from;
}

Fighter generate_random_fighter() {
    Fighter f;

    f.add_health_points(range_rnd(1, 10));
    f.add_force_points(range_rnd(1, 10));
    f.add_defence_points(range_rnd(1, 3));
    f.add_agility_points(range_rnd(1, 10));
    f.add_critical_points(range_rnd(1, 5));

    return f;
}

Fighter create_player() {
    int hp, fp, dp, ap, cp;
    std::cout << "Health points: "; std::cin >> hp;
    std::cout << "Force points: "; std::cin >> fp;
    std::cout << "Critical points: "; std::cin >> cp;
    std::cout << "Defence points: "; std::cin >> dp;
    std::cout << "Agility points: "; std::cin >> ap;

    return Fighter(hp, fp, cp, dp, ap);
}

enum Modes {
    bot2bot = 1,
    player2bot,
    player2player
};

void fight(Fighter f1, std::string name1, Fighter f2, std::string name2) {
    bool is_turn_first = true;
    while (!f1.is_dead() && !f2.is_dead()) {
        if (is_turn_first) {
            double raw_damage = f1.attack();
            double received = f2.damage(raw_damage);

            std::cout << name2 << " received " << received << " points of damage\n";
        }
        else {
            double raw_damage = f2.attack();
            double received = f1.damage(raw_damage);

            std::cout << name1 << " received " << received << " points of damage\n";
        }

        is_turn_first = !is_turn_first;
    }

    std::cout << '\n';

    if (f1.is_dead()) std::cout << name2;
    else std::cout << name1;

    std::cout << " is a winner\n";
}

void task33() {
    srand( time(nullptr) );

    int mode;
    std::cout << "Select mode (1 - bot with bot, 2 - bot with player, 3 - player with player): ";
    std::cin >> mode;

    Fighter fighter1, fighter2;
    std::string name1, name2;

    switch(mode) {
    case bot2bot:
        fighter1 = generate_random_fighter();   name1 = "Bot1";
        fighter2 = generate_random_fighter();   name2 = "Bot2";
        break;
    case player2bot:
        fighter1 = generate_random_fighter();   name1 = "Bot";
        fighter2 = create_player();             name2 = "Player";
        break;
    case player2player:
        std::cout << "Player1:\n";
        fighter1 = create_player();             name1 = "Player1";
        std::cout << "Player2:\n";
        fighter2 = create_player();             name2 = "Player2";
        break;

    default:
        std::cout << "Unknown mode\n";
        return;
    }

    fight(fighter1, name1, fighter2, name2);
}
