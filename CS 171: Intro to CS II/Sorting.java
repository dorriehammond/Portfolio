/*
THIS CODE WAS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
CODE WRITTEN BY OTHER STUDENTS. Dorrie Hammond
*/

import java.text.DecimalFormat;
import java.util.Arrays;

public class Sorting {
	
	public static void BubbleSort(long[] a) {
		int size = a.length; // original length of array
		boolean unsorted;
		for (int i = 0; i < (size - 1); i++) {
			unsorted = false;
			for (int j = 0; j < (size - i - 1); j++) {
				if (a[j] > a[j+1]) {
					exch(a, j, j+1);
					unsorted = true;
				}
			}
			if (unsorted == false) { // if sorted, break
				break;
			}
		}
	}//BubbleSort()
	
	public static void MergeSortNonRec(long[] a) {
	long[] aux = new long[a.length];
	int size = a.length; // length of array

    	for (int i = 1; i < size; i*=2) { // determines size of passes, aka 1, 2, 4, etc.
    		for (int j = 0; j < size; j= j+(2*i)) {
    			int lo = j, mid = j+ i, hi = j+2*i; // calculate lo, mid, hi
            	
            	if (mid < a.length) { // make sure mid is not longer than length of array
            		if (hi > a.length) { // adjust hi to size if too large before merging
            			hi = size;
            		}
            		mergeNonRec(a, aux, lo, mid, hi); // merge Non recursively
            	}
        	}
    	}
   	}

	public static void mergeNonRec(long[] a, long[] aux, int lo, int mid, int hi) {
		// Non recursive version of merge
		// This merge is mainly the same as the Rec merge,
		// but minor changes to keep from going out of bounds (all changes explained below)

		// aux[] a[] merging
        int i = lo, j = mid; // mid not mid+1
        for (int k = lo; k < hi; k++) {
            if      (i == mid)     aux[k] = a[j++]; // if lo is = to mid (end of 1st half pass)
          	else if (j == hi)      aux[k] = a[i++]; // if mid is = to hi (end of 2nd half pass)
            else if (a[j] < a[i])  aux[k] = a[j++]; 
            else                   aux[k] = a[i++];
        }
       	
       	// copy to a[]
        for (int k = lo; k < hi; k++) {
            a[k] = aux[k];
        }
    }
	
	//-------------------------------------------------------------
	//---------- Below is an implementation of Selection Sort -----
	//-------------------------------------------------------------		
	public static void SelectionSort(long[] a) {
		int N = a.length;
	    for (int i = 0; i < N; i++) {
	    	int min = i;
	        for (int j = i+1; j < N; j++) {
	        	if (a[j] < a[min]) min = j;
	        }
	        exch(a, i, min);
	    }
	}//SelectionSort()
	
	
	//-----------------------------------------------------------------------
	//---------- Below is an implementation of Insertion Sort ----------
	//-----------------------------------------------------------------------
	public static void InsertionSort(long[] a) {
        int N = a.length;
        for (int i = 0; i < N; i++) {
            for (int j = i; j > 0 && a[j] < a[j-1]; j--) {
                exch(a, j, j-1);
            }
        }
	}//InsertionSort()

	//-----------------------------------------------------------------------
	//---------- Below is an implementation of recursive MergeSort ----------
	//-----------------------------------------------------------------------
	
    private static void merge(long[] a, long[] aux, int lo, int mid, int hi) {

        // copy to aux[]
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k]; 
        }

        // merge back to a[]
        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++) {
            if      (i > mid)           a[k] = aux[j++];
            else if (j > hi)            a[k] = aux[i++];
            else if (aux[j] < aux[i]) 	a[k] = aux[j++];
            else                        a[k] = aux[i++];
        }
    }

    
    // mergesort a[lo..hi] using auxiliary array aux[lo..hi]
    private static void sort(long[] a, long[] aux, int lo, int hi) {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid + 1, hi);
        merge(a, aux, lo, mid, hi);
    }

    public static void MergeSort(long[] a) {
        long[] aux = new long[a.length];
        sort(a, aux, 0, a.length-1);
    }
    
	//------------------------------------------------------
	//---------- below are several helper methods ----------
	//------------------------------------------------------
	
	// This tests whether your sorted result is correct by comparing it to reference result
	public static boolean testSort(long[] a) {
		long[] a2 = new long[a.length];
		System.arraycopy(a, 0, a2, 0, a.length);
		Arrays.sort(a);
		for(int i = 0; i < a.length; i++)
			if(a2[i] != a[i]) 
				return false;
		return true;
	}//testSort()
	
	
	// This creates an array with n randomly generated elements between (0, n*10]
	private static long[] randArray(int n) {
		long[] rand = new long[n];
		for(int i=0; i<n; i++)
			rand[i] = (int) (Math.random() * n * 10);
		return rand;
	}//randArray()
	
	private static void startTimer() { 
		timestamp = System.nanoTime();
	}//startTimer()
	
	private static double endTimer() {
		return (System.nanoTime() - timestamp)/1000000.0;
	}//endTimer()
	        
    // exchange a[i] and a[j]
    private static void exch(long[] a, int i, int j) {
        long swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
	
	private static long timestamp;
	
	//---------------------------------------------
	//---------- This is the main method ----------
	//---------------------------------------------		
	public static void main(String[] args) {
	
		// run experiments
		final int BUBBLE = 0, SELECT = 1, INSERT = 2, MERGEREC = 3, MERGENONREC = 4;
		int[] algorithms = {BUBBLE, SELECT, INSERT, MERGEREC, MERGENONREC};
		
		// max defines the maximum size of the array to be tested, which is 2^max
		// runs defines the number of rounds to be performed per test, in order to get an average running time.
		int max = 14, runs = 5;
		double[][] stats = new double[algorithms.length][max];
		for(int i=0; i<algorithms.length; i++) {             //loop through each sorting algorithm
			switch(i) {
				case BUBBLE: System.out.print("Running Bubble Sort ..."); break;
				case SELECT: System.out.print("Running Selection Sort ..."); break;
				case INSERT: System.out.print("Running Insertion Sort ..."); break;
				case MERGEREC: System.out.print("Running MergeSort Recursive ..."); break;
				case MERGENONREC: System.out.print("Running MergeSort Non Recursive ..."); break;
			}//switch
			for(int j=0; j<max; j++) {        //loop through each array size 
				double avg = 0;
				for(int k=0; k<runs; k++) {    // loop through each run
					long[] a = randArray((int) Math.pow(2, j+1));
					startTimer();
					switch(i) {
						case BUBBLE: BubbleSort(a); break;
						case SELECT: SelectionSort(a); break;
						case INSERT: InsertionSort(a); break;
						case MERGEREC: MergeSort(a); break;
						case MERGENONREC: MergeSortNonRec(a); break;
					}//switch
					avg += endTimer();
					if (testSort(a) == false)
						System.out.println("The sorting is INCORRECT!" + "(N=" + a.length + ", round=" + k + ").");
				}//for
				avg /= runs;
				stats[i][j] = avg;
			}//for
			System.out.println("done.");
		}//for
		
		DecimalFormat format = new DecimalFormat("0.0000");
		System.out.println();
		System.out.println("Average running time:");
		System.out.println("N\t Bubble Sort\t Selection Sort\t Insertion Sort\tMergeSortRec\tMergeSortNon");
		for(int i=0; i<stats[0].length; i++) {
			System.out.print((int) Math.pow(2, i+1) + "\t  ");
			for(int j=0; j<stats.length; j++) {
				System.out.print(format.format(stats[j][i]) + "\t  ");
			}//for
			System.out.println();
		}//for
	}//main()
	
}//end of class
