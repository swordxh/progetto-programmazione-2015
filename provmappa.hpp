#ifndef PROVMAPPA_H
#define PROVMAPPA_H

#include "game.hpp"
#include "sourcestanza.hpp"
#include <iostream>
using namespace std;

struct lista_stanze {
    stanza room;
    lista_stanze* next;
};
typedef lista_stanze* ptr_listast;

///per ora [header e source tutto insieme]
class Map{
    protected:

        int xmin;
        int ymin;
        int ymax;
        ///minimi e massimi nel piano cartesiano, per poterla stampare

        int pl_chars; //caratteri totali di cui ha bisogno la stampa dei giocatori in ogni stanza
        ptr_listast SThead; //ptr alla testa della lista delle stanze (a mo' di SymbolTable)

    public:
        Map(int numero_di_giocatori);///fine costruttore
        int get_pl_chars();//solo per provare a stamparlo come controllo
        ptr_listast getST(); //ritorna ptr alla testa della lista delle stanze
        ptr_listast SThead_insertR (int ics, int ipsi, ptr_listast head); ///aggiungitore di stanze che ritorna testa
        void SThead_insert (int ics, int ipsi); ///aggiungitore di stanze non ritornante (aggiorna SThead, che è un campo della classe, resta visibile)
        int absh (int x);
        int numCifre(int x);
        ptr_listast reorder (ptr_listast headdy);
        void new_direction (char dir, Player& g1);///fine new_direction
        void stampa ();
};

#endif // PROVMAPPA_H
