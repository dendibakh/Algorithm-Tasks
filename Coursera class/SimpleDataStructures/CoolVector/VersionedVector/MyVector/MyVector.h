#pragma once
#include <stdexcept>
#include <memory>

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

public:
	
	  class iterator
	  {
		  void validateIterator()
		  {
			  if (!ptr)
				  throw std::runtime_error("Wrong iterator");
			  if (currentVersion < *actualVersionPtr)
				  throw std::runtime_error("Iterator is not more actual. You can't use it. Reinitialize it.");
		  }
		  iterator(T* ptr, const std::shared_ptr<int>& versionPtr) : ptr(ptr), actualVersionPtr(versionPtr), currentVersion(*versionPtr)
		  {}
	  public:
		  iterator() : ptr(nullptr)
		  {}
		  iterator(const iterator& rhs) : ptr(rhs.ptr), actualVersionPtr(rhs.actualVersionPtr), currentVersion(rhs.currentVersion)
		  {}
		  iterator& operator=(const iterator& rhs)
		  {
			  ptr = rhs.ptr;
			  actualVersionPtr = rhs.actualVersionPtr;
			  currentVersion = rhs.currentVersion;
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
		  bool expired()
		  {
			  return !ptr || currentVersion < *actualVersionPtr;
		  }
	  private:
		  T* ptr;
		  std::shared_ptr<int> actualVersionPtr;
		  int currentVersion;

		  friend class vector;
	  };
	  
private:

	  iterator last()
	  {
		  if (!arr)
			  return iterator();
		  return iterator(arr + count - 1, versionPtr);
	  }

	  void increaseVersion()
	  {
		  (*versionPtr)++;
	  }

public:

	  vector() : arr(nullptr), count(0), versionPtr(std::make_shared<int>(0))
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
		 increaseVersion();
      }

      T pop_back()
      {
		  checkForEmpty();
         T retval = arr[count - 1];
         deAllocateBackMemory();
		 increaseVersion();
         return retval;
      }

	  void push_front(const T& val)
      {
         allocateFrontMemory();
         arr[0] = val;
		 increaseVersion();
      }

      T pop_front()
      {
		  checkForEmpty();
         T retval = arr[0];
         deAllocateFrontMemory();
		 increaseVersion();
         return retval;
      }

	  T& operator [] (size_t index)
	  {
		  validateIndex(index);
		  return arr[index];
	  }

	  iterator begin()
	  {
		  return iterator(arr, versionPtr);
	  }

	  iterator end()
	  {
		  if (!arr)
			  return iterator();
		  return iterator(arr + count, versionPtr);
	  }

	  iterator insert(const iterator& it, const T& val)
	  {
		  increaseVersion(); 
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
			if (it == iterator(temp + j, versionPtr))
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
		return iterator(arr + insertedIndex, versionPtr);
	}
public:
	  iterator erase(const iterator& i)
	  {
		  checkForEmpty();
		  increaseVersion(); 
		  if (i == begin())
		  {
			  pop_front();
			  return begin();
		  }
		  if (i == last())
		  {
			  pop_back();
			  return iterator(arr + count, versionPtr);
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
			if (it == iterator(temp + i, versionPtr))
			{
				erasedIndex = i;	
				continue;
			}
			arr[j] = temp[i];
			++j;
		}
		delete[] temp;
		return iterator(arr + erasedIndex, versionPtr);
	}

private:
      size_t count;
      int *arr;
	  std::shared_ptr<int> versionPtr;
   };
}