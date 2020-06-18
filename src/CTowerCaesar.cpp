//
// Created by sutymate on 5/5/20.
//

#include <iostream>
#include "CTowerCaesar.hpp"

CTowerCaesar::CTowerCaesar(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price,
        double ratio, std::string description)
        : CTower(x, y, symbol, range, damage, price, ratio, description) {}

size_t CTowerCaesar::attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const {
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
            if (std::rand() % 10 == 0) {
                std::cout << "MMMMMMMMMONSTER KILL!!!!" << std::endl;
                return unit.first;
            }
            else{
                if (unit.second->receiveAttack(damage)) {
                    return unit.first;
                }
            }
        }
    }
    return 0;
}

std::shared_ptr<CTower> CTowerCaesar::clone(size_t &x, size_t &y) const {
    return std::make_shared<CTowerCaesar>(x, y, this->symbol, this->range, this->damage, this->price,
            this->upgrade_ratio, this->description);
}
