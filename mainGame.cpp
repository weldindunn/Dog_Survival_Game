/*
 * mainGame.cpp
 *
 *  Created on: Sep 13, 2021
 *  Author: Weldin Dunn
 */

#include "Board.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main() {
	srand(time(NULL));
	Board board('m', true);
	return 0;
}
