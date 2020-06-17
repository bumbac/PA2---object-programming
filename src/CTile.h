//return CTower::canStep();
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTILE_H
#define SEM_CTILE_H
#include <memory>
#include <vector>
#include <ostream>

class CUnit;
class CTower;
/**
 * Basic 2D cartesian coordinates structure indexed from 0.
 */
struct TCoordinate{
    TCoordinate(const size_t & x, const size_t & y)
        :x(x), y(y){};
    bool operator==(const TCoordinate & other) const;
    size_t x;
    size_t y;
};
/**
 * Base class representing every tile on map(tile, unit, tower).
 */
class CTile{
public:
    /**
     * Creates tile and calculates value value.
     * @param x representing width position
     * @param position representing height position
     * @param symbol symbol shown in game, walls represented by '|', '-', '+'
     * @param goal
     */
    CTile(const TCoordinate position, char symbol = ' ');
    CTile(const size_t x, const size_t y, char symbol = ' ');
    /**
     * Functions used in unit movement and tower placing.
     * @return true if @param symbol is free space ' ' or if its finish 'F'
     */
    [[nodiscard]] bool canStep() const;

    virtual void save(std::ostream &middle_man);

    [[nodiscard]] TCoordinate getPosition(void)const;

    /**
     * Puts only symbol to output stream. Not used for saving.
     * @param os
     * @param tile
     * @return
     */
    friend std::ostream & operator<<(std::ostream &os, const CTile &tile);
    void setSymbol(char symbol);
    char getSymbol();
protected:
    TCoordinate position;
    char symbol;
};
#endif //SEM_CTILE_H
