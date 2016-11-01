#ifndef manageAndDatabase_hpp
#define manageAndDatabase_hpp

#include <stdio.h>
#include <ctime>
#include <stddef.h>
#include <cstdlib>
#include <string.h>
#include <iostream>

#include "coda.hpp"
#include "oggetto.hpp"
#include "player.hpp"
#include "database.hpp"
#include "sourcestanza.hpp"
using namespace std;

class Manage{
protected:
    int n;
    Queue *l;
    databaseObject* database;
    int nPlayers;
    int nRounds;
    Object* defObj;
    //map?
public:
    Manage();
    void builtQueue();
    void fetchDatabaseObjects(Object oggettoDelGioco);
    void spawnMonsterOrObject(Player* giocatore);
    void dropObject(Player* giocatore);
    void setRounds(int n);
    void setPlayers(int n);
    void startGame();
    int sanitycheck();
    void assignDefaultObject();
    void setDefaultObject(Object oggetto);
};


#endif /* manageAndDatabase_hpp */
