//
#ifndef PROVMAPPA_H
#define PROVMAPPA_H

#include "sourcestanza.hpp"
#include "player.hpp"


using namespace std;

struct lista_stanze {
    stanza room;
    lista_stanze* next;
};
typedef lista_stanze* ptr_listast;


class Map{
    protected:

        int xmin;
        int ymin;
        int ymax;
        ///minimi e massimi nel piano cartesiano, per poterla stampare

        int pl_chars; //caratteri totali di cui ha bisogno la stampa dei giocatori in ogni stanza
        ptr_listast SThead; //ptr alla testa della lista delle stanze (a mo' di SymbolTable)

    public:
        Map(int numero_di_giocatori);
        int get_pl_chars();
        ptr_listast getST(); //ritorna ptr alla testa della lista delle stanze
        void SThead_insert (int ics, int ipsi); //aggiungitore di stanze
        int absh (int x);
        int numCifre(int x);
        ptr_listast reorder (ptr_listast headdy);
        bool new_direction (char dir, Player *g1);
        void stampa ();
        stanza* initiatestanze();
};

#endif // PROVMAPPA_H
