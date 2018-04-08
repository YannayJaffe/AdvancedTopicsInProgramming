#include <iostream>
#include "GamePiece.h"
#include "GeneralDefinitions.h"

int main()
{
    GamePiece s(PlayerID::Player1, PieceType::Scissors);
    GamePiece r(PlayerID::Player2, PieceType::Rock);
    std::cout << (r == s) << std::endl;
    
    std::cout << s.toChar() << std::endl << r.toChar() << std::endl;
    return 0;
}