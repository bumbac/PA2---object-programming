//
// Created by sutymate on 4/29/20.
//

#include "CApplication.hpp"

void CApplication::start(void) {
    // loop operating the menu and user choices for menu
    while(true) {
        showMenu();
        std::string answer;
        std::cin >> answer;
        if (answer == "1" || answer == "start") {
            startGame();
            continue;
        }
        if (answer == "2" || answer == "map"){
            is_new_game = true;
            selectMap();
            continue;
        }
        if (answer == "3" || answer == "save") {
            is_new_game = false;
            if (!selectMap())
                is_new_game = true;
            continue;
        }
        if (answer == "4" || answer == "manual" || answer == "man") {
            manual();
            continue;
        }
        if (answer == "5"|| answer == "example" ) {
            exampleGame();
            continue;
        }
        if (answer == "6" || answer == "quit" || answer == "exit")
            break;
        std::cout << "Select one number." << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "BYE...";
}

void CApplication::startGame(){
    // if user did not choose map, default map is used. Still needs to be checked.
    if (!std::filesystem::exists(map_name) || !checkFile(map_name)){
        std::cout << "Map file missing or corrupted, please select other map." << std::endl;
        return;
    }
    std::list<std::string> userCommands{};
    std::cin.clear();
    std::cin.ignore();
    CGame game(map_name, is_new_game, userCommands);
    game.start();
}

void CApplication::showMenu(void) {
    std::string logo {"             _____   _   _   _____      ____      _      __  __   _____        \n"
                      "            |_   _| | | | | | ____|    / ___|    / \\    |  \\/  | | ____|       \n"
                      "              | |   | |_| | |  _|     | |  _    / _ \\   | |\\/| | |  _|         \n"
                      "              | |   |  _  | | |___    | |_| |  / ___ \\  | |  | | | |___        \n"
                      "              |_|   |_| |_| |_____|    \\____| /_/   \\_\\ |_|  |_| |_____|       \n"};

    for (int i = 0; i < 80; i++)
        std::cout << std::endl;
    std::cout << logo << std::endl << std::endl;
    std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "1. START " << map_name.string() << std::endl << std::endl;
    std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "2. SELECT MAP" << std::endl << std::endl;
    std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "3. SELECT SAVE" << std::endl << std::endl;
    std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "4. MANUAL" << std::endl << std::endl;
    std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "5. START EXAMPLE GAME" << std::endl << std::endl;
    std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "6. EXIT" << std::endl << std::endl;
}

bool CApplication::selectMap() {
    std::string map_logo{"                       __  __      _      ____    ____                         \n"
                         "                      |  \\/  |    / \\    |  _ \\  / ___|                        \n"
                         "                      | |\\/| |   / _ \\   | |_) | \\___ \\                        \n"
                         "                      | |  | |  / ___ \\  |  __/   ___) |                       \n"
                         "                      |_|  |_| /_/   \\_\\ |_|     |____/                         \n"};
    std::string save_logo{"                     ____       _     __     __  _____   ____                   \n"
                          "                    / ___|     / \\    \\ \\   / / | ____| / ___|                  \n"
                          "                    \\___ \\    / _ \\    \\ \\ / /  |  _|   \\___ \\                  \n"
                          "                     ___) |  / ___ \\    \\ V /   | |___   ___) |                 \n"
                          "                    |____/  /_/   \\_\\    \\_/    |_____| |____/                  \n"};
    if (is_new_game)
        std::cout << map_logo << std::endl << std::endl;
    else
        std::cout << save_logo << std::endl << std::endl;
    std::string file_directory = "maps";
    if (!is_new_game)
        file_directory = "saves";
    if (! std::filesystem::exists(file_directory)){
        std::filesystem::create_directory(file_directory);
        std::cout << "Folder is empty." << std::endl;
        return false;
    }

    std::vector<std::filesystem::path> available_files;
    int index = 0;
    for (const auto & map: std::filesystem::directory_iterator(file_directory))
        if (! map.is_directory())
            if (checkFile(map)){
                std::string file_name = map.path();
                available_files.push_back(map.path());
                std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << ++index << ". " << file_name << std::endl << std::endl;
            }

    if (index == 0){
        std::cout << "There are no " << file_directory << " in directory, reinstall please." << std::endl;
        return false;
    }
    int menu_choice = 0;
    // max 5 attempts to choose file
    int remaining_attempts = 5;
    while(menu_choice > index || menu_choice < 1){
        if (!remaining_attempts--) {
            std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " <<  "No choice made." << std::endl;
            return false;
        }
        std::cout << std::setw(fill_width/3) << std::setfill(' ') <<  " " << "Select map 1 - " << index << ", please." << std::endl;
        std::cin >> menu_choice;
    }
    map_name = available_files[(menu_choice - 1)];
    return true;
}

void CApplication::manual() {
    std::string manual{"                 __  __      _      _   _   _   _      _      _                  \n"
                       "                |  \\/  |    / \\    | \\ | | | | | |    / \\    | |                 \n"
                       "                | |\\/| |   / _ \\   |  \\| | | | | |   / _ \\   | |                 \n"
                       "                | |  | |  / ___ \\  | |\\  | | |_| |  / ___ \\  | |___              \n"
                       "                |_|  |_| /_/   \\_\\ |_| \\_|  \\___/  /_/   \\_\\ |_____|             \n"};
    std::cout << manual << std::endl;
    std::ifstream instructions(std::filesystem::current_path()/"instructions.txt", std::ios::in);

    if (instructions.good())
        std::cout << instructions.rdbuf() << std::endl;
    else
        std::cout << "Start game by writing start or 1 to the terminal.\n"
                     " You can find more information in the shop in the game.\n"
                     " Enter shop by writing shop to the terminal." << std::endl;
    std::string answer;
    std::cin >> answer;
}

bool CApplication::checkFile(const std::filesystem::path &file_name) const {
    std::ifstream file(file_name.c_str(), std::ios::in);
    if (! file.good())
        return false;
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    // max size_t width, padding with leading zeros
    size_t hash_width = std::to_string((size_t) 0 - 1).length();
    size_t hash_position = length - hash_width - 1;
    if (hash_position < 0)
        return false;
    file.seekg(hash_position);
    size_t file_hash = 0;
    file >> file_hash;
    file.seekg(0);
    std::string context((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    auto hasher = std::hash<std::string>();
    size_t reference_hash = hasher(context.substr(0, hash_position));
    return reference_hash == file_hash;
}

void CApplication::exampleGame() {
    map_name = "maps/map0.txt";
    if (!std::filesystem::exists(map_name) || !checkFile(map_name)){
        std::cout << "Map not found, please select other map." << std::endl;
        return;
    }
    std::list<std::string> userCommands {"buy A 21 4",
                                         "", "", "",
                                         "", "", "",
                                         "shop", "back",
                                         "buy a 16 4",
                                         "", "", "",
                                         "buy B 13 4",
                                         "buy B 93 9"};
    CGame game(map_name, true,userCommands);
    game.start();
}

