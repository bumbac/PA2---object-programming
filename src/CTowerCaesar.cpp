//
// Created by sutymate on 5/5/20.
//

#include "CTowerCaesar.h"



CTowerCaesar::CTowerCaesar(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price, double ratio)
        : CTower(x, y, symbol, range, damage, price, ratio) {}

CTowerCaesar::CTowerCaesar( const CTowerCaesar *origin, const size_t &x, const size_t &y)
    : CTower(origin, x, y) {}

size_t CTowerCaesar::attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const {
    for (auto & unit: units){
        // last units from finish is starting point, do not kill
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
            if (std::rand() % 10 == 0) {
                printf("MMMMMMMMMONSTER KILL!!!!\n");
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
    return std::make_shared<CTowerCaesar>(this, x, y);
}
