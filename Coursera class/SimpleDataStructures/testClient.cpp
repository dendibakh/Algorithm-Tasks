#include "Stack.h"
#include "Deque.h"
#include "ArrayStack.h"
#include "ArrayDeque.h"
#include "DynArrayStack.h"
#include "DynArrayQueue.h"
#include <iostream>

using namespace std;

int main()
{
   DynArrayQueue st;
   /*
   st.push(5);
   std::cout << st.isEmpty() << std::endl;
   std::cout << st.pop() << std::endl;
   std::cout << st.isEmpty() << std::endl;
   st.push(7);
   st.push(8);
   st.push(9);
   std::cout << st.isEmpty() << std::endl;
   std::cout << st.pop() << std::endl; 
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl;
   std::cout << st.isEmpty() << std::endl;
   std::cout << st.pop() << std::endl;
   st.push(11);
   st.push(12);
   st.push(13);
   std::cout << st.isEmpty() << std::endl;
   std::cout << st.pop() << std::endl; 
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl;
   std::cout << st.isEmpty() << std::endl;
   std::cout << st.pop() << std::endl;
   */
   st.push(1);
   st.push(2);
   st.push(3);
   st.push(4);
   st.push(5);
   st.push(6);
   st.push(7);
   st.push(8);
   st.push(9);
   std::cout << st.max_size() << std::endl;
   st.push(10);
   std::cout << st.max_size() << std::endl;
   st.push(11);
   std::cout << st.max_size() << std::endl;
   st.push(12);
   std::cout << st.isEmpty() << std::endl;
   std::cout << st.pop() << std::endl; 
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl; 
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl; 
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl; 
   std::cout << st.pop() << std::endl;
   std::cout << st.pop() << std::endl;
   system("pause");
}