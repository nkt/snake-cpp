#include "Snake.h"

Snake::Snake(int x, int y, unsigned direction) : direction(direction) {
    parts.push_back(coordinate(x, y));
}

void Snake::eat(Fruit fruit) {
    auto back = parts.back();
    parts.push_back(coordinate(back.x, --back.y));
}

void Snake::move() {
    auto head = parts.front();
    switch (direction) {
        case LEFT:
            --head.x;
            break;
        case RIGHT:
            ++head.x;
            break;
        case UP:
            ++head.y;
            break;
        case DOWN:
            --head.y;
            break;
        default:
            throw "Bad direction!";
    }
    for (auto part : parts) {
        if (head == part) {
            throw "Game over!";
        }
    }
    parts.pop_back();
    parts.push_front(head);
}

void Snake::goTo(int x, int y) {
    auto head = parts.front();
    if (head.x == x) {
        try {
            if (head.y < y) { // go to up
                up();
            } else { // go to down
                down();
            }
        } catch(...) {
            if (head.x < x) { // go to right
                right();
            } else { // go to left
                left();
            }
        }
    } else {
        try {
            if (head.x < x) { // go to right
                right();
            } else { // go to left
                left();
            }
        } catch(...) {
            if (head.y < y) { // go to up
                up();
            } else { // go to down
                down();
            }
        }
        
    }

}

void Snake::up() {
    if (direction == DOWN) {
        throw "You broke yourself";
    }
    direction = UP;
}

void Snake::down() {
    if (direction == UP) {
        throw "You broke yourself";
    }
    direction = DOWN;
}

void Snake::left() {
    if (direction == RIGHT) {
        throw "You broke yourself";
    }
    direction = LEFT;
}

void Snake::right() {
    if (direction == LEFT) {
        throw "You broke yourself";
    }
    direction = RIGHT;
}