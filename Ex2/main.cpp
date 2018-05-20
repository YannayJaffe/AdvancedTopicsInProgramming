#include <iostream>
#include "Game.h"
#include "RandomGenerator.h"

int main(int argc, char** argv)
{
    for (int i = 0; i < 200; i++)
    {
        std::cout << i << std::endl;
       // Game game(argc, argv, "rps.output", i);
        //game.runGame();
    }
    return 0;
}