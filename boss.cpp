#include "boss.hpp"
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

finale::finale(Queue *p_curr, int n){
    l = p_curr;
    head = NULL; //prendono la lista
	b = NULL;
	MonsterName[0]='\0';
	k = 1; // Iniziano i turni
	att = 1; // inizio dal primo giocatore
	m = 0;
	scelto = 0;
	p = NULL; // inizio dalla testa
	q = NULL;
	database=NULL;
	Node* scorr = head;; //con scorr vedo l'id più alto, così assegno n
	nPlayers = n;
	delete scorr;
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
	p = this -> returnList() -> returnHead(); // mi metto nella testa della lista
	while (stato==0){
        p=this->returnList()->returnHead();
        for(int j = 0; j < nPlayers; j++){
            q = &p -> player;
            if (b!=NULL){
                HealthBar(q->life(), q->maxHp(), b->LifePoints(), b->MaxLifePoints(), q->showId()); // gli do gli HP attuali\massimi dei giocatori e del boss, aggiungendo l'ID del giocatore
            } // se il boss è vivo, vado in HealthBar
            stato=CalculateDamage(IOManager());
            p = p -> next; //vado al giocatore successivo
            if (p == head) att = -1; //Sono ritornato alla testa? se sì, do a "att" il valore -1
            else att++; //non sono ritornato alla testa, ho trovato il giocatore successivo
        } // attaccano i giocatori
		stato=CalculateDamage(att); //attacca il boss
		att = 1; // così permetto ai giocatori di attaccare nel turno successivo
        k++; // turno finito, passo a quello successivo
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
	for (int m = 0; m < 5; m++){
		if (p->player.showInventory()->slotIsFull(m)){
			cout<<select<<") "<< p->player.showInventory()->getName(m)<< "(dmg "<<p->player.showInventory()->AccessObjectFromInventory(m)<<")"<<endl;
			select++;
		}
	}
	select--;
	int counter=select;
	do{
		cin>>select;
		if ((select<1) || (select>counter)) cout<<"Devi selezionare un oggetto valido!"<<endl;
	}while((select<1) || (select>counter));
	counter=1;
	bool exit=false;
	int i=0;
	bool ispotion=false;
	while (!exit){
		if ((p->player.showInventory()->slotIsFull(i)) && (select==counter)){
			if (p->player.showInventory()->AccessObjectFromInventory(i)==0){
				p->player.lifeFix(-potionHP);
				cout<<"usi la Pozione che ti restituisce "<<potionHP<<" HP!"<<endl;
				p->player.showInventory()->deleteObject(i);
				ispotion=true;
			}
			exit=true;
		}
		else if (p->player.showInventory()->slotIsFull(i)) counter++;
		i++;
	}
	i--;
	if(!ispotion) return p->player.showInventory()->AccessObjectFromInventory(i);
    	else return 0;
}
void finale::WinScreen(char MonsterName[]){
	cout<<"					CONGRATULAZIONI HAI BATTUTO IL "<<MonsterName<<endl;
}
void finale::LoseScreen(){
	cout<<"					SEI MORTO"<<endl;
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
    }// calcola le | in base agli HP attuali tramite una percentuale
    cout<<'|' << endl<<" "; // le parentesi le ho messe solo per delimitare la barra della salute
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
    cout << "                                            \\_____/" << endl;
	i=1;
	while (i <= att){
        cout << "   ";
        if (i == att) cout << "V" << endl;
        else cout << "     ";
        i++;
	}// la V indica il giocatore attuale
	Node* scorr = this->returnList()->returnHead();
	Player* q1 = &scorr -> player;
	for(i = 1; i <= nPlayers; i++){
        q1 = &scorr -> player;
        cout << "   " << scorr -> player.showId();
		if(i < nPlayers)cout<<"    ";
		scorr = scorr -> next;
	}
	cout<<endl;
	scorr = this->returnList()->returnHead();
	for(i = 1; i <= nPlayers; i++){
        q1 = &scorr -> player;
        if ((q1 -> life()) >= 100) cout << q1 -> life() << "/100";
        else cout << " " << q1 -> life() << "/100";
		if(i < nPlayers)cout<<" ";
        scorr = scorr -> next;
	}
	cout<<endl;
	delete scorr;
	delete q1;
}
int finale::CalculateDamage(int Damage){  //ritorna 0 se sono entrambi vivi 1 se il mostro è morto 2 se il giocatore è morto
	int status=0;
	if (b!=NULL){
        if (att != (-1)) b->GotHit(Damage); // il boss subisce danni dal giocatore
        else{
            Node* scorr = this->returnList()->returnHead();
            Player *q1 = &scorr -> player;
            if ((k % 2) == 0){
                for (int i=1; i<=nPlayers; i++){
                    q1 = &scorr -> player;
                    q1 -> lifeFix(b->speciale1()); // usa l'attacco che colpisce tutti i giocatori
                    scorr = scorr -> next; //va al nodo successivo
                    if (scorr == head) att = 1; //sono ritornato alla testa, il boss ha finito
                }
            } //ogni due turni usa l'attacco che colpisce tutti i giocatori
            else if ((k % 3) == 0) {
                    att = q1 -> life();
                    scelto = q1 -> showId(); //potrebbe essere il primo giocatore quello ad avere meno vita
                    for (int i=1; i<=nPlayers; i++){
                        q1 = &scorr -> player;
                        if ((q1 -> life()) < att) {
                                att = q1 -> life();
                                scelto = q1 -> showId();
                        } // ho trovato un giocatore che ha meno vita
                        scorr = scorr -> next; //va al nodo successivo
                        if (scorr == head) att = -1; //Sono ritornato alla testa? se sì, do a "att" il valore -1
                    } //cerca il giocatore con meno vita
                    att = (-1);
                    scorr = this->returnList()->returnHead();
                    while (att == (-1)){
                        q1 = &scorr -> player;
                        if ((q1 -> showId()) == scelto){
                            q1 -> lifeFix(scorr -> player.life()); // ogni tre turni usa l'attacco mortale
                            att = 1;
                        }
                        scorr = scorr -> next; //va al nodo successivo
                    }
                    scelto = 0;
            }
            else {
                    srand(time(0));
                    scelto = (rand() % nPlayers) + 1; //sceglie casualmente uno degli "n" giocatori della lista
                    while (att == (-1)){
                        q1 = &scorr -> player;
                        if ((q1 -> showId()) == scelto){
                            q1 -> lifeFix(b->getDmg());// attacco standard
                            att = 1;
                        }
                        scorr = scorr -> next; //va al nodo successivo
                    }
                    scelto = 0;
            }
            delete scorr;
            delete q1;
        } // stavolta è il boss che attacca
		if (b->LifePoints()<=0){
			delete b;
			b=NULL;
			status=1;
		} // il boss è morto
	}
	if (p->player.life()<=0) status=2; // morte di 1 o più giocatori (DEVO AVERE LA LISTA PER CONTROLLARE LA SALUTE DI TUTTI I GIOCATORI)
	// L'ISTRUZIONE E' DA COMPLETARE: devo distinguere l'eliminazione di uno o più giocatori e il game over (morte di tutti i giocatori)
	return status;
}
