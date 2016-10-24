        //
//  main.cpp
//  Progetto Programmazione
//
//  Created by Damiano Bellucci on 25/09/16.
//  Copyright © 2016 Damiano Bellucci. All rights reserved.
//

#include "game.hpp"
#include "battle.hpp"
using namespace std;

Object::Object(){
    strcpy(name, "\0");
    damage=0;
}
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
void Object::setObject(char nome[], int danno){
    strcpy(name, nome);
    damage=danno;
}

Inventory::Inventory(){
    int i=0;
    for (i=0;i<5;i++){
        //slot[i]=false;
        oggetto[i]=NULL;
    }
}
bool Inventory::slotIsFull(int slotInventario){ //controlla se uno specifico slot dell'inventario è pieno
    if (oggetto[slotInventario]!=NULL) {
        return 1;
    }
    else return 0;
    //return slot[slotInventario]; //ritorna 1 se è pieno, 0 altrimenti
    }
int Inventory::AccessObjectFromInventory (int slotInventario){ //accede ad un oggetto dell'inventario
        return oggetto[slotInventario]->Damage(); //ritorna il danno dell'oggetto a cui si è acceduti nell'inventario
    }
void Inventory::insertObject(Object oggettoDaInserire, int slotInventario){//inserisci oggetto nell'inventario
    oggetto[slotInventario]=new Object;
    *oggetto[slotInventario]=oggettoDaInserire;
        //slot[slotInventario]=1; //dopo l'inserimento, lo slot sarà pieno
    }
void Inventory::deleteObject(int slotInventario){
    //elimina oggetto dall'inventario
    Object* app=oggetto[slotInventario];
    delete app;
    oggetto[slotInventario]=NULL;
    //slot[slotInventario]=0; //indico che lo slot nell'inventario corrispondente all'oggetto eliminato si è svuotato
    }
char* Inventory::getName(int slotInventario){
        return oggetto[slotInventario]->showNameObject();
    }

Player::Player(){
}

Player::Player(int identificatore){ //costruttore player
        inventario=new Inventory; //DA FIXARE!!! mettere inventario=NULL e inizializzarlo solo nel caso in cui viene inserito oggetto
        id=identificatore;
        lp=100;
        maxlp=100;
}
int Player::showId(){
        return id;
    }
int Player::maxHp(){
    if (lp>maxlp) maxlp=lp;
    return maxlp;
}
int Player::life(){ //ritorna i punti vita del giocatore
        if (lp>=0) return lp;
        else return 0;
    }
void Player::lifeFix(int value){ //cambia vita del giocatore in base all'oggetto che gli si passa //da cambiare con input int, sennò mosse mostro non vengono prese
        lp=lp-value;
    }
int Player::useObject(int slotInventary){ //ritorna il danno dell'oggetto scelto tra uno degli oggetti negli slot dell'inventario
        return inventario->AccessObjectFromInventory(slotInventary);
    }
void Player::TakeObject(Object oggetto){ //inserisce un oggetto nel primo slot libero disponibile, i alla fine conterrà l'informazione della posizione dell'eventuale slot libero
        int i=0;
    if (inventario==NULL) {
        inventario=new Inventory;
    }
        while (inventario->slotIsFull(i)) { //scorro nell'inventario per ricercare lo slot libero
            i++;
        }
        if (i<5) { //se c'è uno slot libero tra i primi quattro posti lo riempio
            inventario->insertObject(oggetto,i);
        }
}
Inventory* Player::showInventory(){
        return inventario;
    }

Queue::Queue(){
    q=NULL;
}

void Queue::enqueue (Player giocatore){


    if (q==NULL) {
        q=new Node;
        q->player=giocatore;
        q->next=q;
    }
    else{
        Node* app/*=new node*/;
        app=q;
        while (app->next!=q) {
            app=app->next;
        }
        Node* nodo=new Node;

        nodo->player=giocatore;
        //cout<<&nodo->player<<" "<<&giocatore<<endl;
        nodo->next=q;
        app->next=nodo;
        nodo=NULL;
    }
}

void Queue::dequeue(int idPlayer){
    if (q!=NULL) {
        if ((q->player).showId()==idPlayer && q->next==q) { //caso in cui c'è solo primo elemento (OK)
            Node* app=q;
            q=NULL;
            delete app;

        }
        else{
            if ((q->player).showId()==idPlayer) { //caso in cui elimino elemento in testa in una lista di elementi

                Node* track=q; //faccio puntare ultimo elemento al nuovo primo elemento visto che sto eliminando testa
                while (track->next!=q) {
                    track=track->next;
                }
                track->next=q->next;
                track=NULL;
                delete track;

                Node* app; //elimino elemento di testa //perchè non funziona senza questa riga di comando?
                app=q;
                q=q->next;
                delete app;
                }
            else{ //caso generale eliminazione nodo
                Node* p=new Node;
                p=q;
                bool flag=0;

                while ((p->next->player).showId()!=idPlayer && p->next->next!=q) {
                    p=p->next;
                }

                if ((p->next->player).showId()==idPlayer) {
                    Node* app=new Node;
                    p->next=p->next->next;
                    app=p->next;
                    //delete app;
                }
            }

        }
    }
}
Node* Queue::returnHead(){
    return q;
}
bool Queue::isEmpty(){
    if (q!=NULL) {
        return false;
    }
    return true;
}

Manage::Manage(){
    n=0;
    l=NULL;
    database=NULL;
    defObj=NULL;
    nPlayers=0;
    nRounds=0;
}

void Manage::builtQueue(){
    
    if (nPlayers>0)
    {
        int i=0;
        l=new Queue;
        Queue *p=new Queue;
        for (i=0; i<nPlayers;i++) {
            Player app=Player(i+1);
            p->enqueue(app);
        }
        l=p;
    }
}

Queue* Manage::returnList(){
    return l;
}

bool Manage::databaseEmpty(){
    if (database!=NULL) {
        return false;
    }
    return true;
}
void Manage::fetchDatabaseObjects(Object oggettoDelGioco){
    int j=0;
    Object *app=new Object;
    *app=oggettoDelGioco;
    if(database==NULL){
        int i=0;
        database=new databaseObject;
        for(i=0;i<6;i++){
            database->oggetto[i]=NULL;
        }
    }
    while (database->oggetto[j]!=NULL && j<6){
        j++;
    }
    if(j!=6){
        database->oggetto[j]=new Object;
        database->oggetto[j]=app;
    }
    app=NULL;
}


void Manage::spawnMonsterOrObject(Player* giocatore){
    int die = 0;
    srand(time(0));
    die = (rand() % 100) +1;//DA DECIDERE VALORE VALORE
    if (die<=50) { //spawn mostro e inizio battaglia
        battle b=battle(giocatore, this);
        b.battleManager();
    }
    else{
        if (!this->databaseEmpty()) {
        die = (rand() % 5) +1; //avendo 6 oggetti faccio uscire un numero tra 1 e 6 per selezionare un oggetto a caso da database oggetti
        int count=0;
        
        while (database->oggetto[die]==NULL && count<6 ) {
                if (die==5){
                        die=0;
                }
                else die++;
                count++;
        }
        
        bool error=true;
        int risposta=0;

            if (database->oggetto[die]!=NULL)
            {
                cout<<"Il tuo inventario:"<<endl;
                int i=0;
                int count=0;
                while (i<5) {
                    if(giocatore->showInventory()->slotIsFull(i)){
                        count++;
                        cout<<i+1<<")"<<giocatore->showInventory()->getName(i)<<endl;
                    }
                    i++;
                }
                cout<<endl;
                
                while(error)
                {
                cout <<"Hai trovato l'oggetto "<<database->oggetto[die]->showNameObject()<<", vuoi prenderlo? [1]=SI [0]=NO: "<<endl;
                cin >>risposta;

                if (risposta!=0 && risposta!=1)
                {
                    error=true;
                }
                else
                {
                    error=false;
                }
            }
        }
        if (risposta==1) { //stampo inventario e gestisco sostituzione oggetto se inventario è pieno
            int i=0;
            int count=0;
            while (i<5) {
                if(giocatore->showInventory()->slotIsFull(i)){
                    count++;
                }
                i++;
            }
            if (count==5) {
                int i=0;
                risposta=0;
                bool error=true;
                while(error){
                    cout <<"Il tuo inventario è pieno! Vuoi prendere comunque l'oggetto sostituendolo con uno del tuo inventario? [1]=SI [0]=NO: "<<endl;
                    cin >>risposta;
                    cout <<endl;

                    if (risposta!=0 && risposta!=1)
                    {
                        error=true;
                    }
                    else
                    {
                        error=false;
                    }
                }
            }
            if (risposta==1) {
                if (count==5){
                        int slot;
                        error=true;

                        while (error) {
                            cout <<"Inserisci il numero dello lo slot dell'oggetto che vuoi sostituire: "<<endl;
                            cin >>slot;
                            if(slot>0 && slot<=5)error=false;
                            else cout<<"Attenzione: hai inserito uno slot non valido! ";
                        }
                    slot--;
                    giocatore->showInventory()->deleteObject(slot);
                    giocatore->TakeObject(*database->oggetto[die]);
                }
                else
                {
                    giocatore->TakeObject(*database->oggetto[die]);
                }
            }
        }
        }
    }
}

void Manage::dropObject(Player* giocatore){
    if(!this->databaseEmpty()){
    int die = 0;
    srand(time(0));

    die = (rand() % 5) +1; //avendo 6 oggetti faccio uscire un numero tra 1 e 6 per selezionare un oggetto a caso da database oggetti
    int count=0;
    while (database->oggetto[die]==NULL && count<6 ) {
            if (die==5){
            die=0;
            }
            else die++;
            count++;
    }
    bool error=true;
    int risposta=0;

    if (database->oggetto[die]!=NULL)
    {
        while(error)
        {
            cout <<"Il mostro aveva con sé l'oggetto "<<database->oggetto[die]->showNameObject()<<", vuoi prenderlo? [1]=SI [0]=NO: "<<endl;
            cin >>risposta;

            if (risposta!=0 && risposta!=1)
            {
                error=true;
            }
            else
            {
                error=false;
            }
        }
    }
    if (risposta==1) { //stampo inventario e gestisco sostituzione oggetto se inventario è pieno
        int i=0;
        int count=0;
        while (i<5) {
            if(giocatore->showInventory()->slotIsFull(i)){
                count++;
                //cout<<i+1<<")"<<giocatore->showInventory()->getName(i)<<endl;
            }

            i++;
        }
        cout<<endl;
        if (count==5) {
            int i=0;
            cout<<"Il tuo inventario:"<<endl;
            while (i<5) {
                if(giocatore->showInventory()->slotIsFull(i)){
                cout<<i+1<<")"<<giocatore->showInventory()->getName(i)<<endl;
                }
                
                i++;
            }
            risposta=0;
            error=true;
            while(error){
                cout <<"Il tuo inventario è pieno! Vuoi prendere comunque l'oggetto sostituendolo con uno del tuo inventario? [1]=SI [0]=NO: ";
                cin >>risposta;
                cout <<endl;

                if (risposta!=0 && risposta!=1)
                {
                    //cout<<"Inserisci un comando valido! "<<endl;
                    error=true;
                }
                else
                {
                    error=false;
                }
            }
        }
        if (risposta==1) {
            if (count==5){
                int slot;
                error=true;

                while (error) {
                    cout <<"Inserisci il numero dello lo slot dell'oggetto che vuoi sostituire: "<<endl;
                    cin >>slot;
                    if(slot>0 && slot<=5)error=false;
                    else cout<<"Attenzione: hai inserito uno slot non valido! "<<endl;
                }
                slot--;
                giocatore->showInventory()->deleteObject(slot);
                giocatore->TakeObject(*database->oggetto[die]);
            }
            else
            {
                giocatore->TakeObject(*database->oggetto[die]);
            }
        }
    }
    }
}

void Manage::setRounds(int n){
    nRounds=n;
}
void Manage::setPlayers(int n){
    nPlayers=n;
}

void Manage::assignDefaultObject(){
    if(defObj!=NULL){
        int i=0;
        Node* app=this->returnList()->returnHead();
        for (i=0; i<nPlayers; i++) {
        app->player.TakeObject(*defObj);
        app=app->next;
    }
    app=NULL;
    /*delete app;*/
    }
    
}
void Manage::setDefaultObject(Object oggetto){
    defObj=new Object;
    Object* app=new Object;
    *app=oggetto;
    defObj=app;
    app=NULL;
}
void Manage::startGame(){
    int nplayers=0;
    int nrounds=0;
    bool error=true;
    int roundsCounter=0;
    int ndead=0;
    int nDeath=0;
    cout<<"Inserisci numero giocatori: ";
    cin>>nplayers;
    cout<<endl;
    this->setPlayers(nplayers);
    
    cout<<"Inserisci numero rounds per giocatore: ";
    cin>>nrounds;
    cout<<endl;
    this->setRounds(nrounds);
    
    this->builtQueue();
    this->assignDefaultObject();
    
    Node* app=this->returnList()->returnHead();
    while (!(this->returnList())->isEmpty() && roundsCounter<nRounds){
        //stampa mappa
        ndead=0;
        roundsCounter++;
        cout<<"ROUND "<<roundsCounter<<endl;

        Node* app=this->returnList()->returnHead();
        int i=0;
        for (i=0; i<(nPlayers-nDeath); i++) {
            cout << "Giocatore "<<app->player.showId()<<" fai la tua mossa! [W]=Nord, [S]=sud, [A]=ovest, [D]=est"<<endl;
            //stampa mappa
            //cambia posizione giocatore
            this->spawnMonsterOrObject(&app->player); //battaglia o trova oggetto
            if(app->player.life()<=0){ //Se giocatore è morto lo elimino dalla lista
                l->dequeue(app->player.showId());
                ndead++;
            }
            app=app->next;
            
        }
        nDeath=nDeath+ndead;
        //app=NULL; (meglio qui)
    }
    app=NULL;    
    //SPAWN MOSTRO
    
    
}
