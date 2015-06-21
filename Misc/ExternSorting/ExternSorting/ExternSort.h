#include <fstream>
#include <vector>
#include <limits>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

static const char sourceFileName[] = "C:\\Users\\Dendi\\Documents\\Visual Studio 2013\\Projects\\ExternSorting\\Debug\\source.bin";
static const char resultFileName[] = "C:\\Users\\Dendi\\Documents\\Visual Studio 2013\\Projects\\ExternSorting\\Debug\\result.bin";
static const char pathToFiles[] = "C:\\Users\\Dendi\\Documents\\Visual Studio 2013\\Projects\\ExternSorting\\Debug\\";
static const char extension[] = ".bin";

static const int M = 1000;
static const int N = 100;
static const int length = N * sizeof(int);
static const int piecesAmount = M / N;
static const int pieceslength = piecesAmount * sizeof(int);

boost::random::mt19937 gen;
boost::random::uniform_int_distribution<> dist(1, 1000);

void fillFile()
{
        std::ofstream ofs(sourceFileName, std::ofstream::out | std::ofstream::binary);

        if (ofs.is_open())
        {
                std::vector<int> arr(M);
                for (size_t i = 0; i < M; ++i)
                {
                        arr[i] = dist(gen);
                }
                ofs.write((char*)arr.data(), sizeof(int) * M);
                ofs.close();
        }
        else
                throw std::domain_error("Error opening file");
}

void splitFileToPieces(int pieceNumber)
{
        std::ifstream is(sourceFileName, std::ifstream::binary);
        if (is)
        {
                char * buffer = new char[length];
                is.read(buffer, length);
                if (!is)
                        throw std::runtime_error("Error while reading");
                is.close();

                int* arr = (int*)buffer;
                std::vector<int> v(arr, arr + N);

                std::string pieceFileName = pathToFiles + boost::lexical_cast<std::string>(pieceNumber) + extension;
                std::ofstream ofs(pieceFileName, std::ofstream::out);

                if (ofs.is_open())
                {
                        std::sort(v.begin(), v.end());
                        ofs.write((char*)v.data(), sizeof(int)* N);
                        ofs.close();
                }
                else
                        throw std::domain_error("Error opening file");

                delete[] buffer;
        }
}

void ExternSort()
{
        for (size_t i = 1; i <= piecesAmount; ++i)
        {
                splitFileToPieces(i);
        }
}

void mergePeicesToResultFile(int pieceNumber)
{
        std::vector<int> res;
                
        for (size_t i = 1; i <= piecesAmount; ++i)
        {
                std::string pieceFileName = pathToFiles + boost::lexical_cast<std::string>(i)+extension;
                std::ifstream pieceFile(pieceFileName, std::ifstream::binary);
                
                char * buffer = new char[pieceslength];
                pieceFile.seekg(pieceNumber * pieceslength, 0);
                pieceFile.read(buffer, pieceslength);
                pieceFile.close();
                int* arr = (int*)buffer;
                std::copy(arr, arr + piecesAmount, back_inserter(res));
                delete[] buffer;
        }

        std::sort(res.begin(), res.end());

        std::ofstream ofs(resultFileName, std::ofstream::app);
        ofs.write((char*)res.data(), sizeof(int)* N);
        ofs.close();
}

void generateResult()
{
        {
                std::ofstream ofs(resultFileName, std::ofstream::out); 
        }
        for (size_t i = 0; i < piecesAmount; ++i)
        {
                mergePeicesToResultFile(i);
        }
}