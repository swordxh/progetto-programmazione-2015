#include <iostream>
using namespace std;

#include "headerstanza.h"
#include "taitleheaderplayer.h"

///QUESTO � UN GIOCATORE PROVVISORIO, QUELLO VERO DOVR� AVERE [QUESTI CAMPI E FUNZIONI QUI SOTTO] PI� [TUTTO IL RESTO]

player:: player() {id=3; sonoqui = NULL;}

player:: player(int aidi){ id=aidi; sonoqui = NULL; }

int player:: getid(){ return id;}

stanza* player:: getsonoqui() {return sonoqui;}

void player:: writesonoqui (stanza* nuova){ sonoqui = nuova;}
