/* Your code here! */


#pragma once
#include "dsets.h"
#include "./lib/cs225/PNG.h"

using namespace cs225;


class SquareMaze {
    public:

    void makeMaze (int width, int height);

    bool canTravel (int x, int y, int dir) const;

    PNG* drawMaze()	const;

    PNG* drawMazeWithSolution ();

    void SquareMaze::makeMaze (int width, int height);		

    void SquareMaze::setWall (int x, int y, int dir, bool exists);	

    vector <int> SquareMaze::solveMaze ();







    private:
    DisjointSets maze;
    int height;
    int width;

};