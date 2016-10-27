#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <cstring>
#include <unistd.h>
#include "game.hpp"

const double z = 0.8; // n indica il numero dei giocatori, k aumenta con l'avanzare dei turni, z è il moltiplicatore per la vita del boss, att il giocatore attuale

class boss{
protected:
	int MaxHp; //HP massimi
	int Hp; // HP attuali
	char name[10];// nome
	int damagest, damage1; // damagest è l'attacco standard, damage1 quello che attacca tutti i giocatori, damage2 quello che uccide istantaneamente il giocatore con meno vita
public:
	boss(int *nPlayers); // costruttore
	char *GetName(); // da il nome del boss
	int getDmg(); // metodo col quale il boss usa l'attacco standard
	void GotHit(int dmg); // il boss subisce i danni dei giocatori
	int LifePoints(); // ritorna gli HP attuali
	int MaxLifePoints(); // ritorna gli HP massimi
    int speciale1(); // L'attacco speciale che colpisce tutti i giocatori
};

#endif // BOSS_H_INCLUDED
