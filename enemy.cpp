//#include "stdafx.h"
#include "enemy.h"
#include "goblin.h"
#include "ogre.h"
#include "chimera.h"
#include "demonlord.h"

#include <iostream>//debugging

Enemy* Enemy::createSelectedMonster(int powerlvl) {
	using namespace std;

	/*FOR REFERENCE*/
	//20-74 = goblin, 75-94 = orgre, 95-99 = chimera, >=100 = demon lord

	if (powerlvl >= 20 && powerlvl <= 74) {
		return new Goblin();
	}
	else if (powerlvl >= 75 && powerlvl <= 94) {
		return new Ogre();
	}
	else if (powerlvl >= 95 && powerlvl <= 99) {
		return new Chimera();
	}
	else if (powerlvl >= 100){
		return new DemonLord();
	}
	cout << "Sorry, no monster with a matching value exists.";
	return new Enemy();

}

int Enemy::getMaxHp() {
	return maxhp;
}

int Enemy::getHp() {
	return hp;
}

int Enemy::getDmg() {
	return dmg;
}

int Enemy::getExp() {
	return exp;
}


int Enemy::takeDmg(int damage) {
	hp = hp - damage;
	if (hp <= 0) {
		stillalive = false;
	}
	return 0;
}

bool Enemy::checkIfAlive() {
	return stillalive;
}

std::string Enemy::getName() {
	return name;
}

std::string Enemy::getRace() {
	return race;
}