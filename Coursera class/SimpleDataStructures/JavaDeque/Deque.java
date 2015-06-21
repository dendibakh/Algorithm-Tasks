import java.lang.Iterable;
import java.util.Iterator;
import java.lang.NullPointerException;

public class Deque<Item> implements Iterable<Item> 
{
    private class Node
    {
        Item value;
        Node next;
    }
    
    private Node head;
    private Node tail;
    private int m_size;
    
   public Deque()
   {
       Node head = null;
       Node tail = null;
       m_size = 0;
   }// construct an empty deque
   
   public boolean isEmpty()
   {
       return m_size == 0;
   }// is the deque empty?
   
   public int size()
   {
       return m_size;
   }// return the number of items on the deque
   
   public void addFirst(Item item)
   {
       if (item == null)
           throw new java.lang.NullPointerException();
       if (isEmpty())
       {
           head = new Node();
           tail = head;
           head.value = item;           
           tail.value = item;
       }
       else
       {
           Node newElem = new Node();
           newElem.value = item;
           newElem.next = head;
           head = newElem;
       }
       m_size++;
   }// insert the item at the front
   
   public void addLast(Item item)
   {
       if (item == null)
           throw new java.lang.NullPointerException();
       if (isEmpty())
       {
           head = new Node();
           tail = head;
           head.value = item;           
           tail.value = item;
       }
       else
       {
           Node newElem = new Node();
           newElem.value = item;
           tail.next = newElem;
           tail = newElem;
       }
       m_size++;
   }// insert the item at the end
   
   public Item removeFirst()
   {
       if (isEmpty())
          throw new java.util.NoSuchElementException();
       Item val = head.value;
       Node temp = head;
       head = head.next;
       temp.next = null;
       m_size--;
       return val;
   }// delete and return the item at the front
       
   public Item removeLast()
   {
       if (isEmpty())
          throw new java.util.NoSuchElementException();
       Item val = tail.value;
       Node iter = head;
       while(iter.next != tail)
       {
           iter = iter.next;
       }
       tail = iter;
       iter.next = null;
       m_size--;
       return val;
   }// delete and return the item at the end
   
   public void printOut()
   {
       StdOut.print("Size = " + size());
       StdOut.println();
       StdOut.print("Here is our Deque");
       StdOut.println();
       Node iter = head;
       while(iter != null)
       {
           StdOut.print(iter.value + " ");
           iter = iter.next;
       }
       StdOut.println();
       StdOut.print("head = " + head.value);
       StdOut.println();
       StdOut.print("tail = " + tail.value);
       StdOut.println();
       StdOut.println();
   }
   
   public Iterator<Item> iterator()
   {
       return new DequeIterator();
   }// return an iterator over items in order from front to end
   
   private class DequeIterator implements Iterator<Item>
   {
       private Node current;
       
       DequeIterator()
       {
           current = head;
       }
       
       public boolean hasNext()
       {
           return current != null;
       }
       
       public void remove()
       {
           throw new java.lang.UnsupportedOperationException();
       }
       
       public Item next()
       {
           if (current == null)
               throw new java.util.NoSuchElementException();
           Item item = current.value;
           current = current.next;
           return item;
       }
   }
}