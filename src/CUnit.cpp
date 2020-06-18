//
// Created by sutymate on 4/29/20.
//
#include <cmath>
#include "CUnit.hpp"

CUnit::CUnit(const TCoordinate &coordinate, char symbol, size_t steps, size_t reward, size_t currentHp)
        : CTile(coordinate, symbol), steps(steps), reward(reward), current_hp(currentHp) {}

bool CUnit::moveUnit(std::map<size_t, std::shared_ptr<CTile>> &path, size_t & position)const {
    // reached finish, position = 1 in path
    if (position <= steps){
        position = 1;
        return true;
    }
    // try to move as far as possible and then try closer position
    for (size_t i = position - steps; i < position; i++)
        if(path[i]->canStep()){
            position = i;
            return true;
        }
    return false;
}

bool CUnit::receiveAttack(const size_t &attack) {
    if (current_hp <= attack)
        return true;
    else{
        current_hp -= attack;
        return false;
    }
}

size_t CUnit::getHealth() const {
    return current_hp;
}

std::shared_ptr<CUnit> CUnit::clone(const TCoordinate & coordinate) const {
    return std::make_shared<CUnit>(coordinate, this->symbol, this->steps, this->reward, this->current_hp);
}

size_t CUnit::getReward() const {
    return reward;
}

// preventing unsigned overflow
void CUnit::upgrade(double ratio_bump) {
    size_t previous_hp = current_hp;
    current_hp = std::floor(current_hp * (1.0 + ratio_bump));
    if (previous_hp > current_hp)
        current_hp = previous_hp;
}

void CUnit::save(std::ostream & middle_man)const{
    middle_man << symbol << ' ' << steps << ' ' << reward << ' ' << current_hp;
}

size_t CUnit::getSteps() const {
    return steps;
}

