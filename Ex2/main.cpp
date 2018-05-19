#include <iostream>
#include "Game.h"
#include "RandomGenerator.h"

int main(int argc, char** argv)
{
    /* Game game(argc, argv,"rps.output");
     game.runGame();*/
    RandomGenerator rg;
    
    std::cout << rg.getRange(4, 6) << " " << rg.getRange(4, 6) << " " << rg.getRange(4, 6) << std::endl;
    
}