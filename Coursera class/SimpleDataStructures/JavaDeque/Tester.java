import java.util.Iterator;

public class Tester
{
    public Tester()
    {
        
        
    }
    public static void main(String[] args)
    {
        Integer msize = 0;
        boolean empt = true;
        Integer newItem = 5;
        Deque<Integer> myDeq = new Deque<Integer>();
        msize = myDeq.size();
        empt =  myDeq.isEmpty();
        myDeq.addLast(5);
        myDeq.addFirst(11);
        myDeq.addLast(7);
        myDeq.addLast(9);
        myDeq.addFirst(0);
        myDeq.printOut();
        
        myDeq.removeFirst();
        myDeq.removeLast();
        myDeq.removeLast();
        myDeq.removeFirst();
        myDeq.printOut();
        
        myDeq.addFirst(99);
        myDeq.addLast(100);
        myDeq.printOut();
        Iterator<Integer> myIter = myDeq.iterator();
        while (myIter.hasNext())
        {
            StdOut.print(" " + myIter.next());
        }
    }
}