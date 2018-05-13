//
// Created by yanna on 05/14/18.
//

#ifndef EX2_WINREASON_H
#define EX2_WINREASON_H

#include <string>

struct WinReason
{
    enum class Reason
    {
        ILLEGAL_INIT, // bad initialization (bad piece position vector)
        NO_MORE_FLAGS_INIT, // no more flags after initialization
        ILLEGAL_MOVE, // tried to do an illegal move
        NO_MORE_FLAGS_MOVES, // took over the last remaining flag during a move
        MAX_MOVES_REACHED // played the total maximum moves
    };
    
    static std::string toString(Reason reason)
    {
        std::string winReason;
        switch (reason)
        {
            case Reason::ILLEGAL_INIT:
                winReason = "Bad pieces initialization";
                break;
            case Reason::NO_MORE_FLAGS_INIT:
                winReason = "No flags remaining after initialization";
                break;
            case Reason::ILLEGAL_MOVE:
                winReason = "Did an illegal move";
                break;
            case Reason::NO_MORE_FLAGS_MOVES:
                winReason = "No flags remaining after move";
                break;
            case Reason::MAX_MOVES_REACHED:
                winReason = "Maximum moves reached";
                break;
        }
        return winReason;
    }
};


#endif //EX2_WINREASON_H
