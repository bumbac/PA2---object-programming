//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CGAME_HPP
#define SEM_CGAME_HPP

#include <iostream>
#include <locale>
#include "CMap.hpp"
#include <fstream>
#include <filesystem>
/**
 * Class operates actions outside of game itself (loading game, parsing user actions, saving, showing manual,
 * exiting game).
 */

class CGame{
public:
    /**
     *
     * @param game_name represents path with correct content - file exists, has correct structure, wasn't modified
     * outside of game system
     * @param is_new_game if isSave is true, load defaults in starting new game, otherwise load game data from
     * file.
     */
    CGame(const std::filesystem::path &game_name, bool is_new_game, std::list<std::string> & user_commands);
    /**
     * Start manages all user actions and ends the game correctly.
     * User input is executed through std::cin and is operated by new thread started in this function.
     * After user requests game exit all other user input is ignored and game is saved and frees resources.
     * Game continues until player loses.
     */
    void start(void);

private:
    /** Sequence of first moving the units and then attacking them with towers. Dead units are replaced by new tiles.
     * @return represents player lost
     */
    bool sequence(void);
    /**
     * Receives user input, checks correct structure and appends it to linked list of userCommands which are to be
     * executed.
     */
    void listen(void);
    /**
     * Executes(manual, shop, back, save, exit) commands. Forwards(buy, upgrade commands) user actions to be processed
     * by CMap.
     * @return true if user requests exit or if game ends.
     */
    bool userAction(void);
    /**
     * Pauses the game, shows the shop(towers, units, upgrades) and saves the game.
     */
    void showShop();
    /**
     * Pauses the game, shows instructions and saves the game.
     */
    void showManual() const;

    void lose();

    int fill_width = 80;
    std::unique_ptr<CMap> map;
    std::list<std::string> userCommands;
};
#endif //SEM_CGAME_HPP
