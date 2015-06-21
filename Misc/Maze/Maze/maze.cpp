#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "Maze.h"

using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
   if (argc == 2)
   {
          path p (argv[1]);

          if (!exists(p))
          {
                  cout << "can't find file " << p << endl;
                  return 1;
          }

          if (!is_regular_file(p))
          {
                  cout << p << "is not a regular file." << endl;
                  return 1;
          }
          
		          string fileName = p.string();
                  Maze maze(fileName);
                  if (maze.correct())
                  {
                          string ext = p.extension().string();
                          string outName;
						  if (!p.parent_path().empty())
							  outName += p.parent_path().string() + "\\";
						  outName += p.stem().string() + "Out" + ext;
                          try
                          {
                                  maze.printMazeToFile(outName);
                          }
                          catch (std::exception& e)
                          {
                                  cout << e.what() << endl;
                          }
                  }
                  else
                  {
                          cout << maze.getError() << endl;
                  }

              return 0;
   }

   else
   {
      cout << "Usage: Maze.exe <target file>" << endl;
      return 1;
   }
   return 0;
}