//
// Created by sutymate on 4/29/20.
//

#include "CUpgrade.h"

bool CUpgrade::operator<(const CUpgrade &other) const {
    return this->name.compare(other.name) < 0;
}

CUpgrade::CUpgrade(const std::string &name, const std::string &mDescription, int mPercent, ETarget target)
: name(name), m_description(mDescription), m_Percent(mPercent), target(target) {}
