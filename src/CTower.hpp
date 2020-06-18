//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CTOWER_HPP
#define SEM_CTOWER_HPP

#include "CTile.hpp"
#include "CUnit.hpp"
#include <map>
#include <memory>
 /**
 * abstract class representing tower
 */
class CTower: public CTile{
public:
    /**
     *
     * @param x width position
     * @param y height position
     * @param symbol
     * @param range circle
     * @param damage
     * @param price
     * @param upgrade_ratio increases the damage and range on upgrade, each upgrade increases ratio
     */
    CTower(const size_t &x, const size_t &y, char symbol, size_t range, size_t damage, size_t price, double upgrade_ratio, std::string & description);
    /**
     * Abstract function, every type of tower has special implementation.
     */
    virtual size_t attack(std::map<size_t, std::shared_ptr<CUnit>> & units) const = 0;
    /**
     * Upgrade damage and range by upgrade_ratio
     * @param symbol if symbol corresponds, apply upgrade
     */
    void upgrade(char symbol);
    /**
     * CTower is abstract, each type makes its own clone in new position.
     * @param x new position
     * @param y new position
     * @return smart pointer of new tower - always derived class
     */
    virtual std::shared_ptr<CTower> clone(size_t &x, size_t &y)const = 0;

    std::string getDescription() const;

    void save(std::ostream & middle_man)const override;

    // used in shop
    size_t getPrice(void)const;
    size_t getDamage(void)const;
    size_t getRange(void)const;

protected:
    size_t range;
    size_t damage;
    size_t price;
    double upgrade_ratio;
    std::string description;
};
#endif //SEM_CTOWER_HPP
