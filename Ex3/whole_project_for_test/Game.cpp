//
// Created by yanna on 05/07/18.
//

#include "Game.h"

Game::Game(std::unique_ptr<PlayerAlgorithm> player1, std::unique_ptr<PlayerAlgorithm> player2) :
        totalMoves(0), player1Moves(0), player2Moves(0),
	player1(std::move(player1)), player2(std::move(player2)),
	board(totalXVals, totalYVals)
{

}

int Game::runGame()
{
    int gameInitVal = gameInit();
    if (gameInitVal != -1)
    {
        //if we got in here it means that the game is finished (bad files/bad arguments/bad positioning/no more flags for either players
        return gameInitVal;
    }
    // in here we have both of the players piece vectors initialized and valid. some entries might be null
    // notify both players on initial board and fights
    player1->notifyOnInitialBoard(board, fights);
    player2->notifyOnInitialBoard(board, fights);
    //now both players know the initial board and fight history, can start getting moves from each player and run the game

    std::unique_ptr<Move> move;
    int currentPlayer = PLAYER1;
    int otherPlayer = PLAYER2;
    while (totalMoves < maxMoves)
    {
        totalMoves++;
        if (currentPlayer == PLAYER1)
            player1Moves++;
        else
            player2Moves++;

        if (!doFullMove(currentPlayer))
        { // illegal move
            return otherPlayer;
        }

        // check if any player lost all of his flags
        int winDueFlags = winConditionFlags();
        if (winDueFlags != -1)
        {
            return winDueFlags;
        }

        auto tmp = otherPlayer;
        otherPlayer = currentPlayer;
        currentPlayer = tmp;
    }
    return BOTH;
}

bool Game::doFullMove(int playerId)
{
    std::unique_ptr<Move> move;
    PlayerAlgorithm *thisPlayer = (playerId == PLAYER1) ? player1.get() : player2.get();
    PlayerAlgorithm *otherPlayer = (playerId == PLAYER1) ? player2.get() : player1.get();
    move = thisPlayer->getMove();
    if (!isLegalMove(*move, playerId)) // check legal
    {
        return false;
    }
    std::unique_ptr<FightInfo> fightInfo = playMove(*move, playerId);//actually do the move
    if (fightInfo != nullptr)
        thisPlayer->notifyFightResult(*fightInfo);

    std::unique_ptr<JokerChange> jokerChange = thisPlayer->getJokerChange();
    if (jokerChange != nullptr && !doJokerChange(playerId, *jokerChange))
    { //got a bad joker change
        return false;
    }

    otherPlayer->notifyOnOpponentMove(*move); // notify other player on move
    if (fightInfo != nullptr)
        otherPlayer->notifyFightResult(*fightInfo);
    return true;
}

bool Game::doJokerChange(int playerId, const JokerChange &jokerChange)
{
    if (board.getPlayer(jokerChange.getJokerChangePosition()) != playerId)
        return false; // this position is not owned by the player

    auto &piece = getPlayerPiece(playerId, jokerChange.getJokerChangePosition());
    if (piece == nullptr) // just a sanity check
        return false;

    if (static_cast<char>(std::toupper(piece->getPiece())) != 'J')
        return false; // requested piece is not joker

    auto jokerRep = static_cast<char>(std::toupper(jokerChange.getJokerNewRep()));

    switch (jokerRep)
    {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
            break;
        default:
            return false; // requested joker representation is illegal
    }

    std::unique_ptr<PiecePosition> changedPiece = std::make_unique<PiecePositionImpl>(piece->getPosition(), 'J',
                                                                                      jokerRep);
    piece.swap(changedPiece);
    return true;
}


bool
Game::checkInitialLegalPieces(
        const std::vector<std::unique_ptr<PiecePosition>> &playerPieces) const // checks that the initial placement is legal
{
    BoardImpl tempBoard(totalXVals, totalYVals);
    int id = 1; // in here we check for a single player legallity so the id doesnt matter
    PieceCounter tempPieceCounter(totalRocks, totalPapers, totalScissors, totalBombs, totalJokers, totalFlags);
    for (const auto &piece : playerPieces)
    {
        if (piece == nullptr)
            continue;

        if (!pointInBoard(piece->getPosition()))
            return false;//piece is out of board

        if (!tempPieceCounter.addPiece(piece->getPiece()))
            return false;//bad piece char or trying to add to many pieces

        if (tempBoard.getPlayer(piece->getPosition()) != NONE)
            return false;//trying to add piece to an already occupied spot by the same player

        if (static_cast<char>(std::toupper(piece->getPiece()) == 'J'))
        {
            auto jokerRep = static_cast<char>(std::toupper(piece->getJokerRep()));
            if (jokerRep != 'R' && jokerRep != 'P' && jokerRep != 'S' && jokerRep != 'B')
                return false;// bad joker representation
        }
        tempBoard.setPlayer(piece->getPosition(), id);
    }
    return (tempPieceCounter.getRemaining('F') == 0); // need to use all flags
}

bool Game::pointInBoard(const Point &p) const //return true if point on board
{
    int x = p.getX();
    int y = p.getY();
    return (x >= 1 && x <= totalXVals) && (y >= 1 && y <= totalYVals);
}

void
Game::initBoard() //initialize the board according to the initial piece position vectors. assume both vectors are legal
{
    initPlayerOnBoard(PLAYER1); // sets player 1 pieces on board
    initPlayerOnBoard(
            PLAYER2); // sets player 2 pieces on board if any fights happen, sets losing/tied piece to nullptr and updates board, and updates fights vector
}

void Game::initPlayerOnBoard(
        int playerId) // places player on board, conducts all fights, updates board according to fights, updates fights vector
{ // when calling this method the board can be initialized properly
    std::vector<std::unique_ptr<PiecePosition>> *playerPieces;
    if (playerId == PLAYER1)
    {
        playerPieces = &player1Pieces;
    } else if (playerId == PLAYER2)
    {
        playerPieces = &player2Pieces;
    } else
        return;

    int otherPlayerId = (playerId == PLAYER1 ? PLAYER2 : PLAYER1);

    for (auto &piece : *playerPieces)
    {
        if (piece == nullptr)
            continue;

        if (board.getPlayer(piece->getPosition()) == NONE)
        { // the board location is empty, can safely place the piece
            board.setPlayer(piece->getPosition(), playerId);
        } else if (board.getPlayer(piece->getPosition()) == otherPlayerId)
        {  // the board location is occupied, conduct fight
            auto &otherPiece = getPlayerPiece(otherPlayerId, piece->getPosition());
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

std::unique_ptr<PiecePosition> &
Game::getPlayerPiece(int playerId, const Point &point) // returns the wanted piece in the vector
{
    std::vector<std::unique_ptr<PiecePosition>> *playerPieces;
    if (playerId == PLAYER1)
    {
        playerPieces = &player1Pieces;
    } else if (playerId == PLAYER2)
    {
        playerPieces = &player2Pieces;
    } else
        return nullPiecePosition;

    for (unsigned int i = 0; i < static_cast<unsigned int>(playerPieces->size()); i++)
    {
        if (playerPieces->at(i) == nullptr)
            continue;

        if (playerPieces->at(i)->getPosition().getX() == point.getX() &&
            playerPieces->at(i)->getPosition().getY() == point.getY())
            return playerPieces->at(i);
    }
    return nullPiecePosition;
}

std::unique_ptr<FightInfo>
Game::getFightInfo(const PiecePosition &player1Piece,
                   const PiecePosition &player2Piece) //returns the fight info for these pieces
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
        return std::make_unique<FightInfoImpl>(piece1, piece2, player1Piece.getPosition(), BOTH);

    if (player1Piece > player2Piece)
        return std::make_unique<FightInfoImpl>(piece1, piece2, player1Piece.getPosition(), PLAYER1);

    if (player2Piece > player1Piece)
        return std::make_unique<FightInfoImpl>(piece1, piece2, player1Piece.getPosition(), PLAYER2);

    return nullptr;
}

bool operator>(const PiecePosition &p1, const PiecePosition &p2)
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

bool operator==(const PiecePosition &p1, const PiecePosition &p2)
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

bool operator<(const PiecePosition &p1, const PiecePosition &p2)
{
    if (p1 == p2)
        return false;
    return !(p1 > p2);
}

int Game::gameInit()
{

    player1->getInitialPositions(PLAYER1, player1Pieces); //initialize player1 pieces
    player2->getInitialPositions(PLAYER2, player2Pieces); //initialize player2 pieces

    bool player1InitialLegal = checkInitialLegalPieces(player1Pieces);
    bool player2InitialLegal = checkInitialLegalPieces(player2Pieces);

    if (player1InitialLegal && !player2InitialLegal)
    {
        // player1 initialization is legal, but player2 initialization is illegal

        return PLAYER1;
    }
    if (!player1InitialLegal && player2InitialLegal)
    {
        // player1 initialization is illegal, but player2 initialization is legal

        return PLAYER2;
    }
    if (!player1InitialLegal && !player2InitialLegal)
    {
        // both players initializations are illegal

        return BOTH;
    }
    initBoard();
    //check both players flag count
    // if any of the players dont have flags, and the other does, declare winner. if both lost all flags, declare tie
    return winConditionFlags();
}

int Game::getPieceCount(int playerId,
                        char pieceType)//count how many pieces are there of specified type. if not asked for joker, then treat joker as regular type
{
    std::vector<std::unique_ptr<PiecePosition>> *playerPieces;
    if (playerId == PLAYER1)
        playerPieces = &player1Pieces;
    else if (playerId == PLAYER2)
        playerPieces = &player2Pieces;
    else return 0;

    pieceType = static_cast<char>(std::toupper(pieceType));
    int cnt = 0;
    char currPieceType;
    for (const auto &piece:*playerPieces)
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

bool Game::isLegalMove(const Move &move, int playerId)
{
    if (!pointInBoard(move.getFrom()))
        return false;

    if (!pointInBoard(move.getTo()))
        return false;

    if (board.getPlayer(move.getFrom()) != playerId)
        return false;

    if (board.getPlayer(move.getTo()) == playerId)
    {
        if (move.getFrom().getX() != move.getTo().getX() ||
            move.getFrom().getY() != move.getTo().getY())//check that not stays in the same spot
            return false;
    }

    auto &piece = getPlayerPiece(playerId, move.getFrom());
    if (!isMovable(*piece))
        return false;

    if (!isSingleStep(move))
        return false;

    return true;

}

bool Game::isMovable(const PiecePosition &piece)
{
    auto pieceChar = static_cast<char>(std::toupper(piece.getPiece()));
    if (pieceChar == 'J')
        pieceChar = static_cast<char>(std::toupper(piece.getJokerRep()));

    return (pieceChar == 'R' || pieceChar == 'P' || pieceChar == 'S');

}

std::unique_ptr<FightInfo> Game::playMove(const Move &move, int playerId)
{
    // in here it is certain that the move is legal
    std::unique_ptr<FightInfo> fightInfo;
    board.setPlayer(move.getFrom(), NONE); // mark the board empty at this piece location
    auto &pieceOldLoc = getPlayerPiece(playerId, move.getFrom());
    if (pieceOldLoc == nullptr)
        return nullptr;
    std::unique_ptr<PiecePosition> movedPiece = std::make_unique<PiecePositionImpl>(move.getTo(),
                                                                                    pieceOldLoc->getPiece(),
                                                                                    pieceOldLoc->getJokerRep());
    pieceOldLoc.swap(movedPiece); // change the piece in the vector to the new location

    if (board.getPlayer(move.getTo()) == NONE)
    {// there will be no fight because the spot is empty
        board.setPlayer(move.getTo(), playerId);
        fightInfo = nullptr;
    } else
    {
        // the board is occupied by the other player, pieces should fight.
        fightInfo = getFightInfo(*getPlayerPiece(PLAYER1, move.getTo()), *getPlayerPiece(PLAYER2, move.getTo()));
        if (fightInfo != nullptr)
        {
            board.setPlayer(fightInfo->getPosition(), fightInfo->getWinner()); // sets the winner on board
            if (fightInfo->getWinner() == BOTH)
            { // remove both pieces
                getPlayerPiece(PLAYER1, fightInfo->getPosition()) = nullptr;
                getPlayerPiece(PLAYER2, fightInfo->getPosition()) = nullptr;
            } else
            {
                int loser = (fightInfo->getWinner() == PLAYER1) ? PLAYER2 : PLAYER1; // defines the loser
                // remove the loser's piece
                getPlayerPiece(loser, fightInfo->getPosition()) = nullptr;
            }
        }
    }
    return fightInfo;
}

int Game::winConditionFlags()
{
    int player1Flags = getPieceCount(PLAYER1, 'F');
    int player2Flags = getPieceCount(PLAYER2, 'F');

    if (player1Flags > 0 && player2Flags == 0)
        return PLAYER1;

    if (player1Flags == 0 && player2Flags > 0)
        return PLAYER2;

    if (player1Flags == 0 && player2Flags == 0)
        return BOTH;

    return -1;
}


bool Game::isSingleStep(const Move &move)
{
    int prevX = move.getFrom().getX();
    int prevY = move.getFrom().getY();
    int newX = move.getTo().getX();
    int newY = move.getTo().getY();

    int dx = prevX - newX;
    if (dx < 0)
        dx = -1 * dx;

    int dy = prevY - newY;
    if (dy < 0)
        dy = -1 * dy;


    return (dx + dy == 1);
}


