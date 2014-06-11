#include "Snake.h"

Snake::Snake(int x, int y, unsigned direction) : direction(direction) {
    parts.push_back(coordinate(x, y));
}

void Snake::eat(Fruit fruit) {

}

void Snake::move() {
    for (auto part = parts.begin(); part != parts.end(); ++part) {
        switch (direction) {
            case LEFT:
                --part->x;
                break;
            case RIGHT:
                ++part->x;
                break;
            case UP:
                ++part->y;
                break;
            case DOWN:
                --part->y;
                break;
            default:
                throw "Bad direction!";
        }
    }

    cout << "Move to " << direction << endl;
}


