#include <iostream>
using namespace std;

#include "headerstanza.h"
#include "taitleheaderplayer.h"

///QUESTO è UN GIOCATORE PROVVISORIO, QUELLO VERO DOVRà AVERE [QUESTI CAMPI E FUNZIONI QUI SOTTO] PIù [TUTTO IL RESTO]

player:: player() {id=3; sonoqui = NULL;}

player:: player(int aidi){ id=aidi; sonoqui = NULL; }

int player:: getid(){ return id;}

stanza* player:: getsonoqui() {return sonoqui;}

void player:: writesonoqui (stanza* nuova){ sonoqui = nuova;}
