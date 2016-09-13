// destinyquest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "hero.h"
#include "enemy.h"



int random(int min, int max)
{
	return ((static_cast<double>(std::rand()) / RAND_MAX) * (max - min + 1)) + min;
}

int printStartOrEndSection() {
	using namespace std;
	cout << "--------------------------------------\n";
	return 0;
}

int printStartOrEndEventSection() {
	using namespace std;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	return 0;
}

int printPosition(Hero hiro) {
	using namespace std;
	printStartOrEndSection();
	cout << "Current Position: (" << hiro.getxPosition() << "," << hiro.getyPosition() << ")\n";
	printStartOrEndSection();
	return 0;
}

int printStatus(Hero hiro) {
	using namespace std;
	cout << "Hero: LVL(" << hiro.getLvl() << ") HP(" << hiro.getHp() << "/" << hiro.getMaxHp() <<
		") DMG(" << hiro.getDmg() << ")\n";
	return 0;
}

int printMoveOptions() {
	using namespace std;
	cout <<	"\n\t(W) North\n" << "\t(A) West\n" << "\t(S) South\n" << "\t(D) East\n";
	cout << "\nChoose a direction to move in: ";
	return 0;
}

bool checkValidMove(char inputs[], int length, char checkthis) {
	for (int k = 0; k < length; k++) {
		if (checkthis == inputs[k]) {
			return true;
		}
	}
	return false;
}

int movePlayer(Hero &hiro, char direction) {
	hiro.move(direction);
	return 0;
}

int playerExploreMove(Hero &hiro) {
	using namespace std;
	char movedir(90);
	bool firsttime(true);

	char validChars[] = {'w', 'W', 'a', 'A', 's', 'S', 'd', 'D'};
	bool goodMove(false);

	//check that the move is valid, keep asking if it's not
	while (!goodMove) {
		if (!firsttime) {
			cout << "(Is it THAT HARD to type ONE letter?)\n";
		}
		printMoveOptions();
		cin >> movedir;

		goodMove = checkValidMove(validChars, 8, movedir);
		firsttime = false;
	}

	//update the hero's position
	movePlayer(hiro, movedir);

	return 0;
}

//this is for the monster spawning roll
int rollDie(Hero hiro) {
	using namespace std;

	//the higher the number, the stronger the monster
	//1-9 is nothing, 10-19 is bad luck, 20-59 = goblin, 60-89 = orgre, 90-99 = chimera, >100 = demon lord
	//to justify this...clearly weaker monsters will run away as you get stronger!
	int badLuck = hiro.getLvl() + random(0, 99);
	return badLuck;
}

int peacefulDay(int badluck) {
	using namespace std;
	printStartOrEndEventSection();
	if (badluck > 0 && badluck <= 9) {
		cout << "Just enjoying a peaceful day...\n";
	}
	else if (badluck >= 10 && badluck <= 19) {
		cout << "You stepped in shit.\n";
	
	}
	else cout << "Value entered was not within range\n";

	printStartOrEndEventSection();
	return 0;
}

Enemy* encounter(int badlucklvl) {

	Enemy* deliciousEXP;
	deliciousEXP = Enemy::createSelectedMonster(badlucklvl);

	
	return deliciousEXP;
}

int monsterAlert(Enemy* monster) {
	using namespace std;
	printStartOrEndEventSection();
	cout << "A wild " << monster->getRace() << " has appeared! (arawaremashita)\n";
	printStartOrEndEventSection();
	return 0;
}

int printCombatOptions() {
	using namespace std;
	cout << "\n\t(E) Attack" << "\n\t(R) Run\n";
	cout << "\nWhat will you do: ";
	return 0;
}

//true if you escape, false if you fail
bool tryToEscape() {
	using namespace std;

	bool success;

	int myluck = random(0, 1);
	if (myluck == 0) {
		success = false;
		cout << "you can't escape\n";
	}
	else if (myluck == 1) {
		success = true;
		cout << "running-like-a-coward was successful\n";
	}
	//default bad luck on failure
	else success = false;

	return success;
}

int printMonsterStatus(Enemy* monster) {
	using namespace std;
	cout << monster->getRace() <<": Name[" << monster->getName() << "] HP[" << monster->getHp() << 
		"/" << monster->getMaxHp() <<"] DMG[" << monster->getDmg() << "]\n";
	return 0;
}

int printHeroCombatLog(Hero hiro, Enemy* monster) {
	using namespace std;
	cout << "Hero hits " << monster->getName() << " for " << hiro.getDmg() << " damage!\n";
	return 0;
}

int printMonsterCombatLog(Enemy* monster) {
	using namespace std;
	cout << monster->getName() << " hits Hero for " << monster->getDmg() << " damage!\n";
	printStartOrEndSection();
	return 0;
}

int playerCombatMove(Hero &hiro, Enemy* &monster, bool &incombat, bool &playerDead, bool &monsterDead) {
	using namespace std;


	printPosition(hiro);
	printStatus(hiro);
	printMonsterStatus(monster);

	//initialize as undefined move so that loop will continue
	char move('z');
	bool firsttime(true);

	char validChars[] = { 'e', 'E', 'r', 'R' };
	bool goodMove(false);

	while (!goodMove) {
		if (!firsttime) {
			cout << "No, that isn't an option.\n";
		}
		printCombatOptions();
		cin >> move;

		goodMove = checkValidMove(validChars, 8, move);
		firsttime = false;
	}

	printStartOrEndSection();

	//you try to run
	if (move == 'r' || move == 'R') {
		bool didigetaway = tryToEscape();
		if (didigetaway == true) {
			printStartOrEndSection();
			incombat = false;
			return 0;
		}
		//now monster should attack you for failing to run
		hiro.takeDmg(monster->getDmg());
		printMonsterCombatLog(monster);
		if (hiro.checkIfAlive() == false) {
			incombat = false;
			playerDead = true;
			return 0;
		}

	}

	//or you stay and fight
	else if (move == 'e' || move == 'E') {
		//hero attacks
		monster->takeDmg(hiro.getDmg());
		printHeroCombatLog(hiro, monster);
		//check if monster died
		if (monster->checkIfAlive() == false) {
			incombat = false;
			monsterDead = true;
			return 0;
		}

		//monster attacks
		hiro.takeDmg(monster->getDmg());
		printMonsterCombatLog(monster);
		//check if hero died
		if (hiro.checkIfAlive() == false) {
			incombat = false;
			playerDead = true;
			return 0;
		}
		
		
	}
	else cout << "Error invalid move\n";
	

	return 0;
}

bool askRestart(Hero &hiro) {
	using namespace std;
	cout << "You have died.\nRetry? (y/n): ";

	char selection('z');
	bool firsttime(true);

	char validChars[] = { 'y', 'Y', 'n', 'N' };
	bool goodChoice(false);

	while (!goodChoice) {
		if (!firsttime) {
			cout << "Please type a valid input.\n";
		}
		cin >> selection;

		goodChoice = checkValidMove(validChars, 8, selection);
		firsttime = false;
	}

	if (selection == 'y' || selection == 'Y') {
		//reset hero lvl/stats/position/whatever/everything
		hiro.resetHero();
		//gameover = false;
		return false;
	}
	else return true;
}

int printGameOver() {
	using namespace std;
	cout << "GAME OVER\n";
	return 0;
}


int main()
{
	using namespace std;
	//initial setup
	srand(time(NULL));
		//create hero
			//name the hero after what sempai calls me
			//when showing me my place
			//feelsgoodman
	Hero david_kun = Hero();
	
	//create grid? (not really important, just give him a position)

	//while game not over,
	bool gameover(false); /*MOVE THIS TO GAME WORLD CLASS OR SOMETHING LATUR???*/
	while (!gameover) {
		//print status and location
		printPosition(david_kun);
		printStatus(david_kun);
		
		//player move
		playerExploreMove(david_kun);
			//choose wasd
			//update position
	
		//encounter monster or nothing
		int mybadluck = rollDie(david_kun);
		if (mybadluck <= 19) {
			peacefulDay(mybadluck);
		}
		else {
			Enemy* monster = encounter(mybadluck);
			monsterAlert(monster);

			bool incombat(true);
			bool playerDed(false);
			bool monsterDed(false);
			while (incombat) {
				playerCombatMove(david_kun, monster, incombat, playerDed, monsterDed);
			}
			//check if monster ded
			if (monsterDed) {
				//monster dies >> do the exp stuff
				david_kun.gainExp(monster->getExp());
				//if lvlup player, regen hp, update stats of hero
				david_kun.lvlUp( david_kun.checkHowManyLvlUp(david_kun.getLvl(), david_kun.getTotalExp()) );

				printStartOrEndSection();

			}
			//check if player ded
			if (playerDed) {
				//player dies >> retry?
				gameover = askRestart(david_kun);
			}

		}


	}

	printGameOver();

    return 0;
}

