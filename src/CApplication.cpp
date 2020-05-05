//
// Created by sutymate on 4/29/20.
//

#include "CApplication.h"

void CApplication::start(void) {
    int end_game_flag = false;
    while(! end_game_flag) {
        showMenu();
        int answer;
        std::cin >> answer;
        switch (answer) {
            case 1:
                startGame();
                break;
            case 2:
                selectMap();
                break;
            case 3:
                selectSave();
                break;
            case 4:
                showUnits();
                break;
            case 5:
                manual();
                break;
            case 6:
                exampleGame();
                break;
            case 7: {
                quitExit();
                end_game_flag = true;
                break;
            }
            default:
                std::cout << "error" << std::endl;
        }
    }
    for (int i = 0; i < 50; i++)
        printf("\n");
    printf("BYE!!!!!!!\n");
}

bool CApplication::startGame(){
    CGame game(m_name, is_new_game);
    game.start();

}

void CApplication::showMenu(void) {
    for(int i = 0; i < 50; i++)
        printf("\n");
    std::cout << "1. START " << m_name << std::endl << std::endl;
    std::cout << "2. SELECT MAP" << std::endl << std::endl;
    std::cout << "3. SELECT SAVE" << std::endl << std::endl;
    std::cout << "4. SHOW UNITS AND TOWERS" << std::endl << std::endl;
    std::cout << "5. MANUAL" << std::endl << std::endl;
    std::cout << "6. START EXAMPLE GAME" << std::endl << std::endl;
    std::cout << "7. EXIT" << std::endl << std::endl;
}

