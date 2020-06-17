//
// Created by sutymate on 5/5/20.
//

#include "CTowerBombarda.h"


CTowerBombarda::CTowerBombarda(const CTowerBombarda *original, const size_t &x, const size_t &y)
        :CTower(original, x, y){}

CTowerBombarda::CTowerBombarda(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price, double ratio)
        :CTower(x, y, symbol, range, damage, price, ratio) {}

size_t CTowerBombarda::attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const {
    std::pair<size_t, std::shared_ptr<CUnit>> favorit(0, nullptr);
    size_t min_hp = SIZE_MAX;
    // last units from finish is starting point, do not kill
    for (auto & unit: units){
        if (unit.first == units.rbegin()->first)
            continue;
        TCoordinate unit_coordinates = unit.second->getPosition();
        size_t x_range = 0;
        if (position.x > unit_coordinates.x)
            x_range = std::max(position.x - unit_coordinates.x, x_range);
        else
            x_range = std::max(unit_coordinates.x - position.x, x_range);

        size_t y_range = 0;
        if (position.y > unit_coordinates.y)
            y_range = std::max(position.y - unit_coordinates.y, y_range);
        else
            y_range = std::max(unit_coordinates.y - position.y, y_range);
        if (std::max(x_range, y_range) <= range) {
            if (unit.second->getHealth() < min_hp) {
                min_hp = unit.second->getHealth();
                favorit = unit;
            }
        }
    }
    if (favorit.second != nullptr){
        if (favorit.second->receiveAttack(damage)){
            return favorit.first;
        }
    }
    return 0;
}

std::shared_ptr<CTower> CTowerBombarda::clone(size_t &x, size_t &y) const {
    return std::make_shared<CTowerBombarda>(this, x, y);
}
