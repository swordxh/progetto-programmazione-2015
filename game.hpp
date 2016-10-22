/*
 * main.hpp
 *
 *  Created on: Oct 11, 2016
 *      Author: swordxh
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <ctime>
#include <stddef.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
using namespace std;


class Object{
protected:
    char name[20];
    int damage;
public:
    Object();
    Object(char nome[], int danno);
    int Damage();
    char* showNameObject();
    void setObject(char nome[], int danno);
};

class Inventory{
protected:
    Object *oggetto[5]; //l'inventario è composto al massimo da 5 oggetti
    bool slot[5]; //booleano che indica se uno slot dell'inventario pieno o vuoto
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
    Inventory inventario; //inventario associato al goicatore
public:
    Player(int identificatore);
    int showId();
    int life();
    void lifeFix(int value);
    int useObject(int slotInventary);
    void TakeObject(Object oggetto);
    int maxHp();
    Inventory* showInventory();
};

struct Node{
    Player* player;
    struct Node* next;
};
typedef struct Node node;

class Queue{
protected:
    node* q;
public:
    Queue();
    void enqueue (Player* giocatore); //input id del player
    node* dequeue(Player* giocatore); //torna la testa della lista in quanto potrebbe cambiare se il primo della lista viene eliminato
    bool isEmpty();

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
    //map
public:
    Manage();
    void builtQueue();
    void fetchDatabaseObjects(Object oggettoDelGioco);
    void spawnMonsterOrObject(Player* giocatore);
    void dropObject(Player* giocatore);
    bool databaseEmpty();
    void setRounds(int n);
    void setPlayers(int n);
};
#endif /* GAME_HPP_ */
