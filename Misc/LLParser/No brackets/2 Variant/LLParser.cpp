#include "ComputationalTree.h"
#include "Operations.h"
#include <string>

int parse(const std::string &str) 
{
    ComputationalTree tree;

    for (std::string::const_iterator cit = str.begin(); cit != str.end(); ++cit) 
    {
        switch (*cit) 
        {
            /*case '(':
                push_level(program, 3);
                break;
            case ')':
                pop_level(program, 3);
                break;
                */
            case '*':
                tree.insert(new Operation(OPER_MULTI));
                break;
            case '/':
                tree.insert(new Operation(OPER_DIV));
                break;
            case '+':
                tree.insert(new Operation(OPER_PLUS));
                break;
            case '-':
                tree.insert(new Operation(OPER_MINUS));
                break;
            case ' ':
                break;
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                {
                    int curnum = 0;
                    while (cit != str.end()) 
                    {
                        curnum = 10 * curnum + (*cit - '0');
                        if ((cit + 1) == str.end() || !isdigit(*(cit+1))) {
                            break;
                        }
                        ++cit;
                    }
                    tree.insert(new Value(curnum));
                }
                break;
            default:
                throw std::domain_error("unexpected symbol");
        }
    }

    tree.printLeftTraversal();
    std::cout << "height is: " << tree.height() << std::endl;
    return tree.result();
}

int main()
{
   std::string line;
   std::getline(std::cin, line);
   if (line.length() > 0) 
   {
      try 
      {
         std::cout << "result is: " << parse(line) << std::endl;
         system("pause");
      } 
      catch (std::exception &e) 
      {
         std::cout << "error: " << e.what() << std::endl;
      }
   }
   // Время алгоритма линейное O(N).
   // Пример: 25*10+13-35/7*5*2+10
}