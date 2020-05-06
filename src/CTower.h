//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTOWER_H
#define SEM_CTOWER_H

#include "CTile.h"
#include "CUpgrade.h"
#include "CTowerArcher.h"
/**
 * abstract class representing
 */
class CTower: public CTile{

public:
    /**
     * Creates a tower object same as @param origin with new position.
     * @param origin Tower template(CTowerArcher, CTowerBombarda, CTowerCaesar) used for cloning
     * @param x new position
     * @param y new position
     * @param goal for computing heuristic
     */
    CTower(const CTower *origin, size_t & x, size_t & y, const std::shared_ptr<CTile> goal);
    /**
     * Abstract function, every type of tower has special implementation.
     */
    virtual std::shared_ptr<CUnit> attack(std::map<size_t, std::shared_ptr<CUnit>> & units) const = 0;
    /**
     * CTower is abstract, each type makes its own clone in new position.
     * @param x new position
     * @param y new position
     * @param goal for computing heuristic
     * @return smart pointer for automatic deallocation
     */
    virtual std::shared_ptr<CTower> clone(size_t & x, size_t & y, const std::shared_ptr<CTile> & goal)const = 0;

    inline bool canStep() const override;

    TCoordinate getPosition(void) const override;

    inline size_t getPrice(void)const;

protected:
    const std::string name;
    size_t range;
    size_t damage;
    size_t price;
};
#endif //SEM_CTOWER_H
