//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CAPPLICATION_HPP
#define SEM_CAPPLICATION_HPP

#include <filesystem>

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
     * Start game with save or map name stored in member variable map_name.
     * map_name represents correct save or map, no problems with game initialization should occur.
     */
    void startGame();
    /**
     *  Provides list of maps for new game. After selection checks if file is okay and sets
     *  map_name.
     */
    bool selectMap();
    /**
     * Shows brief instructions on how to play game.
     */
    void manual();
    /**
     * Starts template game with automated commands.
     */
    void exampleGame();
    /**
     * File checks hash on the end of file. The hash is issued by author of the game. If hash does not correspond,
     * file may be corrupted or changed without authors approval.
     * @param file_name
     * @return true if the file is verified and not changed
     */
    [[nodiscard]] bool checkFile(const std::filesystem::path & file_name) const;

    std::filesystem::path map_name = "maps/map0.txt";
    // standard terminal width. Some say that 120 is more suitable.
    int fill_width = 80;
    bool is_new_game = false;
};

#endif //SEM_CAPPLICATION_HPP
