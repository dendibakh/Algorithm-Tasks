#pragma once

class Stack
{
   struct node
   {
      int value;
      node* next;
   };

public:
   Stack()
   {
      head = 0;
   }

   ~Stack()
   {
      while (head)
      {
         pop();
      }
   }

   bool isEmpty()
   {
      return head == 0;
   }

   void push(int val)
   {
      if (isEmpty())
      {
         head = new node;
         head->value = val;
         head->next = 0;
      }
      else
      {
         node* temp = head;
         head = new node;
         head->value = val;
         head->next = temp;
      }
   }

   int pop()
   {
      int retval = 0;
      if (!isEmpty())
      {
         retval = head->value;
         node* temp = head->next;
         delete head;
         head = temp;
      }
      return retval;
   }

private:
   node* head;
};