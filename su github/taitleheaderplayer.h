#ifndef TAITLEHEADERPLAYER_H_INCLUDED
#define TAITLEHEADERPLAYER_H_INCLUDED

#include "headerstanza.h"

///QUESTO è UN GIOCATORE PROVVISORIO, QUELLO VERO DOVRà AVERE [QUESTI CAMPI E FUNZIONI QUI SOTTO] PIù [TUTTO IL RESTO]

 class player{
    protected:
        int id;
        stanza* sonoqui;
    public:
        player();
        player (int aidi);
        int getid();
        stanza* getsonoqui();
        void writesonoqui (stanza* nuova);
};

#endif // TAITLEHEADERPLAYER_H_INCLUDED
