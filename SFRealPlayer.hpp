//
//  SFRealPlayer.h
//  assginment4
//
//  Created by 严若超 on 3/12/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#ifndef SFRealPlayer_hpp
#define SFRealPlayer_hpp
#include "SFGame.hpp"
#include "SFBoard.hpp"
#include "SFPlayer.hpp"
#include "SFPiece.hpp"
class SFRealPlayer : public SFPlayer {
public:
    SFRealPlayer(PieceColor color);
    void takeTurn(SFGame &aGame);
};

#endif /* SFRealPlayer_hpp */
