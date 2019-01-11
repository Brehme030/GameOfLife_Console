#ifndef CELL_H
#define CELL_H

#define ALIVE "*"
#define DEAD " "

#include <iostream>

class Cell {
private:
    bool alive;

public:
    Cell();

    bool getStatus();
    void setStatus(int);
    void setAlive();
    void setDead();

    friend std::ostream& operator << (std::ostream& os, Cell& pCell);
};

#endif // CELL_H
