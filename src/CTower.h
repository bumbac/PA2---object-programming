//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTOWER_H
#define SEM_CTOWER_H

#include <map>
#include "CTile.h"
#include "CUnit.h"
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
     * @param goal for computing value
     */
    CTower(const CTower *origin, const size_t &x, const size_t &y);

    CTower(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price, double ration);

    /**
     * Abstract function, every type of tower has special implementation.
     */
    virtual size_t attack(std::map<size_t, std::shared_ptr<CUnit>> & units) const = 0;
    void upgrade(char symbol);
    /**
     * CTower is abstract, each type makes its own clone in new position.
     * @param x new position
     * @param y new position
     * @param goal for computing value
     * @return smart pointer for automatic deallocation
     */
    virtual std::shared_ptr<CTower> clone(size_t &x, size_t &y)const = 0;

    void save(std::ostream & middle_man)override;

    size_t getPrice(void)const;
    size_t getDamage(void)const;
    size_t getRange(void)const;

protected:
    size_t range;
    size_t damage;
    size_t price;
    double upgrade_ratio;
};
#endif //SEM_CTOWER_H
