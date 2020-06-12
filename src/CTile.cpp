//
// Created by sutymate on 4/29/20.
//

#include "CTile.h"

CTile::CTile(const size_t & x, const size_t & y, const char symbol)
        : position(TCoordinate(x,y)), symbol(symbol){}

TCoordinate CTile::getPosition(void) const {
    return this->position;
}

bool CTile::canStep() const {
    return symbol == ' ';
}

CTile::CTile(CUnit *source)
    : position(TCoordinate(source->getPosition().x, source->getPosition().y)), symbol(' '){}

std::ostream &operator<<(std::ostream &os, const CTile &tile) {
    os << tile.symbol;
    return os;
}

bool TCoordinate::operator==(const TCoordinate &other) const {
    return this->x == other.x && this->y == other.y;
}

