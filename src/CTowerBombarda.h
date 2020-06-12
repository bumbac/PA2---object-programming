//
// Created by sutymate on 5/5/20.
//

#ifndef SEM_CTOWERBOMBARDA_H
#define SEM_CTOWERBOMBARDA_H

#include "CTower.h"
/**
 * Attacks unit in range with smallest health remaining.
 */
class CTowerBombarda: public CTower{
public:
    CTowerBombarda(const CTowerBombarda *original, size_t &x, size_t &y);

    CTowerBombarda(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price);

    bool canStep() const override;

    TCoordinate getPosition(void) const override;

    std::shared_ptr<CUnit> attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const override;

    std::shared_ptr<CTower> clone(size_t &x, size_t &y) const override;
};


#endif //SEM_CTOWERBOMBARDA_H
