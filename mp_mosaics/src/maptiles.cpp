/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    // going  to use a map to to map the average color points back to the tile images

    // store the average color points in a vector that I will use to build the KD tree 
    MosaicCanvas *finalImage = new MosaicCanvas(theSource.getRows(), theSource.getColumns()); 

    std::map<Point<3>, TileImage*> myMap;
    vector<Point<3>> myVec;

    for(auto it = theTiles.begin(); it != theTiles.end(); ++it)
    {
        Point<3> toInsert = convertToXYZ((*it).getAverageColor());
        myMap[toInsert] = &*it;
        myVec.push_back(toInsert);
    }
    

    KDTree<3> tiles(myVec);


    for(int i = 0; i < finalImage->getRows(); ++i)
        for(int j = 0; j < finalImage->getColumns(); ++j) {
            Point<3> averageRegionColor = convertToXYZ(theSource.getRegionColor(i, j));
            finalImage->setTile(i, j, myMap[tiles.findNearestNeighbor(averageRegionColor)]);
        }

    return finalImage;
}

