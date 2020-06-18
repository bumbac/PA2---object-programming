//
// Created by sutymate on 5/5/20.
//

#ifndef SEM_CTOWERBOMBARDA_HPP
#define SEM_CTOWERBOMBARDA_HPP

#include "CTower.hpp"
/**
 * Attacks unit in range with smallest health remaining.
 */
class CTowerBombarda: public CTower{
public:
    CTowerBombarda(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price,
                   double ratio, std::string description);

    size_t attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const override;

    std::shared_ptr<CTower> clone(size_t &x, size_t &y) const override;
};


#endif //SEM_CTOWERBOMBARDA_HPP