#include <string>
#include <utility>

#include "ex4_header.h"
#include "unit_test_util.h"

using std::string;
using std::get;

static bool test1()
{
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            board.setPiece(row, col, "Piece", i);
            i = (i + 1) % 4;
        }
    }
    int occurence[4] = {0, 0, 0, 0};
    for (auto pieceInfo : board)
    {
        occurence[get<3>(pieceInfo)]++;
    }
    for (int i = 0; i < 4; i++)
    {
        if (occurence[i] != 21)
        {
            return false;
        }
    }
    
    return true;
}

static bool test2()
{
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            board.setPiece(row, col, "Piece", i);
            i = (i + 1) % 4;
        }
    }
    int occurence2 = 0;
    for (auto pieceInfo : board.allPiecesOfPlayer(2))
    {
        occurence2++;
    }
    
    if (occurence2 != 21)
    {
        return false;
        
    }
    
    return true;
}

static bool test3()
{
    GameBoard<12, 7, string, 4> board;
    int i = 0;
    for (int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            board.setPiece(row, col, std::string("Piece") + std::to_string(row+col), i);
            i = (i + 1) % 4;
        }
    }
    int occurencePiece = 0;
    for (auto pieceInfo : board.allOccureneceOfPiece("Piece5"))
    {
        occurencePiece++;
    }
    
    if (occurencePiece != 6)
    {
        return false;
        
    }
    
    return true;
}

static bool test4()
{
    GameBoard<12, 7, string, 4> board;
    for (int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            board.setPiece(row, col, std::string("Piece") + std::to_string(row+col), (row+col)%4);
            
        }
    }
    int occurencePiece = 0;
    for (auto pieceInfo : board.allOccureneceOfPieceForPlayer("Piece5",2))
    {
        occurencePiece++;
    }
    
    if (occurencePiece != 0)
    {
        return false;
        
    }
    
    return true;
}

static bool test5()
{
    GameBoard<12, 7, string, 4> board;
    for (int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            board.setPiece(row, col, std::string("Piece") + std::to_string(row+col), (row+col)%4);
            
        }
    }
    int occurencePiece = 0;
    for (auto pieceInfo : board.allOccureneceOfPieceForPlayer("Piece5",1))
    {
        occurencePiece++;
    }
    
    if (occurencePiece != 6)
    {
        return false;
        
    }
    
    return true;
}

int main()
{
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
    RUN_TEST(test5);
    return 0;
}
