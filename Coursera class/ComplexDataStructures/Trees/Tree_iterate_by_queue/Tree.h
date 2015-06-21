#pragma once
#include "complex.h"
#include <map>
#include <queue>

// Когда реализуешь итератор с помощью очереди, предлагаю попробовать реализовать через указатель на предка. Возможно понадобится еще что-то поменять в структуре.
// Плюс: не нужно синхронизироваться при операциях insert, remove. Минус: усложняется алгоритм обхода.
class Tree
{
	struct node
	{
		Complex data;
		node *left, *right;
	};
	void insert(node *&n, Complex c); 
	void clear(node *&n);
	node *&find (node *&n, const Complex &c) const;
	void remove(node *&n);
	bool comp(std::pair<Complex, node*> a, std::pair<Complex, node*> b);
	void print(node *n, std::stringstream &s) const;
	int height(node *n) const;
	void getTreeToMap(node *n, std::multimap <int, std::string> &t, int level) const;
	std::string setw(int level) const;
	std::string setc(int level) const;
	void operator++();
	Tree(const Tree& t);			//запрет копирования
	Tree operator = (const Tree &t); //запрет присваивания
public:
	class iterator
	{
	public:
		iterator();
		iterator(std::vector<std::pair<Complex, node*>>::iterator n);
		~iterator();
		Complex& operator*() const;
		iterator& operator++();
		iterator operator = (const iterator &it);
		bool operator==(const iterator& right) const;
		bool operator!=(const iterator& right) const;
	private:
		std::vector<std::pair<Complex, node*>>::iterator ptr;
	};
	Tree();
	~Tree();
	iterator begin();
	iterator end();
	std::vector<std::pair<Complex, node*>>::iterator getPosition(node *&n);
	void insert(const Complex &c);
	void clear();
	void print() const;
	bool find(const Complex &c);
	std::vector<std::pair<Complex, node*>>::iterator Tree::remove(const Complex &c);
	std::string toString() const;
	int height() const;
	int depth() const;
	void printLeftTraversal() const;
	std::multimap<int, std::string> getNumbers() const; 
private:
	node *root;
	std::vector<std::pair<Complex, node*>> VectNodes;
};