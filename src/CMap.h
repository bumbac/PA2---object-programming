//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CMAP_H
#define SEM_CMAP_H
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <algorithm>
#include <ostream>
#include <filesystem>
#include "CTile.h"
#include "CTower.h"
#include "CUnit.h"
/**
 * Game data structure.
 */
struct TData{
    /**
     * Constructor for new game.
     */
    TData () = default;
    /**
     * Constructor for restoring game
     * @param limit how many units can pass before losing the game
     * @param enemies_in_wave counter, every timestep was one sequence of units movement, tower attack, user action resolution.
     * @param units_killed enemy units killed
     * @param units_escaped enemy units that reached finish point
     * @param units_alive units alive on map
     * @param money available, received for killing units
     */

    size_t m_limit;
    size_t m_money;
    size_t m_all_money;
    size_t m_units_killed;
    size_t m_units_escaped;
    size_t m_enemies_in_wave;
    size_t m_wave_cooldown;
    size_t m_units_alive;
};

typedef struct Node{
    Node(std::shared_ptr<CTile> tile)
            :tile(tile){}
    std::shared_ptr<Node> parent = nullptr;
    int flag = 0;
    size_t value = 0;
    std::shared_ptr<CTile> tile = nullptr;
}Node;

inline bool operator<(const std::shared_ptr<Node> & first, const std::shared_ptr<Node> & second){
    return first->value < second->value;
}

class CMap{
public:
    CMap(const std::filesystem::path& file_path, bool is_new_game);

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
    void printMap(void) const;
    /**
     * Parses and checks user command if action, names and position correspond to map.
     * @param command for checking
     * @return true if command is valid and can be used
     */
    bool validUserAction(std::string & command);

    void showShop()const;

    void upgrade (char tower_symbol);
    /**
     * Puts all tiles in rows separated with std::endl to @param os. Does not put data and other data to @param os.
     * @param os output stream
     * @param map
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const CMap &map);

    const TData & winData ()const;

    bool saveGame()const;

    size_t heuristic(const size_t & x, const size_t & y) const;
private:
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
    std::list<int> waves {10, 10, 10, 15, 15, 15, 20, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::list<std::string> messages;
    size_t height{};
    size_t width{};
    bool use_BFS = false;
    std::shared_ptr<CTile> start;
    std::shared_ptr<CTile> finish;
    TData data{};
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

    std::shared_ptr<Node> &
    BFS(const std::vector<std::vector<std::shared_ptr<Node>>> &grid, std::queue<std::shared_ptr<Node>> &visited,
        std::shared_ptr<Node> &current_node) const;

    std::shared_ptr<Node> &
    A_star(const std::vector<std::vector<std::shared_ptr<Node>>> &grid, std::queue<std::shared_ptr<Node>> &visited,
        std::shared_ptr<Node> &current_node) const;
};

#endif //SEM_CMAP_H
