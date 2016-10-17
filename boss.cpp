#include "boss.hpp"
using namespace std;

boss::boss(){
	strcpy(name,"Drago\0"); // nome
	MaxHp= (n * 100) * z; // "n" = numero giocatori, "z" = fattore che moltiplica vita
	Hp=MaxHp;
	damagest = 20; // attacco standard
	damage1 = 10; // attacco che colpisce tutti i giocatori
	damage2 = 100; // attacco mortale
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
int boss::speciale2(){
	return damage2;
} // il boss usa l'attacco mortale
finale::finale(Player *p_curr){
    p = p_curr; // prende il giocatore dalla lista (DA IMPLEMENTARE)
	b = NULL;
	MonsterName[0]='\0';
	k = 1; // Iniziano i turni
}
void finale::battleManager(){
    if (b == NULL) {
        b = new boss();
        strcpy(MonsterName, b->GetName());
    }// inizializzo il boss
	int stato=0; // Inizia la battaglia
	cout<<"... La situazione e' fin troppo tranquilla..." << endl;
	cout << "Nessun nemico..." << endl;
	cout << "Nessun sinistro rumore di passi..." << endl;
	cout << "Come se tutto cio' fosse la quiete prima della tempesta..." <<endl;
	cout<<endl<<endl<<endl<<"Il "<<MonsterName<<" ti attacca, inizi cosi a difenderti."<<endl;
	while (stato==0){
		if (b!=NULL){
			HealthBar(p->life(), 100, b->LifePoints(), b->MaxLifePoints(),p->showId()); // gli do gli HP attuali\massimi dei giocatori e del boss, aggiungendo l'ID del giocatore
		} // se il boss � vivo, vado in HealthBar
		stato=CalculateDamage(IOManager());
	}// finch� "stato" = 0 (ovvero i giocatori e il boss sono vivi) io sto dentro il while
	if (b!=NULL){
				HealthBar(p->life(), 100, b->LifePoints(), b->MaxLifePoints(),p->showId());
			}// in questo caso i giocatori sono morti (sono fuori dal while)
	if (stato==1){
		WinScreen(MonsterName); // vittoria
	}
	if (stato==2){
		LoseScreen(); // game over
	}
}
int finale::IOManager(){ //ritorna il danno del oggetto che si � scelto
	cout<<endl;
	cout<<"Scegli l'oggetto che vuoi usare per colpire il "<<MonsterName<<":";
	int select=1; // select elenca gli oggetti selezionabili
	for (int i=0; i<5; i++){
		if (p->showInventory()->slotIsFull(i)){
			cout<<select<<") "<< p->showInventory()->getName(i)<< "(dmg "<<p->showInventory()->AccessObjectFromInventory(i)<<")"<<endl;
			select++;
		} //lo slot non deve essere vuoto
	}
	int counter=select; // counter indica l'oggetto col select pi� alto (in poche parole, l'ultimo)
	do{
	cin>>select;
	}while((select<1) || (select>counter)); // seleziono un oggetto, il valore deve essere compreso tra 1 e counter
	counter=1; //
	bool exit=false; //exit � una guardia del while
	int i=0;
	while (!exit){
		if ((p->showInventory()->slotIsFull(i)) && (select==counter)){
			if (p->showInventory()->AccessObjectFromInventory(i)==0){
				p->lifeFix(-20);
				p->showInventory()->deleteObject(i);
			}// caso della pozione: a differenza degli altri oggetti (armi), questo viene eliminato, dando 20 HP al giocatore (la pozione ha il campo damage = 0)
			exit=true; //posso uscire dal while, ho usato l'oggetto
		}// se l'oggetto � quello selezionato, lo uso
		else if (p->showInventory()->slotIsFull(i)) counter++;
		i++;
	}
	return p->showInventory()->AccessObjectFromInventory(i--);
}
void finale::WinScreen(char MonsterName[]){
	cout<<"					CONGRATULAZIONI HAI BATTUTO IL "<<MonsterName<<endl;
}
void finale::LoseScreen(){
	cout<<"					SEI MORTO"<<endl;
}
void finale::HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID){ //20 barrette
	cout << "                                     " << MonsterName << endl;
	cout<<'(';
	int i=1;
	while(i<=78){
		if(((78*currenthpMonster)/maxhpMonster)>=i)cout<<"|";
		else cout<<' ';
		i++;
	} // calcola le | in base agli HP attuali tramite una percentuale
	cout<<')' << endl; // le parentesi le ho messe solo per delimitare la barra della salute
	//disegno drago (DA FARE)
	i=1;
	while (i <= att){
        cout << "   ";
        if (i == att) cout << "V" << endl;
        else cout << "     ";
        i++;
	}// la V indica il giocatore attuale
	i = 1;
	while(i <= n){
        cout << "   " << p -> showId();
		if(i < n)cout<<"    ";
		i++;
	}
	cout<<endl;
	i = 1;
	while(i <= n){
        cout << p -> life() << "/100";
		if(i < n)cout<<" ";
		i++;
	}
	cout<<endl;
}
int finale::CalculateDamage(int Damage){  //ritorna 0 se sono entrambi vivi 1 se il mostro � morto 2 se il giocatore � morto
	int status=0;
	if (b!=NULL){
        if ((k % 2) == 0) p->lifeFix(b->speciale1()); // ogni due turni usa l'attacco che colpisce tutti i giocatori (DEVO AVERE LA LISTA PER SCORRERLA)
        else if ((k % 3) == 0) p->lifeFix(b->speciale2()); // ogni tre turni usa l'attacco mortale (DEVO AVERE LA LISTA PER ACCEDERE AL GIOCATORE CON MENO VITA)
		else p->lifeFix(b->getDmg());// attacco standard (DEVO AVERE LA LISTA PER ATTACCARE UN QUALSIASI GIOCATORE)
		b->GotHit(Damage); // il boss subisce danni dal giocatore (DEVO AVERE LA LISTA PER PERMETTERE L'ATTACCO A TUTTI I GIOCATORI)
		if (b->LifePoints()<=0){
			delete b;
			b=NULL;
			status=1;
		} // il boss � morto
	}
	if (p->life()<=0) status=2; // morte di 1 o pi� giocatori (DEVO AVERE LA LISTA PER CONTROLLARE LA SALUTE DI TUTTI I GIOCATORI)
	// L'ISTRUZIONE E' DA COMPLETARE: devo distinguere l'eliminazione di uno o pi� giocatori e il game over (morte di tutti i giocatori)
    k++; // turno finito, passo al successivo
	return status;
}
