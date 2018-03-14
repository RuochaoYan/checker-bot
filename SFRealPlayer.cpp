//
//  SFRealPlayer.cpp
//  assginment4
//
//  Created by 严若超 on 3/12/18.
//  Copyright © 2018 严若超. All rights reserved.
//

#include "SFRealPlayer.hpp"
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

bool couldJump(int i, int j, SFTile& aTile, SFTile (&aBoard)[8][8]){
    if(aTile.getPiece().isKing() || aTile.getPiece().getColor() == PieceColor::red){
        if(i+2 < 8 && j-2 >= 0 && !aBoard[i+1][j-1].isEmpty() && aBoard[i+1][j-1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i+2][j-2].isEmpty())
            return true;
        if(i+2 < 8 && j+2 < 8 && !aBoard[i+1][j+1].isEmpty() && aBoard[i+1][j+1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i+2][j+2].isEmpty())
            return true;
    }
    if(aTile.getPiece().isKing() || aTile.getPiece().getColor() == PieceColor::black){
        if(i-2 >= 0 && j-2 >= 0 && !aBoard[i-1][j-1].isEmpty() && aBoard[i-1][j-1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i-2][j-2].isEmpty())
            return true;
        if(i-2 >= 0 && j+2 < 8 && !aBoard[i-1][j+1].isEmpty() && aBoard[i-1][j+1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i-2][j+2].isEmpty())
            return true;
    }
    return false;
}

void makeJump(int i, int j, SFTile& aTile, SFTile (&aBoard)[8][8], std::vector<SFLocation>& path, std::vector<SFLocation>& temp){
    temp.push_back(SFLocation(i,j));
    if(temp.size() == 5 || !couldJump(i, j, aTile, aBoard)){
        if(path.size() < temp.size()){
            path = temp;
        }
        temp.pop_back();
        return;
    }
    if(aTile.getPiece().isKing() || aTile.getPiece().getColor() == PieceColor::red){
        if(i+2 < 8 && j-2 >= 0 && !aBoard[i+1][j-1].isEmpty() && aBoard[i+1][j-1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i+2][j-2].isEmpty())
            makeJump(i+2, j-2, aTile, aBoard, path, temp);
        if(i+2 < 8 && j+2 < 8 && !aBoard[i+1][j+1].isEmpty() && aBoard[i+1][j+1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i+2][j+2].isEmpty())
            makeJump(i+2, j+2, aTile, aBoard, path, temp);
    }
    if(aTile.getPiece().isKing() || aTile.getPiece().getColor() == PieceColor::black){
        if(i-2 >= 0 && j-2 >= 0 && !aBoard[i-1][j-1].isEmpty() && aBoard[i-1][j-1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i-2][j-2].isEmpty())
            makeJump(i-2, j-2, aTile, aBoard, path, temp);
        if(i-2 >= 0 && j+2 < 8 && !aBoard[i-1][j+1].isEmpty() && aBoard[i-1][j+1].getPiece().getColor() != aTile.getPiece().getColor() && aBoard[i-2][j+2].isEmpty())
            makeJump(i-2, j+2, aTile, aBoard, path, temp);
    }
    temp.pop_back();
}

int calculateWeight(int i, int j, SFTile& aTile){
    if(!aTile.getPiece().isKing()){
        if(aTile.getPiece().getColor() == PieceColor::red && i+1 == 7){
            return 9;
        }
        if(aTile.getPiece().getColor() == PieceColor::black && i-1 == 0)
            return 9;
    }
    return 1;
}

int makeMove(int i, int j, SFTile& aTile, SFTile (&aBoard)[8][8], std::vector<SFLocation>& path){
    int kMax = 0;
    int m = -1, n = -1;
    if(aTile.getPiece().isKing() || aTile.getPiece().getColor() == PieceColor::red){
        if(i+1 < 8 && j-1 >= 0 && aBoard[i+1][j-1].isEmpty()){
            int k = calculateWeight(i+1, j-1, aTile);
            if(k > kMax){
                kMax = k;
                m = i+1;
                n = j-1;
            }
        }
        if(i+1 < 8 && j+1 < 8 && aBoard[i+1][j+1].isEmpty()){
            int k = calculateWeight(i+1, j+1, aTile);
            if(k > kMax){
                kMax = k;
                m = i+1;
                n = j+1;
            }
        }
    }
    if(aTile.getPiece().isKing() || aTile.getPiece().getColor() == PieceColor::black){
        if(i-1 < 8 && j-1 >= 0 && aBoard[i-1][j-1].isEmpty()){
            int k = calculateWeight(i-1, j-1, aTile);
            if(k > kMax){
                kMax = k;
                m = i-1;
                n = j-1;
            }
        }
        if(i-1 < 8 && j+1 < 8 && aBoard[i-1][j+1].isEmpty()){
            int k = calculateWeight(i-1, j+1, aTile);
            if(k > kMax){
                kMax = k;
                m = i-1;
                n = j+1;
            }
        }
    }
    if(kMax > 0)
        path.push_back(SFLocation(m,n));
    return kMax;
}

struct Movement{
    int weight;
    std::vector<SFLocation> path;
    bool isJump;
    Movement(int i, int j, SFTile& aTile, SFTile (&aBoard)[8][8]){
        if(couldJump(i, j, aTile, aBoard)){
            std::vector<SFLocation> temp;
            makeJump(i, j, aTile, aBoard, path, temp);
            isJump = true;
            weight = 10 + (int)path.size();
        }
        else{
            path.push_back(SFLocation(i,j));
            isJump = false;
            weight = makeMove(i, j, aTile, aBoard, path);
        }
    }
};

SFRealPlayer::SFRealPlayer(PieceColor color) : SFPlayer(color){};

void SFRealPlayer::takeTurn(SFGame &aGame){
        int maxWeight = 0;
        Movement *bestMovement = nullptr;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                SFTile theTile = aGame.getBoard().getTiles()[i][j];
                if(!theTile.isEmpty() && theTile.getPiece().getColor() == getColor()){
                    Movement *theMovement = new Movement(i, j, theTile, aGame.getBoard().getTiles());
                    if(theMovement->weight > maxWeight){
                        maxWeight = theMovement->weight;
                        bestMovement = theMovement;
                    }
                    else
                        delete theMovement;
                }
            }
        }
        if(bestMovement != nullptr){
            if(!bestMovement->isJump){
                aGame.move(this, bestMovement->path[0], bestMovement->path[1]);
            }
            else{
                if(bestMovement->path.size() == 2)
                    aGame.jump(this, bestMovement->path[0], bestMovement->path[1]);
                else if(bestMovement->path.size() == 3)
                    aGame.jump(this, bestMovement->path[0], bestMovement->path[1], bestMovement->path[2]);
                else if(bestMovement->path.size() == 4)
                    aGame.jump(this, bestMovement->path[0], bestMovement->path[1], bestMovement->path[2], bestMovement->path[3]);
                else if(bestMovement->path.size() == 5)
                    aGame.jump(this, bestMovement->path[0], bestMovement->path[1], bestMovement->path[2], bestMovement->path[3], bestMovement->path[4]);
            }
        }
        delete bestMovement;
    }

