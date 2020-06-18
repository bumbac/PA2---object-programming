//
// Created by sutymate on 4/29/20.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include "CMap.hpp"
#include "CTowerArcher.hpp"
#include "CTowerBombarda.hpp"
#include "CTowerCaesar.hpp"
#define FRESH 0
#define OPEN 1
#define CLOSED 2

CMap::CMap(const std::filesystem::path& file_path, bool is_new_game){
    // file_path is correct and can be opened/read
    std::ifstream map_file(file_path, std::ios::in);
    size_t range{}, damage{}, price{}, steps{}, reward{}, hp{};
    double ratio{};
    char symbol = 0;
    std::string line;
    std::getline(map_file, line);
    std::istringstream iss(line);

    // reading structure of map
    iss >> width >> height >> data.m_limit >> data.m_money;
    data.m_all_money = data.m_money;
    if (!is_new_game) {
        iss >> data.m_all_money >> data.m_units_killed >> data.m_units_escaped >> data.m_enemies_in_wave
            >> data.m_wave_cooldown;
        size_t all_units = data.m_units_escaped + data.m_units_killed + data.m_units_alive;
        // waves counter setting
        while (all_units-- != 0) {
            waves.front()--;
            if (waves.front() == 0) {
                if (waves.size() == 1)
                    break;
                waves.pop_front();
            }
        }
    }
    // reading map symbols
    std::vector<std::vector<char>> map_data;
    map_data.resize(width);
    for (auto & column:map_data)
        column.resize(height);
    // reading map with units and towers positions
    for (size_t y = 0; y < height; y++) {
        std::getline(map_file, line);
        std::istringstream iss(line);
        for (size_t x = 0; x < width; x++) {
            symbol = line[x];
            if(symbol == 'F')
                finish = std::make_shared<CTile>(x, y, symbol);
            if(symbol == 'S')
                start = std::make_shared<CTile>(x, y, symbol);
            map_data[x][y] = symbol;
        }
    }

    // reading towers definitions, making casts for cloning
    for (int i = 0; i < 3; i++){
        std::getline(map_file, line);
        std::istringstream iss(line);
        ratio = 0.1;
        iss >> symbol >> range >> damage >> price;
        if (! is_new_game)
            iss >> ratio;
        std::getline(map_file, line);
        if(symbol == 'A')
            all_towers[symbol] = std::shared_ptr<CTower>(new CTowerArcher(0, 0, symbol, range, damage, price,
                    ratio, line));
        if(symbol == 'B')
            all_towers[symbol] = std::shared_ptr<CTower>(new CTowerBombarda(0, 0, symbol, range, damage,
                    price, ratio, line));
        if(symbol == 'C')
            all_towers[symbol] = std::shared_ptr<CTower>(new CTowerCaesar(0, 0, symbol, range, damage, price, ratio,
                    line));
    }

    // reading unit stats
    std::getline(map_file, line);
    std::istringstream iss2 (line);
    iss2 >> symbol >> steps >> reward >> hp;
    // making CUnit cast for cloning, stays on start CTile
    auto start_unit = std::make_shared<CUnit>(start->getPosition(), symbol, steps, reward, hp);
    std::list<size_t> unit_hp{};
    if (! is_new_game){
        // reading hps of units on map, sorted from finish to start
        std::getline(map_file, line);
        std::istringstream iss(line);
        while(iss >> hp)
            unit_hp.emplace_back(hp);
    }
    if (is_new_game)
        use_BFS = std::rand() % 2;
    else
        map_file >> use_BFS;
    map_file.close();
    tiles.resize(width);
    // creating CTiles
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            symbol = map_data[x][y];
            tiles[x].emplace_back(std::make_shared<CTile>(x, y, symbol));
            // creating towers
            if (symbol <= 'C' && symbol >= 'A') {
                auto tower = all_towers[symbol]->clone(x, y);
                tiles[x][y] = tower;
                towers.push_back(tower);
            }
            if (symbol == 'S')
                tiles[x][y] = start;
            if (symbol == 'F')
                tiles[x][y] = finish;
        }
    }
    // auxiliary position for unit cloning
    units[0] = start_unit;
    makePath(use_BFS, unit_hp);
    units[path.size() + 1] = start_unit;
    units.erase(0);
    data.m_units_alive = units.size() - 1;
}

void CMap::makePath(bool useBFS, std::list<size_t> & unit_hp) {
    std::vector<std::vector<std::shared_ptr<Node>>> grid;
    grid.resize(width);
    for (size_t x = 0; x < width; x++){
        for (size_t y = 0; y < height; y++){
            grid[x].emplace_back(std::make_shared<Node>(tiles[x][y]));
            if (!grid[x][y]->tile->canStep())
                grid[x][y]->flag = CLOSED;
            if (grid[x][y]->tile->getSymbol() == units[0]->getSymbol() || grid[x][y]->tile->getSymbol() == '.')
                grid[x][y]->flag = FRESH;
            if (!useBFS)
                grid[x][y]->value = heuristic(x, y);
        }
    }
    // find path from start to finish
    std::shared_ptr<Node> last_node;
    if (useBFS)
        // BFS uses queue
        BFS(grid, last_node);
    else
        // Greedy space search uses priority queue
        GreedySearch(grid, last_node);

    // this should never happen
    if (last_node->tile != finish) {
        throw std::runtime_error("There is no path from start to finish.");
        return;
    }

    // reconstruct path and mark tiles with '.'
    auto tmp = last_node->parent;
    size_t index = 1;
    path[index++] = last_node->tile;
    auto unit = units.begin()->second;
    // start node has no parent
    while (tmp->parent){
        if (tmp->tile->getSymbol() == unit->getSymbol()) {
            auto new_unit = std::make_shared<CUnit>(tmp->tile->getPosition(), unit->getSymbol(), unit->getSteps(),
                                                unit->getReward(), unit_hp.front());
            // setting correct health of units on map, some could be damaged, some are differently upgraded
            unit_hp.pop_front();
            units[index] = new_unit;
            tmp->tile = new_unit;
            tiles[new_unit->getPosition().x][new_unit->getPosition().y] = new_unit;
        } else
            tmp->tile->setSymbol('.');
        path[index++] = tmp->tile;
        tmp = tmp->parent;
    }
}

void CMap::GreedySearch(const std::vector<std::vector<std::shared_ptr<Node>>> &grid, std::shared_ptr<Node> &last_node) const {
    // I chose greedy search because it provides more interesting paths than a_star
    std::priority_queue<std::shared_ptr<Node>> visited;
    visited.push(grid[start->getPosition().x][start->getPosition().y]);
    while(!visited.empty()){
        last_node = visited.top();
        if (last_node->tile == finish)
            break;
        visited.pop();

        size_t x = last_node->tile->getPosition().x;
        size_t y = last_node->tile->getPosition().y;
        if (x > 0)
            if (grid[x - 1][y]->flag == FRESH) {
                visited.push(grid[x - 1][y]);
                grid[x - 1][y]->parent = last_node;
                grid[x - 1][y]->flag = OPEN;
            }
        if (y > 0)
            if (grid[x][y-1]->flag == FRESH) {
                visited.push(grid[x][y - 1]);
                grid[x][y - 1]->parent = last_node;
                grid[x][y - 1]->flag = OPEN;
            }
        if (x < width - 1)
            if (grid[x + 1][y]->flag == FRESH) {
                visited.push(grid[x + 1][y]);
                grid[x + 1][y]->parent = last_node;
                grid[x + 1][y]->flag = OPEN;
            }
        if (y < height - 1)
            if(grid[x][y + 1]->flag == FRESH) {
                visited.push(grid[x][y + 1]);
                grid[x][y + 1]->parent = last_node;
                grid[x][y + 1]->flag = OPEN;
            }
        last_node->flag = CLOSED;
    }
}

void
CMap::BFS(const std::vector<std::vector<std::shared_ptr<Node>>> &grid, std::shared_ptr<Node> &last_node) const {
    std::queue<std::shared_ptr<Node>> visited;
    visited.push(grid[start->getPosition().x][start->getPosition().y]);
    while (!visited.empty()){
        last_node = visited.front();
        if (last_node->tile == finish)
            break;
        visited.pop();
        size_t x = last_node->tile->getPosition().x;
        size_t y = last_node->tile->getPosition().y;
        std::vector<std::shared_ptr<Node>> container;
        if (x > 0)
            container.push_back(grid[x-1][y]);
        if (y > 0)
            container.push_back(grid[x][y-1]);
        if (x < width - 1)
            container.push_back(grid[x+1][y]);
        if (y < height - 1)
            container.push_back(grid[x][y+1]);
        for (auto & successor_node : container){
            if (successor_node->flag == FRESH){
                successor_node->flag = OPEN;
                visited.push(successor_node);
                successor_node->value = last_node->value + 1;
                successor_node->parent = last_node;
            }
        }
        last_node->flag = CLOSED;
    }
}
// manhattan distance heuristic
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


bool CMap::moveUnits(void) {
    // move every unit
    for (auto it = units.begin(); it != --units.end();){
        // easier orientation in code
        auto unit = *it;
        size_t position = unit.first;
        // returns true if unit found free position on path
        if (unit.second->moveUnit(path, position)){
            TCoordinate old_position = unit.second->getPosition();
            // blank tile for replacing
            std::shared_ptr<CTile> blank = std::make_shared<CTile>((unit.second->getPosition()),'.');
            if (path[position] == finish){
                data.m_units_escaped++;
                data.m_units_alive--;
                }
            else {
                TCoordinate new_position = path[position]->getPosition();
                units[position] =  unit.second->clone(new_position);
                path[position] = units[position];
                tiles[new_position.x][new_position.y] = path[position];
            }
            tiles[old_position.x][old_position.y] = blank;
            path[unit.first] = blank;
            // map erase does not invalidates the structure and iterators of container
            it = units.erase(it);
            continue;
        }
        it++;
    }
    // waves mechanism, every wave has some units and every wave upgrades the new units spawned
    if (waves.front() == 0 && waves.size() > 1){
            waves.pop_front();
        messages.emplace_back("NEW WAVE! Enemies are stronger by " + std::to_string(waves.front()) + "%.");
        units.rbegin()->second->upgrade(waves.front() / 100.0);
        data.m_enemies_in_wave = waves.front();
        data.m_wave_cooldown = 5;
    }
    // preventing from playing long games, units get upgraded quite a lot after all enemy waves have been destroyed
    if (waves.size() == 1)
        units.rbegin()->second->upgrade(2.0);

    if (data.m_wave_cooldown == 0) {
        auto & spawn_tile = path.rbegin()->second;
        if (spawn_tile->canStep()) {
            auto new_unit = units.rbegin()->second->clone(spawn_tile->getPosition());
            spawn_tile = new_unit;
            units[path.size()] = new_unit;
            tiles[spawn_tile->getPosition().x][spawn_tile->getPosition().y] = new_unit;
            data.m_units_alive++;
            waves.front()--;
        }
    }
    else
        data.m_wave_cooldown--;
    return data.m_units_escaped >= data.m_limit;
}

void CMap::attackTowers(void) {
    // each tower attacks once
    for (const auto & tower : towers){
        size_t dead_index = tower->attack(units);
        // returns position on path = dead_index
        if (dead_index != 0){
            data.m_units_killed++;
            data.m_units_alive--;
            data.m_money += units[dead_index]->getReward();
            data.m_all_money += units[dead_index]->getReward();
            messages.emplace_back( "Killed unit #: " + std::to_string(units[dead_index]->getPosition().x + 1) + " "
                       + std::to_string(units[dead_index]->getPosition().y + 1) + ", gold:"
                       + std::to_string(units[dead_index]->getReward()));
            std::shared_ptr<CTile> blank = std::make_shared<CTile>(units[dead_index]->getPosition(), '.');
            path[dead_index] = blank;
            tiles[units[dead_index]->getPosition().x][units[dead_index]->getPosition().y] = blank;
            units.erase(dead_index);
        }
    }
}

void CMap::placeTower(std::string & command) {
    auto it = command.begin() + 6;
    std::string x, y;
    char symbol = ::toupper(command[4]);
    // parsing numbers from command
    while (*it != ' ')
        x += *it++;

    it++;
    while (it != command.end())
        y += *it++;

    // command has correct structure, no exceptions
    size_t x_pos = std::stoul(x) - 1;
    size_t y_pos = std::stoul(y) - 1;
    auto tower = all_towers[symbol];
    size_t price = tower->getPrice();

    if (price > data.m_money) {
        std::string tmp;
        tmp = "Not enough money to buy ";
        tmp += symbol;
        tmp +=".";
        messages.emplace_back(tmp);
        return;
    }

    if (blocksPath(x_pos, y_pos)) {
        messages.emplace_back("Can't place tower on " + std::to_string(x_pos + 1) + " "
        + std::to_string(y_pos + 1) + ". It blocks the path.");
        return;
    }

    if (tiles[x_pos][y_pos]->canStep() ){
        auto tmp  = tower->clone(x_pos, y_pos);
        tiles[x_pos][y_pos] = tmp;
        towers.push_back(tmp);
        data.m_money -= tower->getPrice();
    }
    else
        messages.emplace_back("Can't place tower here.");
}

bool CMap::validUserAction(std::string & command) {
    char symbol = ::toupper(command[4]);
    if (all_towers.find(symbol) != all_towers.end()) {
        size_t number_position = std::string("buy X ").length();
        size_t space_position = command.find_first_of(' ', number_position);
        if (space_position == std::string::npos) {
            messages.emplace_back("Invalid command.");
            return false;
        }
        std::string number = command.substr(number_position, space_position - number_position);
        size_t x = 0;
        size_t y = 0;

        try {
            x = std::stol(number);
        }
        catch (const std::invalid_argument &e) {
            messages.emplace_back("Invalid position.");
            return false;
        }
        catch (const std::out_of_range &e) {
            messages.emplace_back("Position out of range.");
            return false;
        }
        number_position = space_position + 1;
        number = command.substr(number_position);

        try {
            y = std::stol(number);
        }
        catch (const std::invalid_argument &e) {
            messages.emplace_back("Invalid position.");
            return false;
        }
        catch (const std::out_of_range &e) {
            messages.emplace_back("Position out of range.");
            return false;
        }

        if (x > width || y > height || x == 0 || y == 0) {
            messages.emplace_back("Position out of range.");
            return false;
        } else {
            command = "buy ";
            command += symbol;
            command += " ";
            command += std::to_string(x) + " " + std::to_string(y);
            return true;
        }
    }
    messages.emplace_back("No item in shop, sorry.");
    return false;
}

bool CMap::blocksPath(size_t &x, size_t &y) const {
    TCoordinate tower_tile (x, y);
    for (const auto & tile:path)
        if (tower_tile == tile.second->getPosition())
            return true;
    return false;
}

void CMap::printMap(void)  {
    std::cout << std::endl;
    if (waves.size() > 1)
        std::cout << "   Enemies this wave: " << data.m_enemies_in_wave << std::endl;
    else
        std::cout << "   LAST INFINITE WAVE!!! Good luck. Every new enemy is stronger than before." << std::endl;
    if (data.m_wave_cooldown)
        std::cout << "   Enemies coming in: " << data.m_wave_cooldown << std::endl;
    std::cout << "   Units killed: " << data.m_units_killed << std::endl;
    std::cout << "   Units escaped: " << data.m_units_escaped << std::endl;
    std::cout << "   Units so far: " << data.m_units_alive + data.m_units_escaped + data.m_units_killed << std::endl;
    std::cout << "   Units limit: " << data.m_limit<< std::endl;
    std::cout << "   Money: " << data.m_money << std::endl;
    std::cout << *this;
    for(const auto & message : messages)
        std::cout << message << std::endl;
    messages.clear();
}

std::ostream &operator<<(std::ostream &os, const CMap &map) {
    // numbering on the top
    std::cout << "    ";
    for (size_t x = 1; x <= map.width; x += 2)
        if (x < 10)
            std::cout << " |";
        else
            std::cout << x/10 << '|';
    std::cout << std::endl;
    std::cout << "    ";
    // numbering on sides and printing tiles symbols
    for (size_t x = 1; x <= map.width; x += 2)
        std::cout << (x - (x/10) * 10) << '|';
    std::cout << std::endl;
    for (size_t y = 0; y < map.height; y++) {
        std::cout << std::setw(3) << std::setfill(' ') << y + 1 << ' ';
        for (size_t x = 0; x < map.width; x++) {
            // tile symbols
                os << *(map.tiles[x][y].get());
        }
        os << std::endl;
    }
    std::cout << std::setw(0) << "    ";
    for (size_t x = 2; x <= map.width; x += 2)
        if (x < 10)
            std::cout << "| ";
        else
            std::cout << '|' << x/10;
    std::cout << std::endl;
    std::cout << "    ";
    for (size_t x = 2; x <= map.width; x += 2)
        std::cout << '|' << (x - (x/10) * 10);
    std::cout << std::endl;
    return os;
}

void CMap::upgrade(char tower_symbol) {
    if (data.m_money >= 1000)
        data.m_money -= 1000;
    messages.emplace_back(&"UPGRADED TOWERS " [ tower_symbol]);
    tower_symbol = ::toupper(tower_symbol);
    all_towers[tower_symbol]->upgrade(tower_symbol);
    // if symbol matches tower symbol, tower gets upgraded. otherwise upgrade is ignored
    for (auto & tower : towers)
        tower->upgrade(tower_symbol);
}

bool CMap::saveGame() const{
    std::cout << "SAVING GAME..." << std::endl;
    std::stringstream context;
    context << width << ' ' << height << ' ' << data.m_limit << ' ' << data.m_money << ' ' << data.m_all_money << ' '
    << data.m_units_killed << ' ' << data.m_units_escaped << ' ' << data.m_enemies_in_wave << ' '
    << data.m_wave_cooldown;
    context << std::endl;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++)
            context << *(tiles[x][y].get());
        context << std::endl;
    }
    for (const auto & tower : all_towers) {
        tower.second->save(context);
        context << std::endl;
    }
    // start tile is unit for cloning
    units.rbegin()->second->save(context);
    context << std::endl;
    for (auto it = units.begin(); it != --units.end(); it++)
        context << it->second->getHealth() << ' ';
    // remove last space
    context.seekp(-1, std::ios::cur);
    context << std::endl;
    context << use_BFS;
    context << std::endl;
    auto hasher = std::hash<std::string>();
    auto hash = hasher(context.str());
    time_t t {0};
    time(&t);
    std::string save_name{"saves/"};
    save_name += ctime(&t);
    // pop newline
    save_name.pop_back();
    std::ofstream save_file(save_name, std::ios::out);
    // write privilege may be denied
    if (! save_file.good())
        throw std::runtime_error("Can't create save.\n");
    save_file << context.rdbuf() << std::setw(std::to_string((size_t) 0 - 1).length()) << std::setfill('0')
        << hash << std::endl;
    save_file.close();
    std::cout << "GAME SAVED to " << save_name  << '.' << std::endl;
    return true;
}

void CMap::showShop() const {
    int fill_width = 20;
    std::cout << "MONEY AVAILABLE: " << data.m_money << std::endl;
    std::cout << "TOWERS:" << std::endl;
    std::cout << "SYMBOL" << std::setw(fill_width) << " |" << std::setw(fill_width) << "PRICE |"
    << std::setw(fill_width) << "DAMAGE |" << std::setw(fill_width) << "RANGE |" << std::setw(fill_width) <<  std::endl;
    for (const auto & tower : all_towers)
        std::cout << std::setw(8) << std::left << *tower.second << std::right << std::setw(fill_width)
        << tower.second->getPrice() << std::setw(fill_width) << tower.second->getDamage() << std::setw(fill_width)
        << tower.second->getRange() << std::endl << tower.second->getDescription() << std::endl;
    std::cout << std::endl << "Command:  buy <TOWER SYMBOL> <WIDTH POSITION> <HEIGHT>POSITION>" << std::endl;
    std::cout << std::endl;
    std::cout << "ENEMY UNIT:" << std::endl;
    std::cout << "SYMBOL:" << " " <<  *start << " HEALTH: " << units.rbegin()->second->getHealth() << " STEPS: "
    << units.rbegin()->second->getSteps()  << " REWARD: "  << units.rbegin()->second->getReward() << std::endl
    << std::endl;
    std::cout << "UPGRADE for TOWERS:" << std::endl;
    std::cout << "Increases damage and range of one type of towers (A, B, C). Upgrades built towers and also towers\n"
                 "built in the future. Costs 1000 gold. Type upgrade <symbol of tower>." << std::endl;
    std::cout << std::endl;
    std::cout << "Buy and place towers with command:\nbuy <TOWERSYMBOL> <width position> <height position>" << std::endl;
    std::cout << "For example: buy a 12 3" << std::endl;
    std::cout << "For example: Buy A 12 3" << std::endl;
    std::cout << "For example: uPgRade a" << std::endl;
    std::cout << "You can also place towers in game." << std::endl;
}

const TData &CMap::gameEndData() const{
    return data;
}

