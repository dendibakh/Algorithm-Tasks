import java.lang.IndexOutOfBoundsException;

public class Percolation {
   // create N-by-N grid, with all sites blocked
   public Percolation(int n)             
   {
       uf = new WeightedQuickUnionUF(n*n);
       N = n;
       arr = new int[N+1][N+1];
       for(int i = 1; i <= N; i++)
           for (int j = 1; j <= N; j++)
              arr[i][j] = 0;
   }
   
   // open site (row i, column j) if it is not already
   public void open(int i, int j)         
   {
       checkCorrectParams(i, j);
       int cur_ind = (i-1) * N + (j-1);
       if ( ((i-1) > 0) && isOpen(i-1,j))
          uf.union((i-1-1) * N + j-1, cur_ind);
       if (((j-1) > 0) && isOpen(i,j-1))
          uf.union((i-1) * N + j-1-1, cur_ind);
       if ((i < N) && isOpen(i+1,j))
          uf.union(i * N + j-1, cur_ind);
       if ((j < N) && isOpen(i,j+1))
          uf.union((i-1) * N + j, cur_ind);
       if (!isOpen(i,j))  
          arr[i][j] = 1;
   }
   
   // is site (row i, column j) open?
   public boolean isOpen(int i, int j)
   {
       checkCorrectParams(i, j);
       return 1 == arr[i][j];
   }
   
   // is site (row i, column j) full?
   public boolean isFull(int i, int j)
   {
       checkCorrectParams(i, j);
       //int rootEnd = uf.find((i-1) * N + j-1);
       for (int k = 1; k <= N; k++)
       {
           //int rootBegin = uf.find(k-1);
           //if ( rootBegin == rootEnd )
           if (isOpen(1, k) && uf.connected((i-1) * N + (j-1), k-1))
               return true;
       }
       return false;
   }
   
   // does the system percolate?
   public boolean percolates()  
   {
       for (int j = 1; j <= N; j++)
           if (isOpen(N, j) && isFull(N, j))
              return true;
       return false;
   }
   
   private int[][] arr;
   private int N;
   private WeightedQuickUnionUF uf;
   
   private void checkCorrectParams(int i, int j)
   {
       if ((i < 1) || (i > N) || (j < 1) || (j > N))
          throw new java.lang.IndexOutOfBoundsException("row index i out of bounds");
   }
   
}