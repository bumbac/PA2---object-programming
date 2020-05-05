//
// Created by sutymate on 5/5/20.
//

#include "CTowerArcher.h"

std::shared_ptr<CUnit> CTowerArcher::attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const {
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
        if (std::max(x_range, y_range) <= range)
            if (unit.second->receiveAttack(damage)) {
                units.erase(unit.first);
                return unit.second;
            }
            else
                return nullptr;
    }
    return nullptr;
}

std::shared_ptr<CTower> CTowerArcher::clone(size_t &x, size_t &y, const std::shared_ptr<CTile> &goal)const {
    return std::make_shared<CTowerArcher>(this, x, y, goal);
}

CTowerArcher::CTowerArcher(const CTowerArcher *original, size_t &x, size_t &y, const std::shared_ptr<CTile> &goal)
:CTower(original, x, y, goal){}


