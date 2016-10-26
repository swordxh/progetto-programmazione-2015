#include "battle.hpp"

battle::battle(Player *p_curr, Manage *man)
{
	p=p_curr;
    	manage=man;
	dracula=NULL;
	spiderman=NULL;
	romero=NULL;
	MonsterName[0]='\0';
	potionHP=45; //è quanti hp restituisce la pozione, è hardcoded nel costruttore
}

void battle::getRandomMonster(){ //aggiorna i puntatori null del costruttore ad uno dei vari mostri, effettivamente spawna 1 solo mostro a round
	int dice=0;
	srand(time(0));
	dice = (rand()%150)+1;
	if (dice <=35){
		dracula = new Vampire();
		strcpy(MonsterName, dracula->GetName());
	}
	else if (dice<=70){
		romero = new Zombie();
		strcpy(MonsterName, romero->GetName());
	}
	else {
		spiderman = new Spider();
		strcpy(MonsterName, spiderman->GetName());
	}
}

/* questo metodo gestisce la logica della battaglia principale, come una sorta di main diciamo, chiama il mostro random e poi chiama le funzioni di stampa healthbar
 * e calcolo danno, entrambe in un ciclo per simulare i turni d'attacco, quando il giocatore o il muore, termina chiamando vittoria oppure sconfitta
 */
void battle::battleManager(){
	if ((dracula==NULL) && (romero==NULL) && (spiderman==NULL)) getRandomMonster();
	int stato=0;
	cout<<"Dentro la stanza senti un respiro cupo, nell oscurità riesci a vedere due occhi lucenti, ti accorgi cosi di non esser solo..."<<endl;
	cout<<endl<<"Il "<<MonsterName<<" ti attacca, inizi cosi a difenderti."<<endl;
	while (stato==0){
			if (dracula!=NULL){
				HealthBar(p->life(), p->maxHp(), dracula->LifePoints(), dracula->MaxLifePoints(),p->showId());
			}
			else if (romero!=NULL){
				HealthBar(p->life(), p->maxHp(), romero->LifePoints(), romero->MaxLifePoints(),p->showId());
			}
			else if (spiderman!=NULL){
				HealthBar(p->life(), p->maxHp(), spiderman->LifePoints(), spiderman->MaxLifePoints(),p->showId());
			}
			stato=CalculateDamage(IOManager()); //questa è la funzione che calcola il danno del mostro e del giocatore, prende in input un altra funzione che chiede quale oggetto si vuole scegliere
			cout<<"----------------------------------------------------------------------------------------------"<<endl<<endl;
		}
		if (dracula!=NULL){
			HealthBar(p->life(), p->maxHp(), dracula->LifePoints(), dracula->MaxLifePoints(),p->showId());
		}
		else if (romero!=NULL){
			HealthBar(p->life(), p->maxHp(), romero->LifePoints(), romero->MaxLifePoints(),p->showId());
		}
		else if(spiderman!=NULL){
			HealthBar(p->life(), p->maxHp(), spiderman->LifePoints(), spiderman->MaxLifePoints(),p->showId());
		}
	if (stato==1){
		WinScreen();
	}
	if (stato==2){
		LoseScreen();
	}
}
int battle::IOManager(){ //ritorna il danno del oggetto che si è scelto
	cout<<endl;
	cout<<"Scegli l'oggetto che vuoi usare per colpire il "<<MonsterName<<":"<<endl;
	int select=1;
	for (int i=0; i<5; i++){  //stampa tutto l'inventario del giocatore
		if (p->showInventory()->slotIsFull(i)){
			cout<<select<<") "<< p->showInventory()->getName(i)<< "(dmg "<<p->showInventory()->AccessObjectFromInventory(i)<<")"<<endl;
			select++;
		}
	}
	select--;
	int counter=select;
	do{ //praticamente serve a gestire i casi in cui l'inventario non è contiguo, in questo caso la scelta numerica da tastiera prende il primo,secondo,ecc oggetto esistente in base al num in input
		select=manage->sanitycheck();
		if ((select<1) || (select>counter)) cout<<"Devi selezionare un oggetto valido!"<<endl;
	}while((select<1) || (select>counter));
	counter=1;
	bool exit=false;
	int i=0;
	bool ispotion=false;
	while (!exit){
		if ((p->showInventory()->slotIsFull(i)) && (select==counter)){
			if (p->showInventory()->AccessObjectFromInventory(i)==0){ //la pozione ha come convenzione 0 di danno, qui viene gestita l'aumento della salute del pg
				p->lifeFix(-potionHP);
				cout<<"usi la Pozione che ti restituisce "<<potionHP<<" HP!"<<endl;
				p->showInventory()->deleteObject(i);
				ispotion=true;
			}
			exit=true;
		}
		else if (p->showInventory()->slotIsFull(i)) counter++;
		i++;
	}
	i--;
	if(!ispotion) return p->showInventory()->AccessObjectFromInventory(i);
    	else return 0;
}
void battle::WinScreen(){ //quando si vince stampa un messaggio e chiama il drop oggetto
	cout<<"			CONGRATULAZIONI HAI BATTUTO IL "<<MonsterName<<endl;
    manage->dropObject(p);
}
void battle::LoseScreen(){ //stampa il messaggio di morte, volevo usarla per chiamare il metodo di morte player ma è stato gestito direttamente dalla lista pg
	cout<<"			SEI MORTO"<<endl;
}
void battle::HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID){ //usa la vita max dei pg e del mostro per fare una semplice proporzione, usata per calcolare in numero di barrette della vita
	cout<<"Player "<<playerID<<"                              "<<MonsterName<<endl;
	cout<<" ____________________"<<"                 "<<" ____________________"<<endl;
	cout<<'|';
	int i=1;
	while(i<=20){ //stampa le barrette vita
		if(((20*currenthpPlayer)/maxhpPlayer)>=i)cout<<"█";
		else cout<<' ';
		i++;
	}
	cout<<"|                |";
	i=1;
	while(i<=20){
		if(((20*currenthpMonster)/maxhpMonster)>=i)cout<<"█";
		else cout<<' ';
		i++;
	}
	cout<<'|'<<endl;
	cout<<" --------------------"<<"                 "<<" --------------------"<<endl;
	cout<<"      "<<currenthpPlayer<<"/"<<maxhpPlayer<<"                                "<<currenthpMonster<<"/"<<maxhpMonster<<endl;
}


/* ritorna 0 se sono entrambi vivi, 1 se il mostro è morto, 2 se il giocatore è morto, il danno viene calcolato allo stesso momento quindi può succedere che mostro e giocatore
 * si uccidano a vicenda; la morte del giocatore ha priorità su tutto infatti viene controllata alla fine, quando un mostro muore il suo oggetto viene cancellato dalla mem.
 * il ritorno 0 (entrambi vivi) serve per far ciclare la funzione che gestisce i "turni" di battaglia, che sa in quel caso che il combattimento è ancora in corso.
 */
int battle::CalculateDamage(int Damage){
	int status=0;
	int beforebattle=p->life();
		if (dracula!=NULL){
			p->lifeFix(dracula->getDmg());
			dracula->GotHit(Damage);
			cout<<"fai "<<Damage<<" di danno al "<<dracula->GetName()<<" e ne subisci "<<beforebattle-(p->life())<<endl<<endl;
			if (dracula->LifePoints()<=0){
				delete dracula;
				dracula=NULL;
				status=1;
			}
		}
		else if (spiderman!=NULL){
			p->lifeFix(spiderman->getDmg(p));
			spiderman->GotHit(Damage);
			cout<<"fai "<<Damage<<" di danno al "<<spiderman->GetName()<<" e ne subisci "<<beforebattle-(p->life())<<endl<<endl;
			if (spiderman->LifePoints()<=0){
				delete spiderman;
				spiderman=NULL;
				status=1;
			}
		}
		else if(romero!=NULL){
			p->lifeFix(romero->getDmg());
			romero->GotHit(Damage);
			cout<<"fai "<<Damage<<" di danno al "<<romero->GetName()<<" e ne subisci "<<beforebattle-(p->life())<<endl<<endl;
			if (romero->LifePoints()<=0){
				delete romero;
				romero=NULL;
				status=1;
			}
		}
	if (p->life()<=0) status=2; //se il giocatore ha meno di 1 hp non importa se abbia ucciso il mostro, la funzione restituisce la sua morte
	return status;
}
