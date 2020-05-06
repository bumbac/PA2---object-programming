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
    const std::string name;
    std::string m_description;
    int m_Percent;
    ETarget target;
};
#endif //SEM_CUPGRADE_H
