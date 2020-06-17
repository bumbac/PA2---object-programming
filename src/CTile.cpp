//
// Created by sutymate on 4/29/20.
//

#include "CTile.h"
CTile::CTile(const TCoordinate position, char symbol)
        : position(position), symbol(symbol){}

CTile::CTile(const size_t x, const size_t y, char symbol)
        :position(x, y), symbol(symbol){}

TCoordinate CTile::getPosition(void) const {
    return this->position;
}

bool CTile::canStep() const {
    return symbol == ' ' || symbol == 'F' || symbol == '.';
}

std::ostream &operator<<(std::ostream &os, const CTile &tile) {
    os << tile.symbol;
    return os;
}

void CTile::save(std::ostream &middle_man){
    middle_man << symbol;
}

char CTile::getSymbol(){
    return symbol;
}

void CTile::setSymbol(char symbol) {
    this->symbol = symbol;
}

bool TCoordinate::operator==(const TCoordinate &other) const {
    return this->x == other.x && this->y == other.y;
}

