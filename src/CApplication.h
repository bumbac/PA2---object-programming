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
 * This class provides console interface for choosing map or save, and for showing instructions
 * how to play game.
 *
 * This class has no user-defined constructor. You can start a game with default map - map1.txt or
 * choose one from folder <executable>/maps/ or resume game in <executable>/saves/.
 * Included is template game with automated commands. It is used for demonstration purposes and testing.
 * Template game starts from main menu - 5. Show example game.
 */
class CApplication{
public:
    /**
     * Instance listens to user input to std::cin and shows corresponding visual.
     * When function start comes to finish successfully(user requests exit) all allocated resources in game are freed
     * and saves are written. No file is left open, user input is ignored.
     */
    void start(void);

private:
    /**
     * Show main menu with user choices:
     * Start game, Select map, Select save, Show manual, Start example game, Exit
     */
    void showMenu(void);
    /**
     * Start game with save or map name stored in member variable m_name.
     * m_name represents correct save or map, no problems with game initialization should occur.
     */
    bool startGame();
    /**
     *  Provides list of maps for new game. After selection checks if file is okay and sets
     *  m_name.
     */
    void selectMap();
    /**
     *  Provides list of saves for new game. After selection checks if file is okay and sets
     *  m_name.
     */
    void selectSave();
    /**
     * Shows description and stats for basic enemy units and towers.
     */
    void showUnits();
    /**
     * Shows brief instructions on how to play game.
     */
    void manual();
    /**
     * Starts template game with automated commands.
     */
    void exampleGame();
    /**
     * At the moment of calling quitExit all resources are freed correctly and save is stored.
     */
    void quitExit();

    std::string m_name = "map1.txt";
    bool is_new_game = true;
};

#endif //SEM_CAPPLICATION_H
