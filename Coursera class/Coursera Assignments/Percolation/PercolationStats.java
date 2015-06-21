import java.util.Random;
import java.lang.IndexOutOfBoundsException;

public class PercolationStats 
{
   // perform T independent computational experiments on an N-by-N grid 
   public PercolationStats(int N, int T)    
   {
       n = N;
       t = T;
       if ((n <= 0) || (t <= 0))
          throw new java.lang.IllegalArgumentException();
       arr = new int[t];
       Random rand = new Random();
       int count = 0;
       for (int i = 0; i < t; i++)
       {
           Percolation perc = new Percolation(n);
           count = 0;
           while (!perc.percolates())
           {
              int row = 1 + rand.nextInt(n);
              int col = 1 + rand.nextInt(n);
              if (perc.isOpen(row, col))
                 continue;
              else count++;
              perc.open(row,col);
           }
           arr[i] = count;
       }
   }
   
   // sample mean of percolation threshold
   public double mean()
   {
       double sum = 0.0;
       for (int i = 0; i < t; i++)
       {
           //if ()
           //StdOut.println(arr[i]);
           sum += (double)arr[i]/(n*n);
       }    
       mean_value = (double)sum/(double)t;
       return mean_value;
   }

   // sample standard deviation of percolation threshold
   public double stddev()
   {
       double sum = 0.0;
       for (int i = 0; i < t; i++)
           sum += ((double)arr[i]/(n*n) - mean_value) * ((double)arr[i]/(n*n) - mean_value);
       dev = Math.sqrt((double)sum/(double)(t-1));
       return dev;
   }
   
   // returns lower bound of the 95% confidence interval
   public double confidenceLo()
   {
       if (mean_value == 0.0)
           mean();
       if (dev == 0.0)
           stddev();
       return (double)mean_value - (double)(1.96 * dev) / (double)Math.sqrt(t);
   }
   
   // returns upper bound of the 95% confidence interval
   public double confidenceHi()
   {
       if (mean_value == 0.0)
           mean();
       if (dev == 0.0)
           stddev();
       return (double)mean_value + (double)(1.96 * dev) / (double)Math.sqrt(t);
   }
   
   // test client, described below
   public static void main(String[] args)
   {
       int N = Integer.parseInt(args[0]);
       int T = Integer.parseInt(args[1]);
       PercolationStats stat = new PercolationStats(N, T);
       /*StdOut.print("mean                    = ");
       System.out.printf("%10.10f", stat.mean());
       StdOut.println();
       StdOut.print("stddev                  = ");
       System.out.printf("%10.10f", stat.stddev());
       StdOut.println();*/
       StdOut.print("95% confidence interval = ");
       System.out.printf("%10.10f", stat.confidenceLo());
       StdOut.print(" , ");
       System.out.printf("%10.10f", stat.confidenceHi());
   }
   private int arr[];
   private int n;
   private int t;
   private double mean_value;
   private double dev;
}