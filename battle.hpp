#ifndef BATTLE_HPP_
#define BATTLE_HPP_

#include "manageGame.hpp"
#include "player.hpp"
#include "monster.hpp"

class battle{
protected:
	Player *p;
	Manage *manage;
	Zombie *romero;
	Vampire *dracula;
	Spider *spiderman;
	char MonsterName[10];
	int potionHP;
public:
    battle(Player *p_curr, Manage *man);
	void battleManager();
	void getRandomMonster();
	int IOManager();
	int CalculateDamage(int Damage);
	void WinScreen();
	void LoseScreen();
	void HealthBar(int currenthpPlayer,int maxhpPlayer, int currenthpMonster,int maxhpMonster, int playerID);
};

#endif /* BATTLE_HPP_ */
