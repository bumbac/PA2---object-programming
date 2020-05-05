//
// Created by sutymate on 4/29/20.
//

#include "CTower.h"

#include <utility>

std::string CTower::getName(void) const {
    return name;
}

size_t CTower::getPrice(void) const {
    return price;
}

bool CTower::canStep() const {
    return false;
}

size_t CTower::getRange() const {
    return range;
}

CTower::CTower(const CTower *origin, size_t &x, size_t &y, const std::shared_ptr<CTile> goal)
:CTile(x, y, origin->symbol, goal), range(origin->range), damage(origin->damage), price(origin->price), name(origin->name){}
