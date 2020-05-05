//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CAPPLICATION_H
#define SEM_CAPPLICATION_H

#include "CMap.h"
#include "CGame.h"
#include "CTile.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
/**
 * This class provides console interface for choosing map or save and for showing instructions how to play game.
 */
class CApplication{
public:
    /**
     * This class has no user-defined constructor and all 
     */
    void start(void);

private:
    void showMenu(void);

    bool startGame();

    void selectMap();

    void selectSave();

    void showUnits();

    void manual();

    void exampleGame();

    void quitExit();

    std::string m_name = "map1.txt";
    bool is_new_game = true;
};

#endif //SEM_CAPPLICATION_H
