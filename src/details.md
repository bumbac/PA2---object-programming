Tower Defense semestral project (BI-PA2 B192)


##Assignment:

Naprogramujte jendoduchou grafickou tower defense hru

Váš engine:

    ze souboru nahraje definici věží (cena, velikost, útok, dosah, ...)
    ze souboru nahraje možné mapy a typy nepřátel (životy, rychlost, odolnost na určitý typ věže ,...)
    implementuje jednoduchou interakci věž vs. útočníci (útok, proběhnutí, ...), počitadlo skóre, detekci vítězství
    (po nezabití x útočníků)
    implementuje alespoň 2 strategie průchodu hracím polem
    umožňuje ukládat a načítat rozehrané hry

Engine může fungovat jako real-time hra, či tahová hra.

Jak může vypadat mapa?

" " označuje možnou lokaci věže a prázdné místa, A, B označuje dva druhy věží, # označuje zeď, @ a % jsou různé druhy
    útočníků.


    #################################################
    #                        #       @@  #          #
    #         #              #    %B  @  ###        #
    #         #              #    %#  @    #    B   #
    <=%%%     #              A    %#       #@@@@@@@<=
    #         #              A    %#       @@   B   #
    #                        A    %#                #
    #                 %%%       %%%#                #
    #################################################

Cesta kudy se budu útočníci ubírat bude vždy nejkratší možná vzhledem ke zdím a věžím. "Nejkratší" se může lišit pro
létající (ignorují zdi) a pozemní jednotky. Pro chytré jednotky, které se vyhýbají věžím. Pro jednotky s krátkým
dohledem (k pohybu využívají jen informaci o okolí 5ti polí a cíl).

Kde lze využít polymorfismus? (doporučené)

    Parametry věží: znak, barva, dosah, zranění, ...
    Efekty útoku věží: zranění, zpomalení, ...
    Políčka mapy: volno, věž, útočník ...
    Strategie hledání cesty: předdefinovaná cesta, nejkratší (BFS, případně náhodná odchylka), A* prohledávání,
    vyhýbání se věžím
    Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

Ukázky:

    https://en.wikipedia.org/wiki/Tower_defense
    https://en.wikipedia.org/wiki/GemCraft
    http://plantsvszombies.wikia.com/wiki/Main_Page
##Details:

This project implements tower defense game with interface in console.
Game is played on rectangle map. Walls, free space, starting point, finish point, towers and units
are illustrated by text symbols. Game is played in real time. Game system provides game saving, resuming saved game
and selecting map.

Player tries to prevent enemy units from reaching finish point by placing defense towers on free space. Player buys
towers with money. Towers cannot obstruct enemy path. Towers attack units in range and player receives money for each
killed unit. Game provides three types of towers with different abilities(range, price, type of attack).
Units start on starting point and they try to get to finish point. They move in shortest path (calculated by A star
or BFS).
Units have different health and speed of movement. Units are upgraded in intervals - their maximum health is increased.
All units movement is atomic. They move in order from closest to finish point - this prevents movement collision.
Game ends when certain amount of units reach finish point.


Towers are placed on map and they select unit in range according to their specification.
There are 3 types types of towers (Archer, Bombarda, Caesar).
    
    Archer attacks first unit in path and range.
    Bombarda attacks unit with lowest health.
    Caesar attacks first unit in path and range and has ability to deal critical damage(kills unit instantly) with 10%
    chance.

#Polymorphism:

Game map is made of a class *CTile* which is a base class for tiles representing walls, free space, starting point,
finish point, units and towers.

*CTiles* as base class is stored in a 2D vector (std::vector<std::vector<std::shared_ptr<CTile>>>).
This way all objects in the game(**tiles, units, towers**) can be stored and accessed from one place and manipulated
in a polymorphic manner(printing, replacing, saving). I plan to utilize this in saving game and in restoring game
from save.

Class *CTower* inherits from *CTile* and represents a base class for towers. This class is **abstract** and provides only basic
member functions(getters) which are not determined by the type of tower.
Classes *CTowerArcher, CTowerBombarda, CTowerCaesar* inherit from *CTower* and implement specific function attack
(deal damage to enemy unit). Towers of same type are easy to clone to other locations in map thanks to polymorphism.
All towers on map are stored in one container and polymorphism allows me to execute attack on units regardless
of tower type.

Uniformity of class *CTower* and *CUnit* allows me to easily implement upgrade system and *CTile* provides easy saving
or restoring game.
I also plan to use polymorphism for showing game interface and printing game state (map, game data).
