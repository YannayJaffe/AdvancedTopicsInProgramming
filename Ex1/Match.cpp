#include "Match.h"

Match::Match(const std::string& player1Board, const std::string& player2Board, const std::string& player1Moves, const std::string& player2Moves)
        : player1Board(player1Board), player2Board(player2Board), player1Moves(player1Moves), player2Moves(player2Moves), board(),
          player1(PlayerID::Player1, board, player1Board, player1Moves), player2(PlayerID::Player2, board, player2Board, player2Moves)
{
    winner = 0;
    matchFinished = false;
    openedInitFiles = false;
    openedMoveFiles = false;
    player1BadLineInit = 0;
    player2BadLineInit = 0;
    
}

void Match::loadBoard()
{
    if (matchFinished)
        return;
    player1BadLineInit = player1.initBoard();
    player2BadLineInit = player2.initBoard();
    if (player1.getState() == Player::PlayerState::UNINIT)
    {
        std::cout << "Couldn't open board init file for " << player1.toString() << std::endl;
        winner = 0;
        matchFinished = true;
        openedInitFiles = false;
        return;
    }
    if (player2.getState() == Player::PlayerState::UNINIT)
    {
        std::cout << "Couldn't open board init file for " << player1.toString() << std::endl;
        winner = 0;
        matchFinished = true;
        openedInitFiles = false;
        return;
    }
    openedInitFiles = true;
    // both init files got scanned, check if init succeeded
    if (player1BadLineInit != 0 && player2BadLineInit != 0)
    {
        std::stringstream ss;
        winner = 0;
        matchFinished = true;
        ss << "Bad Positioning input file for both players - player 1: line " << player1BadLineInit << ", player 2: line " << player1BadLineInit;
        endMatchReason = ss.str();
        return;
    }
    if (player1BadLineInit != 0 && player2BadLineInit == 0)
    {
        std::stringstream ss;
        winner = 2;
        player2.addPoint();
        matchFinished = true;
        ss << "Bad Positioning input file for player 1 - line " << player1BadLineInit;
        endMatchReason = ss.str();
        return;
    }
    if (player2BadLineInit != 0 && player1BadLineInit == 0)
    {
        std::stringstream ss;
        winner = 1;
        player1.addPoint();
        matchFinished = true;
        ss << "Bad Positioning input file for player 2 - line " << player2BadLineInit;
        endMatchReason = ss.str();
        return;
    }
    checkFlags();
    
}

void Match::printBoard(std::ostream& os)
{
    os << board;
}

void Match::printInitErrors(std::ostream& os)
{
    if (player1BadLineInit != 0)
    {
        os << player1.toString() << " Error in init board: " << player1.getLastErrorString() << std::endl;
    }
    if (player2BadLineInit != 0)
    {
        os << player2.toString() << " Error in init board: " << player2.getLastErrorString() << std::endl;
    }
    
}

void Match::playMoves()
{
    if (matchFinished)
        return;
    if (!player1.initMoves())
    {
        std::cout << "Couldn't open moves file for player 1" << std::endl;
        matchFinished = true;
        openedMoveFiles = false;
        winner = 0;
        return;
    }
    if (!player2.initMoves())
    {
        matchFinished = true;
        openedMoveFiles = false;
        std::cout << "Couldn't open moves file for player 2" << std::endl;
        winner = 0;
        return;
    }
    
    PlayerID turnPlayerId = PlayerID::Player2;
    Player* turnPlayer = nullptr;
    while (!matchFinished)
    {
        turnPlayer = (turnPlayerId == PlayerID::Player1) ? &player2 : &player1;
        turnPlayerId = turnPlayer->getId();
        if (!(player1.hasMoreMoves() || player2.hasMoreMoves()))
        {
            matchFinished = true;
            winner = 0;
            endMatchReason = "A tie - both Moves input files done without a winner";
            continue;
        }
        if (!turnPlayer->hasMovablePieces())
        {
            matchFinished = true;
            winner = (turnPlayerId == PlayerID::Player1) ? 2 : 1;
            if (winner == 1)
            {
                player1.addPoint();
            } else player2.addPoint();
            endMatchReason = "All moving PIECEs of the opponent are eaten";
            continue;
        }
        turnPlayer->playMove();
        
        
        checkFlags();
        
    }
    
    
}

void Match::checkFlags()
{
    bool player1Flags = player1.hasMoreMoves();
    bool player2Flags = player2.hasMoreMoves();
    
    if (!player1Flags && player2Flags)
    {
        winner = 2;
        player2.addPoint();
        matchFinished = true;
        endMatchReason = "All flags of the opponent are captured";
        return;
    }
    if (player1Flags && !player2Flags)
    {
        winner = 1;
        player1.addPoint();
        matchFinished = true;
        endMatchReason = "All flags of the opponent are captured";
        return;
    }
    if (!player1Flags && !player2Flags)
    {
        winner = 0;
        matchFinished = true;
        endMatchReason = "A tie - all flags are eaten by both players in the position files";
        return;
    }
}


