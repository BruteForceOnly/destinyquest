//#include "stdafx.h"
#include "hero.h"

#include <iostream> // rite now it's only for debugging, maybe remove later

Hero::Hero() {

	xPos = 0;
	yPos = 0;

	lvl		= 1;
	maxhp	= 30;
	hp		= maxhp;
	dmg		= 4;

	totalexp = 0;

	heroIsAlive = true;

}


int Hero::getxPosition() {
	return xPos;
}

int Hero::getyPosition(){
	return yPos;
}


int Hero::getLvl() {
	return lvl;
}

int Hero::getMaxHp() {
	return maxhp;
}

int Hero::getHp() {
	return hp;
}

int Hero::getDmg() {
	return dmg;
}

int Hero::getTotalExp() {
	return totalexp;
}

int Hero::move(char direction) {
	if (direction == 'w' || direction == 'W') {
		yPos++;
		return 0;
	}
	else if (direction == 'a' || direction == 'A') {
		xPos--;
		return 0;
	}
	else if (direction == 's' || direction == 'S') {
		yPos--;
		return 0;
	}
	else if (direction == 'd' || direction == 'D') {
		xPos++;
		return 0;
	}

	return 1;
}

int Hero::takeDmg(int damage) {
	hp = hp - damage;
	if (hp <= 0) {
		heroIsAlive = false;
	}
	return 0;
}

bool Hero::checkIfAlive() {
	return heroIsAlive;
}

int Hero::resetHero() {

	xPos = 0;
	yPos = 0;

	lvl = 1;
	maxhp = 30;
	hp = maxhp;
	dmg = 4;

	totalexp = 0;

	heroIsAlive = true;

	return 0;

}

int Hero::gainExp(int food) {
	using namespace std;
	cout << "+EXP " << food << endl;

	totalexp += food;
	return 0;
}

int Hero::checkHowManyLvlUp(int currentlvl, int currentexp) {
	using namespace std;

	int numtimestolvlup(0);

	//cout << "I am currently level: " << lvl << endl;
	//cout << "I need " << howMuchExpDoINeed(lvl) << "EXP to level up.\n";
	//cout << "Currently I have " << totalexp << endl;

	//check if you have enough exp for the next lvl
	int targetlvl = currentlvl;
	while(currentexp >= howMuchExpDoINeed(targetlvl)) {
		numtimestolvlup++;
		targetlvl++;

	}

	return numtimestolvlup;
}

int Hero::howMuchExpDoINeed(int level) {
	if (level <= 0) {
		return 0;
	}
	if (level == 1) {
		return (level * EXP_NUM);
	}
	else return (level * EXP_NUM) + (howMuchExpDoINeed(level-1));
}

int Hero::lvlUp(int thismanytimes) {
	using namespace std;

	if (thismanytimes <= 0) {
		return 0;
	}

	lvl		+= thismanytimes;
	maxhp	+= thismanytimes * HP_GAIN_ON_LVLUP;
	dmg		+= thismanytimes * DMG_GAIN_ON_LVLUP;

	hp = maxhp;

	for (int k = 0; k < thismanytimes; k++) {
		cout << "Level Up! +" << HP_GAIN_ON_LVLUP <<
			"HP +" << DMG_GAIN_ON_LVLUP << "DMG\n";
	}

	return 0;
}