import java.util.*;
@SuppressWarnings("unchecked")
/*
THIS CODE WAS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING ANY
SOURCES OUTSIDE OF THOSE APPROVED BY THE INSTRUCTOR. Dorrie Hammond
*/

public class TreePQ<Key,Value> extends AbstractPriorityQueue<Key,Value> {
/* HeapClass/Compare -------------------------------------------------------------- */    
    // HeapTree class
    private HeapTree<Entry<Key,Value>> heap = new HeapTree<>();
    // Compare
    public TreePQ() { super(); }
    public TreePQ(Comparator<Key> comp) { super(comp); }
/* Inherited Methods ------------------------------------------------------ -- */
    // insert element into tree
    public Entry<Key,Value> insert(Key k, Value v) throws IllegalArgumentException {
        checkKey(k);
        Entry<Key,Value> newest = new PQEntry<>(k,v);
        boolean[] path = heap.nextEmpty(); // find path to next empty position
        Position position = heap.pathNew(path,newest); // find next empty position
        upheap(position); // initiate upheap with new insert
        return newest;
    }
    // find min of tree (aka root)
	public Entry<Key,Value> min() {
        Entry<Key,Value> min = heap.minFind();
        return min;
	}
    // remove Min (aka root)
	public Entry<Key,Value> removeMin() {
        if (size() == 0) { return null; } // in case heap is empty
        else if (size() == 1) { return heap.emptyPosition(heap.rootReturn()); } // if heap is only root
        else {
            Entry<Key,Value> min = min(); // Find root of heap
            boolean[] path = heap.leftMost(); // Find path to leftmost of heap
            Position position = heap.path(path); // Find leftmost of heap
            Position root = heap.findRoot();
            heap.swap(root,position);
            root = heap.findRoot();
            heap.emptyPosition(position); // finally, empty last position
            downheap(root); // initiate downheap process
            return min;
        }
	}
    // returns size of heap (int)
    public int size() {return heap.sizeHeap();}
/* Upheap/Downheap Comparisons ---------------------------------------------- */ 
    // Method that implements upheap
    protected void upheap(Position p) {
        // while node is internal
        while (heap.checkP(p)) {
            Position parent = heap.parentCheck(p);
            Entry<Key,Value> p1 = heap.element(p);
            Entry<Key,Value> p2 = heap.element(parent);
            // compare parent and child
            if (compare(p1,p2) >= 0) { break; }
            heap.swap(p,parent); // swap parent/child
            p = parent; // continue loop
        }
    }  

    // Method that implements downheap
    protected void downheap(Position p) {
        Entry<Key,Value> p1;
        Entry<Key,Value> p2;
        // while internal
        while(heap.hasLeft(p)) {
            Position left = heap.leftCheck(p);
            Position smallChild = left;
            if(heap.hasRight(p)) { // check which child is smaller
                Position right = heap.rightCheck(p);
                p1 = heap.element(left);
                p2 = heap.element(right);
                if(compare(p1,p2) > 0) {
                    smallChild = right;
                }
            }
            // check if smaller child is smaller than node
            p1 = heap.element(smallChild);
            p2 = heap.element(p);
            if (compare(p1, p2) >= 0) { break; }
            heap.swap(p,smallChild);
            p = smallChild; // continue loop with smaller child
        }
    }
}