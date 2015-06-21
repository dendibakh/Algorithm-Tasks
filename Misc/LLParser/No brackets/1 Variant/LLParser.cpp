#include "ComputationalTree.h"
#include "Operations.h"
#include <string>

std::list<NextExpr> parse(const std::string &str) 
{
    std::list<NextExpr> exprs;
    std::list<Expression*> tokens;

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
                tokens.push_back(new Operation(OPER_MULTI));
                break;
            case '/':
                tokens.push_back(new Operation(OPER_DIV));
                break;
            case '+':
                tokens.push_back(new Operation(OPER_PLUS));
                break;
            case '-':
                tokens.push_back(new Operation(OPER_MINUS));
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
                    tokens.push_back(new Value(curnum));
                }
                break;
            default:
                throw std::domain_error("unexpected symbol");
        }
    }

    std::list<Expression*>::const_iterator iter = tokens.begin();
    if ((*iter)->getType() == VALUE)
    {
       NextExpr expr;
       expr.operation = OPER_PLUS;
       expr.value = (*iter)->getValue();
       exprs.push_back(expr);
    }

    for (iter++; iter != tokens.end(); ++iter) 
    {
       NextExpr expr;
       if ((*iter)->getType() == SIGN)
          expr.operation = (*iter)->getValue();

       if (++iter == tokens.end())
       {
          break;
       }
       else if ((*iter)->getType() == VALUE)
       {
          expr.value = (*iter)->getValue();
       }
       exprs.push_back(expr);
    }

    for (std::list<Expression*>::iterator del_iter = tokens.begin(); del_iter != tokens.end(); ++del_iter)
    {
       delete *del_iter;
    }

    return exprs;
}

int main()
{
   std::string line;
   std::getline(std::cin, line);
   if (line.length() > 0) 
   {
      try 
      {
         std::list<NextExpr> exprs = parse(line);
         ComputationalTree tree(exprs);
         tree.printLeftTraversal();
         std::cout << "result is: " << tree.result() << std::endl;
         system("pause");
      } 
      catch (std::exception &e) 
      {
         std::cout << "error: " << e.what() << std::endl;
      }
   }
   
   /*
   NextExpr expr;
   expr.operation = OPER_PLUS;
   expr.value = 25;
   vect.push_back(expr);
   expr.operation = OPER_MULTI;
   expr.value = 10;
   vect.push_back(expr);
   expr.operation = OPER_PLUS;
   expr.value = 13;
   vect.push_back(expr);
   expr.operation = OPER_MINUS;
   expr.value = 15;
   vect.push_back(expr);
   expr.operation = OPER_DIV;
   expr.value = 7;
   vect.push_back(expr);
   */
}