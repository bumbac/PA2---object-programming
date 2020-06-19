//return CTower::canStep();
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTILE_HPP
#define SEM_CTILE_HPP
#include <ostream>

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
     * @param y representing height position
     * @param  symbol shown in game, walls represented by '|', '-', '+', path '.', start 'S', finish 'F'
     */
    CTile(const size_t x, const size_t y, char symbol = ' ');
    explicit CTile(const TCoordinate position, char symbol = ' ');
    /**
     * base class is trivial, does not need user-defined destructor
     */
    virtual ~CTile() = default;
    /**
     * Functions used in unit movement and tower placing.
     * @return true if member variable symbol is free space
     */
    [[nodiscard]] bool canStep() const;
    /**
     * Appends symbol to output stream. Derived classes append more data.
     * @param save_stream
     */
    virtual void save(std::ostream &save_stream)const ;

    [[nodiscard]] TCoordinate getPosition(void)const;

    /**
     * Puts only symbol to output stream. Not used for saving.
     * @param os
     * @param tile
     * @return
     */
    friend std::ostream & operator<<(std::ostream &os, const CTile &tile);
    /**
     * Used only in path finding, setting path '.' symbol
     * @param symbol
     */
    void setSymbol(char symbol);
    /**
     * Used only in path finding.
     * @return symbol
     */
    char getSymbol();
protected:
    TCoordinate position;
    char symbol;
};
#endif //SEM_CTILE_HPP
