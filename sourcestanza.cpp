//
#include "sourcestanza.hpp"


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

ptr_listapl stanza:: get_pls() {return pls;} //ritorna il PUNTATORE ALLA TESTA della lista_Players della stanza
void stanza:: write_pls (ptr_listapl gigi) {pls=gigi;}

void stanza:: add_Player(int idPleier){  ///head_insert, pls è sempre puntatore alla testa!
            ptr_listapl tmp = new lista_Players;
            tmp->next_pl = pls;  //se pls era null, va a null; se era altro, tmp gli si metterà davanti
            tmp->idPlayer = idPleier;
            pls = tmp;
        }

void stanza::deleteplayer(int idp){
  ptr_listapl tmp = this->get_pls(); //scorro con tmp
  ptr_listapl tmp2=tmp;
  if (tmp==NULL);
  else if ( tmp->idPlayer == idp ){ //caso Player in 1.nodo
      tmp2=tmp2->next_pl;
      delete tmp;
      tmp=NULL;
      this->write_pls( tmp2);
  }
  else{
      tmp = tmp->next_pl;
      while ( tmp->idPlayer != idp ) {tmp=tmp->next_pl; tmp2=tmp2->next_pl;} //avanzano insieme
      //ora tmp punta al nodo da rimuovere
      tmp=tmp->next_pl;
      delete tmp2->next_pl;
      tmp2->next_pl = tmp; //funziona anche se è l'ultimo
  }
}

ptr_listapl stanza:: rimuv_Player(int idP2remove, ptr_listapl head){ //ritorno ptr alla testa della lista aggiornata
            ///prende ptr alla testa e id del Player da rimuovere(si è spostato) lo trova e lo rimuove
            ptr_listapl tmp = head; //scorro con tmp
            ptr_listapl tmp2=tmp;
            if (head==NULL)return NULL;
            else if ( tmp->idPlayer == idP2remove ){ //caso Player in 1.nodo
                tmp2=tmp2->next_pl;
                delete tmp;
                tmp=NULL;
                return tmp2;
            }
            else{
                tmp = tmp->next_pl;
                while ( tmp->idPlayer != idP2remove ) {tmp=tmp->next_pl; tmp2=tmp2->next_pl;} //avanzano insieme
                //ora tmp punta al nodo da rimuovere
                tmp=tmp->next_pl;
                delete tmp2->next_pl;
                tmp2->next_pl = tmp; //funziona anche se è l'ultimo
                return head;
            }
        }//fine rimuv_Player
