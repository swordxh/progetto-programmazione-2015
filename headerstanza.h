#ifndef HEADERSTANZA_H_INCLUDED
#define HEADERSTANZA_H_INCLUDED

#include <iostream>
using namespace std;

///la stanza NON DEVE INCLUDERE IL PLAYER VERO! funziona indipendentemente!

struct lista_players {
    int idPlayer;
    lista_players*   next_pl;
};
typedef lista_players* ptr_listapl;
///la [lista di giocatori] della stanza (ovvero la lista dei presenti nella stanza che serve per stamparli)
///funziona indipendentemente dai giocatori, è solo un elenco dei presenti COME INT


class stanza{
    protected:
        int x;
        int y;
        stanza* nord;
        stanza* sud;
        stanza* est;
        stanza* west;
        ptr_listapl pls;    //puntatore alla testa della [lista giocatori presenti nella stanza]
        //gente e professore/professoressa: memorizzate cos'è pls che vi servirà!
    public:
        stanza();
        stanza(int xi, int yi);
        int getx();
        int gety();

        stanza* getnord();
        stanza* getsud();
        stanza* getest();
        stanza* getwest();
        void writenord(stanza* niu);
        void writesud(stanza* niu);
        void writeest(stanza* niu);
        void writewest(stanza* niu);

        ptr_listapl get_pls(); //ritorna il PUNTATORE ALLA TESTA della lista_players della stanza
        void write_pls (ptr_listapl gigi);

        void add_player(int idPleier);
        ptr_listapl rimuv_player(int idP2remove, ptr_listapl head);

        //void rem_player(int idP2remove, ptr_listapl head); questa non ritorna il ptr alla testa della lista aggiornata,
        // e infatti se si usa questa non funziona la rimozione dalla testa

};
#endif // HEADERSTANZA_H_INCLUDED
