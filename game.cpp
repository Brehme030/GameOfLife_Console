#include "game.h"

#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>

using std::endl;
using std::cout;
using std::string;
using std::stringstream;
using std::default_random_engine;
using std::uniform_int_distribution;

Game::Game(int row, int column, int mode) {
    this->row = row;
    this->column = column;

    boardNew = new Cell*[row];
    boardOld = new Cell*[row];

    for (int i = 0; i < row; ++i) {
        boardNew[i] = new Cell[column];
        boardOld[i] = new Cell[column];
    }

    if (this->row > 4 && this->column > 4) {
        switch (mode) {
        case 1:
            staticFigure();
            break;
        case 2:
            blinkFigure();
            break;
        case 3:
            gliderFigure();
            break;
        case 4:
            toadFigure();
            break;
        default:
            fillRandom();
        }
    }
}

Game::~Game() {
    for (int i = 0; i < row; ++i) {
        delete[] boardNew[i];
        delete[] boardOld[i];
    }
    delete[] boardNew;
    delete[] boardOld;
}

void Game::fillRandom() {
    std::default_random_engine randGenerator(time(0));
    std::uniform_int_distribution<int> randBinary(0, 1);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            int randomNum = randBinary(randGenerator);
            boardOld[i][j].setStatus(randomNum);
        }
    }
}

string Game::boardString() {
    stringstream ss;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            ss << boardOld[i][j];
        }
        ss << endl;
    }
    string s = ss.str();
    return s;
}

void Game::ruleBook(Cell &cellOld, Cell &cellNew) {
    // implementation of the survival rules
    if (cellOld.getStatus()) {
        if (neighborCount < 2) {
            cellNew.setDead(); // underpopulation -> death
        }
        else if (neighborCount == 2 || neighborCount == 3) {
            cellNew.setAlive(); // lives on
        } else {
            cellNew.setDead(); // overpopulation -> death
        }
    } else {
        if (neighborCount == 3) { // reproduction -> lives
            cellNew.setAlive();
        }
    }
}

int Game::myModulo(int a, int b) {
    return ((b + (a % b)) % b);
}

void Game::countNeighbors(int x, int y) {
    int donutX, donutY;

    for (int i = (-1); i <= 1; i++) {
        for (int j = (-1); j <= 1; j++) {
            int donutX = myModulo((x + i), row); // calculated neighbors respecting torus shape
            int donutY = myModulo((y + j), column);

            if (i == 0 && j == 0) { // don't count cell itself
                continue;
            }
            else if (boardOld[donutX][donutY].getStatus()) {
                neighborCount++;
            }
        }
    }
}

void Game::play() {
    // animates cell develoment for indefinite genereations (doesn't stop when all dead)
    cout << boardString();

    for (;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); //time delay
        system("cls");
        singleStep();
    }
}

void Game::singleStep() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            neighborCount = 0;
            countNeighbors(i, j);
            ruleBook(boardOld[i][j], boardNew[i][j]);
        }
    }
    copyBoards();
    cout << boardString();
}

void Game::copyBoards() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            boardNew[i][j].getStatus() ? boardOld[i][j].setAlive() : boardOld[i][j].setDead();
        }
    }
}

void Game::staticFigure() {
    boardOld[0][1].setAlive();
    boardOld[1][0].setAlive();
    boardOld[1][2].setAlive();
    boardOld[2][1].setAlive();
}

void Game::blinkFigure() {
    boardOld[0][1].setAlive();
    boardOld[1][1].setAlive();
    boardOld[2][1].setAlive();
}

void Game::gliderFigure() {
    boardOld[0][1].setAlive();
    boardOld[1][2].setAlive();
    boardOld[2][0].setAlive();
    boardOld[2][1].setAlive();
    boardOld[2][2].setAlive();
}

void Game::toadFigure() {
    boardOld[0][2].setAlive();
    boardOld[1][2].setAlive();
    boardOld[2][2].setAlive();
    boardOld[1][3].setAlive();
    boardOld[2][3].setAlive();
    boardOld[3][3].setAlive();
}
