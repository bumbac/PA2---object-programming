//
// Created by sutymate on 4/29/20.
//

#ifndef SEM_CUPGRADE_H
#define SEM_CUPGRADE_H

#include <string>
#include "ETarget.h"

class CUpgrade{
    inline bool operator<(const CUpgrade &other) const;
private:
    const std::string name;
    std::string m_description;
    int m_Percent;
    ETarget target;
};
#endif //SEM_CUPGRADE_H
