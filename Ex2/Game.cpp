//
// Created by yanna on 05/07/18.
//

#include "Game.h"

Game::Game(int argc, char** argv) : player1Algo(AlgoType::FILE), player2Algo(AlgoType::FILE), player1(nullptr), player2(nullptr),
                                    board(totalXVals, totalYVals), totalMoves(0)
{
    if (argc < 2)
    {
        isLegalCommandLine = false;
    } else
    {
        isLegalCommandLine = true;
        std::string commandLine(argv[2]);
        if (commandLine == "auto-vs-file")
        {
            player1Algo = AlgoType::AUTO;
            player2Algo = AlgoType::FILE;
            
        } else if (commandLine == "file-vs-auto")
        {
            player1Algo = AlgoType::FILE;
            player2Algo = AlgoType::AUTO;
            
        } else if (commandLine == "auto-vs-auto")
        {
            player1Algo = AlgoType::AUTO;
            player2Algo = AlgoType::AUTO;
        } else if (commandLine == "file-vs-file")
        {
            player1Algo = AlgoType::FILE;
            player2Algo = AlgoType::FILE;
            
        } else
        {
            isLegalCommandLine = false;
        }
    }
    
    
}

bool Game::initPlayersPtrs()
{
    if (!isLegalCommandLine)
        return false;
    
    switch (player1Algo)
    {
        case AlgoType::FILE:
            player1 = std::make_unique<FilePlayerAlgorithm>();
            break;
        case AlgoType::AUTO:
            player1 = std::make_unique<AutoPlayerAlgorithm>();
            break;
    }
    
    switch (player2Algo)
    {
        case AlgoType::FILE:
            player2 = std::make_unique<FilePlayerAlgorithm>();
            break;
        case AlgoType::AUTO:
            player2 = std::make_unique<AutoPlayerAlgorithm>();
            break;
    }
    return (player1 != nullptr && player2 != nullptr);
}

void Game::runGame()
{
    if (!gameInit())
    {
        //if we got in here it means that the game is finished (bad files/bad arguments/bad positioning/no more flags for either players
        return;
    }
    // in here we have both of the players piece vectors initialized and valid. some entries might be null
    // notify both players on initial board and fights
    player1->notifyOnInitialBoard(board, fights);
    player2->notifyOnInitialBoard(board, fights);
    //now both players know the initial board and fight history, can start getting moves from each player and run the game
    
    std::unique_ptr<Move> move;
    while (totalMoves < maxMoves)
    {
        /////////////////////////////
        //do entire move from player1:
        // get move
        move = player1->getMove();
        // check move is legal
        // play move
        // conduct fight
        // notify other player on move and fight
        // play joker change
        // check if won (no more flags)
        /////////////////////////////
        totalMoves++;
    
        /////////////////////////////
        //do entire move from player2:
        // get move
        move = player2->getMove();
        // check move is legal
        // play move
        // conduct fight
        // notify other player on move and fight
        // play joker change
        // check if won (no more flags)
        /////////////////////////////
        totalMoves++;
    }
    declareWinner(BOTH,WinReason::Reason::MAX_MOVES_REACHED);//tie because maxed out the moves
    
    // TODO: implement game moves etc.. look again at winner conditions
    // play the game in turns (player 1 moves first):
    // 1. check how many moves played so far, if more than the max, declare tie.
    // 2. get a play from player, and check validity: first try to move the requested piece, if no more movable pieces, than declare winner
    // 3. when moving the piece, check if a fight happens.
    // 4. update both players pieces vectors, notify both players on the fight, and update the fights vector and board placement.
    // 5. notify other player on the move.
    // 6. after moved the piece, check for a joker change (again, check validity).
    // 7. if a joker change occured, update the player piece vector.
    // 8. check for remaining flags, declare winner if neccessary
    // 9. update moves counter
    
}

bool
Game::checkInitialLegalPieces(const std::vector<std::unique_ptr<PiecePosition>>& playerPieces) const // checks that the initial placement is legal
{
    BoardImpl tempBoard(totalXVals, totalYVals);
    int id = 1; // in here we check for a single player legallity so the id doesnt matter
    PieceCounter tempPieceCounter(totalRocks, totalPapers, totalScissors, totalBombs, totalJokers, totalFlags);
    for (const auto& piece : playerPieces)
    {
        if (piece == nullptr)
            continue;
        
        if (!pointInBoard(piece->getPosition()))
            return false;//piece is out of board
        
        if (!tempPieceCounter.addPiece(piece->getPiece()))
            return false;//bad piece char or trying to add to many pieces
        
        if (tempBoard.getPlayer(piece->getPosition()) != 0)
            return false;//trying to add piece to an already occupied spot by the same player
        
        tempBoard.setPlayer(piece->getPosition(), id);
    }
    return (tempPieceCounter.getRemaining('F') == 0); // need to use all flags
}

bool Game::pointInBoard(const Point& p) const //return true if point on board
{
    int x = p.getX();
    int y = p.getY();
    return (x >= 1 && x <= totalXVals) && (y >= 1 && y <= totalYVals);
}

void Game::initBoard() //initialize the board according to the initial piece position vectors. assume both vectors are legal
{
    initPlayerOnBoard(PLAYER1); // sets player 1 pieces on board
    initPlayerOnBoard(
            PLAYER2); // sets player 2 pieces on board if any fights happen, sets losing/tied piece to nullptr and updates board, and updates fights vector
}

void Game::initPlayerOnBoard(int playerId) // places player on board, conducts all fights, updates board according to fights, updates fights vector
{ // when calling this method the board can be initialized properly
    std::vector<std::unique_ptr<PiecePosition>>* playerPieces;
    if (playerId == PLAYER1)
    {
        playerPieces = &player1Pieces;
    } else if (playerId == PLAYER2)
    {
        playerPieces = &player2Pieces;
    } else
        return;
    
    int otherPlayerId = (playerId == PLAYER1 ? PLAYER2 : PLAYER1);
    
    for (auto& piece : *playerPieces)
    {
        if (piece == nullptr)
            continue;
        
        if (board.getPlayer(piece->getPosition()) == 0)
        { // the board location is empty, can safely place the piece
            board.setPlayer(piece->getPosition(), playerId);
        } else if (board.getPlayer(piece->getPosition()) == otherPlayerId)
        {  // the board location is occupied, conduct fight
            auto& otherPiece = getPlayerPiece(otherPlayerId, piece->getPosition());
            std::unique_ptr<FightInfo> fightInfo;
            if (playerId == PLAYER1)
            {
                fightInfo = getFightInfo(*piece, *otherPiece);
            } else
            {
                fightInfo = getFightInfo(*otherPiece, *piece);
            }
            board.setPlayer(fightInfo->getPosition(), fightInfo->getWinner());
            if (fightInfo->getWinner() == BOTH)
            {
                piece = nullptr;
                otherPiece = nullptr;
            } else if (fightInfo->getWinner() == PLAYER1)
            {
                if (playerId == PLAYER1)
                    otherPiece = nullptr;
                else
                    piece = nullptr;
            } else if (fightInfo->getWinner() == PLAYER2)
            {
                if (playerId == PLAYER1)
                    piece = nullptr;
                else
                    otherPiece = nullptr;
            } else
                return;
            
            fights.push_back(std::move(fightInfo));
        }
    }
}

std::unique_ptr<PiecePosition>& Game::getPlayerPiece(int playerId, const Point& point) // returns the wanted piece in the vector
{
    std::vector<std::unique_ptr<PiecePosition>>* playerPieces;
    if (playerId == 1)
    {
        playerPieces = &player1Pieces;
    } else if (playerId == 2)
    {
        playerPieces = &player2Pieces;
    } else
        return nullPiecePosition;
    
    for (int i = 0; i < playerPieces->size(); i++)
    {
        if (playerPieces->at(i) == nullptr)
            continue;
        
        if (playerPieces->at(i)->getPosition().getX() == point.getX() && playerPieces->at(i)->getPosition().getY() == point.getY())
            return playerPieces->at(i);
    }
    return nullPiecePosition;
}

std::unique_ptr<FightInfo>
Game::getFightInfo(const PiecePosition& player1Piece, const PiecePosition& player2Piece) //returns the fight info for these pieces
{
    if (player1Piece.getPosition().getX() != player2Piece.getPosition().getX() ||
        player1Piece.getPosition().getY() != player2Piece.getPosition().getY())
        return nullptr;
    char piece1 = player1Piece.getPiece();
    if (piece1 == 'J' || piece1 == 'j')
        piece1 = player1Piece.getJokerRep();
    char piece2 = player2Piece.getPiece();
    if (piece2 == 'J' || piece2 == 'j')
        piece2 = player2Piece.getJokerRep();
    
    if (player1Piece == player2Piece)
        return std::make_unique<FightInfoImpl>(piece1, piece2, player1Piece.getPosition(), 0);
    
    if (player1Piece > player2Piece)
        return std::make_unique<FightInfoImpl>(piece1, piece2, player1Piece.getPosition(), 1);
    
    if (player2Piece > player1Piece)
        return std::make_unique<FightInfoImpl>(piece1, piece2, player1Piece.getPosition(), 2);
    
    return nullptr;
}

bool operator>(const PiecePosition& p1, const PiecePosition& p2)
{
    char piece1 = p1.getPiece();
    if (piece1 == 'J' || piece1 == 'j')
        piece1 = p1.getJokerRep();
    char piece2 = p2.getPiece();
    if (piece2 == 'J' || piece2 == 'j')
        piece2 = p2.getJokerRep();
    
    switch (piece1)
    {
        case 'R':
        case 'r':
            switch (piece2)
            {
                case 'S':
                case 's':
                case 'F':
                case 'f':
                    return true;
                default:
                    return false;
            }
            break;
        case 'P':
        case 'p':
            switch (piece2)
            {
                case 'R':
                case 'r':
                case 'F':
                case 'f':
                    return true;
                default:
                    return false;
            }
            break;
        case 'S':
        case 's':
            switch (piece2)
            {
                case 'P':
                case 'p':
                case 'F':
                case 'f':
                    return true;
                default:
                    return false;
            }
            break;
        case 'B':
        case 'b':
            return false;
            break;
        case 'F':
        case 'f':
            return false;
            break;
        default:
            return false;
    }
}

bool operator==(const PiecePosition& p1, const PiecePosition& p2)
{
    char piece1 = p1.getPiece();
    if (piece1 == 'J' || piece1 == 'j')
        piece1 = p1.getJokerRep();
    char piece2 = p2.getPiece();
    if (piece2 == 'J' || piece2 == 'j')
        piece2 = p2.getJokerRep();
    if (std::toupper(piece1) == std::toupper(piece2))
        return true;
    return piece1 == 'B' || piece1 == 'b' || piece2 == 'B' || piece2 == 'b';
}

bool operator<(const PiecePosition& p1, const PiecePosition& p2)
{
    if (p1 == p2)
        return false;
    return !(p1 > p2);
}

bool Game::gameInit()
{
    if (!initPlayersPtrs())
    {
        std::cout
                << "could not initialize players, check command line argument. should be: <player1>-vs-<player2>. player1 and player2 can be either of file or auto.";
        return false;
    }
    
    player1->getInitialPositions(PLAYER1, player1Pieces); //initialize player1 pieces
    player2->getInitialPositions(PLAYER2, player2Pieces); //initialize player2 pieces
    
    bool player1InitialLegal = checkInitialLegalPieces(player1Pieces);
    bool player2InitialLegal = checkInitialLegalPieces(player2Pieces);
    
    if (player1InitialLegal && !player2InitialLegal)
    {
        // player1 initialization is legal, but player2 initialization is illegal
        declareWinner(PLAYER1,WinReason::Reason::ILLEGAL_INIT);
        return false;
    }
    if (!player1InitialLegal && player2InitialLegal)
    {
        // player1 initialization is illegal, but player2 initialization is legal
        declareWinner(PLAYER2,WinReason::Reason::ILLEGAL_INIT);
        return false;
    }
    if (!player1InitialLegal && !player2InitialLegal)
    {
        // both players initializations are illegal
        declareWinner(BOTH,WinReason::Reason::ILLEGAL_INIT);
        return false;
    }
    initBoard();
    //check both players flag count
    // if any of the players dont have flags, and the other does, declare winner. if both lost all flags, declare tie
    int player1Flags = getPieceCount(PLAYER1, 'F');
    int player2Flags = getPieceCount(PLAYER2, 'F');
    if (player1Flags > 0 && player2Flags == 0)
    {
        declareWinner(PLAYER1,WinReason::Reason::NO_MORE_FLAGS_INIT);
        return false;
    }
    if (player1Flags == 0 && player2Flags > 0)
    {
        declareWinner(PLAYER2,WinReason::Reason::NO_MORE_FLAGS_INIT);
        return false;
    }
    if (player1Flags == 0 && player2Flags == 0)
    {
        declareWinner(BOTH,WinReason::Reason::NO_MORE_FLAGS_INIT);
        return false;
    }
    return true;//board init completed, can start on getting player moves
}

int Game::getPieceCount(int playerId,
                        char pieceType)//count how many pieces are there of specified type. if not asked for joker, then treat joker as regular type
{
    std::vector<std::unique_ptr<PiecePosition>>* playerPieces;
    if (playerId == PLAYER1)
        playerPieces = &player1Pieces;
    else if (playerId == PLAYER2)
        playerPieces = &player2Pieces;
    else return 0;
    
    pieceType = static_cast<char>(std::toupper(pieceType));
    int cnt = 0;
    char currPieceType;
    for (const auto& piece:*playerPieces)
    {
        if (piece == nullptr)
            continue;
        
        currPieceType = static_cast<char>(std::toupper(piece->getPiece()));
        if (currPieceType == 'J' && pieceType != 'J')
            currPieceType = static_cast<char>(std::toupper(piece->getJokerRep()));
        
        if (pieceType == currPieceType)
            cnt++;
    }
    
    return cnt;
}
