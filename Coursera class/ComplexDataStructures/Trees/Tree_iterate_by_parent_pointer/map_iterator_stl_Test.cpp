#include "TestHarness.h"
#include "Tree.h"

using namespace std; // std::

const double Eps = 0.0001;

TEST(map_iterator_stl, erase_HowToUse)
{
	typedef pair <int, int> Int_Pair;
	map <int, int> m;
	m.insert( Int_Pair(1, 1) );
	m.insert( Int_Pair(2, 3) );
	m.insert( Int_Pair(3, 3) );

	map <int, int>::iterator it = m.begin();

	//ok
	it = m.erase(it);

	//garbage
	m.erase(it);

	
	//*it;
	//++it;
	//it++;
	
}

TEST(map_iterator_stl, erase_iterators_interaction)
{
	typedef pair <int, int> Int_Pair;
	map <int, int> m;
	m.insert( Int_Pair(1, 1) );
	m.insert( Int_Pair(2, 3) );
	m.insert( Int_Pair(3, 3) );

	map <int, int>::iterator it1 = m.begin();
	map <int, int>::iterator it2 = m.begin();

	//it1 == ok; it2 == garbage
	it1 = m.erase(it1);
}

TEST(map_iterator_stl, iterators_lifetime)
{
	map <int, int>::iterator it;
	try
	{
		typedef pair <int, int> Int_Pair;
		map <int, int> m;
		m.insert( Int_Pair(1, 1) );
		m.insert( Int_Pair(2, 3) );
		m.insert( Int_Pair(3, 3) );

		it = m.begin();
		it = m.erase(it);
		it = m.erase(it);
		it = m.erase(it);

		/* just error
		it = m.erase(it);
		*it
		*/
	}
	catch(exception &e)
	{
		cout << e.what();
	}

	try
	{
		/* just error
		*it;
		*/
	}
	catch(exception &e)
	{
		cout << e.what();
	}
}