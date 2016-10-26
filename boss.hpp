#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <cstring>
#include <unistd.h>
#include "game.hpp"

const int z = 2; // n indica il numero dei giocatori, k aumenta con l'avanzare dei turni, z è il moltiplicatore per la vita del boss, att il giocatore attuale

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

class finale{
protected:
    Queue *l; // l serve per scorrere la lista
    Node* p; //p = giocatore attuale; head = testa
    Node* head; //head è un riferimento per i turni
    boss *b;
    Player *q;
    int k; // per ciclicità attacchi
    int nPlayers; // numero dei giocatori
    char MonsterName[10]; // nome boss
    databaseObject* database; //mi serve per usare l'inventario
    int att; //indica se attacca il boss (-1) o i giocatori (il loro ID)
    int scelto; //indica quale giocatore attaccare nell'attacco standard e in quello mortale
    const int potionHP=30;
    int m;
    Manage *manage; //serve per sanitycheck() e per verificare che gli input da tastiera siano corretti
public:
	finale(Queue *p_curr, int n, Manage *man); // costruttore
	void battleManager(); // metodo che gestisce le basi della battaglia
	int IOManager(); // permette al giocatore di accedere all'inventario
	int CalculateDamage(int Damage);
	void WinScreen(char MonsterName[]); // vittoria
	void LoseScreen(); // perdita di un giocatore (DA IMPLEMENTARE IL GAME OVER DI TUTTI I GIOCATORI, SERVE LA LISTA)
	void HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID); // gestione della grafica e delle barre della salute del giocatore e del boss
	Queue* returnList();
};

#endif // BOSS_H_INCLUDED

