/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT 
CONSULTING CODE WRITTEN BY OTHER STUDENTS.
Dorrie Hammond */

import java.util.Stack;

public class NQueensPuzzle {

  //finds and prints out all solutions to the n-queens problem
  public static int solveNQueens(int n) {
    Stack<Integer> solution = new Stack<Integer>(); // solution stack
    int solutionNum = 0; // keeps track of # of solutions
    int position = 0; // keeps track of position of play

    while(true) { // only go while there are more solutions to find

      while (position < n) { // While loop to find validity / does not exceed n in stack
        
        if (!(isValid(solution, position))) { // if not valid
          position++; // go to next position
        } 

        else if (isValid(solution, position)) { // if valid
          solution.push(position); // push position into stack solution
          position = 0; // start over on next row
        }

      }

      if (solution.isEmpty()) { // if there are no more solutions to find
        break; // this stops the while loop immediately
      }

      if (solution.size() == n) { // is the solution finished?
        printSolution(solution); // print solution
        solutionNum++; // add to keep track of #
        solution.pop(); // pop solution to find the next possible solution (aka keep the loop going)
      }

      position = solution.pop() + 1; // continue loop in new position to find a new solution

    }

    return solutionNum; // return # of solutions
  }

  // this method tests the validity of a test position to continue with finding a solution
  public static boolean isValid (Stack<Integer> solution, int testPosition) {
    int size = solution.size();

    for (int i = 0; i < size; i++) { // search entire row
      if (testPosition == solution.get(i)) { // same column
        return false;

      } else if ((size - i) == (solution.get(i) - testPosition)) { // same minor
        return false;

      } else if ((size - i) == (testPosition - solution.get(i))) { // same major
        return false;
      }
    }
    return true;
  }


  //this method prints out a solution from the current stack
  //(you should not need to modify this method)
  private static void printSolution(Stack<Integer> s) {
    for (int i = 0; i < s.size(); i ++) {
      for (int j = 0; j < s.size(); j ++) {
        if (j == s.get(i))
          System.out.print("Q ");
        else
          System.out.print("* ");
      }//for
      System.out.println();
    }//for
    System.out.println();
  }//printSolution()

  // ----- the main method -----
  // (you shouldn't need to change this method)
  public static void main(String[] args) {

  int n = 8;

  // pass in parameter n from command line
  if (args.length == 1) {
    n = Integer.parseInt(args[0].trim());
    if (n < 1) {
      System.out.println("Incorrect parameter");
      System.exit(-1);
    }//if
  }//if

  int number = solveNQueens(n);
  System.out.println("There are " + number + " solutions to the " + n + "-queens problem.");
 }//main()

}
