#include "types.h"
#include "user.h"
#include "fcntl.h"

#define WIDTH 20
#define HEIGHT 10

int gameOver;
int score;
int length;
int tailX[100], tailY[100];
int x, y, fruitX, fruitY, dir;

void setup() {
    gameOver = 0;
    score = 0;
    length = 1;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = 5;
    fruitY = 5;
    dir = 0; // 0: up, 1: right, 2: down, 3: left
}

void draw() {
    printf(1, "\033[H"); // Move cursor to the top-left corner of the screen
    for (int i = 0; i < WIDTH + 2; i++)
        printf(1, "#");
    printf(1, "\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf(1, "#");
            if (i == y && j == x)
                printf(1, "O");
            else if (i == fruitY && j == fruitX)
                printf(1, "F");
            else {
                int isTail = 0;
                for (int k = 0; k < length; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf(1, "o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(1, " ");
            }

            if (j == WIDTH - 1)
                printf(1, "#");
        }
        printf(1, "\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf(1, "#");
    printf(1, "\n");

    printf(1, "Score:%d\n", score);
}

void input() {
    char c;
    if (read(0, &c, 1) > 0) {
        switch (c) {
            case 'a':
                dir = 3;
                break;
            case 'd':
                dir = 1;
                break;
            case 'w':
                dir = 0;
                break;
            case 's':
                dir = 2;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void algorithm() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < length; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case 0:
            y--;
            break;
        case 1:
            x++;
            break;
        case 2:
            y++;
            break;
        case 3:
            x--;
            break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    for (int i = 0; i < length; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        length++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        algorithm();
    }
    return 0;
}
