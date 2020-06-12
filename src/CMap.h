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
#include <algorithm>
#include <ostream>
#include <filesystem>
#include "CTile.h"
#include "CTower.h"
#include "CUnit.h"
/**
 * Game data structure.
 */
struct Data{
    /**
     * Constructor for new game.
     */
    Data () = default;
    /**
     * Constructor for restoring game
     * @param time_step time counter, every timestep was one sequence of units movement, tower attack, user action resolution.
     * @param units_killed enemy units killed
     * @param units_escaped enemy units that reached finish point
     * @param units_alive units alive on map
     * @param money available money received for killing units
     * @param limit how many units can pass before losing the game
     */
    Data (size_t time_step, size_t units_killed, size_t units_escaped, size_t units_alive,size_t money, size_t limit)
        : m_time_step(time_step), m_units_killed(units_killed), m_units_escaped(units_escaped), m_units_alive(units_alive), m_money(money), m_limit(limit){}

    size_t m_time_step;
    size_t m_units_killed;
    size_t m_units_escaped;
    size_t m_units_alive;
    size_t m_money;
    size_t m_limit;
};

class CMap{
public:
    CMap(const std::filesystem::path& path, bool is_new_game);

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
    bool validUserAction(std::string & command) const;
    /**
     * Puts all tiles in rows separated with std::endl to @param os. Does not put data and other data to @param os.
     * @param os output stream
     * @param map
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const CMap &map);
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
     * All available upgrades, used for upgrading units or towers. Objects are created in constructor, none is added.
     */
    const std::set<std::string, const CUpgrade> all_upgrades;
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
    size_t height{};
    size_t width{};
    std::shared_ptr<CTile> start;
    std::shared_ptr<CTile> finish;
    Data data{};
    /**
     * Checks if player is placing tower on path to finish.
     * @param x
     * @param y
     * @return true if blocks path to finish
     */
    [[nodiscard]] bool blocksPath(const size_t & x, const size_t & y) const;

    /**
     * BFS or A star used for finding shortest path from start to finish.
     * @param useBFS if true use BFS if false use A star.
     */
    void makePath(bool useBFS);

};

typedef struct Node{
    Node(CMap & map, const size_t & x, const size_t & y)
            : value(map.heuristic(x, y)){}
    std::shared_ptr<Node> parent = nullptr;
    int flag = 0;
    size_t value = 0;
    std::shared_ptr<CTile> tile = nullptr;

}Node;
inline bool operator<(const std::shared_ptr<Node> & first, const std::shared_ptr<Node> & second){
    return first->value < second->value;
}
#endif //SEM_CMAP_H
