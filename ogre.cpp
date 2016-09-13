//#include "stdafx.h"
#include "ogre.h"

Ogre::Ogre() {
	name = "Ouguri-kun";
	race = "Ogre";

	maxhp	= 61;
	hp		= maxhp;
	dmg		= 9;
	exp		= 30;

	stillalive = true;
}