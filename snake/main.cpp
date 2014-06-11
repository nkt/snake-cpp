#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Snake.h"

Snake *snake;
Fruit *fruit;

struct rgb {
    float r;
    float g;
    float b;

    rgb(int hex) {
        r = ((hex >> 16) & 0xFF) / 255.0;  // Красный
        g = ((hex >> 8) & 0xFF) / 255.0;   // Зеленый
        b = ((hex) & 0xFF) / 255.0;        // Синий
    }
};


const int
        ESCAPE_KEY = 27,
        FPS = 100,
        SCALE = 25,
        N = 40,
        M = 20,
        WIDTH = SCALE * N,
        HEIGHT = SCALE * M;

const rgb
        BACKGROUND_COLOR(0xf2f0bb),
        GRID_COLOR(0xb6b6b6),
        SNAKE_COLOR(0x33c9d8),
        SNAKE_HEAD_COLOR(0x336bd8),
        FRUIT_COLOR(0x34bd24);


void display();

void keyboard(int key, int x, int y);

void timer(int value);

void drawGrid();

void drawSnake();

void drawFruit();

void bot();

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Snake");

    glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    snake = new Snake(10, 10);
    fruit = new Fruit(N, M);

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(10, timer, 0);

    glutMainLoop();

    return 0;
}

void timer(int value) {
    try {
        snake->move();
        if (fruit->c == snake->parts.front()) {
            snake->eat(*fruit);
            delete fruit;
            
            fruit = new Fruit(N, M);
        }
        snake->goTo(fruit->c.x, fruit->c.y);
    } catch(const char *e) {
        cout << e << endl;
        cout << "You've got " << snake->parts.size() << endl;
        exit(0);
    }
    
    display();
    glutTimerFunc(FPS, timer, 0);
}

void drawCoordinate(coordinate c) {
    glRectf(c.x * SCALE, c.y * SCALE, (c.x + 0.99) * SCALE, (c.y + 0.99) * SCALE);
}

void drawFruit() {
    glColor3f(FRUIT_COLOR.r, FRUIT_COLOR.g, FRUIT_COLOR.b);
    if (fruit) {
        drawCoordinate(fruit->c);
    }
}

void drawSnake() {
    bool head = true;
    for (auto part : snake->parts) {
        if (head) {
            glColor3f(SNAKE_HEAD_COLOR.r, SNAKE_HEAD_COLOR.g, SNAKE_HEAD_COLOR.b);
            head = false;
        } else {
            glColor3f(SNAKE_COLOR.r, SNAKE_COLOR.g, SNAKE_COLOR.b);
        }
        drawCoordinate(part);
    }
}

void drawGrid() {
    glColor3f(GRID_COLOR.r, GRID_COLOR.g, GRID_COLOR.b);
    glBegin(GL_LINES);
    int i;
    for (i = 0; i < WIDTH; i += SCALE) {
        glVertex2f(i, 0);
        glVertex2f(i, HEIGHT);
    }
    for (i = 0; i < HEIGHT; i += SCALE) {
        glVertex2f(0, i);
        glVertex2f(WIDTH, i);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawSnake();
    drawFruit();
    drawGrid();

    glFlush();
}

void keyboard(int key, int x, int y) {
    if (key == ESCAPE_KEY) {
        exit(0);
    }
    switch (key) {
        case 101 :
            snake->up();
            break;
        case 102 :
            snake->right();
            break;
        case 100 :
            snake->left();
            break;
        case 103 :
            snake->down();
            break;
    }
}