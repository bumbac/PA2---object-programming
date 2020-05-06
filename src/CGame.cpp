//
// Created by sutymate on 4/29/20.
//

#include <algorithm>
#include "CGame.h"

void CGame::start(void) {
    std::thread t(&CGame::listen, std::ref(*this));
    while (true) {
        if (sequence())
            break;
        if (!userCommands.empty()) {
            if (userAction())
                break;
        }
        map->printMap();
    }
    t.join();
}

bool CGame::sequence(void) {
    if (map->moveUnits())
        return true;
    map->attackTowers();
    return false;

}

void CGame::listen() {
    std::string command;
    while(true) {
        std::cin >> command >> std::ws;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (command == "buy") {
            if (map->validUserAction(command)) {
                userCommands.push_back(command);
                continue;
            } else {
                continue;
            }
        }

        if ( command == "back" || command == "resume") {
            userCommands.emplace_back("back");
            continue;
        }

        if ( command == "manual" || command == "man" || command == "shop") {
            if (command == "man")
                command += "ual";
            userCommands.push_back(command);
            continue;
        }
        if (command == "exit" || command == "quit") {
            printf("Do you really want to exit? Type (yes\\no)\n");
            std::cin >> command >> std::ws;
            std::transform(command.begin(), command.end(), command.begin(), ::tolower);
            if (command == "yes" || command == "y" || command == "exit" || command == "quit"){
                userCommands.emplace_back("exit");
                break;
            }
        }
        std::printf("Unknown command\n");
        }
}

bool CGame::userAction() {
    std::string & command = userCommands.front();
    userCommands.pop_front();
    if (command == "exit") {
        saveGame();
        return true;
    }
    if (command == "manual")
        showManual();
    if (command == "shop")
        showShop();
    if (command == "back")
        map->printMap();
    if (command.find("buy") != std::string::npos)
        map->placeTower(command);
}

void CGame::showShop() const {
    saveGame();
    printf("shop\nshop\nshop\n");
}

void CGame::showManual() const {
    saveGame();
    printf("man\nman\nman\n");
}

CGame::CGame(const std::string &game_name, bool is_new_game) {

}
