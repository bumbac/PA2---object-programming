//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CUNIT_H
#define SEM_CUNIT_H

#include <map>
#include "CTile.h"
#include "CUpgrade.h"
class CUnit: public CTile{

public:
    CUnit(const size_t &x, const size_t &y, char symbol, const std::shared_ptr<CTile> &goal, const std::string &name,
          const size_t steps, size_t currentHp);
    /**
     * Two units cannot share one tile.
     * @return false, unit cannot access other unit tile or place tower here.
     */
    inline bool canStep() const override;

    inline TCoordinate getPosition(void) const override;
    /**
     * Unit tries to move as far as possible with limit of variable member steps. Unit can stay on one place.
     * @param path
     * @param position
     * @return
     */
    bool moveUnit(std::map<size_t, std::shared_ptr<CTile>> & path, size_t & position);
    /**
     * @param attack to be received.
     * @return true if unit is killed
     */
    bool receiveAttack(const size_t & attack);
    /**
     * Used for Bombarda tower target selection
     * @return current_hp
     */
    inline size_t getHealth() const;
protected:
    const std::string name;
    const size_t steps;
    size_t current_hp;
};
#endif //SEM_CUNIT_H
