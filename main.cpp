#include "chess_pieces.h"
#include<iostream>
#include "chess_game.h"
#include<string>
#include <windows.h>
using namespace std;
int main() {

	Game game;
	game.setup();
	game.run();
	
	
	system("pause");
	return 0;
}
 