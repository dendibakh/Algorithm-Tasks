#include "Maze.h"

using namespace std;

Maze::Maze(const std::string& FileName) : source(-1), destination(-1), dimension(0)
{
   ifstream file(FileName);
   if (file)
   {       
           try
           {
                   parseLabirint(file);
                   buildGraph();
                   findShortestPath();
                   checkExistPath();
                   findLongestPath();
           }
           catch (std::exception &e)
           {
                   error.assign(e.what());
           }
   }
   else
   {
           error.assign("no such file");
   }
   file.close();
}

void Maze::parseLabirint(ifstream& file)
{
        while (!file.eof())
        {
                string line;
                getline(file, line);

                if (!line.size())
                        continue;
                if (!dimension)
                        dimension = line.size();
                else if (dimension != line.size())
                        throw std::domain_error("maze is not quadratic");

                std::vector<bool> newRow(dimension);

                for (std::string::const_iterator cit = line.begin(); cit != line.end(); ++cit)
                {
                        size_t index = cit - line.begin();
                        switch (*cit)
                        {
                        case '8':
                                newRow[index] = WALL;
                                break;
                        case '.':
                                newRow[index] = PATH;
                                break;
                        case 'A':
                                newRow[index] = PATH;
                                source = calcVertexNumberByIndecies(maze.size(), index);
                                break;
                        case 'B':
                                newRow[index] = PATH;
                                destination = calcVertexNumberByIndecies(maze.size(), index);
                                break;
                        default:
                                throw std::domain_error("unexpected symbol");
                        }
                }
                maze.push_back(newRow);
                outSP.push_back(line);
                outLP.push_back(line);
        }
        if (dimension > maze.size())
                throw std::domain_error("maze is not quadratic");
        if (source == -1)
                throw std::domain_error("source A is missing");
        if (destination == -1)
                throw std::domain_error("destination B is missing");
}

void Maze::buildGraph()
{
        mazeGraph.reset(new Graph(dimension * dimension));
        for (unsigned int i = 0; i < dimension; ++i)
        {
                for (unsigned int j = 0; j < dimension; ++j)
                {
                        if (j > 0)
                                if ((maze[i][j] == PATH) && (maze[i][j - 1] == PATH))
                                        mazeGraph->addEdge(Edge(calcVertexNumberByIndecies(i, j - 1), calcVertexNumberByIndecies(i, j)));
                        if (i > 0)
                                if ((maze[i][j] == PATH) && (maze[i - 1][j] == PATH))
                                        mazeGraph->addEdge(Edge(calcVertexNumberByIndecies(i - 1, j), calcVertexNumberByIndecies(i, j)));
                }
        }
}

int Maze::calcVertexNumberByIndecies(int i, int j) const
{
        return i * dimension + j;
}

void Maze::findShortestPath()
{
        shortestPath.reset(new DijkstraSP(*mazeGraph, source));
}

void Maze::findLongestPath()
{
        longestPath.reset(new dfsLP(*mazeGraph, source, destination));
}

void Maze::checkExistPath()
{
   if (!shortestPath->hasPathTo(destination))
      error.assign("no path between source and destination");
}

void Maze::checkForError() const
{
        if (!correct())
                throw std::domain_error(error);
}

bool Maze::correct() const
{
        return error.empty();
}

std::string Maze::getError() const
{
        return error;
}

void Maze::printMazeToFile(const std::string& FileName) const
{
        checkForError();

        std::ofstream ofs(FileName, std::ofstream::out);
        
                if (ofs.is_open())
                {
                        highlightShortestTrackWithStars();
                        for (MazeOutput::iterator i = outSP.begin(); i != outSP.end(); ++i)
                        {
                                ofs << *i << std::endl;
                        }
                        ofs << std::endl;

                        highlightLongestTrackWithStars();
                        for (MazeOutput::iterator i = outLP.begin(); i != outLP.end(); ++i)
                        {
                                ofs << *i << std::endl;
                        }
                        ofs.close();
                }
                else
                        throw std::domain_error("Error opening file");
}

void Maze::highlightShortestTrackWithStars() const
{
        ShortestPathTrack vertecies = shortestPath->pathTo(destination);
        while (!vertecies.empty())
        {
                int curVertex = vertecies.top();
                if ((curVertex != source) && (curVertex != destination))
                {
                        int i_index = curVertex / dimension;
                        int j_index = curVertex % dimension;
                        outSP[i_index][j_index] = '*';
                }       
                vertecies.pop();
        }
}

void Maze::highlightLongestTrackWithStars() const
{
        LongestPathTrack vertecies = longestPath->getPath();
        while (!vertecies.empty())
        {
                int curVertex = vertecies.top();
                if ((curVertex != source) && (curVertex != destination))
                {
                        int i_index = curVertex / dimension;
                        int j_index = curVertex % dimension;
                        outLP[i_index][j_index] = '*';
                }
                vertecies.pop();
        }
}