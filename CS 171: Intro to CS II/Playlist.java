/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN 
WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS. 
Dorrie Hammond */

public class Playlist {
   private Episode head;
   private int size;

   public Playlist(){
      head = null;
      size = 0;
   }

   public boolean isEmpty(){
     return head == null;
   }

   public int getSize(){
     return this.size;
   }

   public void displayPlaylistBackward(){
    String output = " [END]\n";
    Episode current = head;
    while( current.next != head ){
      output = " -> " + current + output;
      current = current.next;
    }
    output = "[BEGIN] " + current + output;
    System.out.println(output);
   }

   public void addFirst( String title, double duration ){
    if (isEmpty()) {
      Episode tempHead = head;
      head = new Episode(title, duration, tempHead, tempHead);
      size++;
    } else {
      Episode tempHead = head;
      head = new Episode(title, duration, tempHead.next, tempHead.prev);
      size++;
    }
   }

   public void addLast( String title, double duration ) {
    if (isEmpty()) {
      addFirst(title, duration);
    } else {
      head.prev = new Episode(title, duration, head, head.prev);
    }
   }

   public Episode deleteFirst() {
    if (isEmpty()) {
      throw new RuntimeException("Cannot delete episode!");
    } else {
      Episode temp = head;
      head = head.next;
      head.prev = temp.prev;
      size--;
      return head;
    }
   }

   public Episode deleteLast(){
    if (isEmpty()) {
      throw new RuntimeException("Cannot delete episode!");
    } else {
      Episode end = head.prev;
      Episode newEnd = end.prev;
      newEnd.next = head;
      head.prev = newEnd;
      size--;
      return end;
    }
   }

   public Episode deleteEpisode(String title){
    if (isEmpty()) {
      throw new RuntimeException("Cannot delete episode!");
    } else {
     Episode current = head;
     Episode prev;
     Episode next;
     while( current.next != head ) {
       if ( current.getTitle() == title ) {
         prev = current.prev;
         next = current.next;
         prev.next = next;
         next.prev = prev;
         size--;
         return current;
       }
       current = current.next;
     }
     return null;
    }
   }

   public Episode deleteEveryMthEpisode(int m) {
    if (isEmpty()) {
      throw new RuntimeException("Cannot delete episode!");
    } else {
      Episode current = head;
      Episode prev;
      Episode next;
      while ( current.next != current && size > 1 ) {
        for (int i = 0; i < (m-1); i++) {
          current = current.next;
        }
        prev = current.prev;
        next = current.next;
        prev.next = next;
        next.prev = prev;
        size--;
        current = current.next;
      }
      return current;
    }
   }

} // End of Playlist class













