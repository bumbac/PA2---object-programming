//
// Created by sutymate on 4/29/20.
//

#include "CTile.h"

CTile::CTile(const size_t & x, const size_t & y, char symbol, std::shared_ptr<CTile> goal)
        :position(TCoordinate(x,y)), symbol(symbol), m_heuristic(0) {
    size_t x_offset = 0;
    size_t y_offset = 0;
    if (x > goal->position.x)
        x_offset = x - goal->position.x;
    else
        x_offset = goal->position.x - x;
    if (y > goal->position.y)
        y_offset = y - goal->position.y;
    else
        y_offset = goal->position.y - y;
    m_heuristic = x_offset + y_offset;
}

TCoordinate CTile::getPosition(void) const {
    return this->position;
}

bool CTile::canStep() const {
    return symbol == ' ';
}

CTile::CTile(CUnit *source)
    :position(TCoordinate(source->getPosition().x, source->getPosition().y)), m_heuristic(source->getHeuristic()), symbol(' '){}

std::ostream &operator<<(std::ostream &os, const CTile &tile) {
    os << tile.symbol;
    return os;
}

bool TCoordinate::operator==(const TCoordinate &other) const {
    return this->x == other.x && this->y == other.y;
}

