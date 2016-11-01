#include "manageGame.hpp"
#include "battle.hpp"
#include "provmappa.hpp"
#include "finale.hpp"

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


void Manage::fetchDatabaseObjects(Object oggettoDelGioco){
    int j=0;
    if(database==NULL){
        int i=0;
        database=new databaseObject;
    }
/*
    while (database->oggetto[j]!=NULL && j<6){
        j++;
    }
    if(j!=6){
        database->oggetto[j]=new Object(oggettoDelGioco.showNameObject(),oggettoDelGioco.Damage());
    }*/

    while (database->slotDatabase(j)!=NULL && j<6){
        j++;
    }
    if(j!=6){
        database->addObjectToDatabase(j,oggettoDelGioco);
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
        if (!database->databaseEmpty()) {
            die = (rand() % 5) +1; //avendo 6 oggetti faccio uscire un numero tra 1 e 6 per selezionare un oggetto a caso da database oggetti
            int count=0;
            while (database->slotDatabase(die)==NULL && count<6) {
                if (die==5){
                    die=0;
                }
                else die++;
                count++;
            }
            bool error=true;
            int risposta=0;
            if (database->slotDatabase(die)!=NULL)
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
                    cout <<"Hai trovato l'oggetto "<<database->slotDatabase(die)->showNameObject()<<", vuoi prenderlo? [1]=SI [0]=NO: "<<endl;
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
                        giocatore->TakeObject(*database->slotDatabase(die));
                    }
                    else{
                        giocatore->TakeObject(*database->slotDatabase(die));
                    }
                }
            }
        }
    }
}

void Manage::dropObject(Player* giocatore){
    if(!database->databaseEmpty()){
        int die = 0;
        srand(time(0));
        die = (rand() % 5) +1; //avendo 6 oggetti faccio uscire un numero tra 1 e 6 per selezionare un oggetto a caso da database oggetti
        int count=0;
        while (database->slotDatabase(die)==NULL && count<6 ) {
            if (die==5){
                die=0;
            }
            else die++;
            count++;
        }
        bool error=true;
        int risposta=0;
        
        if (database->slotDatabase(die)!=NULL)
        {
            while(error)
            {
                cout <<"Il mostro aveva con sé l'oggetto "<<database->slotDatabase(die)->showNameObject()<<", vuoi prenderlo? [1]=SI [0]=NO: "<<endl;
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
                    giocatore->TakeObject(*database->slotDatabase(die));
                }
                else
                {
                    giocatore->TakeObject(*database->slotDatabase(die));
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
    int turni=0;
    
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
    
    cout<<"Indica alla squadra per quanti turni ognuno deve raziare prima di attaccare il drago:"<<endl;
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
        
        turni=nPlayers-ndead;
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
                app->player.getsonoqui()->deleteplayer(app->player.showId());
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
            turni --;
        }while (turni>0);
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
