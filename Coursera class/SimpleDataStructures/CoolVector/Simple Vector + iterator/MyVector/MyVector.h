#pragma once
#include <stdexcept>

namespace MyVector
{
   template <class T>
   class vector
   {
      void allocateBackMemory()
      {
         T* temp = arr;
         ++count;
         arr = new T[count];
         for (size_t i = 0; i < count - 1; ++i)
            arr[i] = temp[i];
         delete[] temp;
      }

	  void allocateFrontMemory()
      {
         T* temp = arr;
         ++count;
         arr = new T[count];
         for (size_t i = 1; i < count; ++i)
            arr[i] = temp[i-1];
         delete[] temp;
      }

      void deAllocateBackMemory()
      {
         T* temp = arr;
         --count;
         arr = new T[count];
         for (size_t i = 0; i < count; ++i)
            arr[i] = temp[i];
         delete[] temp;
      }

	  void deAllocateFrontMemory()
      {
         T* temp = arr;
         --count;
         arr = new T[count];
         for (size_t i = 1; i < count + 1; ++i)
            arr[i-1] = temp[i];
         delete[] temp;
      }

	  void validateIndex(size_t index)
	  {
		 if (count <= index)
            throw std::runtime_error("Wrong index");
	  }

	  void checkForEmpty()
	  {
		  if (isEmpty())
			  throw std::runtime_error("Empty");
	  }

	  T* last()
	  {
		  if (!arr)
			  return nullptr;
		  return arr + count - 1;
	  }

   public:

	  class iterator
	  {
		  void validateIterator()
		  {
			  if (!ptr)
				 throw std::runtime_error("Wrong iterator");
		  }
	  public:
		  iterator() : ptr(nullptr)
		  {}
		  iterator(T* ptr) : ptr(ptr)
		  {}
		  iterator(const iterator& rhs) : ptr(rhs.ptr) 
		  {}
		  iterator& operator=(const iterator& rhs)
		  {
			  ptr = rhs.ptr;
			  return *this;
		  }
		  bool operator == (const iterator& rhs) const
		  {
			  return ptr == rhs.ptr;
		  }
		  bool operator != (const iterator& rhs) const
		  {
			  return !(ptr == rhs.ptr);
		  }
		  iterator& operator ++ ()
		  {
			  validateIterator();
			  ++ptr;
			  return *this;
		  }
		  iterator operator ++ (int)
		  {
			  validateIterator();
			  iterator retVal = *this;
			  ++ptr;
			  return retVal;
		  }
		  T& operator * () 
		  {
		  	  validateIterator();
		 	  return *ptr;
		  }
		  T operator * () const
		  {
		  	  validateIterator();
		 	  return *ptr;
		  }
		  T* operator -> () const
		  {
			  validateIterator();
			  return ptr;
		  }
		  T* operator -> ()
		  {
			  validateIterator();
			  return ptr;
		  }
	  private:
		  T* ptr;
	  };

      vector() : arr(nullptr), count(0)
      {
      }

      ~vector()
      {
         delete[] arr;
      }

      bool isEmpty()
      {
         return count == 0;
      }

	  int getCount()
	  {
		  return count;
	  }

      void push_back(const T& val)
      {
         allocateBackMemory();
         arr[count - 1] = val;
      }

      T pop_back()
      {
		  checkForEmpty();
         T retval = arr[count - 1];
         deAllocateBackMemory();
         return retval;
      }

	  void push_front(const T& val)
      {
         allocateFrontMemory();
         arr[0] = val;
      }

      T pop_front()
      {
		  checkForEmpty();
         T retval = arr[0];
         deAllocateFrontMemory();
         return retval;
      }

	  T& operator [] (size_t index)
	  {
		  validateIndex(index);
		  return arr[index];
	  }

	  T* begin()
	  {
		  return arr;
	  }

	  T* end()
	  {
		  if (!arr)
			  return nullptr;
		  return arr + count;
	  }

	  iterator insert(const iterator& it, const T& val)
	  {
		  if (it == begin())
		  {
			  push_front(val);
			  return begin();
		  }
		  if (it == end())
		  {
			  push_back(val);
			  return last();
		  }
		  return insertInBetween(it, val);
	  }

private:
	iterator insertInBetween(const iterator& it, const T& val)
	{
		T* temp = arr;
		++count;
		arr = new T[count];
		int insertedIndex = 0;
		for (size_t i = 0, j = 0; i < count - 1; ++j)
		{
			if (it == iterator(temp + j))
			{
				arr[j] = val;
				insertedIndex = j;
			}
			else
			{
				arr[j] = temp[i];
				++i;
			}
		}
		delete[] temp;
		return iterator(arr + insertedIndex);
	}
public:
	  iterator erase(const iterator& i)
	  {
		  checkForEmpty();
		  if (i == begin())
		  {
			  pop_front();
			  return begin();
		  }
		  if (i == last())
		  {
			  pop_back();
			  return iterator(arr + count);
		  }
		  return eraseFromBetween(i);
	  }

private:
	iterator eraseFromBetween(const iterator& it)
	{
		T* temp = arr;
		--count;
		arr = new T[count];
		int erasedIndex = 0;
		for (size_t i = 0, j = 0; i < count + 1; ++i)
		{
			if (it == iterator(temp + i))
			{
				erasedIndex = i;	
				continue;
			}
			arr[j] = temp[i];
			++j;
		}
		delete[] temp;
		return iterator(arr + erasedIndex);
	}

private:
      size_t count;
      int *arr;
   };
}