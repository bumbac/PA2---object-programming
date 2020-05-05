//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTOWER_H
#define SEM_CTOWER_H

#include "CTile.h"
#include "CUpgrade.h"
#include "CTowerArcher.h"

class CTower: public CTile{

public:
    CTower(const CTower *origin, size_t & x, size_t & y, const std::shared_ptr<CTile> goal);

    virtual std::shared_ptr<CUnit> attack(std::map<size_t, std::shared_ptr<CUnit>> & units) const = 0;

    virtual std::shared_ptr<CTower> clone(size_t & x, size_t & y, const std::shared_ptr<CTile> & goal)const = 0;

    inline bool canStep() const override;

    inline std::string getName(void)const;

    inline size_t getPrice(void)const;

    inline size_t getRange() const;

protected:
    const std::string name;
    size_t range;
    size_t damage;
    size_t price;
};
#endif //SEM_CTOWER_H
