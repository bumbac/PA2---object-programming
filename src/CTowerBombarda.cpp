//
// Created by sutymate on 5/5/20.
//

#include "CTowerBombarda.h"

std::shared_ptr<CUnit> CTowerBombarda::attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const {
    std::pair<size_t, std::shared_ptr<CUnit>> favorit(0, nullptr);
    size_t min_hp = SIZE_MAX;
    for (auto & unit: units){
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
            units.erase(favorit.first);
            return favorit.second;
        }
    }
    return nullptr;
}

std::shared_ptr<CTower> CTowerBombarda::clone(size_t &x, size_t &y, const std::shared_ptr<CTile> &goal) const {
    return std::make_shared<CTowerBombarda>(this, x, y, goal);
}

CTowerBombarda::CTowerBombarda(const CTowerBombarda *original, size_t &x, size_t &y, const std::shared_ptr<CTile> &goal)
    :CTower(original, x, y, goal){}