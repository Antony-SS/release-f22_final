/* Your code here! */


#pragma once
#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>
#include <queue>
#include <iostream>
#include <map>

using cs225::PNG;

class SquareMaze {
    public:

    bool canTravel (int x, int y, int dir) const;

    PNG* drawMaze()	const;

    PNG* drawMazeWithSolution ();

    void makeMaze (int width, int height);		

    void setWall (int x, int y, int dir, bool exists);	

    std::vector<int> solveMaze ();

    int conversion(int x, int y) const;

    int directionconverter(int dir, int x, int y) const;


    private:

    // Not sure if I am even going to need the set . . . . Could use easily for cycle detection . . .  . 
    DisjointSets maze;

    int height_;
    int width_;

    // going to use 2 vectors to represent my maze, will hold all the information about where walls stand . . . 
    std::vector<bool> base;
    std::vector<bool> rside;
};