//
// Created by sutymate on 4/29/20.
//

#include "CUnit.h"

bool CUnit::canStep() const {
    return false;
}


bool CUnit::moveUnit(std::map<size_t, std::shared_ptr<CTile>> &path, size_t & position) {
    for (size_t i = position + steps; i >= position; --i){
        if( i >= path.size())
            continue;
        if(path[i]->canStep()){
            position = i;
            return true;
        }
    }
    return false;
}

bool CUnit::receiveAttack(const size_t &attack) {
    if (current_hp <= attack) {
        return true;
    }
    else{
        current_hp -= attack;
        return false;
    }
}

size_t CUnit::getHealth() const {
    return current_hp;
}

CUnit::CUnit(const size_t &x, const size_t &y, char symbol, const std::shared_ptr<CTile> &goal, const std::string &name,
             const size_t steps, size_t currentHp) : CTile(x, y, symbol, goal), name(name), steps(steps),
                                                     current_hp(currentHp) {}

TCoordinate CUnit::getPosition(void) const {
    return CTile::getPosition();
}


