//
// Created by sutymate on 4/29/20.
//

#ifndef SEM_CUPGRADE_H
#define SEM_CUPGRADE_H

#include <string>
#include "ETarget.h"
/**
 * Player can buy and use upgrade more than once.
 * Upgrade is also used by game system for making units stronger.
 */
class CUpgrade{
    inline bool operator<(const CUpgrade &other) const;

public:
    CUpgrade(const std::string &name, const std::string &mDescription, int mPercent, ETarget target);
private:
    /**
     * name will be used as key in map
     */
    const std::string name;
    /**
     * Description for shop
     */
    std::string m_description;
    /**
     * Upgrades can be used more than once so the effect is in percent.
     */
    int m_Percent;
    /**
     * target can be tower or units. All units or towers are affected <can be changed actually>.
     */
    ETarget target;
};
#endif //SEM_CUPGRADE_H
