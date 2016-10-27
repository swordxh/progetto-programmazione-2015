#include "boss.hpp"
using namespace std;

boss::boss(int *nPlayers){
        strcpy(name,"Drago\0"); // nome
        MaxHp= (*nPlayers * 100) * z; // "n" = numero giocatori, "z" = fattore che moltiplica vita
        Hp=MaxHp;
        damagest = 10; // attacco standard
        damage1 = 5; // attacco che colpisce tutti i giocatori
}
char *boss::GetName(){
        return name;
} // da il nome del boss
void boss::GotHit(int dmg){
        Hp=Hp-dmg;
} // il boss subisce i danni del giocatore
int boss::getDmg(){
        return damagest;
} // il boss usa l'attacco standard
int boss::LifePoints(){
        return Hp;
} // HP attuali del boss
int boss::MaxLifePoints(){
        return MaxHp;
} // HP massimi del boss
int boss::speciale1(){
        return damage1;
} // il boss usa l'attacco che colpisce tutti i giocatori


