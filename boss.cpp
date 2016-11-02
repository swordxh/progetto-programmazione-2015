#include "boss.hpp"

boss::boss(int *nPlayers){
        strcpy(name,"Drago\0"); // nome
        MaxHp= (*nPlayers * 100) * z; // "n" = numero giocatori, "z" = fattore che moltiplica vita
        Hp=MaxHp;
        damage = 16; // attacco standard
        damage1 = 10; // attacco che colpisce tutti i giocatori
}

// HP massimi del boss
int boss::speciale1(){
        return damage1;
} // il boss usa l'attacco che colpisce tutti i giocatori


