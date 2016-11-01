#include "manageGame.hpp"

int main(){
    char nomespada[30];
    strcpy(nomespada,"excalibur");
    Object spada=Object(nomespada,20);
    char nomefucile[30];
    strcpy(nomefucile,"ak47");
    Object fucile=Object(nomefucile,15);
    char nomepozione[30];
    strcpy(nomepozione,"potion");
    Object pozione=Object(nomepozione,0);
    char nomebacchetta[30];
    strcpy(nomebacchetta,"bacchetta (oggetto base)");
    Object bacchetta=Object(nomebacchetta,10);
    Manage g=Manage();
    
    g.setDefaultObject(bacchetta); //carico oggetto di base
    g.fetchDatabaseObjects(spada);
    g.fetchDatabaseObjects(fucile);
    g.fetchDatabaseObjects(pozione);
    
    g.startGame();
    return 0;
}
