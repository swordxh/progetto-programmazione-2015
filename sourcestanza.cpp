#include <iostream>
#include "sourcestanza.hpp"
using namespace std;

///la stanza NON DEVE INCLUDERE IL PLAYER VERO! funziona indipendentemente!



//lista_players è già definita nell'header, scrivendola anche qui si lamenta perchè viene ridefinita


stanza:: stanza(){x=0; y=0; nord=sud=est=west=NULL; pls=NULL;}
stanza:: stanza(int xi, int yi){x=xi; y=yi; nord=sud=est=west=NULL; pls=NULL;}

int stanza:: getx(){return x;}
int stanza:: gety(){return y;}

stanza* stanza:: getnord() {return nord;}
stanza* stanza:: getsud() {return sud;}
stanza* stanza:: getest() {return est;}
stanza* stanza:: getwest() {return west;}
void stanza:: writenord(stanza* niu){nord=niu;}
void stanza:: writesud(stanza* niu){sud=niu;}
void stanza:: writeest(stanza* niu){est=niu;}
void stanza:: writewest(stanza* niu){west=niu;}

ptr_listapl stanza:: get_pls() {return pls;} //ritorna il PUNTATORE ALLA TESTA della lista_players della stanza
void stanza:: write_pls (ptr_listapl gigi) {pls=gigi;}

void stanza:: add_player(int idPleier){  ///head_insert, pls è sempre puntatore alla testa!
            ptr_listapl tmp = new lista_players;
            tmp->next_pl = pls;  //se pls era null, va a null; se era altro, tmp gli si metterà davanti
            tmp->idPlayer = idPleier;
            pls = tmp;
        }///riesce ad aggiornare pls, lo vede in quanto campo della classe


ptr_listapl stanza:: rimuv_player(int idP2remove, ptr_listapl head){ //ritorno ptr alla testa della lista aggiornata
            ///prende ptr alla testa e id del player da rimuovere(si è spostato), trova il
            ///palyer(scorrendo i presenti nella stanza)(ricordate che è solo un id!!) e lo rimuove
            ///PRECONDITION: DA CHIAMARE SOLO SE [___C'è IL PLAYER___] O CRASHA (così funge anche da test!)
            ///nel senso che nel resto del codice questa funzione viene chiamata solo in casi in cui il player
            /// era effettivamente li e si è spostato, ergo è da rimuovere, quindi se finisce per dover rimuovere
            /// un player non presente significa che c'è stato un errore in un altro pezzo del codice!
            ptr_listapl tmp = new lista_players;
            tmp = head; //scorro con tmp
            if ( tmp->idPlayer == idP2remove ){ //caso player in 1.nodo
                tmp=tmp->next_pl;
                head=tmp;
                return head;
            }
            else{
                ptr_listapl prec = new lista_players;
                prec = tmp;
                tmp = tmp->next_pl;
                while ( tmp->idPlayer != idP2remove ) {tmp=tmp->next_pl; prec=prec->next_pl;} //avanzano insieme
                //ora tmp punta al nodo da rimuovere
                prec->next_pl = tmp->next_pl; //funziona anche se è l'ultimo
                return head;
            }
        }//fine rimuv_player
