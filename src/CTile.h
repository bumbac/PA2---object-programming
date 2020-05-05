//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTILE_H
#define SEM_CTILE_H
#include <memory>
#include <vector>
#include <ostream>            tiles[w]

#include "CUnit.h"

struct TCoordinate{
    TCoordinate( const size_t & x, const size_t & y)
        :x(x), y(y){};
    bool operator==(const TCoordinate & other) const;
    const size_t x;
    const size_t y;
};

class CTile{
public:
    CTile(const size_t & x, const size_t & y, char symbol, std::shared_ptr<CTile> goal);
    CTile( CUnit * source);

    virtual bool canStep() const;

    TCoordinate getPosition(void)const;

    friend std::ostream &operator<<(std::ostream &os, const CTile &tile);

protected:
    const TCoordinate position;
    char symbol;
    size_t m_heuristic;
};
#endif //SEM_CTILE_H
