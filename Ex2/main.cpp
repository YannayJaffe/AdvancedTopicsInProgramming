#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
    Game game(argc, argv,"rps.output");
    game.runGame();
}