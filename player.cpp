#include "player.hpp"

Player::Player(){
}

Player::Player(int identificatore){
    id=identificatore;
    lp=100;
    maxlp=100;
    posizione=NULL;
    inventario=new Inventory;
}
int Player::showId(){
    return id;
}

int Player::maxHp(){
    if (lp>maxlp) maxlp=lp;
    return maxlp;
}
int Player::life(){
    if (lp>=0) return lp;
    else return 0;
}

void Player::lifeFix(int value){
    lp=lp-value;
}

int Player::useObject(int slotInventary){ //ritorna il danno dell'oggetto scelto tra uno degli oggetti negli slot dell'inventario
    return inventario->AccessObjectFromInventory(slotInventary);
}

void Player::TakeObject(Object oggetto){ //inserisce un oggetto nel primo slot libero disponibile, i alla fine conterrà l'informazione della posizione dell'eventuale slot libero
    int i=0;
    while (inventario->slotIsFull(i)) { //scorro nell'inventario per ricercare lo slot libero
        i++;
    }
    if (i<5) { //se c'è uno slot libero tra i primi quattro posti lo riempio
        inventario->insertObject(oggetto,i);
    }
}

Inventory* Player::showInventory(){
    return inventario;
}

void Player::writesonoqui(stanza* room){
    posizione=room;
}

stanza* Player::getsonoqui(){
    return posizione;
}
