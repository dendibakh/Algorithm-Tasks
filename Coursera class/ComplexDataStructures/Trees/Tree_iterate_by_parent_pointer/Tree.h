#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <map>

// ToDo::
// 1) реализовать умные указатели.

namespace MyTree
{
	template <class T>
	class Tree
	{
	private:
		struct Elem
		{
			T Data;
			Elem *Left, *Right, *Parent;
		};

		void ValidateExistsRootElem() const
		{
			if ( !Root )
			{
				throw runtime_error("Дерево пусто");
			}
		}

		void ConstrCopyByPassing(const Elem *PointerToRightTree)
		{
			if ( PointerToRightTree )
			{
				Insert( PointerToRightTree->Data );

				ConstrCopyByPassing( PointerToRightTree->Left );
				ConstrCopyByPassing( PointerToRightTree->Right );
			}
		}

	public:
		Tree():
			Root(NULL)
		{
			ContainerIsValid = new bool;
			*ContainerIsValid = true;
		}

		Tree (const Tree &RightTree):
			Root(NULL)
		{
			ContainerIsValid = new bool;
			*ContainerIsValid = true;

			ConstrCopyByPassing(RightTree.Root);
		}

		~Tree()
		{
			Clear();
			*ContainerIsValid = false;
		}

		class Iterator
		{
		private:
			void ValidateIterator() const
			{
				if ( !(*It_ContainerIsValid) || !ElemOfIterator )
				{
					throw std::runtime_error("Недействительное состояние итератора");
				}
			}

		public:
			Iterator():
				ElemOfIterator(NULL),
				It_ContainerIsValid(NULL)
			{}

			//Begin()
			Iterator(Elem *Pointer, bool *TreeIsValid):
				ElemOfIterator(Pointer),
				It_ContainerIsValid(TreeIsValid)
			{}

			//Iterator(Iterator& Right) = default;
			//Iterator& operator = (Iterator& Right) = default;

			//Get_Data
			T& operator * () const
			{
				ValidateIterator();
				return ElemOfIterator->Data;
			}

			//Dereferencing
			T* operator -> () const
			{
				ValidateIterator();
				return &(ElemOfIterator->Data);
			}

			bool operator == (const Iterator &Right) const
			{
				return ElemOfIterator == Right.ElemOfIterator;
			}
			
			bool operator != (const Iterator &Right) const
			{
				return !(*this == Right);
			}

		private:
			Elem *GetRPointer()
			{
				Elem *Pointer = ElemOfIterator;
				if ( Pointer->Right )
				{
					Pointer = Pointer->Right;
					while ( Pointer->Left )
					{
						Pointer = Pointer->Left;
					}
					return Pointer;
				}
				while ( Pointer->Parent && Pointer != Pointer->Parent->Left )
				{
					Pointer = Pointer->Parent;
				}
				return Pointer->Parent;
			}
		public:
			//++It
			Iterator& operator ++ ()
			{
				ValidateIterator();

				ElemOfIterator = GetRPointer();
				return *this;
			}

			//It++
			Iterator operator ++ (int)
			{
				ValidateIterator();

				Tree<T>::Iterator It = *this;
				++(*this);
				return It;
			}

		private:
			Elem *ElemOfIterator;
			bool *It_ContainerIsValid;
		};

	private:
		Elem* GetPointerToMinElemOfTree(Elem* Pointer) const
		{
			return ( Pointer->Left ? GetPointerToMinElemOfTree(Pointer->Left) : Pointer );
		}

		Elem* GetPointerToMinElemOfTree() const
		{
			return (Root ? GetPointerToMinElemOfTree(Root) : NULL);
		}
	public:
		Iterator Begin() const
		{
			return Iterator(GetPointerToMinElemOfTree(), ContainerIsValid);
		}

		Iterator End() const
		{
			return Iterator(NULL, ContainerIsValid);
		}

		Iterator Erase(Iterator& It)
		{
			Erase(*(It++));
			return It;
		}

	public:
		bool IsEmpty() const
		{
			return Root == NULL;
		}

	public:
		Tree& operator = (const Tree &RightTree)
		{
			if (Root != RightTree.Root)
			{
				Clear();
				ConstrCopyByPassing(RightTree.Root);
			}
			return *this;
		}

	private:
		size_t Height(Elem *Pointer) const
		{
			return ( !Pointer ? 0 : std::max(Height(Pointer->Left), Height(Pointer->Right)) + 1 );
		}
	public:
		size_t Height() const
		{
			return Height(Root);
		}

	private:
		Elem *&Find(const T &Item, Elem *&Pointer) const
		{
			if ( !Pointer || Pointer->Data == Item )
			{
				return Pointer;
			}
			else if ( Pointer->Data > Item )
			{
				return Find(Item, Pointer->Left);
			}
			return Find(Item, Pointer->Right);
		}
	public:
		Iterator Find(const T &Item)
		{
			return Iterator(Find(Item, Root), ContainerIsValid);
		}

	private:
		void Erase(Elem *&Pointer)
		{
			if ( !Pointer )
			{
				throw std::runtime_error("Элемент отсутствует");
			}
			else if ( !Pointer->Left || !Pointer->Right )
			{
				Elem *PointerForErase = Pointer;
				Pointer = (Pointer->Left ? Pointer->Left : Pointer->Right);
				Root && Root->Parent ? Root->Parent = NULL : NULL;
				Pointer && PointerForErase->Parent ? Pointer->Parent = PointerForErase->Parent : NULL;
				delete PointerForErase;
			}
			else
			{
				Elem **PointerForErase = &(Pointer->Right);
				while ( (*PointerForErase)->Left )
				{
					PointerForErase = &( (*PointerForErase)->Left );
				}
				Pointer->Data = (*PointerForErase)->Data;
				Erase(*PointerForErase);
				PointerForErase = NULL;
			}
		}
	public:
		void Erase(const T &Item)
		{
			Erase( Find(Item, Root) );
		}

	private:
		void Clear(Elem *&Pointer)
		{
			if ( Pointer )
			{
				Clear(Pointer->Left);
				Clear(Pointer->Right);

				delete Pointer;
				Pointer = NULL;
			}
		}
	public:
		void Clear()
		{
			Clear(Root);
		}

	private:
		Elem* Insert(const T &Item, Elem *&PointerToParent, Elem *&Pointer)
		{
			if ( !Pointer )
			{
				Pointer = new Elem;
				Pointer->Data = Item;
				Pointer->Left = NULL;
				Pointer->Right = NULL;
				Pointer->Parent = (Pointer==Root ? NULL : PointerToParent);

				return Pointer;
			}
			else if ( Pointer->Data == Item )
			{
				throw std::runtime_error("Такой элемент уже присутствует");
			}
			else if (Pointer->Data < Item)
			{
				return Insert(Item, Pointer, Pointer->Right);
			}
			return Insert(Item, Pointer, Pointer->Left);
		}
	public:
		Iterator Insert(const T &Item)
		{
			return Iterator(Insert(Item, Root->Parent, Root), ContainerIsValid);
		}

	private:
		Elem *GetLE(const T &Item, Elem *ResultPointer, Elem *PointerForPassing) const
		{
			if ( !PointerForPassing )
			{
				return ResultPointer;
			}
			else if ( PointerForPassing->Data == Item )
			{
				return PointerForPassing;
			}
			else if ( PointerForPassing->Data < Item )
			{
				if ( ResultPointer == Root && ResultPointer->Data > Item || 
					Item - PointerForPassing->Data < Item - ResultPointer->Data )
				{
					ResultPointer = PointerForPassing;
				}
				return GetLE(Item, ResultPointer, PointerForPassing->Right);
			}
			return GetLE(Item, ResultPointer, PointerForPassing->Left);
		}
	public:
		T GetLE(const T &Item) const
		{
			Elem *LE_Elem = GetLE(Item, Root, Root);

			if ( !Root || LE_Elem == Root && Root->Data > Item )
			{
				throw std::runtime_error("Элемент отсутствует");
			}
			return LE_Elem->Data;
		}

	private:
		Elem *GetL(const T &Item, Elem *ResultPointer, Elem *PointerForPassing) const
		{
			if ( !PointerForPassing )
			{
				return ResultPointer;
			}
			else if ( PointerForPassing->Data < Item )
			{
				if ( ResultPointer == Root && ResultPointer->Data > Item || 
					Item - PointerForPassing->Data < Item - ResultPointer->Data )
				{
					ResultPointer = PointerForPassing;
				}
				return GetL(Item, ResultPointer, PointerForPassing->Right);
			}
			return GetL(Item, ResultPointer, PointerForPassing->Left);
		}
	public:
		T GetL(const T &Item) const
		{
			return GetL(Item, Root, Root)->Data;
		}

	private:
		T GetLE_OrRoot(const T &Item) const
		{
			return GetLE(Item, Root, Root)->Data;
		}

		T GetMaxElemOfTree() const
		{
			Elem *Pointer = Root;
			while ( Pointer->Right )
			{
				Pointer = Pointer->Right;
			}
			return Pointer->Data;
		}

		void Intersection(Tree &RightTree, Tree &ResultTree, T &Item, bool IsItLeft) const
		{
			T LE_Item = (IsItLeft ? RightTree.GetLE_OrRoot(Item) : GetLE_OrRoot(Item));
			IsItLeft = !IsItLeft;
			if ( LE_Item == Item )
			{
				ResultTree.Insert(Item);

				LE_Item = (IsItLeft ? RightTree.GetL(Item) : GetL(Item));
				IsItLeft = !IsItLeft;
			}

			if ( LE_Item != (IsItLeft ? Root->Data : RightTree.Root->Data) )
			{
				Intersection(RightTree, ResultTree, LE_Item, IsItLeft);
			}
			else
			{
				if ( LE_Item == (IsItLeft ? RightTree.GetLE_OrRoot(LE_Item) : GetLE_OrRoot(LE_Item)) )
				{
					ResultTree.Insert(LE_Item);
				}
			}
		}
	public:
		Tree Intersection(Tree &RightTree) const
		{
			Tree ResultTree;
			if ( !Root || !RightTree.Root )
			{
				return ResultTree;
			}

			T MaxElemOfLeftTree = GetMaxElemOfTree();
			T MaxElemOfRightTree = RightTree.GetMaxElemOfTree();
			if ( MaxElemOfLeftTree > MaxElemOfRightTree )
			{
				Intersection(RightTree, ResultTree, MaxElemOfLeftTree, true);
			}
			else
			{
				Intersection(RightTree, ResultTree, MaxElemOfRightTree, false);
			}

			return ResultTree;
		}

	private:
		void ToString(std::stringstream &TreeInString, Elem *Pointer) const
		{
			if ( Pointer )
			{
				ToString(TreeInString, Pointer->Left);

				TreeInString << Pointer->Data << " ";

				ToString(TreeInString, Pointer->Right);
			}
		}
	public:
		std::string ToString() const
		{
			std::stringstream TreeInString;
			ToString(TreeInString, Root);

			return TreeInString.str().substr(0, TreeInString.str().size() - 1);
		}

	private:
		typedef std::pair <size_t, T> T_Pair;
		typedef std::multimap <size_t, T> T_Map;
		typedef std::pair <typename T_Map::const_iterator, typename T_Map::const_iterator> Multimap_Pair;
		void LeftTraversal(size_t DepthOfRecursion, T_Map &MapOfTreeStrings, const Elem *Pointer) const
		{
			if ( Pointer )
			{
				MapOfTreeStrings.insert( T_Pair(DepthOfRecursion, Pointer->Data) );

				DepthOfRecursion++;
				LeftTraversal(DepthOfRecursion, MapOfTreeStrings, Pointer->Left);
				LeftTraversal(DepthOfRecursion, MapOfTreeStrings, Pointer->Right);
			}
		}

		std::string LeftTraversalInString(T_Map &MapOfTreeStages) const
		{
			std::stringstream LeftTraversalInString;
			for (size_t Stage = 0; Stage < Height(); ++Stage)
			{
				Multimap_Pair RangeOfStage = MapOfTreeStages.equal_range(Stage);
				for ( T_Map::const_iterator i = RangeOfStage.first; i != RangeOfStage.second; ++i )
				{
					LeftTraversalInString << i->second << " ";
				}
				LeftTraversalInString << std::endl;
			}

			return LeftTraversalInString.str();
		}
	public:
		std::string PrintLeftTraversalToString() const
		{
			T_Map MapOfTreeStrings;

			LeftTraversal(0, MapOfTreeStrings, Root);
			return LeftTraversalInString(MapOfTreeStrings);
		}

		void PrintLeftTraversal() const
		{
			cout << PrintLeftTraversalToString();
		}

	private:
		Elem *Root;
		bool *ContainerIsValid;
	};
};