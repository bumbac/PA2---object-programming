//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CUNIT_HPP
#define SEM_CUNIT_HPP

#include "CTile.hpp"
#include <memory>
#include <ostream>
#include <map>

class CUnit: public CTile{
public:
    CUnit(const TCoordinate & coordinate, char symbol, size_t steps, size_t reward, size_t currentHp);
    /**
     * Unit tries to move as far as possible with limit of variable member steps. Unit can stay on one place.
     * @param path
     * @param position
     * @return
     */
    bool moveUnit(std::map<size_t, std::shared_ptr<CTile>> & path, size_t & position) const;
    /**
     * @param attack to be received.
     * @return true if unit is killed
     */
    bool receiveAttack(const size_t & attack);

    void save(std::ostream & middle_man) const override;

    /**
     * Used by Bombarda tower target selection
     * @return current_hp
     */
    size_t getHealth() const;

    size_t getReward() const;

    size_t getSteps()const;

    std::shared_ptr<CUnit> clone(const TCoordinate & coordinate) const;

    void upgrade(double ratio_bump);

protected:
    size_t steps;
    size_t reward;
    size_t current_hp;
};
#endif //SEM_CUNIT_HPP
