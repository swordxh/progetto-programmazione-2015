#include "battle.hpp"

battle::battle(Player *p_curr, Manage *man)
{
	p=p_curr;
    manage=man;
	dracula=NULL;
	spiderman=NULL;
	romero=NULL;
	MonsterName[0]='\0';
}
void battle::getRandomMonster(){
	int dice=0;
	srand(time(0));
	dice = (rand()%100)+1;
	if (dice <=50){
		dracula = new Vampire();
		strcpy(MonsterName, dracula->GetName());
	}
	else if (dice<=80){
		romero = new Zombie();
		strcpy(MonsterName, romero->GetName());
	}
	else {
		spiderman = new Spider();
		strcpy(MonsterName, spiderman->GetName());
	}
}
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
			stato=CalculateDamage(IOManager());
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
	for (int i=0; i<5; i++){
		if (p->showInventory()->slotIsFull(i)){
			cout<<select<<") "<< p->showInventory()->getName(i)<< "(dmg "<<p->showInventory()->AccessObjectFromInventory(i)<<")"<<endl;
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
	while (!exit){
		if ((p->showInventory()->slotIsFull(i)) && (select==counter)){
			if (p->showInventory()->AccessObjectFromInventory(i)==0){
				p->lifeFix(-potionHP);
				cout<<"usi la Pozione che ti restituisce "<<potionHP<<" HP!"<<endl;
				p->showInventory()->deleteObject(i);
			}
			exit=true;
		}
		else if (p->showInventory()->slotIsFull(i)) counter++;
		i++;
	}
	i--;
	return p->showInventory()->AccessObjectFromInventory(i);
}
void battle::WinScreen(){
	cout<<"			CONGRATULAZIONI HAI BATTUTO IL "<<MonsterName<<endl;
    manage->dropObject(p);
}
void battle::LoseScreen(){
	cout<<"			SEI MORTO"<<endl;
}
void battle::HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID){ //20 barrette
	cout<<"Player "<<playerID<<"                              "<<MonsterName<<endl;
	cout<<" ____________________"<<"                 "<<" ____________________"<<endl;
	cout<<'|';
	int i=1;
	while(i<=20){
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
int battle::CalculateDamage(int Damage){  //ritorna 0 se sono entrambi vivi 1 se il mostro è morto 2 se il giocatore è morto
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
	if (p->life()<=0) status=2;
	return status;
}
