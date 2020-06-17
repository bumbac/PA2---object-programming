//
// Created by sutymate on 4/29/20.
//
#include <cmath>
#include <sstream>
#include "CTower.h"
size_t CTower::getPrice(void) const {
    return price;
}

CTower::CTower(const CTower *origin, const size_t &x, const size_t &y)
    : CTile(x, y, origin->symbol), range(origin->range), damage(origin->damage), price(origin->price){}

CTower::CTower(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price, double ratio)
    : CTile(x, y, symbol), range(range), damage(damage), price(price), upgrade_ratio(ratio) {}

void CTower::upgrade(const char symbol) {
    if (symbol != this->symbol)
        return;
    damage = std::floor(damage * (1.0 + upgrade_ratio));
    range += range*upgrade_ratio;
    upgrade_ratio *= 2;
}

void CTower::save(std::ostream & middle_man){
    middle_man << symbol << ' ' << std::to_string(range) << ' ' << std::to_string(damage) << ' ' << std::to_string(price)
     << ' ' << std::to_string(upgrade_ratio);
}

size_t CTower::getDamage(void) const {
    return damage;
}

size_t CTower::getRange(void) const {
    return range;
}
