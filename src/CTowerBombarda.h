//
// Created by sutymate on 5/5/20.
//

#ifndef SEM_CTOWERBOMBARDA_H
#define SEM_CTOWERBOMBARDA_H


#include "CTower.h"

class CTowerBombarda: public CTower{
public:
    CTowerBombarda(const CTowerBombarda *original, size_t &x, size_t &y, const std::shared_ptr<CTile> &goal);

    std::shared_ptr<CUnit> attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const override;

    std::shared_ptr<CTower> clone(size_t &x, size_t &y, const std::shared_ptr<CTile> &goal) const override;
};


#endif //SEM_CTOWERBOMBARDA_H
