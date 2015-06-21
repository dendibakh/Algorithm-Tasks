import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> 
{
   public RandomizedQueue()
   {
       // construct an empty randomized queue
   }

   public boolean isEmpty()           
   {
       return false;// is the queue empty?
   }
   
   public int size()
   {
       return 0;
       // return the number of items on the queue
   }
   
   public void enqueue(Item item)
   {
       
       // add the item
   }
   
   public Item dequeue()
   {
       return null;
       // delete and return a random item
   }
   
   public Item sample()
   {
       return null;
       // return (but do not delete) a random item
   }
   
   public Iterator<Item> iterator()
   {
       return null;
       // return an independent iterator over items in random order
   }
}