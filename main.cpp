#include "game.hpp"
#include "battle.hpp"
#include "boss.hpp"

int main(){
    Object spada=Object("spada",30);
    Object piccone=Object("piccone",10);
    Manage g=Manage();
    
    g.setDefaultObject(piccone); //carico oggetto di base
    g.fetchDatabaseObjects(spada);
    g.fetchDatabaseObjects(spada);
    
    g.startGame();
    return 0;
}
