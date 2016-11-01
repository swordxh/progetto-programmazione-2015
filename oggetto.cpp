#include "oggetto.hpp"
using namespace std;


Object::Object(char nome[], int danno){ //costruttore  inizializzazione
    strcpy(name, nome);
    damage=danno;
}
int Object::Damage(){ //restituisce il danno che causa l'oggetto dall'oggetto3
    if (strcmp(name,"potion")==0) { //gestione del caso oggetto pozione: in questo caso il danno è 0
        return 0;
    }
    return damage;
}

char* Object::showNameObject(){
    return name;
}
