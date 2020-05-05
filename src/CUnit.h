//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CUNIT_H
#define SEM_CUNIT_H

#include <deque>
#include <map>
#include "CTile.h"
#include "CUpgrade.h"

class CUnit: public CTile{

public:
    CUnit(const size_t &x, const size_t &y, char symbol, const std::shared_ptr<CTile> &goal, const std::string &name,
          const size_t steps, size_t currentHp);

    bool canStep() const override;

    bool moveUnit(std::map<size_t, std::shared_ptr<CTile>> & path, size_t & position);

    bool receiveAttack(const size_t & attack);

    size_t getHeuristic() const;
protected:
    const std::string name;
    const size_t steps;
    size_t current_hp;
};
#endif //SEM_CUNIT_H
