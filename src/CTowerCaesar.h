//
// Created by sutymate on 5/5/20.
//

#ifndef SEM_CTOWERCAESAR_H
#define SEM_CTOWERCAESAR_H

#include "CTower.h"
/**
 * Tower has 10% chance of striking critical damage to unit closest to finish in range and killing it instantly.
 */
class CTowerCaesar: public CTower {
public:
    CTowerCaesar(const CTowerCaesar *origin, size_t &x, size_t &y);

    CTowerCaesar(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price);

    bool canStep() const override;

    TCoordinate getPosition(void) const override;

    std::shared_ptr<CUnit> attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const override;

    std::shared_ptr<CTower> clone(size_t &x, size_t &y) const override;
};


#endif //SEM_CTOWERCAESAR_H
