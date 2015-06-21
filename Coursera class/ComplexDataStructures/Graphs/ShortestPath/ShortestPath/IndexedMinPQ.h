#pragma once
#include <vector>

template <class Key>
class IndexedMinPQ
{
	const int NMAX;		        // maximum number of elements on PQ
	int N;			            // number of elements on PQ
	std::vector<int> pq;        // binary heap using 1-based indexing
	std::vector<int> qp;        // inverse of pq - qp[pq[i]] = pq[qp[i]] = i
	std::vector<Key> keys;      // keys[i] = priority of i

public:
	IndexedMinPQ(int NMAX) : NMAX(NMAX), keys(NMAX + 1), pq(NMAX + 1), qp(NMAX + 1), N(0)
	{
		if (NMAX < 0) throw std::runtime_error("Invalid size");
		for (int i = 0; i <= NMAX; i++) 
			qp[i] = -1;
	}

	bool isEmpty() 
	{
		return N == 0;
	}

	
	bool contains(int i) 
	{
		if (i < 0 || i >= NMAX) 
			throw std::runtime_error("Invalid index");
		return qp[i] != -1;
	}

	int size() 
	{
		return N;
	}

	void insert(int i, Key key) 
	{
		if (i < 0 || i >= NMAX) 
			throw std::runtime_error("Invalid index");
		if (contains(i)) 
			throw std::runtime_error("Index is already in the priority queue");
		N++;
		qp[i] = N;
		pq[N] = i;
		keys[i] = key;
		swim(N);
	}

	int minIndex() 
	{
		if (N == 0) 
			throw std::runtime_error("Priority queue underflow");
		return pq[1];
	}

	Key minKey() 
	{
		if (N == 0) 
			throw std::runtime_error("Priority queue underflow");
		return keys[pq[1]];
	}

	int delMin() 
	{
		if (N == 0) 
			throw std::runtime_error("Priority queue underflow");
		int min = pq[1];
		exch(1, N--);
		sink(1);
		qp[min] = -1;            // delete
		//keys[pq[N + 1]] = null;    // to help with garbage collection
		pq[N + 1] = -1;            // not needed
		return min;
	}

	Key keyOf(int i) 
	{
		if (i < 0 || i >= NMAX) 
			throw std::runtime_error("Invalid index");
		if (!contains(i)) 
			throw std::runtime_error("Index is not in the priority queue");
		else return keys[i];
	}

	void changeKey(int i, Key key) 
	{
		if (i < 0 || i >= NMAX)
			throw std::runtime_error("Invalid index");
		if (!contains(i))
			throw std::runtime_error("Index is not in the priority queue");
		keys[i] = key;
		swim(qp[i]);
		sink(qp[i]);
	}

	void decreaseKey(int i, Key key) 
	{
		if (i < 0 || i >= NMAX)
			throw std::runtime_error("Invalid index");
		if (!contains(i))
			throw std::runtime_error("Index is not in the priority queue");
		if ((keys[i] < key) || (keys[i] == key))
			throw std::runtime_error("Calling decreaseKey() with given argument would not strictly decrease the key");
		keys[i] = key;
		swim(qp[i]);
	}

	void increaseKey(int i, Key key) 
	{
		if (i < 0 || i >= NMAX)
			throw std::runtime_error("Invalid index");
		if (!contains(i))
			throw std::runtime_error("Index is not in the priority queue");
		if ((keys[i] > key) || (keys[i] == key))
			throw std::runtime_error("Calling increaseKey() with given argument would not strictly increase the key");
		keys[i] = key;
		sink(qp[i]);
	}

	void deleteElem(int i) 
	{
		if (i < 0 || i >= NMAX)
			throw std::runtime_error("Invalid index");
		if (!contains(i))
			throw std::runtime_error("Index is not in the priority queue");
		int index = qp[i];
		exch(index, N--);
		swim(index);
		sink(index);
		keys[i] = null;
		qp[i] = -1;
	}
	
	/**************************************************************
	* General helper functions
	**************************************************************/
private:
	bool greater(int i, int j) 
	{
		return keys[pq[i]] > keys[pq[j]];
	}

	void exch(int i, int j) 
	{
		int swap = pq[i]; 
		pq[i] = pq[j]; 
		pq[j] = swap;
		qp[pq[i]] = i; 
		qp[pq[j]] = j;
	}

	/**************************************************************
	* Heap helper functions
	**************************************************************/
private:
	void swim(int k) 
	{
		while (k > 1 && greater(k / 2, k)) 
		{
			exch(k, k / 2);
			k = k / 2;
		}
	}

	void sink(int k) 
	{
		while (2 * k <= N) 
		{
			int j = 2 * k;
			if (j < N && greater(j, j + 1)) 
				j++;
			if (!greater(k, j)) 
				break;
			exch(k, j);
			k = j;
		}
	}
};