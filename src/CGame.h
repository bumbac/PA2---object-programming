//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CGAME_H
#define SEM_CGAME_H

#include <iostream>
#include <locale>
#include <thread>
#include "CMap.h"
#include <fstream>
/**
 * Class operates actions outside of game itself (loading game, parsing user actions, saving, showing manual,
 * exiting game).
 */

class CGame{
public:
    /**
     *
     * @param game_name represents file name with correct content - file exists, has correct structure, wasn't modified
     * outside of game system
     * @param is_new_game if is_new_game is true, load defaults in starting new game, otherwise load game data from
     * file.
     */
    CGame(const std::string & game_name, bool is_new_game);
    /**
     * Start manages all user actions and ends the game correctly.
     * User input is executed through std::cin and is operated by new thread started in this function.
     * After user requests game exit all other user input is ignored and game is saved and frees resources.
     * Game continues until player loses.
     */
    void start(void);

private:
    /**
     * @return represents player lose
     */
    bool sequence(void);
    /**
     * This functions runs on separate thread and receives user input, checks correct structure and appends it to linked
     * list of userCommands which are to be executed. Linked list is thread safe in a way that you can append new
     * commands to the finish and remove commands from the front.
     */
    void listen(void);
    /**
     * Executes(show, save, exit commands) or forwards(buy, resume commands) user actions.
     * @return true if user requests finish of game.
     */
    bool userAction(void);
    /**
     * Pauses the game, shows the shop(towers, units, upgrades) and saves the game.
     */
    void showShop(void) const;
    /**
     * Pauses the game, shows brief instructions, units and towers descriptions and saves the game.
     */
    void showManual() const;
    /**
     * Saves the game.
     */
    void saveGame() const;
    std::unique_ptr<CMap> map;
    std::list<std::string> userCommands;
};
#endif //SEM_CGAME_H
