/*
 * monster.cpp
 *
 *  Created on: 26 Sep 2016
 *      Author: swordxh
 */
#include "monster.hpp"

monster::monster(){
	name[0]='\0';
	MaxHp=0;
	Hp=MaxHp;
	damage=0;
}

Vampire::Vampire(){
	strcpy(name,"Vampiro\0");
	MaxHp=40;
	Hp=MaxHp;
	damage=5;
}

Spider::Spider(){
	strcpy(name,"Ragno\0");
	MaxHp=25;
	Hp=MaxHp;
	damage=15;
}

Zombie::Zombie(){
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

int monster::LifePoints(){
	if (Hp>=0) return Hp;
	else return 0;
}

int monster::MaxLifePoints(){
	if (Hp>MaxHp) MaxHp=Hp;
	return MaxHp;
}

int Vampire::getDmg(){
	int dice=0;
	srand(time(0));
	dice = (rand()%100)+1;
	if (dice<=30){
		GotHit(-(damage));
		cout<<"Con un morso doloroso, il "<<name<<", ti succhia via del sangue, restituendogli parte della vita"<<" (+"<<damage<<")"<<endl;
	}
	return monster::getDmg();
}

void Zombie::GotHit(int dmg){
	int dice=0;
	srand(time(0));
	dice = (rand()%100)+1;
	if (dice<=30){
		Hp=Hp-(dmg/2);
		cout<<""<<endl;
		cout<<"Il tuo colpo ha avuto poca efficacia sul "<<name<<", capisci infatti di avergli fatto la metà del danno possibile"<< " (dmg "<<dmg/2<<")"<<endl;
	}
	else monster::GotHit(dmg);
}

int Spider::getDmg(Player* p1){
	int dice=0;
	bool hasobj=false;
	int firsthit;
	srand(time(0));
	dice = (rand()%100)+1;
	if (dice<=45){
		for (int i=1;i<5;i++){
			if (p1->showInventory()->slotIsFull(i)){
			hasobj=true;
			firsthit=i;
			}
		}
		if (hasobj){
			int fermacpu=0;
			do {
				srand(time(0));
				dice = (rand()%4)+1;
				fermacpu++;
			}while ((!(p1->showInventory()->slotIsFull(dice))) && fermacpu<=100);
			cout<<"Il " <<name<< ", con la sua lesta ragnatela, arpiona il tuo zaino e ti ruba un oggetto!";
			if (fermacpu<=100){
				cout<<" ("<< p1->showInventory()->getName(dice) << ")"<<endl;
				p1->showInventory()->deleteObject(dice);
			}
			else {
				cout<<" ("<< p1->showInventory()->getName(firsthit) << ")"<<endl;
				p1->showInventory()->deleteObject(firsthit);
			}
		}
	}
	else return monster::getDmg();
	return 0;
}




