#ifndef GAME_HPP_
#define GAME_HPP_

#include <ctime>
#include <stddef.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include "sourcestanza.hpp"
#include "provmappa.hpp"
using namespace std;


class Object{
protected:
    char name[30];
    int damage;
public:
    Object(char nome[], int danno);
    int Damage();
    char* showNameObject();
};

class Inventory{
protected:
    Object *oggetto[5]; //l'inventario è composto al massimo da 5 oggetti
    public:
    Inventory();
    bool slotIsFull(int slotInventario);
    int AccessObjectFromInventory (int slotInventario);
    void insertObject(Object oggettoDaInserire, int slotInventario);
    void deleteObject(int slotInventario);
    char* getName(int slotInventario);
};

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

struct Node{
    Player player;
    struct Node* next;
};

class Queue{
protected:
    Node* q; //puntatore al primo nodo della lista
public:
    Queue();
    void enqueue (Player giocatore);
    void dequeue(int idPlayer);
    bool isEmpty();
    Node* Head();
};

struct databaseObject{
    Object* oggetto[6];
};
typedef struct databaseObject databaseObject;

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
    bool databaseEmpty();
    void setRounds(int n);
    void setPlayers(int n);
    void startGame();
    int sanitycheck();
    void assignDefaultObject();
    void setDefaultObject(Object oggetto);
};
#endif
