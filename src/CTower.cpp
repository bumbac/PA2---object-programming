//
// Created by sutymate on 4/29/20.
//

#include "CTower.h"
size_t CTower::getPrice(void) const {
    return price;
}

bool CTower::canStep() const {
    return false;
}

CTower::CTower(const CTower *origin, size_t &x, size_t &y)
:CTile(x, y, origin->symbol), range(origin->range), damage(origin->damage), price(origin->price){}

TCoordinate CTower::getPosition(void) const {
    return CTile::getPosition();
}

CTower::CTower(const size_t &x, const size_t &y, const char symbol,
               size_t range, size_t damage, size_t price) : CTile(x, y, symbol), range(range), damage(damage), price(price) {}
