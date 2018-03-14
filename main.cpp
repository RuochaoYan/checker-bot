//
//  main.cpp
//  assginment4
//
//  Created by 严若超 on 3/12/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include <iostream>
#include <SFGame.hpp>
#include <SFPlayer.hpp>
#include "SFRealPlayer.hpp"

int main(int argc, const char * argv[]) {
    SFRealPlayer yourPlayer(PieceColor::red);
    SFRealPlayer opponentPlayer(PieceColor::black);
    SFGame *theGame = SFGame::create();
    theGame->run(yourPlayer, opponentPlayer);
    delete theGame;
    return 0;
}
