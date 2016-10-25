///NESSUNO INVII QUESTO FILE A NESSUN* PROFESSOR* CHE CI SONO UN SACCO DI COMMENTI CHE
/// SERVONO PER IL DEBUG E CHE NON POSSONO ANDARE NELLA VERSIONE FINALE DEL PROGETTO! ^^"""
//e temo pure che ci siano delle osservazioni e commenti sbagliati proprio su cosa fa il codice..

///QUESTO è UN GIOCATORE FINTO con solo int id e puntatore alla stanza,
/// poi ci andrà quello vero, questo è quello con cui ho fatto le prove =)
#include "provmappa.hpp"

        Map::Map(int numero_di_giocatori){
            xmin=ymin=ymax=0;

            //ora calcolo pl_chars
            int giggi = 0;
            for ( int x = numero_di_giocatori; x>0 ; x-- ){ //per ogni giocatore(in senso figurato, non passo Player veri)
                giggi = giggi + numCifre(x) + 1;  //conta quante cifre ha il suo id e le somma al totale
            }
            pl_chars = giggi;
            //conteggia quanto spazio serve per la stampa degli id accanto alle stanze
            //(e affinchè stiano ben incolonnati!)
            //(il +1 è per spampare poi un "." tra un giocatore e l'altro)
            //per esempio: questa è una stanza " [ ] .1.10      "
            //ecco, quanti spazi lasciare dopo il 10 si conterà facendo [ pl_chars - 5 ]

            SThead = new lista_stanze;
            SThead->next = NULL;
            SThead->room = stanza(0,0); //pls NULL
            for (int i=1; i <= numero_di_giocatori; i++ ){ SThead->room.add_Player(i); }
            //int i calcola man mano l'id del Player che sta venendo aggiunto in 0,0, in senso figurato anche qui
            ///id est [nel costruttore] non serve get nessun id da nessun Player! =D
        }///fine costruttore


        int Map::get_pl_chars(){return pl_chars;} //solo per provare a stamparlo come controllo
        ptr_listast Map::getST(){return SThead;} //ritorna ptr alla testa della lista delle stanze

        ptr_listast Map::SThead_insertR (int ics, int ipsi, ptr_listast head){
            ptr_listast tmp = new lista_stanze;
            tmp->room = stanza(ics,ipsi); //costruisce nel campo room una stanza con ics e ipsi e tutti i ptr a NULL
            tmp->next = head ;
            head = tmp;
            return head;
        } ///aggiungitore di stanze che ritorna testa

        void Map::SThead_insert (int ics, int ipsi){
            // vede SThead perchè è un campo della classe
            //e aggiorna la lista senza bisogno di ritornare
            ptr_listast tmp = new lista_stanze;
            tmp->room = stanza(ics,ipsi); //costruisce nel campo room una stanza con ics e ipsi e tutti NULL
            tmp->next = SThead ;
            SThead = tmp;
        } ///aggiungitore di stanze non ritornante (aggiorna SThead, che è un campo della classe, resta visibile)
        //con add_Player ha funzionato..

        ///l'aggiornamento di xmin ymin ymax lo faccio nella costruzione di nuova stanza complessiva,
        ///questa è solo la funzione di inserimento in lista

        ///utility
        int Map::absh (int x){
            if (x<0){return -x;}
            else {return x;}
        }

        ptr_listast Map::reorder (ptr_listast headdy){ ///riordinatore per lista di stanze, bubblesort
            ///serve per riordinare(sulla base del campo x) le STANZE CON MEDESIMA Y nell'ambito della STAMPA!
            //(vedi funzionamento stampa)
            ///NON E' CREATA PER LAVORARE SULLA LISTA_STANZE DELLA MAPPA
            ///MA SU [___LISTE PROVVISORIE CREATE riga per riga APPOSITAMENTE PER OGNI STAMPA___]
            ptr_listast p; //scorre di volta in volta
            ptr_listast ultimo; //evita di riconfrontare quelli già ordinati, puntando il primo dei già-ordinati
            int flag;
            ultimo = NULL;
            flag = 1;
            while ( flag == 1 ){
                p = headdy; //p scorre tutte le volte la lista, dalla testa fino ad [ultimo]
                flag = 0; //flag tornerà 1 se troverò almeno una stanza con x minore della precedente
                //se flag non torna a 1 vuol dire che ho già ordinato tutto
                //e al giro dopo non entrerò nel while grosso e andrò a ritornare la testa
                while (p->next != ultimo) {
                    if ( p->room.getx() > (p->next)->room.getx() ) { //se ho trovato una stanza con x minore della precedente
                        //scambio LE STANZE a cui puntano p e p->next
                        stanza tmp = p->room ;
                        p->room = (p->next)->room ;
                        (p->next)->room = tmp;
                        //scambiate!
                        flag = 1; //"c'è ancora da fare ordine"
                    }//fine caso "c'era da scambiare"
                    p = p->next;
                }//ho scorso fino all'[ultimo attuale], ora aggiorno [ultimo]
                ultimo = p; //ho sistemato tutti fino a ultimo
            }//fine while grosso, falg è rimasto 0, era già tutto in ordine
            return(headdy);
        }///fine reorder
        stanza* Map::initiatestanze(){
            return &SThead->room;
        }

        bool Map::new_direction (char dir, Player *g1){
            ///precondition: char è wasd
            stanza* stvecchia = g1->getsonoqui();
            int ix = stvecchia->getx();
            int iy = stvecchia->gety();
            cout<<"\nstanza vecchia is "<< ix<< iy<< "\n"; //cout di prova

            bool crea = true;
            ///i ptr vengono aggiornati alla creazione della stanza, quindi se un ptr è!=NULL li c'è già una stanza
            if ( ( ( dir=='w') && (stvecchia->getnord()!=NULL) ) ||
                 ( ( dir=='s') && (stvecchia->getsud()!=NULL) ) ||
                 ( ( dir=='d') && (stvecchia->getest()!=NULL) ) ||
                 ( ( dir=='a') && (stvecchia->getwest()!=NULL) )
                ) { crea = false;}

            if (crea){
                //aggiungiamo la stanza: headinsert della stanza, con x e y e tutti i ptr a NULL
                // aggiorna la lista e xmin ymax ymin
                cout<< "\ncreazione!!\n"; //cout di prova
                if (dir == 'w'){
                        SThead_insert (ix, iy+1);
                        if ( iy+1 > ymax ){ymax = iy+1;}
                }
                if (dir == 's'){
                        SThead_insert (ix, iy-1);
                        if ( iy-1 < ymin ){ymin = iy-1;}
                }
                if (dir == 'd'){
                        SThead_insert (ix+1, iy);
                        //xmax non serve
                }
                if (dir == 'a'){
                        SThead_insert (ix-1, iy);
                        if ( ix-1 < xmin ){xmin = ix-1;}
                }
                //stanza nuova creata e NESSUN PTR A POSTO!!!
                cout<<"\nstanza creata, ptr ancora da sistemare\n"; //cout di prova

                ptr_listast gigi = getST();
                int xu = SThead->room.getx(); //x della stanza nuova
                int yu = SThead->room.gety(); //y della stanza nuova
                //cerco le CONFINANTI ALLA STANZA NUOVA scorrendo con gigi,
                //e, quando ne trovo una, aggiorno sia LA STANZA PUNTATA DA GIGI (TRA LE QUALI CI SARà STVECCHIA)
                //sia LA NUOVA, IN QUELLA DIREZIONE (LA NUOVA è SEMPRE IN TESTA, SThead->room.funzionipersmagheggiare)
                while (gigi != NULL){
                        //(la direzione non conta più!)
                        if( ( gigi->room.getx() == xu ) && ( gigi->room.gety() == yu+1 ) ){
                            //trovata stanza a NORD della nuova
                            gigi->room.writesud(&SThead->room);
                            SThead->room.writenord(&gigi->room);
                        }
                        else if( (gigi->room.getx() == xu ) && ( gigi->room.gety() == yu-1 ) ){
                            //trovata stanza a SUD della nuova
                            gigi->room.writenord(&SThead->room);
                            SThead->room.writesud(&gigi->room);
                        }
                        else if( (gigi->room.getx() == xu+1 ) && ( gigi->room.gety() == yu ) ){
                            //trovata stanza a EST della nuova
                            gigi->room.writewest(&SThead->room);
                            SThead->room.writeest(&gigi->room);
                        }
                        else if( (gigi->room.getx() == xu-1 ) && ( gigi->room.gety() == yu ) ){
                            //trovata stanza a WEST della nuova
                            gigi->room.writeest(&SThead->room);
                            SThead->room.writewest(&gigi->room);
                        }
                        gigi = gigi->next;
                }///fine messa-a-posto dei ptr
                //cout<<"ptr a postoss\n";
            }//fine caso [stanza NON già presente] aka (if (crea))

             ///ora spostare il Player
            ptr_listapl satana;
            satana = stvecchia->rimuv_Player (g1->showId(), stvecchia->get_pls()) ;
            cout<<"\nsatana all'opera\n";
            stvecchia->write_pls(satana);
            cout<<"rimozione Player fatta!! qui va!\n";


            //SThead->room.add_Player(g1->showId()); //così lo metteva nella stanza in testa
            if (dir=='w'){ stvecchia->getnord()->add_Player(g1->showId()) ; }
            else if (dir=='a'){ stvecchia->getwest()->add_Player(g1->showId()) ; }
            else if (dir=='s'){ stvecchia->getsud()->add_Player(g1->showId()) ; }
            else if (dir=='d'){ stvecchia->getest()->add_Player(g1->showId()) ; }
            cout<<"add_Player fatta!! qui va!\n";

            //g1->writesonoqui(&SThead->room); //così lo metteva nella stanza in testa
            if (dir=='w'){ g1->writesonoqui(stvecchia->getnord()) ;}
            else if (dir=='a'){ g1->writesonoqui(stvecchia->getwest()) ;}
            else if (dir=='s'){ g1->writesonoqui(stvecchia->getsud()) ;}
            else if (dir=='d'){ g1->writesonoqui(stvecchia->getest()) ;}
            ///sonoqui va all'INDIRIZZO DELLA STANZA
            cout<<"writesonoqui fatta!! qui va!\n";
            return crea;
        }///fine new_direction
        int Map::numCifre(int x){
            if (x<10) return 1;
            else if (x<100) return 2;
            else if (x<1000) return 3;
            else if (x<10000) return 4;
            else if (x<100000) return 5;
            else if (x<1000000) return 6;
            else if (x<10000000) return 7;
            else if (x<100000000) return 8;
            else if (x<1000000000) return 9;
            else return 10;
        }

        void Map::stampa (){
            cout<<"\n\n"; //inizio mappa un po' staccato da (qualunque cosa ci fosse prima)
            cout<<"\nxmin "<<xmin<<"\nymax "<<ymax<<"\nymin "<<ymin<<"\n\n";
            for ( int riga = ymax ; riga >= ymin ; riga-- ){///per ogni riga
                ptr_listast scorro = SThead; //lo vede, è un campo della classe
                while (scorro->room.gety() != riga) { scorro = scorro->next; }
                //ora scorro->room è la prima stanza trovata che ha y==riga
                ptr_listast provv_ST = new lista_stanze; ///provv_ST tiene copie delle stanze utili per la stampa di quella riga
                provv_ST->room = scorro->room;
                provv_ST->next = NULL;
                //è stata aggiunta la prima stanza, ora cerco le altre
                scorro = scorro->next; //se no mette 2 volte la prima trovata
                while ( scorro != NULL ){
                    if ( scorro->room.gety()==riga ){ //se ho trovato un'altra stanza con la stessa y
                        //aggiunge la stanza a provv_ST (head_insert)
                        ptr_listast gniu = new lista_stanze;
                        gniu->room = scorro->room;
                        gniu->next = provv_ST;
                        provv_ST = gniu;
                    }
                    scorro = scorro->next;
                }
                /* //cout di prova
                cout<<"\nprovo a stampare la lista provv_ST\n";
                ptr_listast prow = provv_ST;
                while (prow!=NULL){
                    cout<<prow->room.getx()<<prow->room.gety()<<"\n";
                    prow=prow->next;
                }*/
                ///ora ho tutte le stanze con y==riga nella provv_ST (locale alla riga corrente)

                ///adesso devo ordinare la lista sulla base del campo x
                provv_ST = reorder (provv_ST);
                /*
                cout<<"\nho chiamato reorder SULLA SINGOLA PROVV_ST, provo a stampare la lista provv_ST ORDINATA PER X\n";
                ptr_listast prow1 = provv_ST;
                while (prow1!=NULL){
                    cout<<prow1->room.getx()<<prow1->room.gety()<<"\n";
                    prow1=prow1->next;
                }*/
                ///ora manca solo stampare le stanze coi vari spazi, confrontando con xmin e tra di loro le x
                int j = xmin; //è o 0 o negativo
                ptr_listast provv = provv_ST; //scorro con provv
                //stampata una stanza, passo alla successiva, senza bisogno di cancellare dalla provv_ST quella stampata!
                while (provv!=NULL){ ///finchè non ho finito le stanze su quella riga
                    // uso valore assoluto (absh mia) perchè fa chiarezza =)
                    ///gap (che è int positivo) indica quante "stanze" lasciare affinchè l'incolonnamento sia comprensibile

                    ///la stanza è "  [ ] " ==2sp.prima,1inmezzo,1dopo, "SPAZIO PARETI"
                    ///più la parte dei giocatori (piena o vuota o vie di mezzo che sia) "SPAZIO PL"
                    if ( j!= provv->room.getx() ) { //se ci sono "stanze buche" da lasciare
                        int gap = absh ( j - provv->room.getx() );
                        for (int i = 1; i<= gap; i++){ //per ogni "stanza buca" da lasciare
                            cout<<"      "; //SPAZIO PARETI
                            for (int g = 1; g <= pl_chars; g++){cout<<" ";} //SPAZIO PL = pl_chars spazi
                        }//per ogni stanza buca da lasciare ho stampato gli spazi, visto che
                    }//c'erano stanze buche la lasciare

                    ///ora stampa la stanza "piena" trovata
                    cout<<"  [ ] ";
                    int counter = pl_chars;
                    ptr_listapl stampo = provv->room.get_pls();
                    while (stampo!= NULL){
                        cout<<"."<<stampo->idPlayer;
                        counter = counter -1 -numCifre(stampo->idPlayer);
                        stampo = stampo->next_pl;
                    }//ho finito di stampare i giocatori, lascio gli spazi restanti necessari
                    for ( int i = 1; i <= counter; i++){cout<<" ";}//stampo counter spazi

                    ///passa alla stanza successiva della provv_ST
                    j = provv->room.getx() +1 ; //pronto per il confronto con l' x della stanza dopo
                    provv = provv->next;
                }///ho finito le stanze su quella riga

                cout<<"\n\n"; //scende, va a capo per la prossima riga
            }///fine del "per ogni riga"
        }//fine stampa
