#ifndef HERO_H
#define HERO_H

class Hero {
	int xPos;
	int yPos;

	int lvl;
	int maxhp;
	int hp;
	int dmg;

	//let's say you need x*(your current lvl) exp to level up...
	const static int EXP_NUM = 5; //and this is "x"
	const static int HP_GAIN_ON_LVLUP = 8;
	const static int DMG_GAIN_ON_LVLUP = 3;

	int howMuchExpDoINeed(int level);
	int totalexp;
	
	bool heroIsAlive;

public:
	Hero();
	int getxPosition();
	int getyPosition();
	
	int getLvl();
	int getMaxHp();
	int getHp();
	int getDmg();
	int getTotalExp();

	int move(char direction);
	int takeDmg(int damage);
	bool checkIfAlive();

	int gainExp(int food);
	int checkHowManyLvlUp(int currentlvl, int currentexp);
	int lvlUp(int thismanytimes);


	int resetHero();
};



#endif
