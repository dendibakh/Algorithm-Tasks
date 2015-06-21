#pragma once
#include "utils.h"
#include "DijkstraSP.h"

typedef std::vector<std::vector<int>> pixelsEnergy;

pixelsEnergy calcPixelsEnergy(const PicturePixels& pixels);

class SeamCarver 
{
public:
   SeamCarver(const PicturePixels& pixels);
   int getWidth();                                                   // width  of current picture
   int getHeight();                                                  // height of current picture
   int getEnergy(int x, int y);                                      // energy of pixel at column x and row y in current picture
   DijkstraSP::PathToStack findHorizontalSeam();                     // sequence of indices for horizontal seam in current picture
   DijkstraSP::PathToStack findVerticalSeam();                       // sequence of indices for vertical   seam in current picture
   void removeHorizontalSeam(const DijkstraSP::PathToStack& seam);   // remove horizontal seam from current picture
   void removeVerticalSeam(const DijkstraSP::PathToStack& seam);     // remove vertical   seam from current picture
   PicturePixels getPixels();
private:
   PicturePixels pixels;
   pixelsEnergy pixEnergy;
};