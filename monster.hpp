#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "player.hpp"

using namespace std;

class monster{
protected:
	int MaxHp;
	int Hp;
	char name[10];
	int damage;

public:
	monster();
	char* GetName();
	int getDmg();
	void GotHit(int dmg);
	int LifePoints();
	int MaxLifePoints();

};

class Vampire:public monster{
public:
	Vampire();
	int getDmg();
};

class Zombie:public monster{
public:
	Zombie();
	void GotHit(int dmg);
};

class Spider:public monster{
public:
	Spider();
	int getDmg(Player* p1);
};


#endif /* MONSTER_HPP_ */
