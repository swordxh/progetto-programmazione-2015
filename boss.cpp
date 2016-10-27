/*#include "boss.hpp"
using namespace std;

boss::boss(int *nPlayers){
        strcpy(name,"Drago\0"); // nome
        MaxHp= (*nPlayers * 100) * z; // "n" = numero giocatori, "z" = fattore che moltiplica vita
        Hp=MaxHp;
        damagest = 20; // attacco standard
        damage1 = 10; // attacco che colpisce tutti i giocatori
}
char *boss::GetName(){
        return name;
} // da il nome del boss
void boss::GotHit(int dmg){
        Hp=Hp-dmg;
} // il boss subisce i danni del giocatore
int boss::getDmg(){
        return damagest;
} // il boss usa l'attacco standard
int boss::LifePoints(){
        return Hp;
} // HP attuali del boss
int boss::MaxLifePoints(){
        return MaxHp;
} // HP massimi del boss
int boss::speciale1(){
        return damage1;
} // il boss usa l'attacco che colpisce tutti i giocatori

finale::finale(Queue *p_curr, int n, Manage *man){
    l = p_curr;
    p = NULL;
    head = NULL; //prendono la lista
    b = NULL;
    MonsterName[0]='\0';
    k = 1; // Iniziano i turni
    att = 1; // inizio dal primo giocatore
    manage = man;
    scelto = 0;
    q = NULL;
    database=NULL;
    nPlayers = n;
}
Queue* finale::returnList(){
    return l;
}
void finale::battleManager(){
    head = this -> returnList() -> returnHead();
    if (b == NULL) {
        b = new boss(&nPlayers);
        strcpy(MonsterName, b->GetName());
    }// inizializzo il boss
    int stato=0; // Inizia la battaglia
    cout<<"... La situazione e' fin troppo tranquilla..." << endl;
    cout << "Nessun nemico..." << endl;
    cout << "Nessun sinistro rumore di passi..." << endl;
    cout << "Come se tutto cio' fosse la quiete prima della tempesta..." <<endl;
    cout<<endl<<endl<<endl<<"Il "<<MonsterName<<" ti attacca, inizi cosi a difenderti."<<endl;
    while (stato==0){
        p=this->returnList()->returnHead();// mi metto nella testa della lista
        for(int i = 0; ((i < nPlayers)&&(stato==0)); i++){
            q = &p -> player; //prendo il campo "player"
            if (b!=NULL){
                HealthBar(b->LifePoints(), b->MaxLifePoints()); // gli do gli HP attuali\massimi dei giocatori e del boss, aggiungendo l'ID del giocatore
            } // se il boss è vivo, vado in HealthBar
            stato=CalculateDamage(IOManager());
            p = p -> next; //vado al giocatore successivo
            att++;
        } // attaccano i giocatori
        att = (-1);//Sono ritornato alla testa
        if (stato != 1){
            stato=CalculateDamage(att); //attacca il boss
            att = 1; // così permetto ai giocatori di attaccare nel turno successivo
            k++; // turno finito, passo a quello successivo
        }//se il boss è morto, non faccio queste istruzioni
    }// finchè "stato" = 0 (ovvero i giocatori e il boss sono vivi) io sto dentro il while
    if (b!=NULL){
        HealthBar(b->LifePoints(), b->MaxLifePoints());
    }// in questo caso i giocatori sono morti (sono fuori dal while)
    if (stato==1){
        WinScreen(MonsterName); // vittoria
    }
    if (stato==2){
        LoseScreen(); // game over
    }
}
int finale::IOManager(){ //ritorna il danno del oggetto che si è scelto
	cout<<endl;
	cout<<"Scegli l'oggetto che vuoi usare per colpire il "<<MonsterName<<":"<<endl;
	int select=1;
	for (int i=0; i<5; i++){
		if (q->showInventory()->slotIsFull(i)){
			cout<<select<<") "<< q->showInventory()->getName(i)<< "(dmg "<<q->showInventory()->AccessObjectFromInventory(i)<<")"<<endl;
			select++;
		}
	}//indica, se disponibili, gli oggetti (negli slot pieni) che può usare il giocatore
	select--;
	int counter=select;
	do{
		select=manage->sanitycheck();
		if ((select<1) || (select>counter)) cout<<"Devi selezionare un oggetto valido!"<<endl;
	}while((select<1) || (select>counter)); //scelgo un oggetto
	counter=1;
	bool exit=false;
	int i=0;
	bool ispotion=false;
	while (!exit){
		if ((q->showInventory()->slotIsFull(i)) && (select==counter)){
			if (q->showInventory()->AccessObjectFromInventory(i)==0){
				q->lifeFix(-potionHP);
				cout<<"usi la Pozione che ti restituisce "<<potionHP<<" HP!"<<endl;
				q->showInventory()->deleteObject(i);
				ispotion=true;
			}//in questo caso ho usato la pozione
			exit=true;
		}//ho trovato l'oggetto selezionato
		else if (q->showInventory()->slotIsFull(i)) counter++; //se non ho trovato l'oggetto, vado a quello successivo
		i++;
	}
	i--;
	if(!ispotion) return q->showInventory()->AccessObjectFromInventory(i); //utilizzo un oggetto diverso dalla pozione
    else return 0;
}
void finale::WinScreen(char MonsterName[]){
        cout<<"		CONGRATULAZIONI! AVETE BATTUTO IL "<<MonsterName<<endl;
        cout<<"Grazie al valore dei guerrieri, i nemici, privi di un leader, si arresero..."<<endl;
        cout<<"Al loro ritorno, i re li onorarono con laute ricompense e la gente gli dedico'"<<endl;
        cout<<"poesie epiche: senza di loro, il mondo non sarebbe stato più lo stesso." << endl;
}
void finale::LoseScreen(){
        cout<<"				GAME OVER"<<endl;
        cout << "Nonostante l'atto eroico, cio' non basto' per fermare il drago..." << endl;
        cout << "Orde nemiche rasero uno ad uno villaggi e castelli, conquistando l'intero mondo." << endl;
}
void finale::HealthBar(int currenthpMonster,int maxhpMonster){ //20 barrette
    int g;
    cout <<endl<< "                                     " << MonsterName << endl<<" ";
    for(g=1; g<=78;g++)cout<<"-";
    cout<<endl<<'|';
    g=1;
    while(g<=78){
        if(((78*currenthpMonster)/maxhpMonster)>=g)cout<<"█";
        else cout<<' ';
        g++;
    }cout<<"|";
    cout<<endl<<"|";
    g=1;
    while(g<=78){
        if(((78*currenthpMonster)/maxhpMonster)>=g)cout<<"█";
        else cout<<' ';
        g++;
    }// calcola le █ in base agli HP attuali tramite una percentuale
    cout<<'|' << endl<<" "; // le | le ho messe solo per delimitare la barra della salute
    for(g=1; g<=78;g++)cout<<"-";
    cout<<endl<<endl<<endl;
    cout << "     _______M''''''M____                     ____M''''''''''''M________" << endl;
    cout << " __/      .        . __/\\__            _____/\\___  .8M.. .. D:   +\\_   \\ ___ " << endl;
    cout << "/ _>'''''''<     __/      \\_         /.= . ..   \\ . O          .   \\  OM.   \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout
    cout << "V            \\   /            \\....,',  .     .  \\ .     ..         \\    = < \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout
    cout << "              \\ /_M''''M_      XM______  .  .     .\\ .      ____ .  , \\ D /   \\" << endl;
    cout << "               V         \\    M.       \\________:   \\     M /        <_\\ |     V" << endl;
    cout << "                          \\  /                \\ \\___ \\   /             \\||" << endl;
    cout << "                           \\/..     O .OOO.    \\    \\,| /               V" << endl;
    cout << "                          _/.  M,..  ? : . ..   \\    X||" << endl;
    cout << "                        ./      ?...       ..    \\    V" << endl;
    cout << "                        ( .       N______   N7.   |" << endl;
    cout << "                         X7  M .  /      \\___. . M| " << endl;
    cout << "                        ( O .. O |           \\M  . \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout (qua è a causa della parentesi)
    cout << "                         M._____..)           \\     | " << endl;
    cout << "                         \\|'''''|/             \\   ,|" << endl;
    cout << "                          \\!!!!!/               \\ . |" << endl;
    cout << "                                                 \\  |" << endl;
    cout << "                                            ^     )Z )" << endl;
    cout << "                                           | \\   /M /" << endl;
    cout << "                                           | .\\_/M /" << endl;
    cout << "                                            \\_____/" << endl; //disegno boss
    g=1;
    while (g <= att){
        cout << "   ";
        if (g == att) cout << "V" << endl;
        else cout << "     ";
        g++;
    }// la V indica il giocatore attuale
    Node* scorr = head;
    Player* q1 = &scorr -> player;
    for(g = 0; g < nPlayers; g++){
        q1 = &scorr -> player;
        cout << "   " << q1 -> showId();
        if(g < nPlayers)cout<<"    ";
        scorr = scorr -> next;
    }//rappresenta gli ID dei giocatori
    cout<<endl;
    scorr = head;
    for(g = 0; g < nPlayers; g++){
        q1 = &scorr -> player;
        if ((q1 -> life()) >= 100) cout << q1 -> life() << "/" << q1 -> maxHp(); //la salute massima è dinamica
        else cout << " " << q1 -> life() << "/" << q1 -> maxHp(); // metto uno spazio per rappresentare correttamente lo schema di battaglia
        if(g < nPlayers)cout<<" ";
        scorr = scorr -> next;
    } //rappresenta la salute dei giocatori, attuale e massima
    cout<<endl;
}
int finale::CalculateDamage(int Damage){  //ritorna 0 se sono entrambi vivi 1 se il mostro è morto 2 se tutti i giocatori sono morti (se muore uno faccio dequeue)
        int status=0;
        if (b!=NULL){
            if (att != (-1)) b->GotHit(Damage); // il boss subisce danni dal giocatore
            else{
                Node* scorr = head;
                Player *q1 = &scorr -> player;
                if ((k % 3) == 0) {
                    att = q1 -> life();
                    scelto = q1 -> showId(); //potrebbe essere il primo giocatore quello ad avere meno vita
                    for (int i=0; i<nPlayers; i++){
                        q1 = &scorr -> player;
                        if ((q1 -> life()) < att) {
                            att = q1 -> life();
                            scelto = q1 -> showId();
                        } // ho trovato un giocatore che ha meno vita
                        scorr = scorr -> next; //va al nodo successivo
                    } //cerca il giocatore con meno vita
                    att = (-1);
                    scorr = this->returnList()->returnHead();
                    while (att == (-1)){
                        q1 = &scorr -> player;
                        if ((q1 -> showId()) == scelto){
                            q1 -> lifeFix(scorr -> player.life()); // il boss usa l'attacco prendendo direttamente la salute attuale del giocatore, così, in ogni caso, la azzera sempre
                            if (scorr -> next == scorr) status = 2; //caso in cui ho un solo elemento
                            else {
                                cout << "IL GIOCATORE " << q1 ->showId() << " E' MORTO" << endl;
                                l -> dequeue (q1 -> showId());
                                nPlayers--;
                                head = this -> returnList() -> returnHead();
                                p = head; //può essere stato il primo elemento della lista quello ad essere eliminato, quindi aggiorno la testa
                            }//caso in cui ho una lista di almeno 2 elementi, dove faccio dequeue e aggiorno i puntatori
                            att = 1;
                        }
                        scorr = scorr -> next; //va al nodo successivo
                    }//attacca il giocatore con meno vita
                    scelto = 0;
                }//attacco mortale
                else if ((k % 2) == 0){
                    for (int i=0; i<nPlayers; i++){
                        q1 = &scorr -> player;
                        q1 -> lifeFix(b->speciale1()); // usa l'attacco che colpisce tutti i giocatori
                        if ((q1 -> life()) <= 0) {
                            if (scorr -> next == scorr) status = 2; //caso in cui ho un solo elemento
                            else {
                                cout << "IL GIOCATORE " << q1 ->showId() << " E' MORTO" << endl;
                                l -> dequeue (q1 -> showId());
                                nPlayers--;
                                head = this -> returnList() -> returnHead();
                                p = head; //può essere stato il primo elemento della lista quello ad essere eliminato, quindi aggiorno la testa
                            }//caso in cui ho una lista di almeno 2 elementi, dove faccio dequeue e aggiorno i puntatori
                        }
                        scorr = scorr -> next; //va al nodo successivo
                    }
                    att = 1;
                } //ogni due turni usa l'attacco che colpisce tutti i giocatori
                else {
                    srand(time(0));
                    scelto = (rand() % nPlayers); //scelto indica il numero dei nodi che devo attraversare: se = 0, io attacco il giocatore del nodo in cui sono allo stato attuale, se = a un qualunque valore "i", io dovrò attraversare "i" nodi
                    while (att == (-1)){
                        q1 = &scorr -> player;
                        if (scelto == 0){
                            q1 -> lifeFix(b->getDmg());// attacco standard
                            if ((q1 -> life()) <= 0) {
                                if (scorr -> next == scorr) status = 2; //caso in cui ho un solo elemento
                                else {
                                    cout << "IL GIOCATORE " << q1 ->showId() << " E' MORTO" << endl;
                                    l -> dequeue (q1 -> showId());
                                    nPlayers--;
                                    head = this -> returnList() -> returnHead();
                                    p = head; //può essere stato il primo elemento della lista quello ad essere eliminato, quindi aggiorno la testa
                                }//caso in cui ho una lista di almeno 2 elementi, dove faccio dequeue e aggiorno i puntatori
                            }
                            att = 1; //ho finito, posso uscire dal while
                        }//sono sul giocatore che devo attaccare
                        else scelto--; //ho attraversato un nodo
                        scorr = scorr -> next; //va al nodo successivo
                    }
                    scelto = 0;
                }//attacco standard
            } // stavolta è il boss che attacca
            if (b->LifePoints()<=0){
                delete b;
                b=NULL;
                status=1;
            } // il boss è morto
        }
        return status;
}*/
#include "boss.hpp"
using namespace std;

boss::boss(int *nPlayers){
        strcpy(name,"Drago\0"); // nome
        MaxHp= (*nPlayers * 100) * z; // "n" = numero giocatori, "z" = fattore che moltiplica vita
        Hp=MaxHp;
        damagest = 10; // attacco standard
        damage1 = 5; // attacco che colpisce tutti i giocatori
}
char *boss::GetName(){
        return name;
} // da il nome del boss
void boss::GotHit(int dmg){
        Hp=Hp-dmg;
} // il boss subisce i danni del giocatore
int boss::getDmg(){
        return damagest;
} // il boss usa l'attacco standard
int boss::LifePoints(){
        return Hp;
} // HP attuali del boss
int boss::MaxLifePoints(){
        return MaxHp;
} // HP massimi del boss
int boss::speciale1(){
        return damage1;
} // il boss usa l'attacco che colpisce tutti i giocatori

finale::finale(Queue *p_curr, int n, Manage *man){
    l = p_curr;
    p = NULL;
    head = NULL; //prendono la lista
    b = NULL;
    MonsterName[0]='\0';
    k = 1; // Iniziano i turni
    att = 1; // inizio dal primo giocatore
    manage = man;
    m = 0;
    scelto = 0;
    q = NULL;
    database=NULL;
    nPlayers = n;
    potionHP=45;
}
Queue* finale::returnList(){
    return l;
}
void finale::battleManager(){
    head = this -> returnList() ->Head();
    if (b == NULL) {
        b = new boss(&nPlayers);
        strcpy(MonsterName, b->GetName());
    }// inizializzo il boss
    int stato=0; // Inizia la battaglia
    cout<<"... La situazione e' fin troppo tranquilla..." << endl;
    cout << "Nessun nemico..." << endl;
    cout << "Nessun sinistro rumore di passi..." << endl;
    cout << "Come se tutto cio' fosse la quiete prima della tempesta..." <<endl;
    cout<<endl<<endl<<endl<<"Il "<<MonsterName<<" ti attacca, inizi cosi a difenderti."<<endl;
    while (stato==0){
        p=this->returnList()->Head();// mi metto nella testa della lista
        for(int i = 0; ((i < nPlayers)&&(stato==0)); i++){
            q = &p -> player; //prendo il campo "player"
            if (b!=NULL){
                HealthBar(q->life(), q->maxHp(), b->LifePoints(), b->MaxLifePoints(), q->showId()); // gli do gli HP attuali\massimi dei giocatori e del boss, aggiungendo l'ID del giocatore
            } // se il boss è vivo, vado in HealthBar
            stato=CalculateDamage(IOManager());
            p = p -> next; //vado al giocatore successivo
            att++; //non sono ritornato alla testa, ho trovato il giocatore successivo
        } // attaccano i giocatori
        att = (-1);
        if (stato != 1){
            stato=CalculateDamage(att); //attacca il boss
            att = 1; // così permetto ai giocatori di attaccare nel turno successivo
            k++; // turno finito, passo a quello successivo
        }//se il boss è morto, non faccio queste istruzioni
    }// finchè "stato" = 0 (ovvero i giocatori e il boss sono vivi) io sto dentro il while
    if (b!=NULL){
        HealthBar(p->player.life(), p->player.maxHp(), b->LifePoints(), b->MaxLifePoints(), p->player.showId());
    }// in questo caso i giocatori sono morti (sono fuori dal while)
    if (stato==1){
        WinScreen(MonsterName); // vittoria
    }
    if (stato==2){
        LoseScreen(); // game over
    }
}
int finale::IOManager(){ //ritorna il danno del oggetto che si è scelto
	cout<<endl;
	cout<<"Scegli l'oggetto che vuoi usare per colpire il "<<MonsterName<<":"<<endl;
	int select=1;
	for (int i=0; i<5; i++){
		if (q->showInventory()->slotIsFull(i)){
			cout<<select<<") "<< q->showInventory()->getName(i)<< "(dmg "<<q->showInventory()->AccessObjectFromInventory(i)<<")"<<endl;
			select++;
		}
	}//indica, se disponibili, gli oggetti (negli slot pieni) che può usare il giocatore
	select--;
	int counter=select;
	do{
		select=manage->sanitycheck();
		if ((select<1) || (select>counter)) cout<<"Devi selezionare un oggetto valido!"<<endl;
	}while((select<1) || (select>counter)); //scelgo un oggetto
	counter=1;
	bool exit=false;
	int i=0;
	bool ispotion=false;
	while (!exit){
		if ((q->showInventory()->slotIsFull(i)) && (select==counter)){
			if (q->showInventory()->AccessObjectFromInventory(i)==0){
				q->lifeFix(-potionHP);
				cout<<"usi la Pozione che ti restituisce "<<potionHP<<" HP!"<<endl;
				q->showInventory()->deleteObject(i);
				ispotion=true;
			}//in questo caso ho usato la pozione
			exit=true;
		}//ho trovato l'oggetto selezionato
		else if (q->showInventory()->slotIsFull(i)) counter++; //se non ho trovato l'oggetto, vado a quello successivo
		i++;
	}
	i--;
	if(!ispotion) return q->showInventory()->AccessObjectFromInventory(i); //utilizzo un oggetto diverso dalla pozione
    else return 0;
}
void finale::WinScreen(char MonsterName[]){
        cout<<"		CONGRATULAZIONI! AVETE BATTUTO IL "<<MonsterName<<endl;
        cout<<"Grazie al valore dei guerrieri, i nemici, privi di un leader, si arresero..."<<endl;
        cout<<"Al loro ritorno, i re li onorarono con laute ricompense e la gente gli dedico'"<<endl;
        cout<<"poesie epiche: senza di loro, il mondo non sarebbe stato più lo stesso." << endl;
}
void finale::LoseScreen(){
        cout<<"				GAME OVER"<<endl;
        cout << "Nonostante l'atto eroico, cio' non basto' per fermare il drago..." << endl;
        cout << "Orde nemiche rasero uno ad uno villaggi e castelli, conquistando l'intero mondo." << endl;
}
void finale::HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID){ //20 barrette
    int g;
    cout <<endl<< "                                     " << MonsterName << endl<<" ";
    for(g=1; g<=78;g++)cout<<"-";
    cout<<endl<<'|';
    int i=1;
    while(i<=78){
        if(((78*currenthpMonster)/maxhpMonster)>=i)cout<<"█";
        else cout<<' ';
        i++;
    }cout<<"|";
    cout<<endl<<"|";
    i=1;
    while(i<=78){
        if(((78*currenthpMonster)/maxhpMonster)>=i)cout<<"█";
        else cout<<' ';
        i++;
    }// calcola le █ in base agli HP attuali tramite una percentuale
    cout<<'|' << endl<<" "; // le | le ho messe solo per delimitare la barra della salute
    for(g=1; g<=78;g++)cout<<"-";
    cout<<endl<<endl<<endl;
    cout << "     _______M''''''M____                     ____M''''''''''''M________" << endl;
    cout << " __/      .        . __/\\__            _____/\\___  .8M.. .. D:   +\\_   \\ ___ " << endl;
    cout << "/ _>'''''''<     __/      \\_         /.= . ..   \\ . O          .   \\  OM.   \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout
    cout << "V            \\   /            \\....,',  .     .  \\ .     ..         \\    = < \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout
    cout << "              \\ /_M''''M_      XM______  .  .     .\\ .      ____ .  , \\ D /   \\" << endl;
    cout << "               V         \\    M.       \\________:   \\     M /        <_\\ |     V" << endl;
    cout << "                          \\  /                \\ \\___ \\   /             \\||" << endl;
    cout << "                           \\/..     O .OOO.    \\    \\,| /               V" << endl;
    cout << "                          _/.  M,..  ? : . ..   \\    X||" << endl;
    cout << "                        ./      ?...       ..    \\    V" << endl;
    cout << "                        ( .       N______   N7.   |" << endl;
    cout << "                         X7  M .  /      \\___. . M| " << endl;
    cout << "                        ( O .. O |           \\M  . \\" << endl; // Ho aggiunto un altra " alla fine, altrimenti non finiva il cout (qua è a causa della parentesi)
    cout << "                         M._____..)           \\     | " << endl;
    cout << "                         \\|'''''|/             \\   ,|" << endl;
    cout << "                          \\!!!!!/               \\ . |" << endl;
    cout << "                                                 \\  |" << endl;
    cout << "                                            ^     )Z )" << endl;
    cout << "                                           | \\   /M /" << endl;
    cout << "                                           | .\\_/M /" << endl;
    cout << "                                            \\_____/" << endl; //disegno boss
    i=1;
    while (i <= att){
        cout << "   ";
        if (i == att) cout << "V" << endl;
        else cout << "     ";
        i++;
    }// la V indica il giocatore attuale
    Node* scorr = this->returnList()->Head();
    Player* q1 = &scorr -> player;
    for(i = 1; i <= nPlayers; i++){
        q1 = &scorr -> player;
        cout << "   " << scorr -> player.showId();
        if(i < nPlayers)cout<<"    ";
        scorr = scorr -> next;
    }//rappresenta gli ID dei giocatori
    cout<<endl;
    scorr = this->returnList()->Head();
    for(i = 1; i <= nPlayers; i++){
        q1 = &scorr -> player;
        if ((q1 -> life()) >= 100) cout << q1 -> life() << "/" << q1 -> maxHp(); //la salute massima è dinamica
        else cout << " " << q1 -> life() << "/" << q1 -> maxHp(); // metto uno spazio per rappresentare correttamente lo schema di battaglia
        if(i < nPlayers)cout<<" ";
        scorr = scorr -> next;
    } //rappresenta la salute dei giocatori, attuale e massima
    cout<<endl;
}
int finale::CalculateDamage(int Damage){  //ritorna 0 se sono entrambi vivi 1 se il mostro è morto 2 se tutti i giocatori sono morti (se muore uno faccio dequeue)
        int status=0;
        if (b!=NULL){
        if (att != (-1)) b->GotHit(Damage); // il boss subisce danni dal giocatore
        else{
            Node* scorr = this->returnList()->Head();
            Player *q1 = &scorr -> player;
            if ((k % 3) == 0) {
                att = q1 -> life();
                scelto = q1 -> showId(); //potrebbe essere il primo giocatore quello ad avere meno vita
                for (int i=0; i<nPlayers; i++){
                    q1 = &scorr -> player;
                    if ((q1 -> life()) < att) {
                        att = q1 -> life();
                        scelto = q1 -> showId();
                    } // ho trovato un giocatore che ha meno vita
                    scorr = scorr -> next; //va al nodo successivo
                    if (scorr == head) att = -1; //Sono ritornato alla testa? se sì, do a "att" il valore -1
                } //cerca il giocatore con meno vita
                att = (-1);
                scorr = this->returnList()->Head();
                while (att == (-1)){
                    q1 = &scorr -> player;
                    if ((q1 -> showId()) == scelto){
                        q1 -> lifeFix(scorr -> player.life()); // il boss usa l'attacco prendendo direttamente la salute attuale del giocatore, così, in ogni caso, la azzera sempre
                        if (scorr -> next == scorr) status = 2; //caso in cui ho un solo elemento
                        else {
                            cout << "IL GIOCATORE " << q1 ->showId() << " E' MORTO" << endl;
                            l -> dequeue (q1 -> showId());
                            nPlayers--;
                            p=this->returnList()->Head();
                            head = this -> returnList() ->Head();
                        }//caso in cui ho una lista di almeno 2 elementi, dove faccio dequeue e aggiorno i puntatori
                        att = 1;
                    }
                    scorr = scorr -> next; //va al nodo successivo
                }//attacca il giocatore con meno vita
                scelto = 0;
            }//attacco mortale
            else if ((k % 2) == 0){
                for (int i=0; i<nPlayers; i++){
                    q1 = &scorr -> player;
                    q1 -> lifeFix(b->speciale1()); // usa l'attacco che colpisce tutti i giocatori
                    if ((q1 -> life()) <= 0) {
                        if (scorr -> next == scorr) status = 2; //caso in cui ho un solo elemento
                        else {
                            cout << "IL GIOCATORE " << q1 ->showId() << " E' MORTO" << endl;
                            l -> dequeue (q1 -> showId());
                            nPlayers--;
                            p=this->returnList()->Head();
                            head = this -> returnList() ->Head();
                        }//caso in cui ho una lista di almeno 2 elementi, dove faccio dequeue e aggiorno i puntatori
                    }
                    scorr = scorr -> next; //va al nodo successivo
                    if (scorr == head) att = 1; //sono ritornato alla testa, il boss ha finito
                }
            } //ogni due turni usa l'attacco che colpisce tutti i giocatori
            else {
                srand(time(0));
                scelto = (rand() % nPlayers); //scelto indica il numero dei nodi che devo attraversare: se = 0, io attacco il giocatore del nodo in cui sono allo stato attuale, se = a un qualunque valore "i", io dovrò attraversare "i" nodi
                while (Damage == (-1)){
                    q1 = &scorr -> player;
                    if (scelto == 0){
                        q1 -> lifeFix(b->getDmg());// attacco standard
                        if ((q1 -> life()) <= 0) {
                            if (scorr -> next == scorr) status = 2; //caso in cui ho un solo elemento
                            else {
                                cout << "IL GIOCATORE " << q1 ->showId() << " E' MORTO" << endl;
                                l -> dequeue (q1 -> showId());
                                nPlayers--;
                                p=this->returnList()->Head();
                                head = this -> returnList() ->Head();
                            }//caso in cui ho una lista di almeno 2 elementi, dove faccio dequeue e aggiorno i puntatori
                        }
                        Damage = 1; //ho finito, posso uscire dal while
                    }//sono sul giocatore che devo attaccare
                    else scelto--; //ho attraversato un nodo
                    scorr = scorr -> next; //va al nodo successivo
                }
                scelto = 0;
            }//attacco standard

        } // stavolta è il boss che attacca
        if (b->LifePoints()<=0){
            delete b;
            b=NULL;
            status=1;
            } // il boss è morto
        }
        else status=1;


        return status;
}
