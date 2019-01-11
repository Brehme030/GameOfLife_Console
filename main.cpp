#include "cell.h"
#include "game.h"

int main() {
    Game* myGame = new Game(10, 10, 3);
    /*
        parameters: rows, columns, pattern
        patterns:
        1 -> static
        2 -> blink
        3 -> glider
        4 -> toad
        all others -> random
    */
    myGame->play();
}

/*
 * TO-DO:
 * exception handling
 * include more complex pattern to marvel at
 */
