#include "game.hpp"
#include "battle.hpp"
#include "boss.hpp"

int main(){
    char nomespada[15];
    strcpy(nomespada,"excalibur");
    Object spada=Object(nomespada,25);
    char nomefucile[15];
    strcpy(nomefucile,"ak47");
    Object fucile=Object(nomefucile,13);
    char nomepozione[15];
    strcpy(nomepozione,"potion");
    Object pozione=Object(nomepozione,0);
    char nomebacchetta[15];
    strcpy(nomebacchetta,"bacchetta");
    Object bacchetta=Object(nomebacchetta,10);
    Manage g=Manage();
    
    g.setDefaultObject(bacchetta); //carico oggetto di base
    g.fetchDatabaseObjects(spada);
    g.fetchDatabaseObjects(fucile);
    g.fetchDatabaseObjects(pozione);
    
    g.startGame();
    return 0;
}
