//
// Created by sutymate on 4/29/20.
//

#include "CGame.hpp"
#include <algorithm>
#include <thread>
#include <fstream>
#include <iostream>

CGame::CGame(const std::filesystem::path &game_name, bool is_new_game, std::list<std::string> & user_commands)
        : map(std::make_unique<CMap>(CMap(game_name, is_new_game))), userCommands(user_commands){}

void CGame::start(void) {
    bool example_game = false;
    if(!userCommands.empty())
        example_game = true;

    while (true) {
        map->printMap();

        if (!example_game)
            listen();
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (userAction())
            return;

        if (sequence()) {
            lose();
            return;
        }
    }

}

bool CGame::sequence(void) {
    if (map->moveUnits())
        return true;
    map->attackTowers();
    return false;
}

void CGame::listen() {
    std::string command;
    std::getline(std::cin, command);
    // next turn, user input only whitespace
    if (command.empty())
        return;
    // buy tower
    if (command.substr(0, 3) == "buy" && command.length() > 8) {
        // checking the structure of command
        if (map->validUserAction(command))
            userCommands.emplace_back(command);
        return;
    }
    // upgrade tower
    if (command.substr(0, 7) == "upgrade" && command.length() == 9){
        if (command[8] <= 'c' && command[8] >= 'a') {
            userCommands.emplace_back(command);
            return;
        }
    }

    // resume game from manual or shop
    if ( command == "back" || command == "resume") {
        userCommands.emplace_back("back");
        return;
    }

    // show manual / shop
    if ( command == "manual" || command == "man" || command == "shop") {
        if (command == "man")
            command += "ual";
        userCommands.emplace_back(command);
        return;
    }

    // save
    if (command == "save"){
        userCommands.emplace_back(command);
        return;
    }

    // exit with confirmation. Save the game and then exits
    if (command == "exit" || command == "quit") {
        printf("Do you really want to exit? Type (yes\\no)\n");
        std::getline(std::cin, command);
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (command == "yes" || command == "y" || command == "exit" || command == "quit"){
            userCommands.emplace_back("exit");
            return;
        }
    }
    std::cout << "Unknown command." << std::endl;
}

bool CGame::userAction() {
    // commands in userCommands are in correct structure
    if (userCommands.empty())
        return false;
    std::string command = userCommands.front();
    userCommands.pop_front();

    if (command == "exit") {
        map->saveGame();
        return true;
    }

    if (command == "save")
        map->saveGame();

    if (command == "manual")
        showManual();

    if (command == "shop") {
        showShop();
        return userAction();
    }

    if (command == "back")
        map->printMap();

    if (command.find("upgrade") != std::string::npos)
        map->upgrade(command[8]);

    if (command.find("buy") != std::string::npos)
        map->placeTower(command);

    return false;
}

void CGame::showShop() {
    map->saveGame();
    for (int i = 0; i < 10; i ++)
        std::cout << std::endl;

    std::string shop ("   _____   _    _    ____    _____  \n"
                      "  / ____| | |  | |  / __ \\  |  __ \\ \n"
                      " | (___   | |__| | | |  | | | |__) |\n"
                      "  \\___ \\  |  __  | | |  | | |  ___/ \n"
                      "  ____) | | |  | | | |__| | | |     \n"
                      " |_____/  |_|  |_|  \\____/  |_|     \n"
                      "                                    \n"
                      "                                    \n"
                      "");
    std::cout << std::setw(fill_width)  << std::setfill(' ') << std::left << shop << std::endl;
    map->showShop();
    // user can buy in the shop
    listen();
}

void CGame::showManual() const {
    map->saveGame();
    for (int i = 0; i < 10; i ++)
        std::cout << std::endl;

    std::string manual("\n"
                       "\n"
                       "  __  __      _      _   _   _   _      _      _     \n"
                       " |  \\/  |    / \\    | \\ | | | | | |    / \\    | |    \n"
                       " | |\\/| |   / _ \\   |  \\| | | | | |   / _ \\   | |    \n"
                       " | |  | |  / ___ \\  | |\\  | | |_| |  / ___ \\  | |___ \n"
                       " |_|  |_| /_/   \\_\\ |_| \\_|  \\___/  /_/   \\_\\ |_____|\n"
                       "                                                     \n"
                       );
    std::cout << std::setw(fill_width)  << std::setfill(' ') << std::left << manual << std::endl;
    std::ifstream instructions(std::filesystem::current_path()/"instructions.txt", std::ios::in);
    if (instructions.good())
        std::cout << std::setw(fill_width)  << std::setfill(' ') << std::left << instructions.rdbuf() << std::endl;

    std::cout << std::setw(fill_width)  << std::setfill(' ') << std::left
        << "You can find more information in the shop in the game." << std::endl;
    std::string answer;
    // any input returns to game
    std::getline(std::cin, answer);
}

void CGame::lose() {
    for (int i = 0; i < 10; i ++)
        std::cout << std::endl;

    std::string win_logo{"                   _        ___    ____    _____   _                            \n"
                         "                  | |      / _ \\  / ___|  | ____| | |                           \n"
                         "                  | |     | | | | \\___ \\  |  _|   | |                           \n"
                         "                  | |___  | |_| |  ___) | | |___  |_|                           \n"
                         "                  |_____|  \\___/  |____/  |_____| (_)                           "};
    std::string request("\n"
                        "\n"
                        "                                                              \n"
                        "            _ __   _ _   ___   ___  ___    ___   _ _   | |_   ___   _ _ \n"
                        "           | '_ \\ | '_| / -_) (_-< (_-<   / -_) | ' \\  |  _| / -_) | '_|\n"
                        "           | .__/ |_|   \\___| /__/ /__/   \\___| |_||_|  \\__| \\___| |_|  \n"
                        "           |_|                              _     _                     \n"
                        "           | |_   ___     __   ___   _ _   | |_  (_)  _ _    _  _   ___ \n"
                        "           |  _| / _ \\   / _| / _ \\ | ' \\  |  _| | | | ' \\  | || | / -_)\n"
                        "            \\__| \\___/   \\__| \\___/ |_||_|  \\__| |_| |_||_|  \\_,_| \\___|\n"
                        "                                                              \n"
                        "");
    std::cout << std::setw(fill_width)  << std::setfill(' ') << std::right << win_logo << std::endl;
    std::cout << request << std::endl;
    const TData & data = map->gameEndData();
    std::cout << std::setw(fill_width/2) << "UNITS KILLED: " << data.units_killed << std::endl;
    std::cout << std::setw(fill_width/2) << "UNITS ESCAPED: " << data.units_escaped << std::endl;
    std::cout << std::setw(fill_width/2) << "UNITS ALIVE: " << data.units_alive << std::endl;
    std::cout << std::setw(fill_width/2) << "GOLD EARNED: " << data.all_money << std::endl;
    std::cout << std::setw(fill_width/2) << "UNUSED GOLD: " << data.money << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // user can read stats, waiting for input
    std::getline(std::cin, win_logo);
}

