#include "monster.hpp"

monster::monster(){ //la classe monster è una classe fantoccio che ha metodi base utili a tutti i mostri, non viene mai usata direttamente
	name[0]='\0';
	MaxHp=0;
	Hp=MaxHp;
	damage=0;
}

Vampire::Vampire(){ //costruttore del vampiro
	strcpy(name,"Vampiro\0");
	MaxHp=40;
	Hp=MaxHp;
	damage=5;
}

Spider::Spider(){ //costruttore del ragno
	strcpy(name,"Ragno\0");
	MaxHp=25;
	Hp=MaxHp;
	damage=10;
}

Zombie::Zombie(){ //costruttore dello zombie
	strcpy(name,"Non-Morto\0");
	MaxHp=30;
	Hp=MaxHp;
	damage=8;
}

char* monster::GetName(){
	return name;
}

void monster::GotHit(int dmg){
	Hp=Hp-dmg;
}

int monster::getDmg(){
	return damage;
}

int monster::LifePoints(){ //restituisce hp del mostro, se è negativo restituisce 0, in modo che la healthbar non si rompa
	if (Hp>=0) return Hp;
	else return 0;
}

int monster::MaxLifePoints(){ //è una funzione che serve alla healthbar per calcolare la proporzione
	if (Hp>MaxHp) MaxHp=Hp;
	return MaxHp;
}

int Vampire::getDmg(){ //il vampiro ha un abilità speciale che gli permette di succhiare vita dal giocatore e aggiungerla a se stesso, fatta facendo danno normale più un incremento proporzionale a danno
	int dice=0;
	srand(time(0));
	dice = (rand()%100)+1;
	if (dice<=30){
		GotHit(-(damage));
		cout<<"Con un morso doloroso, il "<<name<<", ti succhia via del sangue, restituendogli parte della vita"<<" (+"<<damage<<")"<<endl;
	}
	return monster::getDmg(); //se l'abilità non si è attivata ritrono il danno del mostro
}

void Zombie::GotHit(int dmg){ //lo zombie ha la probabilità di dimezzare il danno ricevuto, è semplicemente un tiro di dado che dimezza la variabile passata col danno del oggetto
	int dice=0;
	srand(time(0));
	dice = (rand()%100)+1;
	if (dice<=30){
		Hp=Hp-(dmg/2);
		cout<<""<<endl;
		cout<<"Il tuo colpo ha avuto poca efficacia sul "<<name<<", capisci infatti di avergli fatto la metà del danno possibile"<< " (dmg "<<dmg/2<<")"<<endl;
	}
	else monster::GotHit(dmg); //se l'abilità non si è attivata faccio danno normale allo zombie
}


/* il ragno ha la probabilità di cancellare un oggetto a caso dal inventario del giocatore quando attacca, il tiro di dado determina lo slot, e si tenta di cancellare
 * l'oggetto nello slot (solo se lo slot è pieno); siccome la rand del c++ fa schifo, ho messo che se dopo 100 numeri casuali non ha beccato nemmeno un oggetto,
 * il ciclo si ferma e cancella semplicemente il primo oggetto non default del inventario. Prima di ciclare per tirare fuori numeri random infatti faccio un ciclo
 * per vedere se esistono oggetti non default e tengo conto del primo.
 */
int Spider::getDmg(Player* p1){
	int dice=0;
	bool hasobj=false; //se non ha oggetti non default il ragno non può cancellare nulla, ha oggetti se ne ha almeno 1
	int firsthit; //primo oggetto non default
	srand(time(0));
	dice = (rand()%100)+1;
	for (int i=1;i<5;i++){ //segno il primo oggetto beccato
		if (p1->showInventory()->slotIsFull(i)){
		hasobj=true; //segno che ha almeno 1 oggetto
		firsthit=i;
		}
	}
	if (dice<=45 && hasobj){
		int fermacpu=0;
		do {
			srand(time(0));
			dice = (rand()%4)+1;
			fermacpu++; //dopo 100 cicli di while inutili suppongo che il random continui con quel andamento,allora esco
		}while ((!(p1->showInventory()->slotIsFull(dice))) && fermacpu<=100);
		cout<<"Il " <<name<< ", con la sua lesta ragnatela, arpiona il tuo zaino e ti ruba un oggetto!";
		if (fermacpu<=100){
			cout<<" ("<< p1->showInventory()->getName(dice) << ")"<<endl;
			p1->showInventory()->deleteObject(dice); //cancello il primo oggetto
		}
		else {
			cout<<" ("<< p1->showInventory()->getName(firsthit) << ")"<<endl;
			p1->showInventory()->deleteObject(firsthit); //cancello l'oggetto trovato da random
		}
	}
	else return monster::getDmg(); //se l'abilità non si è attivata ritrono il danno del mostro
	return 0;
}




