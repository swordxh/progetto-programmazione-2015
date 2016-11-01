#ifndef FINALE_HPP_INCLUDED
#define FINALE_HPP_INCLUDED

#include "boss.hpp"
#include "coda.hpp"
#include "player.hpp"
#include "database.hpp"
#include "manageGame.hpp"

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
    int potionHP;
    Manage *manage; //serve per sanitycheck() e per verificare che gli input da tastiera siano corretti
public:
	finale(Queue *p_curr, int n, Manage *man); // costruttore
	void battleManager(); // metodo che gestisce le basi della battaglia
	int IOManager(); // permette al giocatore di accedere all'inventario
	int CalculateDamage(int Damage);
	void WinScreen(char MonsterName[]); // vittoria
	void LoseScreen(); // perdita di un giocatore
	void HealthBar(int currenthpMonster,int maxhpMonster); // gestione della grafica e delle barre della salute del giocatore e del boss
	Queue* returnList();
};

#endif // FINALE_HPP_INCLUDED
