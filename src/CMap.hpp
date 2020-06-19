//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CMAP_HPP
#define SEM_CMAP_HPP
#include <list>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <filesystem>
#include "CTile.hpp"
#include "CTower.hpp"
#include "CUnit.hpp"

/**
 * Game data structure.
 */
struct TData{
    TData() = default;
    size_t limit;
    size_t money;
    size_t all_money;
    size_t units_killed;
    size_t units_escaped;
    size_t enemies_in_wave;
    size_t wave_cooldown;
    size_t units_alive;
};
/**
 * Wrapper structure used for path finding, both for BFS and Greedy algorithm.
 */
typedef struct Node{
    Node(std::shared_ptr<CTile> tile)
        : tile(tile){}
    std::shared_ptr<Node> parent = nullptr;
    // 0 - FRESH, 1 - OPEN, 2 - CLOSED
    int flag = 0;
    size_t value = 0;
    std::shared_ptr<CTile> tile = nullptr;
}Node;

inline bool operator<(const std::shared_ptr<Node> & first, const std::shared_ptr<Node> & second){
    return first->value < second->value;
}

class CMap{
public:
    /**
     *
     * @param file_path represents map or save in maps/ or saves/ folder. File is checked for integrity before passing
     * to this constructor
     * @param is_new_game used in different file structure for new map and save
     */
    CMap(const std::filesystem::path& file_path, bool is_new_game);
    /**
     * class is non trivial (std::string messages), needs user-defined destructor
     */
     ~CMap();
    /**
     * Move units in order from closest to finish point. Move only on predefined path.
     * @return true if enough units have passed to lose the game
     */
    bool moveUnits(void);
    /**
     * Each tower attacks target. If the unit is killed replaces it with free space tile and increments killed counter.
     */
    void attackTowers(void);
    /**
     * Parses command for buying. Command has correct structure. Checks if player has enough money and check
     * tile availability. Resolves tower building and placing it in containers.
     * @param command with name and position of desired tower
     */
    void placeTower(std::string & command);
    /**
     * Clears windows and prints map with game data.
     */
    void printMap(void);
    /**
     * Parses and checks user command if action, names and position correspond to map. Does not check resources
     * and position availability.
     * @param command for checking
     * @return true if command is valid and can be used
     */
    bool validUserAction(std::string & command);
    /**
     * Prints available towers, units and their specifications.
     */
    void showShop()const;
    /** Upgrades all towers of the same type - tower_symbol.
     * @param tower_symbol
     */
    void upgrade (char tower_symbol);
    /**
     * Puts all tiles in rows separated with std::endl to @param os. Does not put data and other data to @param os.
     * @param os output stream
     * @param map
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const CMap &map);
    /**
     * @return statistics of units killed, money collected...
     */
    const TData & gameEndData ()const;
    /**
     * Saves the state of the game to file in saves/ folder. Filename is current time.
     * @return true if successful
     * @throws runtime_exception if file cant be created
     */
    bool saveGame()const;

private:
    /**
     * @param x position
     * @param y position
     * @return manhattan distance - heuristic value for Greedy Algorithm
     */
    size_t heuristic(const size_t & x, const size_t & y) const;
    /**
     * Checks if player is placing tower on path to finish.
     * @param x
     * @param y
     * @return true if blocks path to finish
     */
    [[nodiscard]] bool blocksPath(size_t & x,size_t & y) const;

    /**
     * BFS or A star used for finding shortest path from start to finish.
     * @param useBFS if true use BFS if false use A star.
     */
    void makePath(bool useBFS, std::list<size_t> & unit_hp);

    void
    BFS(const std::vector<std::vector<std::shared_ptr<Node>>> &grid, std::shared_ptr<Node> &last_node) const;

    void
    greedySearch(const std::vector<std::vector<std::shared_ptr<Node>>> &grid, std::shared_ptr<Node> &last_node) const;
    /**
     * In tiles are stored all elements of map(tiles, units, towers).
     */
    std::vector<std::vector<std::shared_ptr<CTile>>> tiles;
    /**
     * All available types of towers, used for cloning.
     */
    std::map<char, std::shared_ptr<CTower>> all_towers;
    /**
     * All towers placed on map, order not important.
     */
    std::vector<std::shared_ptr<CTower>> towers;
    /**
     * All units on map, ordered by size_t position on path, ascending from finish to start.
     */
    std::map<size_t, std::shared_ptr<CUnit>> units;
    /**
     * All tiles which make path ordered from finish to start tile.
     */
    std::map<size_t, std::shared_ptr<CTile>> path;
    /**
     * Waves have different number of units in them. Waves are longer and upgrade ratio is higher. Last wave is
     * infinite and upgrades units until overflow - overflow does not happen.
     */
    std::list<int> waves {10, 10, 10, 15, 15, 15, 20, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    /**
     * Messages for user - info of units killed and unsuccessful command parsing, announcing new waves.
     */
    std::list<std::string> messages;
    size_t height{};
    size_t width{};
    bool use_BFS;
    std::shared_ptr<CTile> start;
    std::shared_ptr<CTile> finish;
    TData data{};
};

#endif //SEM_CMAP_HPP
