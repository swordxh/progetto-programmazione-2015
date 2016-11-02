#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include <cstring>
#include <unistd.h>
#include "monster.hpp"
using namespace std;

const double z = 0.88; // n indica il numero dei giocatori, k aumenta con l'avanzare dei turni, z è il moltiplicatore per la vita del boss, att il giocatore attuale

class boss:public monster{
protected:
        int damage1; // damagest è l'attacco standard, damage1 quello che attacca tutti i giocatori, damage2 quello che uccide istantaneamente il giocatore con meno vita
public:
    boss(int *nPlayers);
    int speciale1(); // L'attacco speciale che colpisce tutti i giocatori
};

#endif // BOSS_H_INCLUDED
