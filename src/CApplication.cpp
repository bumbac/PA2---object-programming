//
// Created by sutymate on 4/29/20.
//

#include "CApplication.h"

void CApplication::start(void) {
    while(! end_game_flag) {
        showMenu();
        int answer = 0;
        std::cin >> answer;
        switch (answer) {
            case 1:
                startGame();
                break;
            case 2:
                isSave = false;
                selectMap();
                break;
            case 3:
                isSave = true;
                selectMap();
                break;
            case 4:
                //showUnits();
                break;
            case 5:
                manual();
                break;
            case 6:
                exampleGame();
                break;
            case 7: {
                quitExit();
                break;
            }
            default:
                std::cout << "Select one." << std::endl;
        }
    }
    for (int i = 0; i < 50; i++)
        printf("\n");
    printf("BYE!!!!!!!\n");
}

void CApplication::startGame(){
    if (!std::filesystem::exists(map_name) || !checkFile(map_name)){
        std::cout << "Map not found, please select one." << std::endl;
        return;
    }
    CGame game(map_name, !isSave);
    game.start();
}

void CApplication::showMenu(void) {
    for(int i = 0; i < 50; i++)
        printf("\n");
    std::cout << "1. START " << map_name << std::endl << std::endl;
    std::cout << "2. SELECT MAP" << std::endl << std::endl;
    std::cout << "3. SELECT SAVE" << std::endl << std::endl;
    //std::cout << "4. SHOW UNITS AND TOWERS" << std::endl << std::endl;
    std::cout << "5. MANUAL" << std::endl << std::endl;
    std::cout << "6. START EXAMPLE GAME" << std::endl << std::endl;
    std::cout << "7. EXIT" << std::endl << std::endl;
}

void CApplication::selectMap() {

    int index = 1;
    std::filesystem::path maps = std::filesystem::current_path();
    std::string target = "maps";
    if (isSave)
        target = "saves";
    for (const auto & map: std::filesystem::directory_iterator(maps)){
        if (map.is_directory())
            if(map.path() ==  (maps/target))
                maps = map.path();
    }
    if (maps == std::filesystem::current_path()) {
        std::cout << "There is no directory with maps, create one or reinstall." << std::endl;
        quitExit();
        return;
    }
    std::vector<std::filesystem::path> choices;
    for (const auto & map: std::filesystem::directory_iterator(maps)){
        if (!map.is_directory())
            if (checkFile(map)){
                std::string file_name = map.path();
                std::string file_map_name;
                for (auto rit = file_name.rend(); rit != file_name.rbegin(); rit++){
                    if (*rit == '/')
                        break;
                    file_map_name += *rit;
                }
                choices.push_back(map.path());
                std::cout << index++ << ". " << file_map_name << std::endl;
            }
    }
    index--;
    if (index == 0){
        std::cout << "There are no maps in directory, create one or reinstall." << std::endl;
        quitExit();
        return;
    }
    int answer = 0;
    int exitCounter = 5;
    while(answer > index || answer < 1){
        std::cout << "Select map 1 - " << index << " please." << std::endl;
        std::cin >> answer;
        exitCounter--;
        if (!exitCounter) {
            std::cout << "No choice made." << std::endl;
            quitExit();
            return;
        }
    }
    map_name = choices[(answer - 1)];
}

void CApplication::manual() {
    std::cout << " SOME INSTRUCTIONS: " << std::endl;
}

void CApplication::quitExit() {
    end_game_flag = true;
}

bool CApplication::checkFile(const std::filesystem::path &file_name) const {
    std::ifstream file(file_name.c_str(), std::ios::in);
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    size_t hash_width = std::to_string((size_t) 0 - 1).length();
    size_t hash_position = length - hash_width;
    if (hash_position < 0)
        return false;
    auto hasher = std::hash<std::string>();
    file.seekg(hash_position);
    size_t file_hash = 0;
    file >> file_hash;
    if (file_hash == 0)
        return false;
    file.seekg(0);
    std::string context((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    size_t reference_hash = hasher(context.substr(0, hash_position));
    return reference_hash == file_hash;
}

void CApplication::exampleGame() {

}

