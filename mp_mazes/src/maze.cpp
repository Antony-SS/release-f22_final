/* Your code here! */

#include "maze.h"


using cs225::HSLAPixel;
using cs225::PNG;



// gets me point from 1d vector of 2d pt
int SquareMaze::conversion(int x, int y) const {
    return (x+(y*width_));
}

bool SquareMaze::canTravel (int x, int y, int dir) const {
    
    if(x < -1 || y < -1){
        return false;
    }
    bool isWall;
    switch (dir)
    {
    case 0:
        /* code */
        isWall = rside.at(conversion(x,y));
        return !isWall;
        break;
    case 1:
        isWall = base.at(conversion(x,y));
        return !isWall;
        break;

    case 2:

        if (x == 0) {
            return false;
        }

        isWall = rside.at(conversion(x-1, y));
        return !isWall;
        break;

    case 3:
        if (y == 0) {
            return false;
        }
        isWall = base.at(conversion(x, y - 1));
        return !isWall;
        break;

    default:
        std::cout << "Shouldn't ever reach here . . ." << std::endl;
        return true;
        break;
    }
}

PNG* SquareMaze::drawMaze()	const {
    
    PNG* toReturn = new PNG(width_ * 10 + 1, height_ * 10 + 1);

    // top wallz other than entrance
  for (int i = width_*10; i >= 0; --i) { // could change?
    if (i < 1 || i > 9) {
      HSLAPixel & pixref = toReturn->getPixel(i, 0);
      pixref.l = 0;
    }
  }

  // left wallz
  for (int i = height_* 10; i >= 0; --i) {
      HSLAPixel & pixref = toReturn->getPixel(0, i);
      pixref.l = 0;
  }


  for (int x = 0; x < width_; ++x) { 
    for (int y = 0; y < height_; ++y) {

        // base wallz
        if (base.at(conversion(x,y))) {
            for (int z = 0; z <= 10; ++z) {
            HSLAPixel & pixref = toReturn->getPixel(z+x*10, (y+1)*10);
            pixref.l = 0;
            }
        }

      // right wallz
      if (rside.at(conversion(x,y))) { // this might be wrong
        for (int z = 0; z <= 10; ++z) {
          HSLAPixel & pixref = toReturn->getPixel((x+1)*10, z+y*10);
          pixref.l = 0;
        }
      }
    }
  }
  return toReturn;
}


PNG* SquareMaze::drawMazeWithSolution () {

      // starting point for the path
    int x = 5;
    int y = 5;

    std::vector<int> solved = solveMaze();
    PNG* toReturn = drawMaze();


  for (auto& currentDirection : solved) {
    for (int i = 9; i >= 0; --i) {
      HSLAPixel & pixref = toReturn->getPixel(x, y);
      pixref.s = 1;
      pixref.h = 0;
      pixref.a = 1;
      pixref.l = 0.5;

      switch (currentDirection) {
        case 0:
            x++;
            break;
        case 1:
            y++;
            break;
        case 2:
            x--;
            break;
        case 3:
            y--;
            break;
        default:
            break;
      }
    }
  }

  HSLAPixel & pixel = toReturn->getPixel(x, y);
  pixel.h = 0;
  pixel.a = 1;
  pixel.l = 0.5;
  pixel.s = 1;

  // have to uncolor the exit now . . . 

  // path ends 4 to right of where we should start "erasing" and 5 up (b/c of maze wall width)

  int tmpx = x - 4;
  int tmpy = y + 5;

  for (int i = 8; i >= 0; --i) {
    HSLAPixel & pixref = toReturn->getPixel(tmpx + i, tmpy);
    pixref.l = 1;
  }

    return toReturn;
}

void SquareMaze::SquareMaze::makeMaze (int width, int height) {
    width_ = width;
    height_ = height;

    maze.clear();
    // Vectors manage their own memory so I don't have to manually delete anything


    // assuming perimeters are already in
    // _|_|_| will fill up the maze 

    for (int i = 0; i < width_ * height_; ++i) {
        rside.push_back(true); // true means that there is a wall
        base.push_back(true);
    } 

    // intialize all elements to neg 1
    maze.addelements(height_* width_);

    while(maze.size(0) != width_*height_) {
        
        int wall = rand() % 2; // esentially just a way to get a random booleans
        int x = rand() % width_;
        int y = rand() % height_;


        if (wall == 0) { // going to open a path down

            int convertedpt = conversion(x,y);
            int newpt = directionconverter(1, x, y);
            bool currentwall = base.at(convertedpt);

            if (y != height - 1 && currentwall && maze.find(convertedpt) != maze.find(newpt)) {  // check for not in same set (cycle), not in last row, and not already unwalled
                base[convertedpt] = false;
                maze.setunion(maze.find(convertedpt), maze.find(newpt)); // MIGHT HAVE TO SWAP THESE TWO
            }

        } else if (wall == 1) { // probably should be an else alone. going to open path right

            int convertedpt = conversion(x,y);
            int newpt = directionconverter(0, x, y);
            bool currentwall = rside.at(convertedpt);

            if (x != width - 1 && currentwall && maze.find(convertedpt) != maze.find(newpt) ) {
                rside[convertedpt] = false;
                maze.setunion(maze.find(convertedpt), maze.find(newpt)); // MIGHT HAVE TO SWAP THESE TWO
            }
        }
    }
}

// make this a switch statement

int SquareMaze::directionconverter(int dir, int x, int y) const {

    switch (dir)
    {
    case 0:
    // right 1
        return (x + 1) + (y * width_);
        break;
    case 1:
        // down 1
        return x + ((y + 1) * width_);
        break;
    case 2:
        // left 1
        return (x - 1) + (y * width_);
        break;
    case 3:
        // up 1
        return x + ((y - 1) * width_);
    default:
        std::cout << "SHOULD NEVER REACH HERE" << std::endl;
        return -100; //should never happen
        break;
    }

    
}

		

void SquareMaze::SquareMaze::setWall (int x, int y, int dir, bool exists) {
    if (dir == 0) {
        rside[conversion(x,y)] = exists;
    } else {
        base[conversion(x,y)] = exists;
    }
}	

std::vector <int> SquareMaze::SquareMaze::solveMaze () {

    std::vector<bool> seen;

    for(int i = 0; i < height_ * width_; ++i){
        seen.push_back(false);
    }
    
    std::queue<int> search;
    search.push(0);
    seen[0] = true;


    // int furthestNode = 0;
    int counter = width_;
    std::map<int, int> path;
    std::vector<int> toReverse;
    std::map<int, int> distances;

    distances[0] = 0;

    while(!search.empty()) {

        int tmp = search.front();

        seen[tmp] = true;

        int x = tmp % width_;
        int y = tmp / width_;

        search.pop();


        for(int i = 0; i < 4; ++i)
        {
            int newpt = directionconverter(i, x, y);
            if (canTravel(x, y, i) && !seen[newpt]) {
                distances[newpt] = distances[tmp] + 1; // updating distances
                search.push(newpt);
                path[newpt] = x + y*width_;
            }
        }
        
        if(height_ - 1 == y) {

            counter--;

            if(counter == 0){
                break;
            }
        }
    }

    // find longest length path to bottom of maze 
    int longestindex = -1;
    int finaldistance = -1;

    for (int i = conversion(0, height_ - 1); i < width_ * height_; ++i) {
        if (distances[i] > finaldistance) {
            longestindex = i;
            finaldistance = distances[i];
        }
    }

    while (longestindex != 0) {
        for (int i = 0; i < 4; i++) {
            if (longestindex == directionconverter(i, path[longestindex] % width_, path[longestindex] / width_)) {
                toReverse.push_back(i);
            }    
        }
        longestindex = path[longestindex];
    }

    std::vector<int> toReturn;

    for(int i = int(toReverse.size()) -1; i >= 0; --i){
        toReturn.push_back(toReverse[i]);
    }

    return toReturn;
}
