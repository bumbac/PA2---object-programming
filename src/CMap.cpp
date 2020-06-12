//
// Created by sutymate on 4/29/20.
//

#include <iostream>
#include <fstream>
#include <queue>
#include "CMap.h"
#include "CTowerArcher.h"
#include "CTowerBombarda.h"
#include "CTowerCaesar.h"
#define FRESH 0
#define OPEN 1
#define CLOSED 2
//todo commentary

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
    auto it = command.begin() + 6;
    std::string x, y, price;
    char symbol = ::toupper(command[4]);
    while (*it++ != ' ')
        x += *it;
    while (*it++ != ' ')
        y += *it;
    while (it++ != command.end())
        price += *it;
    size_t x_pos = std::stoul(x);
    size_t y_pos = std::stoul(y);
    auto tower = all_towers[symbol];
    size_t price_number = std::stoull(price);

    if (price_number > data.m_money) {
        printf("Not enough money to buy %c.\n", symbol);
        return;
    }

    if (blocksPath(x_pos, y_pos)) {
        printf("Can't place tower on %lu %lu. It blocks the path.\n", x_pos, y_pos);
        return;
    }

    if (tiles[x_pos][y_pos]->canStep() ){
        std::shared_ptr<CTower> tmp  = tower->clone(x_pos, y_pos);
        tiles[x_pos][y_pos] = tmp;
        towers.push_back(tmp);
        data.m_money -= tower->getPrice();
    }
    else
        printf("Can't place tower here.\n");
}

bool CMap::validUserAction(std::string & command) const {
    std::string first;
    std::cin >> first >> std::ws;
    if (first.length() == 1) {
        char symbol = ::toupper(first[0]);
        if (all_towers.find(symbol) != all_towers.end()) {
            std::string number;
            size_t x = 0;
            size_t y = 0;

            std::cin >> number >> std::ws;
            try {
                std::stoul(number, &x, 10);
            }
            catch (const std::invalid_argument &e) {
                std::printf("Invalid position.\n");
                return false;
            }
            catch (const std::out_of_range &e) {
                std::printf("Position out of range.\n");
                return false;
            }
            std::cin >> number >> std::ws;
            try {
                std::stoul(number, &y, 10);
            }
            catch (const std::invalid_argument &e) {
                std::printf("Invalid position.\n");
                return false;
            }
            catch (const std::out_of_range &e) {
                std::printf("Position out of range.\n");
                return false;
            }

            if (x > width || y > height) {
                std::printf("Position out of range.\n");
                return false;
            } else {
                command += " ";
                command += symbol;
                command += " ";
                command += std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(all_towers.find(first[0])->second->getPrice());
                return true;
            }
        }
    }
    else{
        std::transform(first.begin(), first.end(), first.begin(), ::tolower);
        if(all_upgrades.find(first) != all_upgrades.end()){
            command += first;
            return true;
        }
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
    //todo revision
    for (size_t i = 0; i < height; i++)
        printf("\n");
    std::cout.width(width);
    std::cout.fill('=');
    std::cout << std::endl;
    std::cout.fill(' ');
    std::cout << "Timestep: " << data.m_time_step << std::endl;
    std::cout << "Units killed: " << data.m_units_killed << std::endl;
    std::cout << "Units escaped: " << data.m_units_escaped << std::endl;
    std::cout << "Units limit: " << data.m_limit<< std::endl;
    std::cout << "Money: " << data.m_money << std::endl;
    std::cout << this;

}

std::ostream &operator<<(std::ostream &os, const CMap &map) {
    //todo
    for (const auto & row: map.tiles) {
        for (const auto & tile:row)
            os << tile;
        os << std::endl;
    }
    return os;
}

CMap::CMap(const std::filesystem::path& path, bool is_new_game){
    //todo check if can open file
    std::ifstream mapFile(path.c_str(), std::ios::in);
    size_t startX, startY, goalX, goalY, limit, range, damage, price, steps, hp;
    char symbol;
    std::string line;
    // reading structure of map
    mapFile >> width;
    mapFile >> height;
    mapFile >> startX;
    mapFile >> startY;
    mapFile >> goalX;
    mapFile >> goalY;
    mapFile >> data.m_limit;
    std::getline(mapFile,line);
    std::vector<std::vector<char>> mapData;
    mapData.resize(width);
    for (auto & column:mapData)
        column.resize(height);
    // reading map with units and towers positions
    for (int y = 0; y < height; y++) {
        std::getline(mapFile,line);
        for (int x = 0; x < width; x++) {
            if(line[x] == 'F')
                finish = std::make_shared<CTile>(x, y, 'F');
            if(line[x] == 'S')
                start = std::make_shared<CTile>(x, y, 'S');
            mapData[x][y] = line[x];
        }
    }
    // reading towers definitions, making casts for cloning
    for (int i = 0; i < 3; i++){
        mapFile >> symbol;
        mapFile >> range;
        mapFile >> damage;
        mapFile >> price;
        if(symbol == 'A')
            all_towers[symbol] = std::shared_ptr<CTower>(new CTowerArcher(0, 0, symbol, range, damage, price));
        if(symbol == 'B')
            all_towers[symbol] = std::shared_ptr<CTower>(new CTowerBombarda(0, 0, symbol, range, damage, price));
        if(symbol == 'C')
            all_towers[symbol] = std::shared_ptr<CTower>(new CTowerCaesar(0, 0, symbol, range, damage, price));
        std::getline(mapFile, line);
    }
    // reading unit stats
    mapFile >> symbol;
    mapFile >> steps;
    mapFile >> hp;
    std::list<size_t> unit_hp{};
    if (! is_new_game){
        while (mapFile.peek() != '\n'){
            mapFile >> hp;
            unit_hp.emplace_back(hp);
        }
    }
    tiles.resize(width);
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            symbol = mapData[x][y];
            tiles[x].emplace_back(std::make_shared<CTile>(x, y, symbol));
            if (symbol <= 'C' && symbol >= 'A')
                tiles[x][y] = all_towers[symbol]->clone(x, y);
            if (symbol == 'S')
                tiles[x][y] = start;
            if (symbol == 'F')
                tiles[x][y] = finish;
        }
    }
    bool useBFS = true;
    mapFile >> useBFS;
    mapFile.close();
    makePath(useBFS);
}




void CMap::makePath(bool useBFS) {
    std::vector<std::vector<std::shared_ptr<Node>>> grid;
    grid.resize(width);
    for (size_t x = 0; x < width; x++){
        for (size_t y = 0; y < height; y++){
            grid[x].emplace_back(std::make_shared<Node>(*this, x, y));
            grid[x][y]->tile = tiles[x][y];
            if (!grid[x][y]->tile->canStep())
                grid[x][y]->flag = CLOSED;
        }
    }

    std::queue<std::shared_ptr<Node>> visited;
    visited.push(grid[start->getPosition().x][start->getPosition().y]);
    visited.front()->value = 0;
    auto current_node = visited.front();
    while (!visited.empty()){
        current_node = visited.front();
        if (current_node->tile == finish)
            break;
        visited.pop();
        size_t x = current_node->tile->getPosition().x;
        size_t y = current_node->tile->getPosition().y;
        std::vector<std::shared_ptr<Node>> container;
        if (x > 0)
            container.push_back(grid[x-1][y]);
        if (y > 0)
            container.push_back(grid[x][y-1]);
        if (x < width -1)
            container.push_back(grid[x+1][y]);
        if (y < height - 1)
            container.push_back(grid[x][y+1]);
        while(!container.empty()){
            auto successor_node = container.back();
            if (successor_node->flag == FRESH){
                successor_node->flag = OPEN;
                visited.push(successor_node);
                successor_node->value = current_node->value + 1;
                successor_node->parent = current_node;
            }
            container.pop_back();
        }
        current_node->flag = CLOSED;
    }
    if (current_node->tile != finish)
        return;
    auto tmp = current_node;
    size_t index = 0;
    while (tmp->parent){
        path[index++] = tmp->tile;
        tmp = tmp->parent;
    }
    path[index] = tmp->tile;
}

size_t CMap::heuristic(const size_t &x, const size_t &y) const {
    size_t x_offset{}, y_offset{};
    if (x > finish->getPosition().x)
        x_offset = x - finish->getPosition().x;
    else
        x_offset = finish->getPosition().x - x;

    if (y > finish->getPosition().y)
        y_offset = y - finish->getPosition().y;
    else
        y_offset = finish->getPosition().y - y;
    return x_offset + y_offset;
}
