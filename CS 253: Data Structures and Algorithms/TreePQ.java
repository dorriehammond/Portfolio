import java.util.Comparator;

@SuppressWarnings("unchecked")

/**
 * The TreePQ class builds a heap based priority queue, using HeapTree as its linked tree structure.
 * @param <K> Key
 * @param <V> Value
 */
public class TreePQ<K,V> extends AbstractPriorityQueue<K,V> {

    // HeapTree variable to store the (key, value) pairs as Entries
	private HeapTree<Entry<K,V>> heap;
    
    // Prints a string representation of the PQ
	@Override
	public String toString(){
		return heap.toString();
	}

    // Accessor method for the HeapTree
    public BinaryTree<Entry<K,V>> getTree(){
        return heap;
    }

    // Default Constructor
    public TreePQ(){
        super();
        heap = new HeapTree<>();
    }

    // Constructor with given Comparator
    public TreePQ(Comparator<K> comp) {
        super(comp); 
        heap = new HeapTree();
    }

    // Upheap pushes myNode up the heap until it is in the correct location relative to its parent
    protected void upheap(Position<Entry<K,V>> myNode){
        while(heap.parent(myNode) != null){
            Position<Entry<K,V>> parent = heap.parent(myNode);
            if(compare(myNode.getElement(), parent.getElement()) >= 0)
                break;
            heap.swap(myNode, parent);
            myNode = parent;
        }
    }
    
    // Downheap pushes myNode down the heap until it is in the correct location relative to its children
    protected void downheap(Position<Entry<K,V>> myNode){
        while(heap.left(myNode) != null){
            Position<Entry<K,V>> leftChild = heap.left(myNode);
            Position<Entry<K,V>> rightChild = heap.right(myNode);
            Position<Entry<K,V>> smallChild = heap.left(myNode);
            if(rightChild != null && compare(smallChild.getElement(), rightChild.getElement()) > 0)
            smallChild = rightChild;
            if(compare(smallChild.getElement(), myNode.getElement())>= 0)
            break;
            heap.swap(myNode, smallChild);
            myNode = smallChild;
        }
    }
    
    // Returns the size of the PQ
    public int size(){
        return heap.size();
    }

    // Returns the minimum key on the PQ
    public Entry<K,V> min() {
        if (heap.isEmpty()) return null;
        return heap.root().getElement();
    }

    // Inserts the given (key,value) pair onto the PQ
    public Entry<K,V> insert(K k, V v) throws IllegalArgumentException {
        checkKey(k);
        Entry<K,V> newest = new PQEntry<>(k,v);
        Position<Entry<K,V>> newPos=heap.add(newest);
        upheap(newPos);
        return newest;
    }

    // Removes the minimum key from the PQ
    public Entry<K,V> removeMin(){
        Entry<K,V> rootEntry = heap.removeRoot();
        if(!isEmpty())
            downheap(heap.root());
        return rootEntry;
    }
    
    
    
}