#include <iostream>
#include "Game.h"
#include "RandomGenerator.h"

int main(int argc, char** argv)
{
    
    Game game(argc, argv, "rps.output");
    game.runGame();
    
    return 0;
    
}