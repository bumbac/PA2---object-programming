//
// Created by sutymate on 4/29/20.
//
#include "CTower.hpp"
#include <cmath>

CTower::CTower(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price,
        double upgrade_ratio, std::string description)
    : CTile(x, y, symbol), range(range), damage(damage), price(price), upgrade_ratio(upgrade_ratio),
    description(description) {}

CTower::~CTower() {}

    // preventing unsigned overflow and crazy steep upgrading
void CTower::upgrade(const char symbol) {
    if (symbol != this->symbol)
        return;
    size_t previous = damage;
    damage = std::floor(damage * (2.0 + upgrade_ratio));
    if (previous > damage)
        damage = previous;
    previous = range;
    range += range*upgrade_ratio;
    if (range < previous)
        range = previous;
    if (upgrade_ratio > 100)
        return;
    upgrade_ratio *= 2;
}

void CTower::save(std::ostream & middle_man)const {
    middle_man << symbol << ' ' << std::to_string(range) << ' ' << std::to_string(damage) << ' '
        << std::to_string(price) << ' ' << std::to_string(upgrade_ratio) << std::endl << description;
}

size_t CTower::getRange(void) const {
    return range;
}

size_t CTower::getDamage(void) const {
    return damage;
}

size_t CTower::getPrice(void) const {
    return price;
}

std::string CTower::getDescription() const {
    return description;
}

