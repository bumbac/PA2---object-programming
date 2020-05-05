//
// Created by sutymate on 4/28/20.
//

#ifndef SEM_CGAME_H
#define SEM_CGAME_H

#include <iostream>
#include <locale>
#include <thread>
#include "CMap.h"
#include <fstream>

class CGame{
public:
    CGame(const std::string & game_name, bool is_new_game);

    void start(void);

private:
    bool sequence(void);

    int listen(void);

    bool userAction(void);

    void showShop(void) const;

    void showManual() const;

    std::unique_ptr<CMap> map;
    std::list<std::string> userCommands;
    std::string activeWindow;
};
#endif //SEM_CGAME_H
