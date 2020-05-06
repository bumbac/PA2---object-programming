//
// Created by sutymate on 4/29/20.
//

#include "CTower.h"

#include <utility>

size_t CTower::getPrice(void) const {
    return price;
}

bool CTower::canStep() const {
    return false;
}


CTower::CTower(const CTower *origin, size_t &x, size_t &y, const std::shared_ptr<CTile> goal)
:CTile(x, y, origin->symbol, goal), name(origin->name), range(origin->range), damage(origin->damage), price(origin->price){}

TCoordinate CTower::getPosition(void) const {
    return CTile::getPosition();
}
