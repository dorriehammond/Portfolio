import java.util.Comparator;
import java.util.*;
import java.lang.Math;

/*
THIS CODE WAS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING ANY
SOURCES OUTSIDE OF THOSE APPROVED BY THE INSTRUCTOR. Dorrie Hammond
*/

public class HeapTree<E> extends LinkedBinaryTree<E> {

/* -------------------------------------------------------------- */
    // Checks validity of position
    protected boolean hasLeft(Position<E> p) {
        Node<E> node = validate(p);
        Node<E> left = node.getLeft();
        if (left == null) { return false; } 
        else { return true; }
    }
    protected boolean hasRight(Position<E> p) {
        Node<E> node = validate(p);
        Node<E> right = node.getRight();
        if (right == null) { return false; } 
        else { return true; }
    }
    protected boolean checkP(Position<E> p) {
        Node<E> node = validate(p);
        Node<E> parent = node.getParent();
        if (parent == null) { return false; }
        else { return true; }        
    }
/* -------------------------------------------------------------- */
    // returns position of parent/children & returns element of position
    protected Position<E> parentCheck(Position<E> p) {
        return parent(p);
    }
    protected Position<E> leftCheck(Position<E> p) {
        return left(p);
    }
    protected Position<E> rightCheck(Position<E> p) {
        return right(p);
    }
    protected E element(Position<E> p) {
        Node<E> node = validate(p);
        return node.getElement();
    }
/* -------------------------------------------------------------- */
    // Method that swaps the elements of two Positions
    protected void swap(Position<E> p1, Position<E> p2) {
        // temporary element variables
        Node<E> n1 = validate(p1); Node<E> n2 = validate(p2);
        E e1 = n1.getElement(); E e2 = n2.getElement();
        // swap element values
        n1.setElement(e2); n2.setElement(e1);
    }
/* -------------------------------------------------------------- */
   // Return Element of Min (Aka root)
    public E minFind() {
        if (size() == 0) return null;
        Node<E> root = validate(root());
        return root.getElement();
    }
    // Return calculated height of heap
    protected int height(int i) {
        double h = Math.log(i)/Math.log(2);
        return (int) h;
    }
    // Finds path to leftmost Position
    protected boolean[] leftMost() {
        int size = size();
        if (size == 0) { return null; }
        else if (size == 1) { return null; }
        else {
            int h = height(size);
            boolean[] map = new boolean[h];
                for (int i = h; i > 0; i--) {
                    if (size%2 == 0) {
                        size = size/2;
                        map[i-1] = false;
                    } else {
                        size = size/2;
                        map[i-1] = true;
                }
            }
            return map;
        }
    }
    // Finds Path to next empty position in heap
    protected boolean[] nextEmpty() {
        int size = size() + 1;
        if (size == 0) { return null; }
        else if (size == 1) { return null; }
        else {
            int h = height(size);
            boolean[] map = new boolean[h];
                for (int i = h; i > 0; i--) {
                    if (size%2 == 0) {
                        size = size/2;
                        map[i-1] = false;
                    } else {
                        size = size/2;
                        map[i-1] = true;
                }
            }
            return map;
        }        
    }
    // finds position of leftmost
    protected Position<E> path(boolean[] path) {
        int size = size();
        Position<E> position = null;
        if (size == 0) {}
        else if (size == 1) { position = root(); }
        else {
            position = root();
            int h = height(size);
            for (int i = h-1; i >= 0; i--) {
                if (path[i] == true) {
                    position = left(position);
                } else {
                    position = right(position);
                }
            }
        }
        return position;
    }
    // finds position of next empty position
    protected Position<E> pathNew(boolean[] path, E element) {
        int size = size() + 1;
        Position<E> position = null;
        if (size == 0) {}
        else if (size == 1) { addRoot(element); position = root(); }
        else {
            position = root();
            int h = height(size);
            for (int i = 0; i < h-1; i++) {
                if (path[i] == true) {
                    position = left(position);
                } else {
                    position = right(position);
                }
            }
            if (path[h-1] == true) {
                addLeft(position,element);
                position = left(position);
            } else {
                addRight(position,element);
                position = right(position);  
            }
        }
        return position;
    }
// Additional Helper Methods
    protected Position<E> findRoot() {
        return root();
    }
    protected E emptyPosition(Position<E> p) {
        return remove(p);
    }
    protected Position<E> rootReturn() {
        return root();
    }
    protected int sizeHeap() {
        return size();
    }
}