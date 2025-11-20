#include "game.h"
#include "S&Lsfml.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	ini_snakeleadder();

	int mode = gamemenu();
	gamefun(mode);

	return 0;
}
