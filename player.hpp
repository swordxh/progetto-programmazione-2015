#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <ctime>
#include <stddef.h>
#include <cstdlib>
#include <string.h>
#include <iostream>

#include "sourcestanza.hpp"
#include "oggetto.hpp"
#include "inventario.hpp"
using namespace std;

class Player{
protected:
    int id; //identificatore giocatore
    int lp; //punti vita giocatore
    int maxlp;
    Inventory* inventario; //inventario associato al goicatore
    stanza* posizione;
public:
    Player();
    Player(int identificatore);
    int showId();
    int life();
    void lifeFix(int value);
    int useObject(int slotInventary);
    void TakeObject(Object oggetto);
    int maxHp();
    Inventory* showInventory();
    void writesonoqui(stanza* room);
    stanza* getsonoqui();
};

#endif /* player_hpp */
