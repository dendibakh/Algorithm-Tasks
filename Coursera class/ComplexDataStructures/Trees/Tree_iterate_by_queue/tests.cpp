#include "tree.h"
#include "TestHarness.h"

using namespace std;

TEST(Complex, reim)
{
	DOUBLES_EQUAL(1, Complex(1, -1).re(), 0.00001);
	DOUBLES_EQUAL(-1, Complex(-1, -1).re(), 0.00001);
	DOUBLES_EQUAL(-1, Complex(1, -1).im(), 0.00001);
	DOUBLES_EQUAL(-1, Complex(1, -1).im(), 0.00001);
}
TEST(Complex, summ)
{
	Complex sum=Complex(1, 2)+Complex(2, 2);
	DOUBLES_EQUAL(3, sum.re(), 0.00001);
	DOUBLES_EQUAL(4, sum.im(), 0.00001);
}
TEST(Complex, difference)
{
	Complex sum=Complex(1, 2)-Complex(2, 2);
	DOUBLES_EQUAL(-1, sum.re(), 0.00001);
	DOUBLES_EQUAL(0, sum.im(), 0.00001);
}
TEST(Complex, multiplication)
{
	Complex sum=Complex(1, 2)*Complex(2, 2);
	DOUBLES_EQUAL(-2, sum.re(), 0.00001);
	DOUBLES_EQUAL(6, sum.im(), 0.00001);
}
TEST(Complex, division)
{
	Complex sum=Complex(1, 2)/Complex(2, 2);
	DOUBLES_EQUAL(0.75, sum.re(), 0.00001);
	DOUBLES_EQUAL(0.25, sum.im(), 0.00001);
}
TEST(Complex, conjugate)
{
	Complex c=Complex(1, 2).conj();
	DOUBLES_EQUAL(1, c.re(), 0.00001);
	DOUBLES_EQUAL(-2, c.im(), 0.00001);
}
TEST(Complex, abs)
{
	DOUBLES_EQUAL(5, Complex(3, 4).abs(), 0.00001);
}

TEST(Complex, max)
{
	CHECK(Complex(2,1).abs() > Complex(1,1).abs());
	CHECK(Complex(2,3).abs() > Complex(1,2).abs());
	CHECK(!(Complex(2,3).abs() > Complex(4,2).abs()));
	CHECK(!(Complex(2,-1).abs() > Complex(4,2).abs()));
}

TEST(Complex, min)
{
	CHECK(Complex(1,1).abs() < Complex(2,1).abs());
	CHECK(Complex(1,1).abs() < Complex(1,3).abs());
	CHECK(!(Complex(5,1).abs() < Complex(2,3).abs()));
}

TEST(Complex, min_eq)//меньше или равно
{
	CHECK(Complex(1,1).abs() <= Complex(1,1).abs());
	CHECK(Complex(1,1).abs() <= Complex(1,3).abs());
	CHECK(!(Complex(2,5).abs() <= Complex(4,2).abs()));
}

TEST(Complex, max_eq)// //больше или равно
{
	CHECK(Complex(1,1).abs() >= Complex(1,1).abs());
	CHECK(Complex(1,3).abs() >= Complex(1,2).abs());
	CHECK(!(Complex(1,2).abs() >= Complex(1,3).abs()));
}
TEST(Complex, toString)
{
	CHECK_EQUAL("2-3i", Complex(2, -3).toString())
}

//-----------------тесты двоичного дерева------------------------

TEST(Tree, insert)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, 3));
	CHECK_EQUAL("1+2i 2+3i ", t.toString())
}
TEST(Tree, insert2)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, -4));
	CHECK_EQUAL("1+2i 2-4i ", t.toString())
}

TEST(Tree, clear)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, -4));
	t.clear();
	CHECK_EQUAL("", t.toString())
}

TEST(Tree, insertAfterClear)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, -4));
	t.clear();
	t.insert(Complex(1, 1));
	CHECK_EQUAL("1+1i ", t.toString())
}

TEST(Tree, remove)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, 4));
	t.remove(Complex(2, 4));
	CHECK_EQUAL("1+2i ", t.toString())
}

TEST(Tree, remove2)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, 4));
	t.remove(Complex(2, 4));
	t.insert(Complex(3, 4));
	CHECK_EQUAL("1+2i 3+4i ", t.toString())
}

TEST(Tree, remove3)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, 4));
	t.remove(Complex(2, 4));
	t.insert(Complex(3, 4));
	t.insert(Complex(-1, -1));
	CHECK_EQUAL("-1-1i 1+2i 3+4i ", t.toString())
}

TEST(Tree, remove4)
{
	Tree t;
	t.insert(Complex(1, 2));
	t.insert(Complex(2, 4));
	t.clear();
	t.insert(Complex(1, 1));
	t.insert(Complex(2, 2));
	t.remove(Complex(1, 1));
	t.insert(Complex(3, 3));
	t.insert(Complex(-1, -1));
	CHECK_EQUAL("-1-1i 2+2i 3+3i ", t.toString());
	t.clear();
	CHECK_EQUAL("", t.toString())
}

TEST(Tree, insert10)
{
	Tree t;
	for(int i=0; i<10; i++)
		t.insert(Complex(i, i));

	CHECK_EQUAL("0 1+1i 2+2i 3+3i 4+4i 5+5i 6+6i 7+7i 8+8i 9+9i ", t.toString());
	t.remove(Complex(9, 9));
	CHECK_EQUAL("0 1+1i 2+2i 3+3i 4+4i 5+5i 6+6i 7+7i 8+8i ", t.toString());
	t.remove(Complex(8, 8));
	CHECK_EQUAL("0 1+1i 2+2i 3+3i 4+4i 5+5i 6+6i 7+7i ", t.toString());
}

TEST(Tree, insertDel)
{
	Tree t;
	for(int i=0; i<10; i++)
		t.insert(Complex(i, i));
	t.remove(Complex(1, 1));
	CHECK_EQUAL("0 2+2i 3+3i 4+4i 5+5i 6+6i 7+7i 8+8i 9+9i ", t.toString());
}

TEST(Tree, insertDel2)
{
	Tree t;
	t.insert(Complex(4, 5));
	t.insert(Complex(7, 6));
	t.insert(Complex(-1, 0));
	t.insert(Complex(-3, 0));
	t.insert(Complex(4, 4));
	t.insert(Complex(6, 6));
	t.insert(Complex(7, 7));
	t.insert(Complex(0, 0));
	CHECK_EQUAL("0 -1 -3 4+4i 4+5i 6+6i 7+6i 7+7i ", t.toString());
	t.remove(Complex(4, 4));
	CHECK_EQUAL("0 -1 -3 4+5i 6+6i 7+6i 7+7i ", t.toString());
}

TEST(Tree, errorElementAlreadyExist)
{
	try
	{
		Tree t;
		t.insert(Complex(1, 2));
		t.insert(Complex(1, 2));
		FAIL("нет выброса исключения при попытке добавить уже существующий элемент");
	}
	catch(std::exception &)
	{}
}
TEST(Tree, height)
{
	Tree t;
	for(int i=0; i<10; i++)
		t.insert(Complex(i, i));
	CHECK_EQUAL(10, t.height());
}

TEST(Tree, height2)
{
	Tree t;
	t.insert(Complex(1, 1));
	t.insert(Complex(2, 3));
	t.insert(Complex(4, 5));
	CHECK_EQUAL(3, t.height());
}

TEST(Tree, depth)
{
	Tree t;
	for(int i=0; i<10; i++)
		t.insert(Complex(i, i));
	CHECK_EQUAL(9, t.depth());
}

TEST(Tree, errorElementNotFound)
{
	try
	{
		Tree t;
		t.insert(Complex(1, 2));
		t.insert(Complex(1, 3));
		t.remove(Complex(1, 4));
		FAIL("нет выброса исключения при попытке удалить несуществующий элемент");
	}
	catch(std::exception &)
	{}
}

TEST(Tree, output)
{
	Tree t;
	t.insert(Complex(3, 3));        
	t.insert(Complex(2, 10));
	t.insert(Complex(1, 0));
	t.insert(Complex(0, 0));
	t.insert(Complex(10, 10));
	t.insert(Complex(1, 1));
	t.insert(Complex(1, 10));
	t.insert(Complex(2, 2));
	t.insert(Complex(3, 4));
	t.insert(Complex(7, 10));
	std::multimap<int, std::string> m=t.getNumbers();
	std::multimap<int, std::string>::iterator it;
	it=m.begin();
	CHECK_EQUAL("3+3i", it->second);
	it++;
	CHECK_EQUAL(1, it->first);
	CHECK_EQUAL("1", it->second);
}

TEST(Tree, iterator)
{
	Tree t;
	t.insert(Complex(3, 3));        
	t.insert(Complex(2, 10));
	t.insert(Complex(1, 0));
	t.insert(Complex(0, 0));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("0", (*it).toString());
	it++;
	CHECK_EQUAL("1", (*it).toString());
	it++;
	CHECK_EQUAL("3+3i", (*it).toString());
	it++;
	CHECK_EQUAL("2+10i", (*it).toString());
}

TEST(Tree, iteratorEnd)
{
	Tree t;
	t.insert(Complex(1, 0));
	t.insert(Complex(0, 0));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("0", (*it).toString());
	it++;
	CHECK_EQUAL("1", (*it).toString());
	it++;
	CHECK(it==t.end());
}

TEST(Tree, TwoIterators)
{
	Tree t;
	t.insert(Complex(3, 3));        
	t.insert(Complex(2, 10));
	t.insert(Complex(1, 0));
	t.insert(Complex(0, 0));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("0", (*it).toString());
	it++;
	CHECK_EQUAL("1", (*it).toString());
	it++;
	CHECK_EQUAL("3+3i", (*it).toString());
	it++;
	CHECK_EQUAL("2+10i", (*it).toString());
	it++;
	CHECK(it==t.end());
	Tree::iterator it1=t.begin();
	Tree::iterator it2=t.begin();
	it1++;
	it2++;
	CHECK_EQUAL("1", (*it1).toString());
	CHECK_EQUAL("1", (*it2).toString());
	it2++;
	CHECK_EQUAL("1", (*it1).toString());
	CHECK_EQUAL("3+3i", (*it2).toString());
	it1++;
	it1++;
	CHECK_EQUAL("2+10i", (*it1).toString());
	CHECK_EQUAL("3+3i", (*it2).toString());
	it2++;
	CHECK(it==t.end());
}

TEST(Tree, iteratorPlus)
{
	Tree t;
	t.insert(Complex(1, 0));
	t.insert(Complex(0, 0));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("0", (*it).toString());
	it++;
	CHECK_EQUAL("1", (*it).toString());
	it++;
	CHECK(it==t.end());
}

TEST(Tree, iteratorDel)
{
	Tree t;
	t.insert(Complex(2, 0));
	t.insert(Complex(0, 0));
	t.insert(Complex(2, 2));
	t.insert(Complex(3, 3));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("0", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("2", (*it).toString());
	it++;
	CHECK_EQUAL("2+2i", (*it).toString());
}

TEST(Tree, iteratorDel2)
{
	Tree t;
	t.insert(Complex(5));
	t.insert(Complex(3));
	t.insert(Complex(2));
	t.insert(Complex(1));
	t.insert(Complex(4));
	t.insert(Complex(8));
	t.insert(Complex(7));
	t.insert(Complex(9));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("1", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("2", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("3", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("4", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("5", (*it).toString());
	it++;
	CHECK_EQUAL("7", (*it).toString());
}

TEST(Tree, iteratorDel3)
{
	Tree t;
	t.insert(Complex(5));
	t.insert(Complex(3));
	t.insert(Complex(2));
	t.insert(Complex(1));
	t.insert(Complex(4));
	t.insert(Complex(8));
	t.insert(Complex(7));
	t.insert(Complex(9));
	Tree::iterator it=t.begin();
	CHECK_EQUAL("1", (*it).toString());
	it++;
	CHECK_EQUAL("2", (*it).toString());
	it++;
	CHECK_EQUAL("3", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("4", (*it).toString());
	it++;
	CHECK_EQUAL("5", (*it).toString());
	it++;
	CHECK_EQUAL("7", (*it).toString());
	it=t.remove(*it);
	CHECK_EQUAL("1 2 4 5 8 9 ", t.toString()); //проверка правильности структуры после удаления
}