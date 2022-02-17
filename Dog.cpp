/*
 * Dog.cpp
 *
 *  Created on: Sep 13, 2021
 *  Author: Weldin Dunn
 */

#include "Dog.hpp"
#include <iostream>

using namespace std;

Dog::Dog(string n) {
	name = n;
	strength = 50;
	x = 0;
	y = 0;
}

Dog::Dog() {
	name = "Gracie";
	strength = 50;
	x = 0;
	y = 0;
}

void Dog::printDog() {
	cout << "Name: " << name << endl;
	cout << "Strength: " << strength << endl;
}

bool Dog::changeStrength(int amt) {
	strength += amt;
	printDog();
	if (strength < 1) {
		die();
		return false;
	} else {
		return true;
	}
}

void Dog::die() {
	//This is a reference to Friday the 13th on NES
	cout << "You and your friends are dead." << endl;
	cout << "GAME OVER" << endl;
}

void Dog::won() {
	//This is a reference to Ghosts n' Goblins on NES
	cout << "Conglaturation." << endl;
	cout << "This story is happy end." << endl;
	cout << "Being the wise and corageour dog that" << endl;
	cout << "you are you feel strongth welling in" << endl;
	cout << "your body. Return to starting point!" << endl;
	cout << "Challenge again!" << endl;
}

void Dog::reset() {
	strength = 50;
	x = 0;
	y = 0;
}
