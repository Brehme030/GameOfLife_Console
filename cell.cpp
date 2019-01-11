#include "cell.h"

using std::ostream;

Cell::Cell() {
    this->setDead();
}

bool Cell::getStatus() {
    return alive;
}

void Cell::setAlive() {
    alive = true;
}

void Cell::setDead() {
    alive = false;
}

void Cell::setStatus(int status) {
    status == 1 ? this->setAlive() : this->setDead();
}

ostream& operator<<(ostream& os, Cell& pCell) {
    if (pCell.getStatus()) {
        os << ALIVE; // preprocessor directives in pch.h
    }
    else {
        os << DEAD;
    }
    return os;
}
