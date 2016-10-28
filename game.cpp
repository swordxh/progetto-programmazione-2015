#include "game.hpp"
#include "battle.hpp"
#include "provmappa.hpp"
#include "finale.hpp"
using namespace std;

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

Inventory::Inventory(){
    int i=0;
    for (i=0;i<5;i++){
        oggetto[i]=NULL;
    }
}

bool Inventory::slotIsFull(int slotInventario){ //controlla se uno specifico slot dell'inventario è pieno
    if (oggetto[slotInventario]!=NULL) {
        return 1;
    }
    else return 0;
}

int Inventory::AccessObjectFromInventory (int slotInventario){
        return oggetto[slotInventario]->Damage();
    }
void Inventory::insertObject(Object oggettoDaInserire, int slotInventario){
    oggetto[slotInventario]=new Object(oggettoDaInserire.showNameObject(),oggettoDaInserire.Damage());
    *oggetto[slotInventario]=oggettoDaInserire;
}

void Inventory::deleteObject(int slotInventario){
    Object* app=oggetto[slotInventario];
    delete app;
    oggetto[slotInventario]=NULL;
    }
char* Inventory::getName(int slotInventario){
        return oggetto[slotInventario]->showNameObject();
    }

Player::Player(){
}

Player::Player(int identificatore){
    id=identificatore;
    lp=100;
    maxlp=100;
    posizione=NULL;
    inventario=new Inventory;
}
int Player::showId(){
        return id;
}

int Player::maxHp(){
    if (lp>maxlp) maxlp=lp;
    return maxlp;
}
int Player::life(){
    if (lp>=0) return lp;
    else return 0;
}

void Player::lifeFix(int value){
    lp=lp-value;
}

int Player::useObject(int slotInventary){ //ritorna il danno dell'oggetto scelto tra uno degli oggetti negli slot dell'inventario
        return inventario->AccessObjectFromInventory(slotInventary);
}

void Player::TakeObject(Object oggetto){ //inserisce un oggetto nel primo slot libero disponibile, i alla fine conterrà l'informazione della posizione dell'eventuale slot libero
        int i=0;
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

void Player::writesonoqui(stanza* room){
    posizione=room;
}

stanza* Player::getsonoqui(){
    return posizione;
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
        Node* app=q;
        while (app->next!=q) {
            app=app->next;
        }
        Node* nodo=new Node;
        nodo->player=giocatore;
        nodo->next=q;
        app->next=nodo;
        nodo=NULL;
    }
}

void Queue::dequeue(int idPlayer){
    if (q!=NULL) {
        if ((q->player).showId()==idPlayer && q->next==q){ //caso in cui c'è solo primo elemento
            Node* app=q;
            q=NULL;
            delete app;
            app=NULL;
        }
        else{
            if ((q->player).showId()==idPlayer) { //caso in cui elimino elemento in testa in una lista di elementi
                Node* track=q; //faccio puntare ultimo elemento al nuovo primo elemento visto che sto eliminando testa
                while (track->next!=q) {
                    track=track->next;
                }

                track->next=q->next;
                track=NULL;

                Node* app; //elimino elemento di testa
                app=q;
                q=q->next;
                delete app;
                app=NULL;

                }
            else{ //caso generale eliminazione nodo
                Node* p=q;

                while ((p->next->player).showId()!=idPlayer && p->next->next!=q) {//inizio a controllare dall'elemento dopo la testa visto che quest'ultima è già stata controllata nei casi prima. Caso in cui ho due elementi: non entro nel while
                    p=p->next;
                }
                if ((p->next->player).showId()==idPlayer) { //devo controllare che non sia finito nel caso in cui non c'è elemento cercato e abbia solo due nodi
                    Node* app=new Node;
                    app=p->next;
                    p->next=p->next->next;
                    delete app;
                    app=NULL;
                }
            }

        }
    }
}

Node* Queue::Head(){
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
    l=new Queue;
    database=NULL;
    defObj=NULL;
    nPlayers=0;
    nRounds=0;
}

void Manage::builtQueue(){
    if (nPlayers>0){
        int i=0;
        Queue *p=new Queue;
        for (i=0; i<nPlayers;i++) {
            Player app=Player(i+1);
            p->enqueue(app);
        }
        l=p;
    }
}

bool Manage::databaseEmpty(){
    if (database!=NULL) {
        return false;
    }
    return true;
}

void Manage::fetchDatabaseObjects(Object oggettoDelGioco){
    int j=0;
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
        database->oggetto[j]=new Object(oggettoDelGioco.showNameObject(),oggettoDelGioco.Damage());
    }
}

int Manage::sanitycheck(){
    int num=0;
    bool failed=false;
    do{
        failed=false;
        cin>>num;
        if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"L'input dev'essere un intero!"<<endl;
            failed=true;
        }
    }while(failed);
    return num;
}

void Manage::spawnMonsterOrObject(Player* giocatore){
    int die = 0;
    srand(time(0));
    die = (rand() % 100) +1;
    if (die<=70) {
        battle *b= new battle(giocatore, this);
        b->battleManager();
        delete b;
        b=NULL;
    }
    else{
        if (!this->databaseEmpty()) {
        die = (rand() % 5) +1; //avendo 6 oggetti faccio uscire un numero tra 1 e 6 per selezionare un oggetto a caso da database oggetti
        int count=0;
        while (database->oggetto[die]==NULL && count<6) {
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
                risposta=sanitycheck();
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
                risposta=0;
                bool error=true;
                while(error){
                    cout <<"Il tuo inventario è pieno! Vuoi prendere comunque l'oggetto sostituendolo con uno del tuo inventario? [1]=SI [0]=NO: "<<endl;
                    risposta=sanitycheck();
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
                            slot=sanitycheck();
                            if(slot>1 && slot<=5)error=false;
                            else cout<<"Attenzione: hai inserito uno slot non valido! ";
                        }
                    slot--;
                    giocatore->showInventory()->deleteObject(slot);
                    giocatore->TakeObject(*database->oggetto[die]);
                }
                else{
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
            risposta=sanitycheck();
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
                    risposta=sanitycheck();
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
                        slot=sanitycheck();
                        if(slot>1 && slot<=5)error=false;
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
        Node* app=l->Head();
        for (i=0; i<nPlayers; i++) {
            app->player.TakeObject(*defObj);
            app=app->next;
        }
        app=NULL;
    }
}

void Manage::setDefaultObject(Object oggetto){
    defObj=new Object(oggetto.showNameObject(),oggetto.Damage());
}

void Manage::startGame(){
    cout<<"I nostri eroi, sotto incarico del Signore di Hasfurgharden, s'incamminano verso le miniere scarlatte, tana del feroce Drago di Rungehan. \nIl regno è ormai allo stremo, le famiglie più povere non riescono più a sopravvivere dopo l'arrivo del malefico mostro, che ogni dì razia il villagio;\n solo i nostri eroi possono salvarli, che Restafor li benedica! "<<endl<<endl;
    int nplayers=0;
    int nrounds=0;
    int roundsCounter=0;
    int ndead=0;
    bool flag=false;
    bool retry=false;
    int appdeath=-1;

    cout<<"Quanti eroi vuoi inviare nel dungeon?: "<<endl;
    do{
      retry=false;
      nplayers=sanitycheck();
      if (nplayers<1){
          retry=true;
          cout<<"devi inserire un numero maggiore di 0!"<<endl;
        }
    }while (retry);
    cout<<endl;
    this->setPlayers(nplayers);

    cout<<"Indica alla squadra quanto devono raziare prima di attaccare il drago:"<<endl;
    do{
      retry=false;
      nrounds=sanitycheck();
      if (nrounds<1){
          retry=true;
          cout<<"devi inserire un numero maggiore di 0!"<<endl;
        }
    }while (retry);
    cout<<endl;
    this->setRounds(nrounds);

    this->builtQueue();
    this->assignDefaultObject();
    Map mappa(nPlayers);
    stanza* basemappa=mappa.initiatestanze();
    bool newroom=false;
    char dir;

    Node* app=l->Head();

    while (l->Head()!=NULL && roundsCounter<nRounds){
        roundsCounter++;
        cout<<"                              ROUND "<<roundsCounter<<endl;
        cout<<"[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]"<<endl;
        do{

            flag=false;
            mappa.stampa();
            if (app->player.getsonoqui()==NULL)app->player.writesonoqui(basemappa);
            cout << "Giocatore "<<app->player.showId()<<" fai la tua mossa! [W]=Nord, [S]=sud, [A]=ovest, [D]=est"<<endl;
            do{
                retry=false;
                cin>>dir;
                if ((dir!='w') && (dir!='a') && (dir!='s') && (dir!='d')){
                    retry=true;
                    cout<<"devi inserire uno dei seguenti caratteri minuscoli! w a s d"<<endl;
                }
            }while (retry);
            newroom=mappa.new_direction(dir, &app->player);
            if (newroom)this->spawnMonsterOrObject(&app->player); //battaglia o trova oggetto
            if(app->player.life()<=0){ //Se giocatore è morto lo elimino dalla lista
                flag=true;
                appdeath=app->player.showId();
                app=app->next; //prima di eliminare nodo lista devo far scorrere app perchè sta puntando il nodo da eliminare
                if (app->next==app) { //nel caso in cui devo eliminare l'unico elemento nella lista app non potrà puntare al successivo (in quanto il successivo è sempre il primo elemento che andrà eliminato
                    app=NULL;
                }
                l->dequeue(appdeath);
                ndead++;
            }
            if (!flag && app!=NULL)app=app->next; //se non c'è stata eliminazione e coda non è vuota faccio scorrere app
            cout<<"======================================================================"<<endl;
        }while (app!=l->Head());
    }
    app=NULL;
    if (l->Head()!=NULL){
        finale fine(l, nPlayers-ndead, this);
        fine.battleManager();
    }
    else cout<<"       PURTROPPO TUTTI GLI EROI SONO PERITI, QUAL DISGRAZIA PER IL REGNO DI HASFURGHARDEN!!!!";
    delete l;
    l=NULL;
}
