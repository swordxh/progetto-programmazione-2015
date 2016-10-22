#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <cstring>
#include <unistd.h>
#include "game.hpp"

const int n = 1, k = 1, z = 1.5, att = 1; // n indica il numero dei giocatori, k aumenta con l'avanzare dei turni, z Ë il moltiplicatore per la vita del boss, att il giocatore attuale

class boss{
protected:
	int MaxHp; //HP massimi
	int Hp; // HP attuali
	char name[10];// nome
	int damagest, damage1, damage2; // damagest Ë l'attacco standard, damage1 quello che attacca tutti i giocatori, damage2 quello che uccide istantaneamente il giocatore con meno vita
public:
	boss(); // costruttore
	char *GetName(); // da il nome del boss
	int getDmg(); // metodo col quale il boss usa l'attacco standard
	void GotHit(int dmg); // il boss subisce i danni dei giocatori
	int LifePoints(); // ritorna gli HP attuali
	int MaxLifePoints(); // ritorna gli HP massimi
    int speciale1(); // L'attacco speciale che colpisce tutti i giocatori
    int speciale2(); // L'attacco mortale
};

class finale{
protected:
    Player *p;
    boss *b;
    int k; // per ciclicit‡ attacchi
    char MonsterName[10]; // nome boss
public:
	finale(Player *p_curr); // costruttore
	void battleManager(); // metodo che gestisce le basi della battaglia
	int IOManager(); // permette al giocatore di accedere all'inventario
	int CalculateDamage(int Damage);
	void WinScreen(char MonsterName[]); // vittoria
	void LoseScreen(); // perdita di un giocatore (DA IMPLEMENTARE IL GAME OVER DI TUTTI I GIOCATORI, SERVE LA LISTA)
	void HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID); // gestione della grafica e delle barre della salute del giocatore e del boss
};

#endif // BOSS_H_INCLUDED
