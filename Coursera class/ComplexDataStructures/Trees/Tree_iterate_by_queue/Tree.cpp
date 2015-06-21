#include "tree.h"
#include <sstream>



Tree::iterator::iterator(std::vector<std::pair<Complex, node*>>::iterator n)
{
	ptr=n;
}

Tree::iterator::~iterator(){}

Complex& Tree::iterator::operator*() const
{
	return ptr->first;
}

Tree::iterator& Tree::iterator::operator++()
{
	ptr++;
	return *this;
}

Tree::iterator Tree::iterator::operator = (const Tree::iterator &it)
{
	ptr=it.ptr;
	return *this;
}

bool Tree::iterator::operator==(const iterator &right) const
{
	return ptr == right.ptr;
}

bool Tree::iterator::operator!=(const iterator &right) const
{
	return !(*this == right);
}

Tree::iterator Tree::begin()
{
	return iterator(VectNodes.begin());
}

Tree::iterator Tree::end()
{
	return iterator(VectNodes.end());
}
//------------------------------------------------------------------------
std::vector<std::pair<Complex, Tree::node*>>::iterator Tree::getPosition(node *&n)
{
	std::vector<std::pair<Complex, node*>>::iterator it=
			std::lower_bound (VectNodes.begin(), VectNodes.end(), std::make_pair(n->data, n));
	return it;
}

void Tree::insert(node *&n, Complex c)
{
	if (n==NULL)
	{
		n=new node;
		n->data=c;
		n->left=NULL;
		n->right=NULL;
		std::vector<std::pair<Complex, node*>>::iterator it=getPosition(n);
		VectNodes.insert(it, std::make_pair(n->data, n));
	}
	else
	{
		if (c==n->data)
		{
			throw std::runtime_error("элемент уже есть");
		}
		else if (c < n->data)
		{
			insert(n->left, c);
		}
		else
		{
			insert(n->right, c);
		}
	}
}

void Tree::clear(node *&n)
{
	if (n!=NULL) 
	{
		clear(n->left);
		clear(n->right);
		delete n;
		n=NULL;
	}
}

Tree::node *&Tree::find(node *&n, const Complex &c) const
{
	if (n==NULL)
		return n;
	if (n->data==c)
		return n;
	if (n->data<c)
		return find(n->right, c);
	else
		return find(n->left, c);
}

void Tree::remove(node *&n)
{
	if (n==NULL)
	{
		throw std::runtime_error("элемент не найден­");
	}
	else if (!n->left || !n->right) 
	{
		node *save = n;
		n = (n->left) ? n->left : n->right;
		delete save;
	}
	else 
	{
		node **save = &n->right;
		while ((*save)->left) 
			save = &((*save)->left);
		n->data = (*save)->data;
		remove(*save);
	}
}


void Tree::print(node *n, std::stringstream &s) const
{
	if (n!=NULL) 
	{
		print(n->left, s);
		s << n->data.toString() << " ";
		print(n->right, s);
	}
}

int Tree::height(node *n) const
{
	if (n==NULL) 
		return 0;  
	int x = height(n->left);  
	int y = height(n->right);
	if (x > y) 
		return x+1;
	else       
		return y+1;
}

void Tree::getTreeToMap(node *n, std::multimap<int, std::string> &t, int level) const
{
	if (n!=NULL) 
	{
		getTreeToMap(n->left, t, level+1);
		t.insert(std::pair<int, std::string>(level, n->data.toString()));
		getTreeToMap(n->right, t, level+1);
	}
	else
		t.insert(std::pair<int, std::string>(level, "----"));
}

std::string Tree::setw(int level) const
{
	if (level==0)
		return "";
	int n=78;
	for (int i=1; i<level; i++)
		n=n/2;
	std::string s(n-4, ' ');
	return s;
}

std::string Tree::setc(int level) const
{
	int n=78;
	for (int i=0; i<level; i++)
		n=n/2;
	std::string s(n-4, ' ');
	return s;
}
//--------------------------------------------------------------
Tree::Tree():root(NULL){}

Tree::~Tree()
{
	clear(root);
}

void Tree::insert(const Complex &c)
{
	insert(root, c);
}

void Tree::clear()
{
	clear(root);
	VectNodes.clear();
}

void Tree::print() const
{
	std::stringstream s;
	print(root, s);
	std::cout << s.str();
}

bool Tree::find(const Complex &c)
{
	return (find(root, c)!=NULL);
}

std::vector<std::pair<Complex, Tree::node*>>::iterator Tree::remove(const Complex &c)
{  
	node *&p = find(root, c);
	std::vector<std::pair<Complex, Tree::node*>>::iterator it;
	if (p)
	{
		it=getPosition(p);
		it=VectNodes.erase(it);
	}
	remove(p);
	return it;
}

std::string Tree::toString() const
{
	std::stringstream s;
	print(root, s);
	return s.str();
}

int Tree::height() const
{
	return height(root);
}

int Tree::depth() const
{
	return height(root)-1;
}

void Tree::printLeftTraversal() const
{
	system("mode con cols=160 lines=65");
	system("cls");
	std::multimap<int, std::string> t;
	getTreeToMap(root, t, 0);
	std::multimap<int, std::string>::iterator it;
	for(int level=0; level < height(root); level++)
	{
		std::cout << setc(level); 
		for(it=t.begin(); it!=t.end(); it++)
			if (it->first==level)
				std::cout << it->second << setw(level); 
		std::cout << std::endl;
	}
}

std::multimap<int, std::string> Tree::getNumbers() const
{
	std::multimap<int, std::string> t;
	getTreeToMap(root, t, 0);
	return t;
}
// После того как исправишь все замечания...
// Давай сделаем функцию печати уровней дерева. Название для нее printLeftTraversal,
// Каждый новый уровень печатается с новой строки
// Например:
//       A
//     /   \
//    B     C
//   / \   / \
//  D   E F   G
// На первом этапе можно не печатать символы / и \. Отступы тоже можно не учитывать. Но если сделаешь - будет круто!
// Подумай, как можно протестировать данную функцию. 
