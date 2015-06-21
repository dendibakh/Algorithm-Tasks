#include "Seam Carving.h"
#include <limits>

pixelsEnergy calcPixelsEnergy(const PicturePixels& pixels)
{
   pixelsEnergy pixEnergy(pixels.size(), std::vector<int>(pixels[0].size(), 0));
   int height = static_cast<int>(pixels.size());
   int width = static_cast<int>(pixels[0].size());
   for (int i = 0; i < height; ++i)
   {
      for (int j = 0; j < width; ++j)
      {
         if ((i == 0) || (i == height - 1) || (j == 0) || (j == width - 1))
         {
            pixEnergy[i][j] = 195075; // 255^2 + 255^2 + 255^2
         }
         else
         {
            int Rx = pixels[i][j+1][0] - pixels[i][j-1][0];
            int Gx = pixels[i][j+1][1] - pixels[i][j-1][1];
            int Bx = pixels[i][j+1][2] - pixels[i][j-1][2];

            int Ry = pixels[i+1][j][0] - pixels[i-1][j][0];
            int Gy = pixels[i+1][j][1] - pixels[i-1][j][1];
            int By = pixels[i+1][j][2] - pixels[i-1][j][2];

            pixEnergy[i][j] = Rx*Rx + Gx*Gx + Bx*Bx + Ry*Ry + Gy*Gy + By*By;
         }
      }
   }
   return pixEnergy;
}

SeamCarver::SeamCarver(const PicturePixels& pixels) : pixels(pixels), pixEnergy(calcPixelsEnergy(pixels))
{

}

int SeamCarver::getWidth()
{
   return static_cast<int>(pixEnergy[0].size());
}

int SeamCarver::getHeight()
{
   return static_cast<int>(pixEnergy.size());
}

int SeamCarver::getEnergy(int x, int y)
{
   return pixEnergy[y][x];
}

DijkstraSP::PathToStack SeamCarver::findHorizontalSeam()
{
   DijkstraSP::PathToStack seam;
   return seam;
}

DijkstraSP::PathToStack SeamCarver::findVerticalSeam()
{
   // build horizontal graph
   int height = getHeight();
   int width = getWidth();
   EWDiGraph graph(height * width + 2);
   for (int i = 0; i < height - 1; ++i)
   {
      for (int j = 0; j < width; ++j)
      {
         int curVertex = i * width + j;
         int belowVertex = (i + 1) * width + j;
         if (j > 0)
            graph.addEdge(Edge(curVertex, belowVertex - 1, pixEnergy[i][j]));
         graph.addEdge(Edge(curVertex, belowVertex, pixEnergy[i][j]));
         if (j < width - 1)
            graph.addEdge(Edge(curVertex, belowVertex + 1, pixEnergy[i][j]));
      }
   }
   // add source and target vertex to graph
   int source = height * width;
   int target = height * width + 1;
   int lastRowBeginIndex = (height - 1) * width;
   for (int i = 0; i < width; ++i)
   {
      graph.addEdge(Edge(source, i, 0));
      graph.addEdge(Edge(lastRowBeginIndex + i, target, 0));
   }
   
   // find seam with minimal energy
   DijkstraSP::PathToStack seam;
   DijkstraSP DSP(graph, source);
   if (!DSP.hasPathTo(target))
      return seam;
   seam = std::move(DSP.pathTo(target));
   seam.pop_front(); // remove target
   seam.pop_back();  // remove source
   return seam;
}

void SeamCarver::removeHorizontalSeam(const DijkstraSP::PathToStack& seam)
{

}

void SeamCarver::removeVerticalSeam(const DijkstraSP::PathToStack& seam)
{
   int height = getHeight();
   int width = getWidth();
   for (auto i = seam.begin(); i != seam.end(); ++i)
   {
      int toRemove = *i;
      int y = toRemove / width;
      int x = toRemove % width;
      pixels[y].erase((pixels[y].begin() + x));
      pixEnergy[y].erase((pixEnergy[y].begin() + x));
   }
}

PicturePixels SeamCarver::getPixels()
{
   return pixels;
}