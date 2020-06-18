//
// Created by sutymate on 5/5/20.
//

#ifndef SEM_CTOWERARCHER_HPP
#define SEM_CTOWERARCHER_HPP

#include "CTower.hpp"
/**
 * Attacks enemy closest to finish.
 */
class CTowerArcher : public CTower {
public:
    CTowerArcher(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price,
                 double ratio, std::string description);

    size_t attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const override;

    std::shared_ptr<CTower> clone(size_t &x, size_t &y) const override;
};


#endif //SEM_CTOWERARCHER_HPP
