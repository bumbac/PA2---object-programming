//
// Created by sutymate on 5/5/20.
//

#ifndef SEM_CTOWERCAESAR_H
#define SEM_CTOWERCAESAR_H


#include "CTower.h"

class CTowerCaesar: public CTower {
public:
    CTowerCaesar(const CTowerCaesar *origin, size_t &x, size_t &y, const std::shared_ptr<CTile> &goal);

    std::shared_ptr<CUnit> attack(std::map<size_t, std::shared_ptr<CUnit>> &units) const override;

    std::shared_ptr<CTower> clone(size_t &x, size_t &y, const std::shared_ptr<CTile> &goal) const override;

private:
    unsigned number_of_targets = 3;
};


#endif //SEM_CTOWERCAESAR_H
