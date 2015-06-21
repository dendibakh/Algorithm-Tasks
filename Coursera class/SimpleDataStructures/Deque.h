#pragma once

class Deque
{
   struct node
   {
      int value;
      node* next;
   };

public:
   Deque()
   {
      head = 0;
   }

   ~Deque()
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
         tail = new node;
         tail->value = val;
         tail->next = 0;
         head = tail;
      }
      else
      {
         node* temp = tail;
         tail = new node;
         tail->value = val;
         tail->next = 0;
         temp->next = tail;
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
   node* tail;
};