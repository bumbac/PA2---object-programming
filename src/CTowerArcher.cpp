//
// Created by sutymate on 5/5/20.
//
#include "CTowerArcher.hpp"

CTowerArcher::CTowerArcher(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price,
        double ratio, std::string description)
        : CTower(x, y, symbol, range, damage, price, ratio, description) {}

size_t CTowerArcher::attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const {
    // units is ordered map, first unit is closest to finish, last unit is cast for unit spawning
    for (auto & unit: units){
        // last units from finish is starting point, do not kill
        if (unit.first == units.rbegin()->first)
            continue;
        TCoordinate unit_coordinates = unit.second->getPosition();
        size_t x_range = 0;
        if (position.x > unit_coordinates.x)
            x_range = position.x - unit_coordinates.x;
        else
            x_range = unit_coordinates.x - position.x;

        size_t y_range = 0;
        if (position.y > unit_coordinates.y)
            y_range = position.y - unit_coordinates.y;
        else
            y_range = unit_coordinates.y - position.y;
        if (std::max(x_range, y_range) <= range) {
            if (unit.second->receiveAttack(damage)) {
                return unit.first;
            } else
                return 0;
        }
    }
    return 0;
}

std::shared_ptr<CTower> CTowerArcher::clone(size_t &x, size_t &y)const {
    return std::make_shared<CTowerArcher>(x, y, this->symbol, this->range, this->damage, this->price,
            this->upgrade_ratio, this->description);
}




