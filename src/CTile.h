//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTILE_H
#define SEM_CTILE_H
#include <memory>
#include <vector>
#include <ostream>
#include "CUnit.h"
/**
 * Basic 2D cartesian coordinates structure indexed from 0.
 */
struct TCoordinate{
    TCoordinate( const size_t & x, const size_t & y)
        :x(x), y(y){};
    bool operator==(const TCoordinate & other) const;
    const size_t x;
    const size_t y;
};
/**
 * Base class representing every tile on map(tile, unit, tower).
 */
class CTile{
public:
    /**
     * Creates tile and calculates heuristic value.
     * @param x representing width position
     * @param y representing height position
     * @param symbol symbol shown in game, walls represented by '|', '-', '+'
     * @param goal
     */
    CTile(const size_t & x, const size_t & y, char symbol, std::shared_ptr<CTile> goal);
    CTile( CUnit * source);
    /**
     * Functions used in unit movement and tower placing.
     * @return true if @param symbol is free space ' '
     */
    virtual bool canStep() const;

    virtual TCoordinate getPosition(void)const;
    /**
     * Puts only symbol to output stream. Not used for saving.
     * @param os
     * @param tile
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const CTile &tile);

protected:
    const TCoordinate position;
    char symbol;
    size_t m_heuristic;
};
#endif //SEM_CTILE_H
