#ifndef __Snake__
#define __Snake__

#include <iostream>
#include <list>
#include <ctime>

using namespace std;

struct coordinate {
    int x;
    int y;

    coordinate(int x = 0, int y = 0) : x(x), y(y) {
    }

    bool operator==(const coordinate right) {
        return x == right.x && y == right.y;
    }
};

struct Fruit {
    coordinate c;

    Fruit(int maxX, int maxY) {
        srand((unsigned) time(0));
        c = coordinate(rand() % maxX, rand() % maxY);
    }
};

class Snake {
public:
    enum directions {
        LEFT, RIGHT, UP, DOWN
    };
    unsigned direction;

    list<coordinate> parts;

    Snake(int x, int y, unsigned direction = LEFT);

    void eat(Fruit fruit);

    void move();

    void up() {
        direction = UP;
    }

    void down() {
        direction = DOWN;
    }

    void left() {
        direction = LEFT;
    }

    void right() {
        direction = RIGHT;
    }
};

#endif
