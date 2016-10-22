/*
 * battle.hpp
 *
 *  Created on: 25 Sep 2016
 *      Author: swordxh
 */

#ifndef BATTLE_HPP_
#define BATTLE_HPP_

#include "game.hpp"//da eliminare
#include "monster.hpp"

class battle{
protected:
	Player *p;
    Manage *manage;
	Zombie *romero;
	Vampire *dracula;
	Spider *spiderman;
	char MonsterName[10];
	const int potionHP=30;
public:
    battle(Player *p_curr, Manage *man);
	void battleManager();
	void getRandomMonster();
	int IOManager();
	int CalculateDamage(int Damage);
	void WinScreen();
	void LoseScreen();
	void HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID);
};

#endif /* BATTLE_HPP_ */

	while (stato==0){
		if (b!=NULL){
			HealthBar(p->life(), 100, b->LifePoints(), b->MaxLifePoints(),p->showId()); // gli do gli HP attuali\massimi dei giocatori e del boss, aggiungendo l'ID del giocatore
		} // se il boss è vivo, vado in HealthBar
		stato=CalculateDamage(IOManager());
	}// finchè "stato" = 0 (ovvero i giocatori e il boss sono vivi) io sto dentro il while
	if (b!=NULL){
				HealthBar(p->life(), 100, b->LifePoints(), b->MaxLifePoints(),p->showId());
			}// in questo caso i giocatori sono morti (sono fuori dal while)
	if (stato==1){
		WinScreen(MonsterName); // vittoria
	}
	if (stato==2){
		LoseScreen(); // game over
	}
}
int finale::IOManager(){ //ritorna il danno del oggetto che si è scelto
	cout<<endl;
	cout<<"Scegli l'oggetto che vuoi usare per colpire il "<<MonsterName<<":";
	int select=1; // select elenca gli oggetti selezionabili
	for (int i=0; i<5; i++){
		if (p->showInventory()->slotIsFull(i)){
			cout<<select<<") "<< p->showInventory()->getName(i)<< "(dmg "<<p->showInventory()->AccessObjectFromInventory(i)<<")"<<endl;
			select++;
		} //lo slot non deve essere vuoto
	}
	int counter=select; // counter indica l'oggetto col select più alto (in poche parole, l'ultimo)
	do{
	cin>>select;
	}while((select<1) || (select>counter)); // seleziono un oggetto, il valore deve essere compreso tra 1 e counter
	counter=1; //
	bool exit=false; //exit è una guardia del while
	int i=0;
	while (!exit){
		if ((p->showInventory()->slotIsFull(i)) && (select==counter)){
			if (p->showInventory()->AccessObjectFromInventory(i)==0){
				p->lifeFix(-20);
				p->showInventory()->deleteObject(i);
			}// caso della pozione: a differenza degli altri oggetti (armi), questo viene eliminato, dando 20 HP al giocatore (la pozione ha il campo damage = 0)
			exit=true; //posso uscire dal while, ho usato l'oggetto
		}// se l'oggetto è quello selezionato, lo uso
		else if (p->showInventory()->slotIsFull(i)) counter++;
		i++;
	}
	return p->showInventory()->AccessObjectFromInventory(i--);
}
void finale::WinScreen(char MonsterName[]){
	cout<<"					CONGRATULAZIONI HAI BATTUTO IL "<<MonsterName<<endl;
}
void finale::LoseScreen(){
	cout<<"					SEI MORTO"<<endl;
}
void finale::HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID){ //20 barrette
    cout <<endl<< "                                     " << MonsterName << endl<<" ";
    for(int g=1; g<=78;g++)cout<<"-";
    cout<<endl<<'|';
	int i=1;
	while(i<=78){
        if(((78*currenthpMonster)/maxhpMonster)>=i)cout<<"█";
		else cout<<' ';
		i++;
    }cout<<"|";
    cout<<endl<<"|";
    i=1;
    while(i<=78){
        if(((78*currenthpMonster)/maxhpMonster)>=i)cout<<"█";
        else cout<<' ';
        i++;
    }// calcola le | in base agli HP attuali tramite una percentuale
    cout<<'|' << endl<<" "; // le parentesi le ho messe solo per delimitare la barra della salute
    for(int g=1; g<=78;g++)cout<<"-";
    cout<<endl<<endl<<endl;
	cout << "     _______M''''''M____                     ____M''''''''''''M________" << endl;
    cout << " __/      .        . __/\\__            _____/\\___  .8M.. .. D:   +\\_   \\ ___ " << endl;
    cout << "/ _>'''''''<     __/      \\_         /.= . ..   \\ . O          .   \\  OM.   \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout
    cout << "V            \\   /            \\....,',  .     .  \\ .     ..         \\    = < \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout
    cout << "              \\ /_M''''M_      XM______  .  .     .\\ .      ____ .  , \\ D /   \\" << endl;
    cout << "               V         \\    M.       \\________:   \\     M /        <_\\ |     V" << endl;
    cout << "                          \\  /                \\ \\___ \\   /             \\||" << endl;
    cout << "                           \\/..     O .OOO.    \\    \\,| /               V" << endl;
    cout << "                          _/.  M,..  ? : . ..   \\    X||" << endl;
    cout << "                        ./      ?...       ..    \\    V" << endl;
	cout << "                        ( .       N______   N7.   |" << endl;
    cout << "                         X7  M .  /      \\___. . M| " << endl;
    cout << "                        ( O .. O |           \\M  . \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout (qua è a causa della parentesi)
    cout << "                         M._____..)           \\     | " << endl;
    cout << "                         \\|'''''|/             \\   ,|" << endl;
    cout << "                          \\!!!!!/               \\ . |" << endl;
    cout << "                                                 \\  |" << endl;
	cout << "                                            ^     )Z )" << endl;
    cout << "                                           | \\   /M /" << endl;
    cout << "                                           | .\\_/M /" << endl;
    cout << "                                            \\_____/" << endl;
	i=1;
	while (i <= att){
        cout << "   ";
        if (i == att) cout << "V" << endl;
        else cout << "     ";
        i++;
	}// la V indica il giocatore attuale
	i = 1;
	while(i <= n){
        cout << "   " << p -> showId();
		if(i < n)cout<<"    ";
		i++;
	}
	cout<<endl;
	i = 1;
	while(i <= n){
        cout << p -> life() << "/100";
		if(i < n)cout<<" ";
		i++;
	}
	cout<<endl;
}
int finale::CalculateDamage(int Damage){  //ritorna 0 se sono entrambi vivi 1 se il mostro è morto 2 se il giocatore è morto
	int status=0;
	if (b!=NULL){
        if ((k % 2) == 0) p->lifeFix(b->speciale1()); // ogni due turni usa l'attacco che colpisce tutti i giocatori (DEVO AVERE LA LISTA PER SCORRERLA)
        else if ((k % 3) == 0) p->lifeFix(b->speciale2()); // ogni tre turni usa l'attacco mortale (DEVO AVERE LA LISTA PER ACCEDERE AL GIOCATORE CON MENO VITA)
		else p->lifeFix(b->getDmg());// attacco standard (DEVO AVERE LA LISTA PER ATTACCARE UN QUALSIASI GIOCATORE)
		b->GotHit(Damage); // il boss subisce danni dal giocatore (DEVO AVERE LA LISTA PER PERMETTERE L'ATTACCO A TUTTI I GIOCATORI)
		if (b->LifePoints()<=0){
			delete b;
			b=NULL;
			status=1;
		} // il boss è morto
	}
	if (p->life()<=0) status=2; // morte di 1 o più giocatori (DEVO AVERE LA LISTA PER CONTROLLARE LA SALUTE DI TUTTI I GIOCATORI)
	// L'ISTRUZIONE E' DA COMPLETARE: devo distinguere l'eliminazione di uno o più giocatori e il game over (morte di tutti i giocatori)
    k++; // turno finito, passo al successivo
	return status;
}

