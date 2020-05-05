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
#include "CTile.h"
#include "CTower.h"
#include "CUnit.h"

struct Data{
    Data ()
        :m_time_step(0), m_units_killed(0), m_units_escaped(0), m_units_alive(0), m_money(50){}

    Data (size_t time_step, size_t units_killed, size_t units_escaped, size_t units_alive,size_t money)
        : m_time_step(time_step), m_units_killed(units_killed), m_units_escaped(units_escaped), m_units_alive(units_alive), m_money(money){}

    size_t m_time_step;
    size_t m_units_killed;
    size_t m_units_escaped;
    size_t m_units_alive;
    size_t m_money;
};

class CMap{
public:
    CMap (const std::string & name, bool is_new_game);
    bool moveUnits(void);

    void attackTowers(void);

    void placeTower(std::string & command);

    void printMap(void) const;

    bool validUserAction(std::string & command) const;

    friend std::ostream &operator<<(std::ostream &os, const CMap &map);

private:
    std::vector<std::vector<std::shared_ptr<CTile>>> tiles;
    std::map<std::string, CTower> all_towers;
    std::map<std::string, CUpgrade> all_upgrades;
    std::vector<std::shared_ptr<CTower>> towers;
    std::map<size_t, std::shared_ptr<CUnit>> units;
    std::map<size_t, std::shared_ptr<CTile>> path;
    size_t win;
    size_t height;
    size_t width;
    const std::shared_ptr<CTile> start;
    const std::shared_ptr<CTile> end;
    Data data;

    bool blocksPath(const size_t & x, const size_t & y) const;

};


#endif //SEM_CMAP_H
