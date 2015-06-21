#include "util.h"
#include <fstream>
#include <boost/config/warning_disable.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

vector<synset> parseSynsets(const string& FileName)
{
	ifstream file;
	file.open (FileName);
	vector<synset> vect(linesCount);
	if (file)
	{
		while (!file.eof())
		{
			string line;
			getline(file, line);
			typedef tokenizer<boost::char_separator<char> > tokenizer;
			char_separator<char> sepComma(",");
			tokenizer tokens(line, sepComma);
			int i = 0;
			int id = 0;
			for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
			{
				if (0 == i)
				{
					id = lexical_cast<int>(*tok_iter);
				}
				else if (1 == i)
				{
					char_separator<char> sepSpace(" ");
					tokenizer tok(*tok_iter, sepSpace);
					for(tokenizer::iterator beg=tok.begin(); beg!=tok.end();++beg)
					{
						vect[id].synonym.insert(*beg);
					}
				}
				else
				{
					vect[id].gloss += *tok_iter;
				}
				++i;
			}
		}
	}
	file.close();
	return vect;
}

vector<hypernyms> parseHypernyms(const string& FileName)
{
	ifstream file;
	file.open (FileName);
	vector<hypernyms> vect(linesCount);
	if (file)
	{
		while (!file.eof())
		{
			string line;
			getline(file, line);
			tokenizer<> tokens(line);
			int i = 0;
			int synsetID = 0;
			for (tokenizer<>::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
			{
				if (0 == i)
				{
					synsetID = lexical_cast<int>(*tok_iter);
				}
				else 
				{
					vect[synsetID].insert(lexical_cast<int>(*tok_iter));
				}
				++i;
			}
		}
	}
	file.close();
	return vect;
}