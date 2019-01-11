#ifndef GAME_H
#define GAME_H

#include "cell.h"

class Game {
private:
    int row;
    int column;
    int size;
    Cell** boardOld;
    Cell** boardNew;
    int neighborCount = 0;

public:
    Game(int, int, int);
    ~Game();

    void play(); // infinite loop
    int myModulo(int, int);

// private:
    void singleStep();
    void ruleBook(Cell&, Cell&);
    void countNeighbors(int, int);
    std::string boardString();
    void copyBoards();

    void blinkFigure();
    void staticFigure();
    void gliderFigure();
    void toadFigure();
    void fillRandom();
};

#endif // GAME_H
