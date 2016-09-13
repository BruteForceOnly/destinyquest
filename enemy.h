#ifndef ENEMY_H
#define ENEMY_H
#include <string>

class Enemy{
protected:
	std::string name;
	std::string race;

	int maxhp;
	int hp;
	int dmg;
	int exp;

	bool stillalive;

public:
	//the powerlvl is same as random bad luck value determined in main
	static Enemy* createSelectedMonster(int powerlvl);
	int getMaxHp();
	int getHp();
	int getDmg();
	int getExp();

	std::string getName();
	std::string getRace();

	int takeDmg(int damage);
	bool checkIfAlive();
};


#endif
