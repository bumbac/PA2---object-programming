//
// Created by sutymate on 4/29/20.
//

#include <iostream>
#include "CMap.h"

bool CMap::moveUnits(void) {
    for (auto & unit:units){
        size_t position = unit.first;
        if (unit.second->moveUnit(path, position)){
            TCoordinate old_position(unit.second->getPosition().x, unit.second->getPosition().y);
            std::shared_ptr<CTile> blank = std::make_shared<CTile>((unit.second.get()));
            if (position == path.size()){
                data.m_units_escaped++;
                tiles[old_position.x][old_position.y] = blank;
                unit.second = nullptr;
                path[unit.first] = blank;
                continue;
            }
            else {
                TCoordinate new_position = path[position]->getPosition();
                path[position] = tiles[old_position.x][old_position.y];
                tiles[new_position.x][new_position.y] = path[position];
                tiles[old_position.x][old_position.y] = blank;
                units[position] = unit.second;
                path[unit.first] = blank;
            }
        }
    }
    return data.m_units_escaped >= data.m_limit;
}

void CMap::attackTowers(void) {
    for (const auto & tower : towers){
        auto dead = tower->attack(units);
        if (dead != nullptr){
            data.m_units_killed++;
            std::shared_ptr<CTile> blank = std::make_shared<CTile>((dead.get()));
            for (auto & tile:path){
                if (tile.second == dead){
                    tile.second = blank;
                    break;
                }
            }
            tiles[dead->getPosition().x][dead->getPosition().y] = blank;
        }
    }
}

void CMap::placeTower(std::string & command) {
    auto it = command.begin() + 3;
    std::string what, x, y, price;
    while (*it != ' ')
        what += *it++;
    while (*it != ' ')
        x += *it++;
    while (*it != ' ')
        y += *it++;
    while (it != command.end())
        price += *it++;
    size_t x_pos = std::stoul(x);
    size_t y_pos = std::stoul(y);
    auto tower = all_towers[what];
    size_t price_number = std::stoull(price);

    if (price_number > data.m_money) {
        printf("Not enough money to buy %s.\n", what.data());
        return;
    }

    if (blocksPath(x_pos, y_pos)) {
        printf("Can't place tower on %lu %lu. It blocks the path.\n", x_pos, y_pos);
        return;
    }

    if (tiles[x_pos][y_pos]->canStep() ){
        std::shared_ptr<CTower> tmp  = tower->clone(x_pos, y_pos, finish);
        tiles[x_pos][y_pos] = tmp;
        towers.push_back(tmp);
        data.m_money -= tower->getPrice();
    }
    else
        printf("Can't place %s here.\n",what.data());
}

bool CMap::validUserAction(std::string & command) const {
    std::string first;
    std::cin >> first >> std::ws;
    if (all_towers.find(first) != all_towers.end()){
        std::string number;
        size_t x;
        size_t y;

        std::cin >> number >> std::ws;
        try{
            std::stoul(number, &x, 10);
        }
        catch (const std::invalid_argument & e){
            std::printf("Invalid position.\n");
            return false;
        }
        catch (const std::out_of_range & e){
            std::printf("Position out of range.\n");
            return false;
        }
        std::cin >> number >> std::ws;
        try{
            std::stoul(number, &y, 10);
        }
        catch (const std::invalid_argument & e){
            std::printf("Invalid position.\n");
            return false;
        }
        catch (const std::out_of_range & e){
            std::printf("Position out of range.\n");
            return false;
        }

        if (x > width || y > height){
            std::printf("Position out of range.\n");
            return false;
        }
        else{
            command += " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(all_towers.find(first)->second->getPrice());
            return true;
        }
    }

    if(all_upgrades.find(first) != all_upgrades.end()){
        command += first;
        return true;
    }
    printf("%s is not in shop. Type <shop> to see our offers!.\n", first.data());
    return false;
}

bool CMap::blocksPath(const size_t &x, const size_t &y) const {
    TCoordinate tower_tile (x, y);
    for (const auto & tile:path)
        if (tower_tile == tile.second->getPosition())
            return false;
    return true;
}

void CMap::printMap(void) const {
    for (size_t i = 0; i < height; i++)
        printf("\n");
    std::cout.width(width);
    std::cout.fill('=');
    std::cout << std::endl;
    std::cout.fill(' ');
    std::cout << "Timestep: " << data.m_time_step << std::endl;
    std::cout << "Units killed: " << data.m_units_killed << std::endl;
    std::cout << "Units escaped: " << data.m_units_escaped << std::endl;
    std::cout << "Money: " << data.m_money << std::endl;
    std::cout << this;

}

std::ostream &operator<<(std::ostream &os, const CMap &map) {
    for (const auto & row: map.tiles) {
        for (auto & tile:row)
            os << tile;
        os << std::endl;
    }
    return os;
}
