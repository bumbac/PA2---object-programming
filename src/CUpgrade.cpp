//
// Created by sutymate on 4/29/20.
//

#include "CUpgrade.h"

bool CUpgrade::operator<(const CUpgrade &other) const {
    return this->name.compare(other.name) < 0;
}
