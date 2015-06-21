#pragma once

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "DijkstraSP.h"
#include "dfsLP.h"

static const bool WALL = false;
static const bool PATH = true;

class Maze
{
   int calcVertexNumberByIndecies(int i, int j) const;
   void parseLabirint(std::ifstream& file);
   void buildGraph();
   void findShortestPath();
   void findLongestPath();
   void checkExistPath();

   void highlightShortestTrackWithStars() const;
   void highlightLongestTrackWithStars() const;

public:
   
   typedef std::vector<std::vector<bool>> MazeField;
   typedef std::vector<std::string> MazeOutput;
   typedef DijkstraSP::PathToStack ShortestPathTrack;
   typedef dfsLP::VertexStack LongestPathTrack;
   
   Maze(const std::string& FileName);
   Maze(const Maze& rhs) = delete;
   Maze& operator=(const Maze& rhs) = delete;

   bool correct() const;
   std::string getError() const;

   void printMazeToFile(const std::string& FileName) const;

protected: // to have ability to call them from test class
   void checkForError() const;   

protected: // to have ability to test those attributes
   int source;
   int destination;
   unsigned int dimension;
   std::string error;

   MazeField maze;
   
   std::unique_ptr<Graph> mazeGraph;
   std::unique_ptr<DijkstraSP> shortestPath;
   std::unique_ptr<dfsLP> longestPath;
   
   mutable MazeOutput outSP;
   mutable MazeOutput outLP;
};